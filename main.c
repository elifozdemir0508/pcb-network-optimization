#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "io_adapter.h"
#include "kruskal.h" 
#include "Connectedness.h"

#define INPUT_FILE "ui/shared_data/input_graph.json"
#define OUTPUT_FILE "ui/shared_data/output_mst.json"
#define FLAG_FILE "ui/shared_data/calculate.flag"

/**
 * @brief Sürekli çalışarak UI ile C backend arasındaki iletişimi dinler ve tetiklendiğinde MST hesaplar.
 * * @retval 0: Program başarılı bir şekilde sonlandığında döndürülür.
 * * @author: Cafer Tura Çetin
 */
int main() {
    // printf çıktırlarını okumak için
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Sistem baslatildi. Arayuzden hesaplama komutu bekleniyor...\n");

    while(1) {
        
        FILE *cal_flag = fopen(FLAG_FILE, "r");

        if (cal_flag != NULL) {
            // Flag dosyasını okuduk, işimiz bitti kapatıyoruz
            fclose(cal_flag); 
            
            // İŞLEM BİTİNCE FLAG DOSYASINI SİL
            if (remove(FLAG_FILE) != 0) {
                printf("UYARI: Flag dosyasi silinemedi.\n");
            }

            // ---------------------------------------------------------
            // 1. JSON VERİSİNİ OKUMA VE GRAFI OLUŞTURMA
            // ---------------------------------------------------------
            FILE *input_json = fopen(INPUT_FILE, "rb");
            if (input_json == NULL) {
                printf("HATA: Json Dosyasi bulunamadi.\n");
                continue; 
            }
            
            if (fseek(input_json, 0, SEEK_END) != 0) {
                fclose(input_json); continue;
            }
            long input_json_size = ftell(input_json);
            if (input_json_size <= 0) {
                fclose(input_json); continue;
            }
            rewind(input_json);

            char *input_json_string = (char*)malloc(input_json_size + 1);
            if (input_json_string == NULL) {
                fclose(input_json); continue; 
            }

            size_t read_size = fread(input_json_string, 1, input_json_size, input_json);
            input_json_string[read_size] = '\0';
            fclose(input_json);

            Graph *input_graph = (Graph*)malloc(sizeof(Graph)); 
            if (input_graph == NULL) {
                free(input_json_string); continue;
            }

            int succes = json_to_graph(input_json_string, input_graph);
            free(input_json_string); 

            if (succes != 0) {
                printf("HATA: Giris Json verisi cozumlenirken hata olustu. Kod: %d\n", succes);
                free(input_graph); 
                continue;
            }

            // ---------------------------------------------------------
            // FAZ 1: KRUSKAL'DAN ÖNCE DFS BAĞLANTI KONTROLÜ
            // ---------------------------------------------------------
            printf("\n[SISTEM] Faz 1: Anakart baglanti testi baslatiliyor...\n");
            int pcb_baglantili_mi = CheckConnectedness(input_graph);
            
            if (pcb_baglantili_mi == 0) {
                // Arayüzün haberi olması için sahte/boş bir output oluşturulabilir veya 
                // ayrı bir error.json basılabilir.
                printf("ISLEM IPTAL EDILDI: Devrede kopukluk var, optimizasyon yapilamaz.\n");
                free(input_graph);
                continue; 
            }

            // ---------------------------------------------------------
            // FAZ 2: KRUSKAL ALGORİTMASI VE OPTİMİZASYON
            // ---------------------------------------------------------
            printf("[SISTEM] Optimizasyon (Kruskal) baslatiliyor...\n");
            MSTResult mst_output = kruskal_mst(input_graph);
            
           

            // ---------------------------------------------------------
            // 3. ÇIKTIYI (MST) JSON OLARAK YAZMA
            // ---------------------------------------------------------
            char *output_mst_string = mstresult_to_json(&mst_output);
            if (output_mst_string == NULL) {
                printf("HATA: MST sonucu JSON'a donusturulemedi.\n");
                free(input_graph);
                continue;
            }

            FILE *output_mst = fopen(OUTPUT_FILE, "w");
            if (output_mst == NULL) {
                printf("HATA: Cikti json dosyasi olusturulamadi.\n");
            } else {
                if (fputs(output_mst_string, output_mst) == EOF) {
                    printf("HATA: Cikti json dosyasina yazilamadi.\n");
                } else {
                    printf("[SISTEM] BASARILI: MST hesaplandi ve arayuz icin '%s' dosyasina yazildi.\n", OUTPUT_FILE);
                }
                fclose(output_mst);
            }

            // Bellek temizliği
            free(output_mst_string);
            free(input_graph); 
            
            printf("\nYeni islem bekleniyor...\n");
        }

        sleep(1);
    }

    return 0;
}