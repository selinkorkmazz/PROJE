#include <stdio.h>
#include <conio.h>   //getch fonksiyonunu kullanarak herhangi bir girdi alabilmek icin bu kutuphane ekli
#include <stdlib.h>  //her sorudan sonra ekranı temizleme fonksiyonunu kullanabilmek için
#include <windows.h> //yazi fontunu değiştirebilmek için
#define maxline 500  // dosyalardan çekilen metinlerin satırlarındaki max karakter sayisi
char secenek;
int renk = 1;

// kullanıcının girdilerine gore sonuc parametrelerine değer atayan fonksiyon
void switc(int *c1, int *c2, int *c3)
{
   //pointer ile dışarıdaki parametrenin adresine atama yapılır 
    switch (secenek)
    {
    case 'A':
    case 'a':
        (*c1)++;
        break;
    case 'B':
    case 'b':
        (*c2)++;
        break;
    case 'C':
    case 'c':
        (*c3)++;
        break;
    }
}

// her ekran temizlemeden sonra yazı fontunun rengini değiştiren fonksiyon
void color()
{
    switch (renk)
    {
    case 1:
        system("color 01");
        break;
    case 2:
        system("color 02");
        break;
    case 3:
        system("color 03");
        break;
    case 4:
        system("color 04");
        break;
    case 5:
        system("color 05");
        break;
    case 6:
        system("color 06");
        break;
    case 7:
        system("color 08");
        break;
    }
}

void main()
{
    int cikis;
    // program bir kez çalıştıktan sonra kullanıcının tekrar çözmek istemesi veya programı sonlandırması için girdiği değere göre döngü
    do
    {
        /*puan, ilk başta sorulan soruların sonuçlarına göre 3 farklı bölgeden (bati,ortadoğu,asya) birine atanıyor
        sonrasında puana göre her bölge için farklı sorular soruluyor ve her bölgenin soruları farklı dosyalardan çekiliyor
        ilk sorulan sorular ana dosyadan çekiliyor*/

        FILE *anasorular = fopen("anasorular.txt", "r");
        char line[maxline];
        int satir = 1, puan[3] = {0, 0, 0};
        int avrupa = 0, balkanlar = 0, iskandinav = 0, turkiye = 0, ortaAsya = 0, kuzeyAfrika = 0, rusya = 0, guneyAsya = 0, uzakDogu = 0;
        renk = 1; // her seferinde renk döngüsünün baştan başlayabilmesi için

        // terminal temizlenip yazı rengi ayarlandıktan sonra ekrana yazı yazdırıyor
        system("cls");
        system("color 05");
        printf("\n**********************************************\n");
        printf("* HANGI ULKENIN INSANISIN TESTINE HOSGELDIN! *\n");
        printf("**********************************************\n\n\n\n");
        printf("Testi baslatmak icin ENTER'a bas!");
        getch();
        system("cls");
        // herhangi bir girdi alındıktan sonra (ENTER) terminal tekrar temizlenip sorular dosyadan çekilmeye başlanıyor

        if (anasorular == NULL)
        {
            // dosyanın açılamama ihtimalinde ekrana kırmızı uyarı yazısı veren karar yapısı
            system("color 0C");
            puts("\nDOSYA ACILAMADI!\n");
            getch();
            exit(1); // alınan hata sonucu programı sonlandırma fonksiyonu
        }

        // dosyadan soruları satır satır çekme döngüsü
        while (fgets(line, maxline, anasorular))
        {
            printf(line);
            if (satir % 4 == 0) // 4e bölümünden kalanı 1 olan satırlar çekiliyor
            {
                // her soruda (4 satırda) bir terminalin rengi değiştiriliyor
                color();
                renk++;
                // her soruda (4 satırda) bir kullanıcıdan girdi alınıyor
                scanf("%s", &secenek);
                // kullanıcının  girdisine göre switch karar yapısı üzerinden parametrelere puan ataması yapılıyor
                switc(&puan[0], &puan[1], &puan[2]);
                // her sorudan sonra terminal temizleniyor
                system("cls");
            }
            satir++;
        }
        // dosyadan bütün sorular çekildikten sonra dosya kapatılıyor
        fclose(anasorular);
        renk = 1;

        // eğer kullanıcı sorulan ilk 5 soruda 2şer eşit seçenek seçmişse (2,2,1) kullanıcıya yeni bir soru sorulur
        if ((puan[0] == 2 && puan[1] == 2) || (puan[0] == 2 && puan[2] == 2) || (puan[1] == 2 && puan[2] == 2))
        {
            color();
            renk++;
            printf("Hangi muzik turunu seversin?\nA)Klasik Muzik\nB)Folk/Halk Muzigi\nC)Lirik Muzik\n");
            scanf("%s", &secenek);
            switc(&puan[0], &puan[1], &puan[2]);
            system("cls");

            // eğer sorulan 6. sorudan sonra hala kullanıcı girdileri eşit seçeneklerse (2,2,2) tekrar bir soru sorulur
            if (puan[0] == puan[1] || puan[0] == puan[2] || puan[1] == puan[2])
            {
                color();
                renk++;
                printf("Hangi yas araligindasin?\nA)15-30\nB)30-45\nC)45-60+\n");
                scanf("%s", &secenek);
                switc(&puan[0], &puan[1], &puan[2]);
                system("cls");
            }
            // 7 sorudan 3 şıkkın eşit olma ihtimali yoktur (3,2,2). Böylece puanlama doğru yapılabilir
        }
        renk = 1;
        satir = 1;

        // sorulan ana sorulardan sonra alınan girdilere göre batı(puan[0]), ortadoğu(puan[1]) veya asya(puan[2]) bolgelerinden en buyuk olanı seçilir
        // eğer batı(puan[0]) büyükse:
        if (puan[0] > puan[1] && puan[0] > puan[2])
        {
            FILE *sorular1 = fopen("sorular1.txt", "r");
            color();
            renk++;
            printf("Verdigin cevaplara bakarsak Bati esintilerine sahipsin!\nHadi bu sorulari da cevapla ve tam olarak hangi cografi bolgenin insani oldugunu bul!\nDevam etmek icin ENTER'a bas.\n");
            getch();
            system("cls");
            if (sorular1 == NULL)
            {
                system("color 0C");
                puts("\nDOSYA ACILAMADI!\n");
                getch();
                exit(1);
            }
            while (fgets(line, maxline, sorular1))
            {
                printf(line);
                if (satir % 4 == 0)
                {
                    color();
                    renk++;
                    scanf("%s", &secenek);
                    switc(&avrupa, &balkanlar, &iskandinav);
                    system("cls");
                }
                satir++;
            }
            // sorular dosyadan teker teker çekilip cevaplar alındıktan sonra dosya kapatılır
            fclose(sorular1);

            // eğer sorulan 3 farklı soruya 3 seçeneğin her biri cevap verilirse (1,1,1) kullanıcıya yeni bir soru sorulur, bu sorunun cevabına göre test devam eder
            if (avrupa == balkanlar && avrupa == iskandinav && balkanlar == iskandinav)
            {
                color();
                renk++;
                printf("Hangi konaklama turunu tercih edersin?\nA)Otel\nB)Cadir\nC)Bungalov\n");
                scanf("%s", &secenek);
                switc(&avrupa, &balkanlar, &iskandinav);
                system("cls");
            }

            // alınan sonuçlara göre puanı büyük olan bölge (avrupa, balkanlar veya iskandinavlar) yazdırılır
            if (avrupa > balkanlar && avrupa > iskandinav)
            {
                printf("Sen tam bir Avrupalisin! Bilim ve sanatin merkezi, ayrica cok sosyal ve renkli bir cografya.\nInsanlari guleryuzlu ve refah bir toplumda yasadiklari icin daha ozgur ruhlular.\nBu testte verdigin cevaplara bakarsak bu toplumda yasamak sana daha iyi gelecek!\n");
            }
            else if (balkanlar > avrupa && balkanlar > iskandinav)
            {
                printf("Sen aslinda Balkanlarda yasamaliydin! Aslinda kultur olarak Turkiye'ye benzese de kendine ozgu gelenekleri de bulunan bir cografya.\nIklimi guzel ve ferah. Zengin topraklar ve temiz havasiyla tam bir rotani ciz-sirt cantanla dolas bolgesi!\n");
            }
            else if (iskandinav > avrupa && iskandinav > balkanlar)
            {
                printf("Sen Iskandinav ulkelerinde dogmaliydin! Huzurlu ve guvenli yasamin topraklari. En guzel balik yemekleri, her turlu sebze ve meyvenin dogali burada.\nKoklu bir kultur uzerine kurulmus, muhtesem bir dogaya sahip medeni bir cografya. Oradaki yasam tam sana gore!\n");
            }
        }

        // eğer orta doğu(puan[1]) büyükse
        else if (puan[1] > puan[0] && puan[1] > puan[2])
        {
            FILE *sorular2 = fopen("sorular2.txt", "r");
            color();
            renk++;
            printf("Verdigin cevaplar Orta Dogu cografyasına yakin gorunuyor!\nHadi bu sorulari da cevapla ve tam olarak hangi cografi bolgenin insani oldugunu bul!\nDevam etmek icin ENTER'a bas.\n");
            getch();
            system("cls");
            if (sorular2 == NULL)
            {
                system("color 0C");
                puts("\nDOSYA ACILAMADI!\n");
                getch();
                exit(1);
            }
            while (fgets(line, maxline, sorular2))
            {
                printf(line);
                if (satir % 4 == 0)
                {
                    color();
                    renk++;
                    scanf("%s", &secenek);
                    switc(&turkiye, &ortaAsya, &kuzeyAfrika);
                    system("cls");
                }
                satir++;
            }
            // sorular dosyadan teker teker çekilip cevaplar alındıktan sonra dosya kapatılır
            fclose(sorular2);

            // alınan cevapların eşit olma ihtimalini içerip yeni soru soran karar yapısı
            if (turkiye == ortaAsya && turkiye == kuzeyAfrika && ortaAsya == kuzeyAfrika)
            {
                color();
                renk++;
                printf("Hangi turistik bolgeye gitmeyi tercih edersin?\nA)Kapadokya\nB)Almati Golleri\nC)Piramitler\n");
                scanf("%s", &secenek);
                switc(&turkiye, &ortaAsya, &kuzeyAfrika);
                system("cls");
            }

            // alınan sonuçlara göre puanı büyük olan bölge(türkiye, orta asya veya kuzey afrika) yazdırılır
            if (turkiye > ortaAsya && turkiye > kuzeyAfrika)
            {
                printf("Sen tam bir Turksun! Kulturu, cografyasi, iklimi, yemekleri, her seyi senlik!");
            }
            else if (ortaAsya > turkiye && ortaAsya > kuzeyAfrika)
            {
                printf("Sen Orta Asya taraflarindan eski Turk kanina sahipsin! Sert bozkir iklimi ve sert mizacli insanlariyla unlu.\nKulturlerine olan bagliliklariyla da taniniyorlar. Buradaki hayat tam sana gore!\n");
            }
            else if (kuzeyAfrika > turkiye && kuzeyAfrika > ortaAsya)
            {
                printf("Sende Kuzey Afrika esintileri var! Guclu aile baglari ve kulturlerine bagliliklariyla meshur olan bu cografya senin icin ideal!");
            }
        }

        // eğer asya(puan[2]) büyükse
        else if (puan[2] > puan[0] && puan[2] > puan[1])
        {
            FILE *sorular3 = fopen("sorular3.txt", "r");
            color();
            renk++;
            printf("Verdigin cevaplara gore Asya cografyasina daha cok yaklasiyorsun!\nHadi bu sorulari da cevapla ve tam olarak hangi cografi bolgenin insani oldugunu bul!\nDevam etmek icin ENTER'a bas.\n");
            getch();
            system("cls");
            if (sorular3 == NULL)
            {
                system("color 0C");
                puts("\nDOSYA ACILAMADI!\n");
                getch();
                exit(1);
            }
            while (fgets(line, maxline, sorular3))
            {
                printf(line);
                if (satir % 4 == 0)
                {
                    color();
                    renk++;
                    scanf("%s", &secenek);
                    switc(&rusya, &guneyAsya, &uzakDogu);
                    system("cls");
                }
                satir++;
            }
            // sorular dosyadan teker teker çekilip cevaplar alındıktan sonra dosya kapatılır
            fclose(sorular3);

            // alınan cevapların eşit olma ihtimalini içerip yeni soru soran karar yapısı
            if (rusya == guneyAsya && rusya == uzakDogu && guneyAsya == uzakDogu)
            {
                color();
                renk++;
                printf("Karakterinize en yakin secenek hangisi?\nA)Soguk\nB)Paylasimci\nC)Caliskan\n");
                scanf("%s", &secenek);
                switc(&rusya, &guneyAsya, &uzakDogu);
                system("cls");
            }

            // alınan sonuçlara göre puanı büyük olan bölge(rusya, güney asya, uzak doğu) yazdırılır
            if (rusya > guneyAsya && rusya > uzakDogu)
            {
                printf("Rusya'da yasam tam sana gore! Soguk insanlar gibi gorunseler de arkadasliga cok onem verirler.\nDunya klasiklerine cok sey katmis olan Rus yazarlarinin muzelerini ziyaret etmek, orijinal kitaplarini okumak,\nheyecan verici tiyatro produksiyonlarini ve filmlerini izlemek...\nOraya kesin gitmelisin!");
            }
            else if (guneyAsya > rusya && guneyAsya > uzakDogu)
            {
                printf("Sen Guney Asya kulturune yakinsin! Sicak kanli insanlari ve dunyaya olan farkli bakis acilariyla ic huzurunu bulmani saglayacak bir bolge.\nBuradaki yasami deneyimlemen gerek!\n");
            }
            else if (uzakDogu > rusya && uzakDogu > guneyAsya)
            {
                printf("Senin Uzak Dogu'da yasaman gerek! Gelismis teknolojileriyle insa ettikleri cagdas medeniyetleri yasamak icin super bir secim! Guleryuzlu ve kibar insanlari orada icini isitacak!\n");
            }
        }
        printf("\n\n\nTesti bastan cozmek istiyorsaniz 0'a basiniz. Programi sonlandirmak icin 1'e basiniz.\n");
        scanf("%d", &cikis);
        system("cls");
    } while (cikis != 1);
}
