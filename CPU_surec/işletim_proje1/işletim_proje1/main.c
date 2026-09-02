#include <stdlib.h>
#include <stdio.h>
#define MAX 100

void bellek_durumu(int cerceveler[], int cerceve_sayisi){
    printf("[");
    for(int i=0;i<cerceve_sayisi;i++){//tüm çerçeveleri tek tek kontrol eder
        if(cerceveler[i]== -1){
            printf("-");//çerçeve boşsa - işareti koyar
        }else{
            printf("%d",cerceveler[i]);//çerçeve boş değilse sayfa numarasını yazar
        }
        if(i<cerceve_sayisi - 1){ //çerçeveleri yazdırırken sayılar arasına virgül koymayı sağlar
            printf(", ");
        }
    }
    printf("]");
}

//özet tablo kısmını yazdırır
void ozet_yazdir(int sayfa_hatasi , int toplam_eleman_sayisi){
    printf("--------SONUÇ ÖZETİ--------\n");
    printf("%s : %d\n","Toplam referans sayisi",toplam_eleman_sayisi);
    printf("%s : %d\n","Page fault sayisi",sayfa_hatasi);
    printf("%s : %d\n","Page hit sayisi",toplam_eleman_sayisi-sayfa_hatasi);
    printf("%s : %.2f\n","Page fault orani:",(float)sayfa_hatasi/toplam_eleman_sayisi*100);
    printf("%s : %.2f\n","Page Hit orani:",(float)(toplam_eleman_sayisi-sayfa_hatasi)/toplam_eleman_sayisi*100);
}

//FİFO
int fifo(int dizi[],int toplam_eleman_sayisi , int cerceve_sayisi,int detay_goster){
    int cerceveler[MAX],hata=0,sira=0;
    for(int i=0;i<cerceve_sayisi;i++){
        cerceveler[i]=-1;//tüm çerçeveleri boş hale getirirr
    }
    if(!detay_goster){
        printf("\nReferans\tBellek Durumu\tSonuc\n");//tablo başlığı yazdırır
    }
    for(int i=0;i<toplam_eleman_sayisi;i++){//tüm sayfa numaralarını gezer
        int sayfa = dizi[i],bulundu=0;
        for(int j=0;j<cerceve_sayisi;j++){//çerçeveyi gezer
            if(cerceveler[j]==sayfa){//çerçevede o sayfa var mı diye bakar
                bulundu=1;//hit yapılır
                break;
            }
        }
        if(!bulundu){
            hata++;//bulunamazsa hata artar
            cerceveler[sira]=sayfa;//sayfa numarası o an en eski elemanı gösteren sira indeksindeki çerçevenin içine yazılır
            sira = (sira+1) % cerceve_sayisi;
            //sırayı bir sonraki çerçeveye kaydırır mod alma sayesinde sıra son çerçeveye gelince tekrar otomatik olarak 0.indexe döner her zaman en eski olan çıkarılmış olur
        }
        if(!detay_goster){
            printf("%d\t\t\t",sayfa);
            bellek_durumu(cerceveler , cerceve_sayisi);
            printf("\t\t%s\n",bulundu ? "Hit" : "Fault");
        }
    }
    return hata;//toplam yapılan hata sayısını döndürür
}
//LRU
int lru(int dizi[],int toplam_eleman_sayisi, int cerceve_sayisi,int detay_goster){
    int cerceveler[MAX],son_kullanim[10]/*en son ne zaman kullanıldıgını tutar*/,hata=0;
    for(int i=0;i<cerceve_sayisi;i++){//başlangıcta çerçeveler ve zaman sıfırlanıyor
        cerceveler[i] = -1;
        son_kullanim[i]= -1;
    }
    if(!detay_goster){
        printf("\nReferanslar\tBellek Durumu\tSonuc\n");
    }
    for(int i=0;i<toplam_eleman_sayisi;i++){
        int sayfa = dizi[i] , bulundu = 0 , index=-1;
        for(int j=0;j<cerceve_sayisi;j++){//tüm çerevelere bakar
            if(cerceveler[j]==sayfa){// bulunduysa bulundu olarak işaretler ve index değişkenine hangi çerçevede oldugunu kaydeder
                bulundu = 1;
                index = j;
                break;
            }
        }
        if(bulundu){
            son_kullanim[index] = i;
            //sadece o çerçevenin son kullanılma zamanı güncellenir ve simülasyonun o anki saati i olarak kaydedilir.
        }else{
            hata++;//bulunamadıysa hata sayısı artar
            int degisecek = 0 , bos_yer = -1;
            for(int j=0;j<cerceve_sayisi;j++){
                if(cerceveler[j]== -1){//çerçeve boşsa
                    bos_yer = j;//o çerçeve indexini boş_yer değişkenine atar
                    break;
                }
            }
            if(bos_yer != -1){//boş_yer boş değilse
                degisecek = bos_yer;//sayfanın yerleşeceği yer orası olur
            }else{//boş yer yoksa
                int min = son_kullanim[0];
                for(int j=1;j<cerceve_sayisi;j++){
                    if(son_kullanim[j]<min){//en küçük zaman en uzun süredir kullanılmayan çerçeve
                        min=son_kullanim[j];
                        degisecek=j;//en uzun süredir kullanılmayan çerçeveye yeni sayfa gelir
                    }
                }
            }
            cerceveler[degisecek]=sayfa;//boş yere veye en uzun süredir kullanılmayan çerçeveye yeni sayfa yazılır
            son_kullanim[degisecek]=i;
        }
        if(!detay_goster){
            printf("%d\t\t\t",sayfa);
            bellek_durumu(cerceveler,cerceve_sayisi);
            printf("\t\t%s\n",bulundu ? "Hit":"Fault");
        }
    }
    return hata;
}

//Optimal
int optimal(int dizi[],int toplam_eleman_sayisi, int cerceve_sayisi, int detay_goster){
    int cerceveler[MAX], hata = 0;
        for (int i = 0; i < cerceve_sayisi; i++) cerceveler[i] = -1;

        if (!detay_goster) printf("\nReferans\tBellek Durumu\tSonuc\n");
        for (int i = 0; i < toplam_eleman_sayisi; i++) {
            int sayfa = dizi[i], bulundu = 0;
            
            for (int j = 0; j < cerceve_sayisi; j++) {//tüm çerçeveleri geziyo
                if (cerceveler[j] == sayfa) {//istenen sayfa bulunduysa bulundu olarak işaretler
                    bulundu = 1;
                    break;
                }
            }
        
            if (!bulundu) {//bulunamadıysa
                hata++;
                int degisecek = -1;
                for (int j = 0; j < cerceve_sayisi; j++) {//çerçeveleri gezer
                    if (cerceveler[j] == -1) {//çerçeve boşsa
                        degisecek = j;//yeni sayfanın geleceği index
                        break;
                    }
                }
                if (degisecek == -1) {//boş yer yoksa
                    int uzaklik = -1; //en geç kullanılan sayıyı bulamk için var
                    for (int j = 0; j < cerceve_sayisi; j++) {//çerçeveleri gezer
                        int sonraki = 999;
                        for (int k = i + 1/*o an bulundugu adımdan i adım sonrasından aramaya başlar*/; k < toplam_eleman_sayisi/*sayfa listesinin en sonuna kadar ileriye doğru yürür*/; k++) {
                            if (dizi[k] == cerceveler[j]) {// k anında istenecek sayfa j çerçevenin içindeki ile aynı mı?
                                sonraki = k;//o sayfanın gelecekte ilk kez kullanılacağı anı
                                break;
                            }
                        }
                        if (sonraki == 999) {//o iç döngü hiçbir şey bulamamış demek yani o çerçevedeki sayfa gelecekte bir daha asla kullanılmayacak
                            degisecek = j;//yerine yeni sayfa yazılacak hedefi o anki çerçeve degisecek = j olarak belirler
                            break;
                        }
                        //Bu şart bloğu, gelecekte tekrar kullanılacak sayfalar arasından en geç ihtiyaç duyulacak olanı tespit edip bellekten atılacak kurban olarak seçer.
                        if (sonraki > uzaklik) {
                            uzaklik = sonraki;
                            degisecek = j;
                        }
                    }
                }
                cerceveler[degisecek] = sayfa;
            }
            if (!detay_goster) {
                printf("%d\t\t\t", sayfa); bellek_durumu(cerceveler, cerceve_sayisi);
                printf("\t\t%s\n", bulundu ? "Hit" : "Fault");
            }
        }
        return hata;
}

//LFU
int lfu(int dizi[], int toplam_eleman_sayisi, int cerceve_sayisi, int detay_goster) {
    int cerceveler[MAX], frekans[10] = {0}, zaman[10]/*en son kullanımi tutucak*/ = {0}, hata = 0;
    for (int i = 0; i < cerceve_sayisi; i++) {
        cerceveler[i] = -1;
        frekans[i] = 0;//hit sayısı
    }

    if (!detay_goster) {
        printf("\nReferans\tBellek Durumu\tSonuc\n");
    }
    for (int i = 0; i < toplam_eleman_sayisi; i++) {
        int sayfa = dizi[i], bulundu = 0, index = -1;
        for (int j = 0; j < cerceve_sayisi; j++) {//tüm çerçevelere bakar
            if (cerceveler[j] == sayfa) {
                bulundu = 1;
                index = j;//bulundugu çerçeve indexini index değişkenine atar
                break;
            }
        }
        if (bulundu) {
            frekans[index]++;//hit arttırılır
            zaman[index]=i;//sayfaya en son erişilen an
        } else {
            hata++;
            int degisecek = -1;
            for (int j = 0; j < cerceve_sayisi; j++) {
                if (cerceveler[j] == -1) {//çerçeve boşsa
                    degisecek = j;//sayfa oraya yerleşir
                    break;
                }
            }
            if (degisecek == -1) {//çerçeve doluysa
                int min = frekans[0];
                degisecek = 0;
                for (int j = 1; j < cerceve_sayisi; j++) {
                    if (frekans[j] < min) {
                        min = frekans[j];
                        degisecek = j;//en az hit alan çerçevenin indexini seçer
                    }
                    else if (frekans[j] == min && zaman[j] < zaman[degisecek]) {//iki çerçevenin kullanım sıklıgı aynıysa en uzun süre hit almamış, belleğe daha eski girmiş olan çerçeve belirlenir
                        degisecek = j;
                    }
                }
            }
            cerceveler[degisecek] = sayfa;//bulunan çerçevenin üzerine yeni sayfayı yazar.
            
            //o çerçevenin eski sayfasından kalan kullanım geçmişi silinir yeni sayfa için frekans skoru sıfırdan yani 1 olarak başlatılır. Giriş veya erişim zamanı da güncel saat i olarak güncellenir.
            frekans[degisecek] = 1;
            zaman[degisecek] = i;
        }
        if (!detay_goster) {
            printf("%d\t\t\t", sayfa); bellek_durumu(cerceveler, cerceve_sayisi);
            printf("\t\t%s\n", bulundu ? "Hit" : "Fault");
        }
    }
    return hata;
}

int main(int argc, const char * argv[]) {
   
    int dizi[MAX], cerceve_sayisi, dizi_uzunlugu = 0, secim;

        printf("Referans dizisi girin (Bitirmek icin -1): ");
        while (1) {
            int sayfa_numarasi;
            scanf("%d", &sayfa_numarasi);
            if (sayfa_numarasi == -1){
                break;
            }
            dizi[dizi_uzunlugu++] = sayfa_numarasi;
        }// -1 girilene kadar referans dizisi yazılır
    
        printf("Cerceve sayisi: ");
        scanf("%d", &cerceve_sayisi);//çerçeve sayısı girilr

        while (1) {
            printf("\n1 - FIFO\n2 - LRU\n3 - Optimal\n4 - LFU\n5 - Tumunu Calistir ve Karsilastir\n0 - Cikis\nSecim: ");
            scanf("%d", &secim);//yapılacak işlem seçilir

            if (secim == 0){
                break;
            }

            if (secim == 5) {
                int f1 = fifo(dizi, dizi_uzunlugu, cerceve_sayisi, 1);
                int f2 = lru(dizi, dizi_uzunlugu, cerceve_sayisi, 1);
                int f3 = optimal(dizi, dizi_uzunlugu, cerceve_sayisi, 1);
                int f4 = lfu(dizi, dizi_uzunlugu, cerceve_sayisi, 1);
                
                printf("\n%15s %15s %15s %15s %15s\n", "Algoritma", "Page Fault", "Page Hit", "Fault Orani", "Hit Orani");
                printf("-----------------------------------------------------------------------------\n");
                printf("%15s %15d %15d %15.2f %15.2f\n", "FIFO", f1, dizi_uzunlugu-f1, (float)f1/dizi_uzunlugu*100, (float)(dizi_uzunlugu-f1)/dizi_uzunlugu*100);
                printf("%15s %15d %15d %15.2f %15.2f\n", "LRU", f2, dizi_uzunlugu-f2, (float)f2/dizi_uzunlugu*100, (float)(dizi_uzunlugu-f2)/dizi_uzunlugu*100);
                printf("%15s %15d %15d %15.2f %15.2f\n", "Optimal", f3, dizi_uzunlugu-f3, (float)f3/dizi_uzunlugu*100, (float)(dizi_uzunlugu-f3)/dizi_uzunlugu*100);
                printf("%15s %15d %15d %15.2f %15.2f\n", "LFU", f4, dizi_uzunlugu-f4, (float)f4/dizi_uzunlugu*100, (float)(dizi_uzunlugu-f4)/dizi_uzunlugu*100);
            } else {
                int f = 0;
                if (secim == 1) {
                    printf("\n--- FIFO Algoritmasi Simulasyonu ---\n");
                    f = fifo(dizi, dizi_uzunlugu, cerceve_sayisi, 0);
                }
                else if (secim == 2) {
                    printf("\n--- LRU Algoritmasi Simulasyonu ---\n");
                    f = lru(dizi, dizi_uzunlugu, cerceve_sayisi, 0);
                }
                else if (secim == 3) {
                    printf("\n--- Optimal Algoritma Simulasyonu ---\n");
                    f = optimal(dizi, dizi_uzunlugu, cerceve_sayisi, 0);
                }
                else if (secim == 4) {
                    printf("\n--- LFU Algoritmasi Simulasyonu ---\n");
                    f = lfu(dizi, dizi_uzunlugu, cerceve_sayisi, 0);
                }
                else {
                    printf("Gecersiz secim!\n");
                    continue;
                }
                
                ozet_yazdir(f, dizi_uzunlugu);
            }
        }
    
    return 0 ;
}
