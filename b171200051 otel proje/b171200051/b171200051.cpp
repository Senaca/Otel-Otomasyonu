/************************************************************
** 	 	 	 	 	    SAKARYA ÜNİVERSİTESİ
** 	 	 	   BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
** 	 	 	     BİLİŞİM SİSTEMLERİ MÜHENDİSLİĞİ BÖLÜMÜ
**    	 	          PROGRAMLAMAYA GİRİŞ DERSİ
** 	 	 	 	        2017-2018 GÜZ DÖNEMİ
**
** 	 	 	 	ÖDEV NUMARASI: 5
** 	 	 	 	ÖĞRENCİ ADI: Betül Sena Çağlar
** 	 	 	 	ÖĞRENCİ NUMARASI:  b171200051
**              DERSİN ALINDIĞI GRUP: A Grubu
************************************************************/


#include "stdafx.h"
#include<iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include<iomanip>
using namespace std;


class otel
{
public:                   //değişkenleri tanımlama
	string m_ad;
	string m_soyad;
	string m_no;
	int m_kimlik;
	string oda_no;
	int ucret;
	string odakayit_no;
	int o_no;
	int mus_no;
public:                   //kullanılcak metodları tanımlama
	void anamenu();
	void musteriislemleri();
	void musteri_ekle();
	void musteri_sil(string numara);
	void odaislemleri();
	void oda_ekle();
	void oda_sil(string numara);
	void oda_listele();
	void musteri_listele();
	void oda_kayit();
	void odakayit_ekle();
	void odakayit_sil(string numara);
	void odakayit_listele();
}musteri;

void otel::anamenu()          //Anamenü altprogramı oluşturma
{
	int secim;
	do
	{
		cout << "\n Otel Islemleri" << endl;
		cout << "---------------------" << endl;
		cout << "1-Oda Islemleri\n";
		cout << "2-Musteri Islemleri\n";
		cout << "3-Oda Kayit Islemleri\n";
		cout << "99-Cikis\n";
		cout << "Seciminiz:";
		cin >> secim;

		switch (secim)            //Anamenüde seçilen işleme göre metodları çağırma
		{
		case 1: odaislemleri(); break;
		case 2: musteriislemleri(); break;
		case 3: oda_kayit(); break;
		case 99:exit(99); break;
		default:
		{
			cout << "Hatali Secim" << endl;            //Hata mesajı
			cout << "Devam etmek icin tiklayiniz...";
			_getch();
			system("cls");

		}
		}
	} while (secim != 99);      //99 girilene kadar programdan çıkmamasını sağlayan koşul
}

void otel::odaislemleri()         //Oda işlemleri menüsü altprogramı oluşturma
{
	system("cls");
	int secim1;
	cout << "1-Oda Ekle" << endl;
	cout << "2-Oda Sil" << endl;
	cout << "3-Odalari Listele" << endl;
	cout << "99-Ust Menu" << endl;
	cout << "Seciminiz:";
	cin >> secim1;
	system("cls");

	switch (secim1)
	{
	case 1: musteri.oda_ekle(); break;
	case 2: cout << "Kayidi Silinecek Oda Numarasi:"; cin >> musteri.oda_no;
		musteri.oda_sil(musteri.oda_no); break;
	case 3: musteri.oda_listele(); break;
	case 99: break;
	default:
	{
		cout << "Hatali Secim" << endl;              //Hata mesajı
		cout << "Devam etmek icin tiklayiniz...";
		_getch();
		system("cls");
	}
	}
}

void otel::oda_ekle()
{
	ofstream odaEkle("Oda.txt", ios::app);          //Oda dosyasına bilgi girmek için dosya açma
	system("cls");
	cout << "Oda numarasi:"; cin >> musteri.oda_no;       //kullanıcından kaydedilcek bilgiler isteme
	cout << "Oda ucreti:"; cin >> musteri.ucret;

	odaEkle << musteri.oda_no << "\t\t\t" << musteri.ucret << endl;
	odaEkle.close();          //dosya kapama
	system("cls");
}

void otel::oda_listele()
{
	ifstream odaListele("Oda.txt", ios::app);       //Oda dosyasını listelemek için dosya açma
	system("cls");
	cout << "ODA NUMARASI" << setw(20) << "ODA UCRETI\n     \n";
	while (!odaListele.eof())            //eof komutuyla dosyada sonuna ulaşıp ulaşmadığını kontrol etme
	{                                    //dosya sonuna ulaşmadıysa döngü kendini tekrar ediyor
		odaListele >> musteri.oda_no >> musteri.ucret;
		cout << setw(7) << musteri.oda_no << setw(15) << musteri.ucret << endl;
	}
	odaListele.close();   //dosya kapama
}

void otel::oda_sil(string numara)  //oda numarası için string değişkeniyle parametre oluşturuldu
{
	int f;          //uzunluk kıyaslamak için atanan değer
	string osil;
	string No;      //satır okuma işlemi için tanımlanan değer 
	ifstream odaListele;
	odaListele.open("Oda.txt");   //Oda dosyası açma
	system("cls");
	ofstream sil("Sil.txt");     //Sil dosyası oluşturma
	while (getline(odaListele, osil))   //getline odaListele de listelenen odaları sil değişkenine satır satır okuttu
	{
		if (numara.size() == 1) f = numara.size();       //Oda numarasının kaç basamaklı olduğu nu kontrol etme
		if (numara.size() == 2) f = numara.size() + 1;      //kaç basamaklı olduğunu f değişkenine atama
		if (numara.size() == 3) f = numara.size() + 2;
		No = osil.substr(0, f);                  //0'dan bulunan oda uzunluğu kadar satır okuma
		if (No != numara) sil << osil << endl;    //Oda numarasıyla okunan değer karşılaştırma
	}
	
	system("Pause");
	sil.close();     //sil dosyası kapama
	odaListele.close();   //odalisteleme kapama
	remove("Oda.txt");   //Oda dosyasındaki istenen kayıtı silme
	rename("Sil.txt", "Oda.txt");    //Sil dosyasının adı Oda dosyasıyla değiştirildi
}

void otel::musteriislemleri()          //Müşteri işlemleri menüsü altprogramı oluşturma
{
	system("cls");
	int secim2;

	cout << "1-Musteri Ekle" << endl;
	cout << "2-Musteri Sil" << endl;
	cout << "3-Musteri Listele" << endl;
	cout << "99-Ust Menu" << endl;
	cout << "Seciminiz:";
	cin >> secim2;

	switch (secim2)
	{
	case 1:musteri.musteri_ekle(); break;
	case 2: cout << "Kayidi Silinecek Musteri Numarasi:"; cin >> musteri.m_no;
		musteri.musteri_sil(musteri.m_no); break;
	case 3:musteri.musteri_listele(); break;
	case 99:break;
	default:
	{
		cout << "Hatali Secim" << endl;
		cout << "Devam etmek icin tiklayiniz...";
		_getch();
		system("cls");
	}
	}
}

void otel::musteri_ekle()
{
	ofstream musEkle("Musteriler.txt", ios::app);     //Musteriler dosyasına bilgi girmek için dosya açma
	system("cls");
	cout << "Musteri Numarasi:"; cin >> musteri.m_no;
	cout << "Musteri Ad:"; cin >> musteri.m_ad;           //istenilen bilgileri girme
	cout << "Musteri Soyad:"; cin >> musteri.m_soyad;
	cout << "TC Kimlik No:"; cin >> musteri.m_kimlik;
	musEkle << musteri.m_no << "\t" << musteri.m_ad << "   " << musteri.m_soyad << "\t" << musteri.m_kimlik << endl;
	musEkle.close();  //dosya kapama
	system("cls");
}

void otel::musteri_listele()
{
	ifstream musteriListele("Musteriler.txt", ios::app);            //Musteriler dosyasını listelemek için dosya açma
	system("cls");
	cout << setw(3) << "MUSTERI NUMARASI" << setw(15) << "MUSTERI ADI " << setw(15) << " MUSTERI SOYADI" << setw(15) << "TC KIMLIK NO" << endl;
	while (!musteriListele.eof())
	{
		musteriListele >> musteri.m_no >> musteri.m_ad >> musteri.m_soyad >> musteri.m_kimlik;
		cout << setw(7) << musteri.m_no << setw(19) << musteri.m_ad << setw(15) << musteri.m_soyad << setw(15) << musteri.m_kimlik << endl;
	}
	musteriListele.close();     //dosya kapama
}

void otel::musteri_sil(string numara)
{
	int f;
	string No;
	string osil;
	ifstream musteriListele;
	musteriListele.open("Musteriler.txt");
	system("cls");
	ofstream sil("Sil.txt");
	while (getline(musteriListele, osil))
	{
		if (numara.size() == 1) f = numara.size();
		if (numara.size() == 2) f = numara.size() + 1;
		if (numara.size() == 3) f = numara.size() + 2;
		No = osil.substr(0, f);
		if (No != numara) sil << osil << endl;
	}
	system("Pause");
	sil.close();
	musteriListele.close();
	remove("Musteriler.txt");
	rename("Sil.txt", "Musteriler.txt");
}

void otel::oda_kayit()
{
	system("cls");
	int secim3;
	cout << "<<< ODA KAYIT >>>" << endl;
	cout << "1-Oda Kayit Ekle" << endl;
	cout << "2-Oda Kayit Sil" << endl;
	cout << "3-Oda Kayit Listele" << endl;
	cout << "99-Ust Menu" << endl;
	cout << "Seciminiz:";
	cin >> secim3;

	switch (secim3)
	{
	case 1: musteri.odakayit_ekle(); break;
	case 2: cout << "Silinecek Oda Kayit Numarasi:"; cin >> musteri.odakayit_no;
		musteri.odakayit_sil(musteri.odakayit_no); break;
	case 3: musteri.odakayit_listele(); break;
	case 99:anamenu(); break;
	default:
	{
		cout << "Hatali Secim" << endl;
		cout << "Devam etmek icin tiklayiniz...";
		_getch();
		system("cls"); }
	}
}

void otel::odakayit_ekle()
{
	ofstream okayitEkle("Odakayit.txt", ios::app);
	system("cls");
	cout << "Oda Kayit Numarasi:"; cin >> musteri.odakayit_no;
	cout << "Lutfen musteri atanacak oda numarasini girin:"; cin >> musteri.o_no;
	cout << "Lutfen atama yapilacak musterinin numarasini girin:"; cin >> musteri.mus_no;

	okayitEkle << musteri.odakayit_no << "\t" << musteri.o_no << "\t" << musteri.mus_no << endl;
	okayitEkle.close();
	system("cls");
}

void otel::odakayit_listele()
{
	ifstream okayitListele("Odakayit.txt", ios::in || ios::app);
	system("cls");
	cout << "ODA KAYIT NUMARASI " << setw(18) << "ODA NUMARASI" << setw(30) << "MUSTERI NUMARASI\n     \n";
	cout << "------------------" << setw(21) << "---------------" << setw(21) << "----------------" << endl;
	while (!okayitListele.eof())
	{
		okayitListele >> musteri.odakayit_no >> musteri.o_no >> musteri.mus_no;
		cout << setw(7) << musteri.odakayit_no << setw(25) << musteri.o_no << setw(21) << musteri.mus_no << endl;
	}
	okayitListele.close();
}

void otel::odakayit_sil(string numara)
{
	int f;
	string No;
	string osil;
	ifstream okayitListele;
	okayitListele.open("Odakayit.txt");
	system("cls");
	ofstream sil("Sil.txt");
	while (getline(okayitListele, osil))
	{
		if (numara.size() == 1) f = numara.size();
		if (numara.size() == 2) f = numara.size() + 1;
		if (numara.size() == 3) f = numara.size() + 2;
		No = osil.substr(0, f);
		if (No != numara) sil << osil << endl;
	}
	system("pause");
	sil.close();
	okayitListele.close();
	remove("Odakayit.txt");
	rename("Sil.txt", "Odakayit.txt");
}

int main()
{
	musteri.anamenu();    //musteri nesnesinden anamenu alt programını çağırma
	system("pause");
	return 0;
}




