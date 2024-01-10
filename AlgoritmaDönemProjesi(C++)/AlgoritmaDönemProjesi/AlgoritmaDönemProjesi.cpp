/**
 * @author Kadir Can Geyik
 * @brief Algoritmalar ve Programlama Dersi Dönem Projesi
 * @date 2024-01-10
 * @copyright Copyright (c) 2024
 * @contact kadircngyk@gmail.com
 */
#include <iostream> 
#include <vector>
#include <algorithm> 
#include <string> 
#include <fstream> 

using namespace std;

//Ogrenci adında bir yapı oluşturuyoruz
struct Ogrenci {
    string Adi; //Öğrencinin adı dosyadan okunacak
    string Soyadi; // Öğrencinin soyad dosyadan okunacak
    int Yasi =0; // 18-60 arası random oluşturulacak
    string Cevaplar; //Random şekilde 10 adet D-Y harf DYDYDYDYDY şeklinde oluşturulacak
    string Sonuclar; //Öğrencinin verdiği cevaplara göre karşılaştırma sonrası her soru için doğrumu yanlış mı yapmış?
    int Not = 0; //Öğrencinin notu karşılaştırma sonrası nota eklenecek
};

//Dosyadan isim okumak için kullanılan fonksiyon...
void DosyadanIsimOkuyalim(const string& dosyaIsmi, vector<string>& yazilacakListe) {
    ifstream dosyam(dosyaIsmi.c_str());
    if (!dosyam.is_open()) {
        cout << dosyaIsmi << " dosyasi acilmiyor lutfen tekrar deneyiniz ! " << endl;
    }
    for (string satirim; getline(dosyam, satirim); ) {
        yazilacakListe.push_back(satirim);
    }
  
}
//Bu fonksiyonda kullanıcıdan string bir cevap anahtarı girilmesi istenecek ve okunacak
void CevapAnahtari(string& cevapAnahtarim)
{
    cout << "Lutfen 10 harften olusan (D ve Y harfleri) bir cevap anahtari giriniz.(Örnek format DYDYDYDYDY):\n "<<endl;
    cin >> cevapAnahtarim;
}
void OgrencileriOlustur(vector<Ogrenci>& Ogrenciler, int ogrenciSayisi, const vector<string>& adlar, const vector<string>& soyadlar) {


    // for döngüsü ile kullanıcının girdiği sayıya göre öğrencileri oluşturuyoruz
    for (int i = 0; i < ogrenciSayisi; ) {
        Ogrenci ogrenci;
        ogrenci.Adi = adlar[rand() % adlar.size()];
        ogrenci.Soyadi = soyadlar[rand() % soyadlar.size()];
        ogrenci.Yasi = rand() % 43 + 18;

        // ayni ogrenciden olmamasi icin bir durum tanımlıyoruz.
        bool ayniOgrenciVar = false;

        // for döngüsüyle öğrencileri geziyoruz aynı öğrenci var ise öğrenciyi eklemeyecek yok ise vektöre push edecek, ekleyecek.
        for (const Ogrenci& kayitliOgrenci : Ogrenciler) {
            if (kayitliOgrenci.Adi == ogrenci.Adi && kayitliOgrenci.Soyadi == ogrenci.Soyadi) {
                ayniOgrenciVar = true;
                // True ise öğrenciyi ekleme 
                // ogrenci sayisini bir arttır çünkü öğrenci eklenmedi ve for dongümüzden 1 ogrenci boşa çıktı.
                break;
            }
        }
        // eğer aynı öğrenci yok ise vektöre push et        // eğer aynı öğrenci yok ise vektöre push et ve i'yi arttır
        if (!ayniOgrenciVar) {
            // false ise ögrenciyi vectöre push et...
            Ogrenciler.push_back(ogrenci);
            // ogrenci eklendiyse i'yi arttır
            ++i;
        }

        // Ekledikten sonra ekrana i'yi ve eklenen öğrencinin bilgilerini yazdırarak programın ilerleyip ilerlemediğini kontrol edebiliriz
        //cout << "Eklenen Ogrenci Sayisi: " << i << endl;
        //cout << "Eklenen Ogrenci Bilgisi: " << ogrenci.Adi << " " << ogrenci.Soyadi << " " << ogrenci.Yasi << endl;
    }
}
//Bu fonksiyonda her öğrenci için soru sayısına göre random cevap oluşturuyoruz.
void SorularinCevaplariniOlustur(vector<Ogrenci>& Ogrenciler, int soruSayisi)
{
    //for döngüsü ile öğrencileri gezip öğrenci yapılarımıza cevapları ekliyoruz
    for (Ogrenci& ogrenci : Ogrenciler) {
        ogrenci.Not = 0;
        for (int i = 0; i < soruSayisi; ++i) {
            char cevap = rand() % 2 == 0 ? 'D' : 'Y';
            ogrenci.Cevaplar += cevap;
        }
    }
}
//Bu fonksiyonda öğrencilerin verdiği cevaplar ile kullanıcıdan aldığımız cevap anahtarını karşılaştırıyoruz
void PuanlariHesapla(vector<Ogrenci>& Ogrenciler, const string& cevapAnahtari)
{
    //öğrencilerin cevap anahtarlarını geziyoruz öğrencilerin cevapları ile kullanıcının cevaplarını karşılaştırıyoruz
    for (Ogrenci& ogrenci : Ogrenciler) {
        for (int i = 0; i < cevapAnahtari.size(); i++) {
            //eğer öğrencinin cevabı kullanıcının verdiği cevaba eşit ise,
            //öğrencinin notuna 10 puan ekle Sonuc dogru ise Sonuclara 'D' ekle
            if (ogrenci.Cevaplar[i] == cevapAnahtari[i]) {
                ogrenci.Not += 10;
                ogrenci.Sonuclar += 'D';
            }
            //değil ise sonuclara 'Y' ekle i değişkenini 1 arttırıp sonraki cevaba geç  
            else
            {
                ogrenci.Sonuclar += 'Y';
            }
        }  
    }   
}
//Bu fonksiyonda öğrencileri Ad,soyad,yaş veya notuna göre sıralıyoruz.
void Ogrencilerisirala(vector<Ogrenci>& Ogrenciler, char sirala)
{
    //switch ile kullanıcıdan aldığımız char ifadeye göre herhangi bir case'i çalıştırıyoruz. 
    //Kullanıcı geçer veya yanlış bir sıralama tanımlar ise default ile ada göre sıralıyoruz.
    switch (sirala) {
        //ada göre sıralama
    case 'A': case 'a':
        sort(Ogrenciler.begin(), Ogrenciler.end(), [](const auto& k1, const auto& k2) { return k1.Adi < k2.Adi; });
        break;
        //soyada göre sıralama
    case 'S': case 's':
        sort(Ogrenciler.begin(), Ogrenciler.end(), [](const auto& k1, const auto& k2) { return k1.Soyadi < k2.Soyadi; });
        break;
        //yaşa göre sıralama
    case 'Y': case 'y':
        sort(Ogrenciler.begin(), Ogrenciler.end(), [](const auto& k1, const auto& k2) { return k1.Yasi < k2.Yasi; });
        break;
        //nota göre sıralama
    case 'N': case 'n':
        sort(Ogrenciler.begin(), Ogrenciler.end(), [](const auto& k1, const auto& k2) { return k1.Not > k2.Not; });
        break;
        //default olarak ada göre sıralama
    default:
        sort(Ogrenciler.begin(), Ogrenciler.end(), [](const auto& k1, const auto& k2) { return k1.Adi < k2.Adi; });
        break;
    }
}
int main() {

    int ogrencisayisi = 0; //ogrencisayisi değiişkenini öğrenci sayısını kullanıcıdan almak için tanımlıyoruz
    int sorular = 10; //kaç adet soru olmasını istiyoruz ?
    int dogrusayisi = 0;
    //burada do while döngüsü kullanıyoruz.
    //Kullanıcının 0 ile 2500 arası haricinde bir sayı girdiğinde
    //hata bilgisi vermek ve tekrar girmesini istediğimiz için kullanıyoruz.
    do {
        cout << "Lutfen ogrenci sayisi giriniz ! 0 ile 2500 arasi:\n";
        //öğrencisayisini oku
        cin >> ogrencisayisi;
        //eğer öğrenci sayısı 0 ile 2500 arasında değilse kullanıcıya bilgi ver 
        if (ogrencisayisi <= 0 || ogrencisayisi > 2500) {
            cout << "Gecersiz ogrenci sayisi! Lutfen tekrar giriniz." << endl;
        }
    } while (ogrencisayisi <= 0 || ogrencisayisi > 2500); //0 ile 2500 arası değilse öğrencisayısı tekrar do'nun içerisine gir.

    //Ad ve soyad dosyalarının adlarını tanımlıyoruz
    const string adDosyasi = "ad.txt";
    const string soyadDosyasi = "soyad.txt";

    //Ad ve soyad vektorlerini oluşturuyoruz...
    vector<string> adlar;
    vector<string> soyadlar;

    // Dosyalardan random isim ve soyisimler almak için dosyaları oku ve adlar soyadlar vektörlerimize tanımla
    DosyadanIsimOkuyalim(adDosyasi, adlar);
    DosyadanIsimOkuyalim(soyadDosyasi, soyadlar);


    //Ogrencileri oluşturuyoruz...
    vector<Ogrenci> ogrenciler;
    OgrencileriOlustur(ogrenciler, ogrencisayisi, adlar, soyadlar);

    //Soru cevaplarını oluşturuyoruz...
    SorularinCevaplariniOlustur(ogrenciler, sorular);

    //Cevap anahtarını okuyoruz...
    string cevapAnahtari;
    CevapAnahtari(cevapAnahtari);

    //Puanları hesapliyoruz..
    PuanlariHesapla(ogrenciler, cevapAnahtari);

    //Öğrenciler arasında Sıralama yapiyoruz...
    char siralama;//kullanıcıdan sıralama yapma şeklini girmesini ve bunu okumak için tanımlıyoruz. (Daha sonra OgrencilerisiraLa fonksiyonumuza göndereceğiz.)
    cout << "Ogrencileri nasil siralamak istersiniz ?\nAda Gore = A\nSoyada Gore = S\nYasa Gore = Y\nNota Gore = N:\n" << endl;
    //kullanıcıdan bir sıralama şekli girmesini istiyoruz
    cin >> siralama;

    //Kullanici tercihine göre ogrencileri siraliyoruz ogrencileri ve kullanıcıdan aldığımız siralama değişkenini fonksiyonumuza gönderiyoruz...
    Ogrencilerisirala(ogrenciler, siralama);

    //Son olarak sonuclari sıraladıktan sonra ekrana uygun biçimde yazdiriyoruz...
    for (int i = 0; i < ogrenciler.size(); ++i) {

        const Ogrenci& ogrenci = ogrenciler[i];
        cout << "[" << i + 1 << ".Ogrenci] - [Adi-Soyadi: " << ogrenci.Adi + ogrenci.Soyadi << "] - [Yasi: " << ogrenci.Yasi << "] - [Puani: " << ogrenci.Not << "] - [Sonuc: " << ogrenci.Sonuclar + "]" << endl;
    }
}