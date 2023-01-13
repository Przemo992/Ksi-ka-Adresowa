#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <array>
#include <vector>
#include <sstream>


using namespace std;

struct Osoba {

    int id = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", eMail = "", adresZamieszkania = "";
};
string wczytajLinie();
void zapisywanieOsobyDoPliku(vector <Osoba>& osoby, int iloscOsob);
int zapisNowejOsoby(vector <Osoba>& osoby, int iloscOsob);
void wyszukiwaniePoImieniu(vector <Osoba>& osoby, string dane, int iloscOsob);
void wyszukiwaniePoNazwisku(vector <Osoba>& osoby, string dane, int iloscOsob);
void wyszukajOsobe(vector <Osoba>& osoby, int iloscOsob);
void wyswietlWszystkichAdresatow(vector <Osoba>& osoby, int iloscOsob);
int wczytanieDanychzPliku (vector <Osoba>& osoby);
int usunAdresata(vector <Osoba>& osoby, int iloscOsob);
void aktualizujPoUsusnieciu (vector <Osoba>& osoby, int iloscOsob);
void edytujAdresata(vector <Osoba>& osoby, int iloscOsob);
int wyszukiwaniePoId(vector <Osoba>& osoby, int id, int iloscOsob);


int main() {

    vector <Osoba> osoby;
    int iloscOsob = wczytanieDanychzPliku(osoby);
    char wybor;

    for(;;) {
        system("cls");
        cout << "Witaj w Menu Ksiazki Adresowej" << endl << endl;
        cout << "Wybierz opcje z Menu" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Zapisanie nowej osoby." << endl;
        cout << "2. Wyszukaj osobe." << endl;
        cout << "3. Wyswietl wszystkie osoby zapisane w ksiazce adresowej." << endl;
        cout << "4. Usun Osobe." << endl;
        cout << "5. Edytuj Adresata." << endl;
        cout << "9. Zamknij program." << endl;
        cout << "----------------------------------------" << endl;
        wybor = getch();

        switch(wybor) {
        case '1':
            iloscOsob = zapisNowejOsoby(osoby, iloscOsob);
            break;
        case '2':
            wyszukajOsobe(osoby, iloscOsob);
            break;
        case '3':
            wyswietlWszystkichAdresatow(osoby, iloscOsob);
            break;
        case '4':
            iloscOsob = usunAdresata(osoby, iloscOsob);
            break;
        case '5':
            edytujAdresata(osoby, iloscOsob);
            break;
        case '9':
            exit (0);
        }
    }
}

string wczytajLinie() {

    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}
void zapisywanieOsobyDoPliku(vector <Osoba>& osoby, int iloscOsob) {

    string imie, nazwisko, nrTelefonu, eMail, adresZamieszkania;
    fstream plik;

    plik.open("wizytowki.txt", ios::out | ios::app);

    plik << osoby[iloscOsob].id << '|';
    plik << osoby[iloscOsob].imie << '|';
    plik << osoby[iloscOsob].nazwisko << '|';
    plik << osoby[iloscOsob].nrTelefonu << '|';
    plik << osoby[iloscOsob].eMail << '|';
    plik << osoby[iloscOsob].adresZamieszkania << '|'<<endl;
    plik.close();
}
int zapisNowejOsoby(vector <Osoba>& osoby, int iloscOsob) {

    string imie, nazwisko, nrTelefonu, eMail, adresZamieszkania;
    cout << "Prosze o podanie danych osoby do zapisania:\n";
    cout << "Podaj Imie: ";
    imie = wczytajLinie();
    cout << "\nPodaj Nazwisko: ";
    nazwisko = wczytajLinie();
    int i = 0;
    while (i < iloscOsob) {
        if ((osoby[i].imie == imie) && (osoby[i].nazwisko == nazwisko)) {
            cout << "Taka osoba juz jest w bazie.\n";
            cout << "\nId osoby:           " << osoby[i].id;
            cout << "\nImie:               " << osoby[i].imie;
            cout << "\nNazwisko:           " << osoby[i].nazwisko;
            cout << "\nNr telefonu:        " << osoby[i].nrTelefonu;
            cout << "\neMail:              " << osoby[i].eMail;
            cout << "\nAdres zamieszkania: " << osoby[i].adresZamieszkania << endl;
            system("Pause");
            return iloscOsob;
        } else {
            i++;
        }
    }
    cout << "\nPodaj nr telefonu: ";
    nrTelefonu = wczytajLinie();
    cout << "\nPodaj adres email: ";
    eMail = wczytajLinie();
    cout << "\nPodaj adres zamieszkania: ";
    adresZamieszkania = wczytajLinie();

    Osoba osobaTemp;
    osobaTemp.imie = imie;
    osobaTemp.nazwisko = nazwisko;
    osobaTemp.nrTelefonu = nrTelefonu;
    osobaTemp.eMail = eMail;
    osobaTemp.adresZamieszkania = adresZamieszkania;
    if(osoby.size() == 0){osobaTemp.id = 1;
    }
    else {osobaTemp.id = osoby[osoby.size() - 1].id + 1;
    }
    osoby.push_back(osobaTemp);
    zapisywanieOsobyDoPliku(osoby, iloscOsob);

    cout << "\nDodano kontakt do ksiazki adresowej";

    Sleep(1000);
    return iloscOsob + 1;
}
void wyszukiwaniePoImieniu(vector <Osoba>& osoby, string dane, int iloscOsob) {
    int i = 0, osoba = 0;
    while (i < iloscOsob) {
        if (osoby[i].imie == dane) {
            cout << endl << "Id osoby:           " << osoby[i].id;
            cout << endl << "Imie:               " << osoby[i].imie;
            cout << endl << "Nazwisko:           " << osoby[i].nazwisko;
            cout << endl << "Nr telefonu:        " << osoby[i].nrTelefonu;
            cout << endl << "eMail:              " << osoby[i].eMail;
            cout << endl << "Adres zamieszkania: " << osoby[i].adresZamieszkania << endl;
            osoba++;
        }
        i++;
    }
    if (osoba == 0) cout << "Nie ma takiej osoby w bazie! " << endl << endl;
system("Pause");
}
void wyszukiwaniePoNazwisku(vector <Osoba>& osoby, string dane, int iloscOsob) {

    int i = 0, osoba = 0;
    while (i < iloscOsob) {
        if (osoby[i].nazwisko == dane) {
            cout <<endl << "Id osoby:           " << osoby[i].id;
            cout <<endl << "Imie:               " << osoby[i].imie;
            cout <<endl << "Nazwisko:           " << osoby[i].nazwisko;
            cout <<endl << "Nr telefonu:        " << osoby[i].nrTelefonu;
            cout <<endl << "eMail:              " << osoby[i].eMail;
            cout <<endl << "Adres zamieszkania: " << osoby[i].adresZamieszkania << endl;
            osoba++;
        }
        i++;
    }
    if (osoba == 0) cout << "Nie ma takiej osoby w bazie! " << endl << endl;
system("Pause");
}
void wyszukajOsobe(vector <Osoba>& osoby, int iloscOsob) {

    char wybor;
    string imie, nazwisko;

    for(;;) {
        system("cls");
        cout << "Po jakiej danej chcesz wyszukac: " << endl << endl ;
        cout << "1. Wyszukaj po imieniu." << endl;
        cout << "2. Wyszukaj po nazwisku." << endl;
        cout << "3. Powrot do menu glownego" << endl << endl;
        cout << "Wybor: ";
        wybor = getch();
        if (wybor == '3') break;
        switch(wybor) {
        case '1':
            cout << endl << "Podaj imie: ";
            imie = wczytajLinie();
            wyszukiwaniePoImieniu(osoby, imie, iloscOsob);
            break;

        case '2':
            cout << endl << "Podaj nazwisko: ";
            nazwisko = wczytajLinie();
            wyszukiwaniePoNazwisku(osoby, nazwisko, iloscOsob);
            break;;
        default:
            cout << endl << "Bledny wybor"<<endl;
            system("Pause");
        }
    }
}
void wyswietlWszystkichAdresatow(vector <Osoba>& osoby, int iloscOsob) {

    if(iloscOsob == 0) cout << "Ksiazka adresowa jest pusta"<<endl;

    for (int i = 0; i < iloscOsob; i++) {
        cout << "Id osoby:           " <<osoby[i].id << endl;
        cout << "Imie:               " <<osoby[i].imie << endl;
        cout << "Nazwisko:           " <<osoby[i].nazwisko << endl;
        cout << "Nr telefonu:        " <<osoby[i].nrTelefonu << endl;
        cout << "eMail:              " <<osoby[i].eMail << endl;
        cout << "Adres zamieszkania: " <<osoby[i].adresZamieszkania << endl << endl;
    }
    system("Pause");

}
int wczytanieDanychzPliku (vector <Osoba>& osoby){
    Osoba osobyTemp;
    string daneOsoby{};
    fstream plik;
    plik.open("wizytowki.txt",ios::out | ios::in | ios::app);
    int pozycjaDanychOsoby;
    int iloscOsob = 0;
    if (plik.good())
    {
        while(getline(plik,daneOsoby))
        {
            string danePojedynczejOsoby{};
            pozycjaDanychOsoby = 1;

            for (size_t i{}; i < daneOsoby.length(); ++i)
            {
                if (daneOsoby[i] != '|')
                {
                    danePojedynczejOsoby += daneOsoby[i];
                }
                else
                {
                    switch(pozycjaDanychOsoby)
                    {
                    case 1:
                        osobyTemp.id = atoi(danePojedynczejOsoby.c_str());
                        break;
                    case 2:
                        osobyTemp.imie = danePojedynczejOsoby;
                        break;
                    case 3:
                        osobyTemp.nazwisko = danePojedynczejOsoby;
                        break;
                    case 4:
                        osobyTemp.nrTelefonu = danePojedynczejOsoby;
                        break;
                    case 5:
                        osobyTemp.eMail = danePojedynczejOsoby;
                        break;
                    case 6:
                        osobyTemp.adresZamieszkania = danePojedynczejOsoby;
                        break;
                    }
                    danePojedynczejOsoby = "";
                    pozycjaDanychOsoby ++;
                }
            }
            osoby.push_back(osobyTemp);
            iloscOsob++;
        }
    }
    plik.close();
    return iloscOsob;
}
int usunAdresata(vector <Osoba>& osoby, int iloscOsob){

int idDoUsuniecia;

    cout << "Podaj ID adresata do usuniecia: ";
    cin >> idDoUsuniecia;
char potwierdzenieUsuniecia;
    int i = 0, osoba = 0;
    while (i < iloscOsob) {
        if (osoby[i].id == idDoUsuniecia) {
            cout << "Czy na pewno chcesz usunac tego adresata? Jesli tak, kliknij t: \n";
            wyszukiwaniePoId(osoby, idDoUsuniecia, iloscOsob);
            potwierdzenieUsuniecia = getch();

            if (potwierdzenieUsuniecia == 't') {
                osoby.erase(osoby.begin() + i);
                cout << "\nAdresat o ID " << idDoUsuniecia << " zostal usuniety.\n";
                osoba++;

            }else {
            cout << "\nAdresat o ID " << idDoUsuniecia << " nie zostal usuniety.\n";
            system("Pause");
            return iloscOsob;
            }
        }
        i++;
    }
    if (osoba == 0) cout << "Nie ma takiego ID w bazie! \n\n";
    system("Pause");
    aktualizujPoUsusnieciu(osoby, iloscOsob - osoba);
    return iloscOsob - osoba;
}
void aktualizujPoUsusnieciu (vector <Osoba>& osoby, int iloscOsob) {
remove( "wizytowki.txt" );

for (int i = 0; i < iloscOsob; i++){
zapisywanieOsobyDoPliku(osoby, i);
}
}
int wyszukiwaniePoId(vector <Osoba>& osoby, int id, int iloscOsob) {
    int i = 0, osoba = 0;
    while (i < iloscOsob) {
        if (osoby[i].id == id) {
            cout << endl << "Id osoby:           " << osoby[i].id;
            cout << endl << "Imie:               " << osoby[i].imie;
            cout << endl << "Nazwisko:           " << osoby[i].nazwisko;
            cout << endl << "Nr telefonu:        " << osoby[i].nrTelefonu;
            cout << endl << "eMail:              " << osoby[i].eMail;
            cout << endl << "Adres zamieszkania: " << osoby[i].adresZamieszkania << endl;
            osoba++;
            //system("Pause");
            return i;
        }
        i++;
    }
    if (osoba == 0) cout << "Nie ma takiej osoby w bazie! " << endl << endl;
    system("Pause");
return -1 ;
}
void edytujAdresata(vector <Osoba>& osoby, int iloscOsob) {

    int idDoEdycji;
    char wybor;

    cout << "Podaj ID adresata ktorego chcesz edytowac: ";
    cin >> idDoEdycji;
    int nrAdresata = wyszukiwaniePoId(osoby, idDoEdycji, iloscOsob);
    if (nrAdresata == -1) return;
    system("Pause");

    for(;;) {
        system("cls");
        cout << "Jakie dane chcesz edytowac: \n\n";
        cout << "1. Imie.\n";
        cout << "2. Nazwisko.\n";
        cout << "3. Nr Telefonu.\n";
        cout << "4. eMail.\n";
        cout << "5. Adres Zamieszkania.\n";
        cout << "6. Powrot do menu glownego\n\n";
        cout << "Wybor: ";
        wybor = getch();
        if (wybor == '6') break;
        switch(wybor) {
        case '1': {
            cout << "\nPodaj nowe imie: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].imie = nowaDana;
            aktualizujPoUsusnieciu(osoby, iloscOsob);
            cout << "Zmieniono Imie na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '2': {
            cout << "\nPodaj nowe nazwisko: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].nazwisko = nowaDana;
            aktualizujPoUsusnieciu(osoby, iloscOsob);
            cout << "Zmieniono Nazwisko na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '3': {
            cout << "\nPodaj nowy nr Telefonu: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].nrTelefonu = nowaDana;
            aktualizujPoUsusnieciu(osoby, iloscOsob);
            cout << "Zmieniono nr Telefonu na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '4': {
            cout << "\nPodaj nowy adres eMail: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].eMail = nowaDana;
            aktualizujPoUsusnieciu(osoby, iloscOsob);
            cout << "Zmieniono adres eMail na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '5': {
            cout << "\nPodaj nowy adres Zamieszkania: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].adresZamieszkania = nowaDana;
            aktualizujPoUsusnieciu(osoby, iloscOsob);
            cout << "Zmieniono adres Zamieszkania na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }

        default:
            cout << "\nBledny wybor\n";
            system("Pause");
        }
    }
}
