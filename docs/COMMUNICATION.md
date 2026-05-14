## Arayüz ile Backend Haberleşmesi: JSON mimarisi

- Arayüzde hesaplama için graf oluşturulduktan ve hesaplama komutu verildikten sonra arayüz ui/shared_data klsörüne input_graph.json dosyasını arayüzde oluşturulan grafa göre oluşturacak ve aynı dizin içerisine backend'in jsonun hesaplmaya hazır olduğunu anlaması ve hesaplamak işlemine geçebilmesi için calculate.flag isimli bir bayrak görevi gören dosyayı da oluşturması gerekiyor.
- Ardından Backend input_json dosyasını alıp io_adapter.c kaynak koudnaki fonksiyonları kullanarak kruskal algortimasının kullanabileceği graph structına çevirmeli ve bu graph ile mst hesaplamasını yapmalı. Hesaplamanın ardından kruskal algortimasının geriye döndüreceği MST_result struct'ını, io_adapter.c kaynak dosyaında bulunan fonskiyonları kullanarak arayüzün beklediği oputput_grapf.json formatına çevirdikten sonra ui/shared_data klaösürne atomik olarak yazmalı. 
- Bu haberleşme akışının gerçekleşmesi için gerekli fonksiyonlar burda yer almaktadır.

- Projede arayüz ile hesaplama katmanının haberleşmesi için kullanılacak olan json formatları aşağıda yer almaktadır.

### Input JSON:

    {
        "request_meta": {"algorithm": "kruskal", "action": "calculate_mst", "node_count": 3},
        "nodes": [{"id": 0, "x": 100, "y": 100}, {"id": 1, "x": 175, "y": 145}],
        "edges": [{"source": 0, "target": 1, "weight": 87.46}]
    }

### Output JSON:

    {
        "response_meta": {"total_cost": 156.42},
        "mst_edges": [
            {"source": 0, "target": 1},
            {"source": 1, "target": 2}
        ]
    }