#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "io_adapter.h"
#include "kruskal.h" 

#define INPUT_FILE "ui/shared_data/input_graph.json"
#define OUTPUT_FILE "ui/shared_data/output_mst.json"
#define FLAG_FILE "ui/shared_data/calculate.flag"

/**
 * @brief Sürekli çalışarak UI ile C backend arasındaki iletişimi dinler ve tetiklendiğinde MST hesaplar.
 * 
 * @retval 0: Program başarılı bir şekilde sonlandığında döndürülür.
 * 
 * @author: Cafer Tura Çetin
 * 
 * @note: Sonsuz bir döngü içerisinde "calculate.flag" dosyasını bekler ve dosya bulunduğunda hesaplama adımlarını işletir.
 */
int main() {

    while(1) {
        
        FILE *cal_flag = fopen(FLAG_FILE, "r");

        if (cal_flag != NULL) {
            // Flag dosyasını okuduk, işimiz bitti kapatıyoruz
            fclose(cal_flag); 
            
            // İŞLEM BİTİNCE FLAG DOSYASINI SİL Kİ TEKRAR TEKRAR ÇALIŞMASIN
            if (remove(FLAG_FILE) != 0) {
                printf("UYARI: Flag dosyası silinemedi.\n");
            }

            FILE *input_json = fopen(INPUT_FILE, "rb");
            if (input_json == NULL) {
                printf("HATA: Json Dosyası bulunamadı.\n");
                continue; // return 1 yerine continue kullan ki program kapanmasın, dinlemeye devam etsin
            }
            
            if (fseek(input_json, 0, SEEK_END) != 0) {
                printf("HATA: Json dosyası okunurken konum değiştirilemedi.\n");
                fclose(input_json);
                continue;
            }
            long input_json_size = ftell(input_json);
            if (input_json_size < 0) {
                printf("HATA: Json dosyasının boyutu okunamadı.\n");
                fclose(input_json);
                continue;
            }
            if (input_json_size == 0) {
                printf("HATA: Json dosyası boş.\n");
                fclose(input_json);
                continue;
            }
            rewind(input_json);

            char *input_json_string = (char*)malloc(input_json_size + 1);
            if (input_json_string == NULL) {
                printf("HATA: Json verisi belleğe alınamadı.\n");
                fclose(input_json);
                continue; 
            }

            size_t read_size = fread(input_json_string, 1, input_json_size, input_json);
            if (read_size != (size_t)input_json_size) {
                if (ferror(input_json)) {
                    printf("HATA: Json dosyası okunamadı.\n");
                } else {
                    printf("HATA: Json dosyası eksik okundu.\n");
                }
                free(input_json_string);
                fclose(input_json);
                continue;
            }
            input_json_string[read_size] = '\0';
            fclose(input_json);

            // 1. DÜZELTME: Graph için bellek ayırıyoruz
            Graph *input_graph = (Graph*)malloc(sizeof(Graph)); 
            if (input_graph == NULL) {
                printf("HATA: Graph belleği ayrılamadı.\n");
                free(input_json_string);
                continue;
            }

            int succes = json_to_graph(input_json_string, input_graph);
            
            // 2. DÜZELTME: input_json_string ile işimiz bitti, belleği serbest bırakalım
            free(input_json_string); 

            if (succes != 0) {
                printf("HATA: Giriş Json verisi çözümlenirken bir hata oluştu. Kod: %d\n", succes);
                free(input_graph); // Hata durumunda da temizlik yap
                continue;
            }

            MSTResult mst_output = kruskal_mst(input_graph);
            
            char *output_mst_string = mstresult_to_json(&mst_output);
            if (output_mst_string == NULL) {
                printf("HATA: MST sonucu JSON'a dönüştürülemedi.\n");
                free(input_graph);
                continue;
            }

            FILE *output_mst = fopen(OUTPUT_FILE, "w");
            if (output_mst == NULL) {
                printf("HATA: çıktı json dosyası oluşturulamadı.\n");
                // Gerekli temizlikler eklenebilir
            } else {
                if (fputs(output_mst_string, output_mst) == EOF) {
                    printf("HATA: çıktı json dosyasına yazılamadı.\n");
                } else if (fclose(output_mst) != 0) {
                    printf("HATA: çıktı json dosyası kapatılamadı.\n");
                } else {
                    printf("BAŞARILI: MST hesaplandı ve %s konumuna yazıldı.\n", OUTPUT_FILE);
                }
            }

            // string belleğini serbest bırak
            free(output_mst_string);
            free(input_graph); 
        }

        printf("Hesaplama Komutu Bekleniyor...\n");
        sleep(1);

    }

    return 0;
}