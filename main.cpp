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

    int id = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", eMail = "", adresZamieszkania = "";
};
struct Uzytkownik {

    int id = 0;
    string login = "", haslo = "";
};
string wczytajLinie();
//-------------KSIAZKA ADRESOWA-------------------
void zapisywanieOsobyDoPliku(vector <Osoba>& osoby, int nrOsoby);
void zapisywanieOsobyDoPlikuPoEdycji(vector <Osoba>& osoby, int nrOsoby);
int zapisNowejOsoby(vector <Osoba>& osoby, int idUzytkownika);
void wyszukiwaniePoImieniu(vector <Osoba>& osoby, string dane);
void wyszukiwaniePoNazwisku(vector <Osoba>& osoby, string dane);
void wyszukajOsobe(vector <Osoba>& osoby);
void wyswietlWszystkichAdresatow(vector <Osoba>& osoby);
int wczytanieDanychzPliku (vector <Osoba>& osoby);
void usunAdresata(vector <Osoba>& osoby);
void aktualizujPoUsusnieciu (int idAdresataDoUsuniecia);
void edytujAdresata(vector <Osoba>& osoby, int iloscOsob);
void aktualizujPoEdycji (vector <Osoba>& osoby, int nrAdresata);
int wyszukiwaniePoId(vector <Osoba>& osoby, int id, int iloscOsob);
void menuKsiazkiAdresowej(int idUzytkownika, vector <Uzytkownik>& uzytkownicy);
int liczenieLiniTekstuPliku();
int podanieIdOstatniegoAdresata();
//-------------LOGOWANIE UZYTKOWNIKOW--------------
string zakrywanieHasla();
void logowanie(vector <Uzytkownik>& uzytkownicy);
void zapisywanieUzytkownikaDoPliku(vector <Uzytkownik>& uzytkownicy, int nrUzytkownika);
void rejestrowanieNowejOsoby(vector <Uzytkownik>& uzytkownicy);
void wczytanieUzytkownikowzPliku (vector <Uzytkownik>& uzytkownicy);
void menuLogowania();
void aktualizujUzytkownikowPoZmianieHasla(vector <Uzytkownik>& uzytkownicy);
void zmianaHasla(int idUzytkownia, vector <Uzytkownik>& uzytkownicy);

int main() {

    menuLogowania();

}

//-------------KSIAZKA ADRESOWA-------------------
string wczytajLinie() {

    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}
void zapisywanieOsobyDoPliku(vector <Osoba>& osoby, int nrOsoby) {

    string imie, nazwisko, nrTelefonu, eMail, adresZamieszkania;
    fstream plik;

    plik.open("wizytowki.txt", ios::out | ios::app);

    plik << osoby[nrOsoby].id << '|';
    plik << osoby[nrOsoby].idUzytkownika << '|';
    plik << osoby[nrOsoby].imie << '|';
    plik << osoby[nrOsoby].nazwisko << '|';
    plik << osoby[nrOsoby].nrTelefonu << '|';
    plik << osoby[nrOsoby].eMail << '|';
    plik << osoby[nrOsoby].adresZamieszkania << '|'<<endl;

    plik.close();
}
void zapisywanieOsobyDoPlikuPoEdycji(vector <Osoba>& osoby, int nrOsoby) {

    string imie, nazwisko, nrTelefonu, eMail, adresZamieszkania;
    fstream plik;

    plik.open("wizytowkiTemp2.txt", ios::out | ios::app);

    plik << osoby[nrOsoby].id << '|';
    plik << osoby[nrOsoby].idUzytkownika << '|';
    plik << osoby[nrOsoby].imie << '|';
    plik << osoby[nrOsoby].nazwisko << '|';
    plik << osoby[nrOsoby].nrTelefonu << '|';
    plik << osoby[nrOsoby].eMail << '|';
    plik << osoby[nrOsoby].adresZamieszkania << '|'<<endl;

    plik.close();
}
int zapisNowejOsoby(vector <Osoba>& osoby, int idUzytkownika) {

    int iloscOsob = osoby.size();
    int liczbaAdresatow = liczenieLiniTekstuPliku();
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
    osobaTemp.idUzytkownika = idUzytkownika;

    if(liczbaAdresatow == 0) {
        osobaTemp.id = 1;
    } else {
        osobaTemp.id = podanieIdOstatniegoAdresata() + 1;
    }

    osoby.push_back(osobaTemp);
    zapisywanieOsobyDoPliku(osoby, iloscOsob);

    cout << "\nDodano kontakt do ksiazki adresowej";

    Sleep(1000);
    return iloscOsob + 1;
}
void wyszukiwaniePoImieniu(vector <Osoba>& osoby, string dane) {

    int iloscOsob = osoby.size();

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
void wyszukiwaniePoNazwisku(vector <Osoba>& osoby, string dane) {

    int iloscOsob = osoby.size();
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
void wyszukajOsobe(vector <Osoba>& osoby) {

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
            wyszukiwaniePoImieniu(osoby, imie);
            break;

        case '2':
            cout << endl << "Podaj nazwisko: ";
            nazwisko = wczytajLinie();
            wyszukiwaniePoNazwisku(osoby, nazwisko);
            break;;
        default:
            cout << endl << "Bledny wybor"<<endl;
            system("Pause");
        }
    }
}
void wyswietlWszystkichAdresatow(vector <Osoba>& osoby) {

    int iloscOsob = osoby.size();

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
int wczytanieDanychzPliku (vector <Osoba>& osoby, int idUzytkownika) {

    int iloscOsob = 0;
    string daneOsoby{};
    fstream plik;

    Osoba osobyTemp;

    plik.open("wizytowki.txt",ios::out | ios::in | ios::app);

    if (plik.good()) {
        while(getline(plik,daneOsoby)) {
            string danePojedynczejOsoby{};
            int pozycjaDanychOsoby = 1;

            for (size_t i{}; i < daneOsoby.length(); ++i) {
                if (daneOsoby[i] != '|') {
                    danePojedynczejOsoby += daneOsoby[i];
                } else {
                    switch(pozycjaDanychOsoby) {
                    case 1:
                        osobyTemp.id = atoi(danePojedynczejOsoby.c_str());
                        break;
                    case 2:
                        osobyTemp.idUzytkownika = atoi(danePojedynczejOsoby.c_str());
                        break;
                    case 3:
                        osobyTemp.imie = danePojedynczejOsoby;
                        break;
                    case 4:
                        osobyTemp.nazwisko = danePojedynczejOsoby;
                        break;
                    case 5:
                        osobyTemp.nrTelefonu = danePojedynczejOsoby;
                        break;
                    case 6:
                        osobyTemp.eMail = danePojedynczejOsoby;
                        break;
                    case 7:
                        osobyTemp.adresZamieszkania = danePojedynczejOsoby;
                        break;
                    }
                    danePojedynczejOsoby = "";
                    pozycjaDanychOsoby ++;
                }
            }

            if (osobyTemp.idUzytkownika == idUzytkownika) {
                osoby.push_back(osobyTemp);
                iloscOsob++;
            }
        }
    }
    plik.close();

    return iloscOsob;
}
void usunAdresata(vector <Osoba>& osoby) {

    int idDoUsuniecia;
    int iloscOsob = osoby.size();

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
                aktualizujPoUsusnieciu(idDoUsuniecia);
                osoba++;
            } else {
                cout << "\nAdresat o ID " << idDoUsuniecia << " nie zostal usuniety.\n";
                system("Pause");
                return;
            }
        }
        i++;
    }
    if (osoba == 0) cout << "Nie ma takiego ID w bazie! \n\n";
    system("Pause");
}
void aktualizujPoUsusnieciu (int idAdresataDoUsuniecia) {

    fstream plik, plikTemp;
    string linia, liniaTemp;
    int idAdresata;

    plik.open("wizytowki.txt", ios::in);
    plikTemp.open("wizytowkiTemp.txt", ios::out);

    while(getline(plik, linia)) {
        idAdresata = atoi(linia.c_str());
        if (idAdresata == idAdresataDoUsuniecia) continue;
        else plikTemp << linia << endl;
    }

    plik.close();
    plikTemp.close();

    remove( "wizytowki.txt" );
    rename ("wizytowkiTemp.txt", "wizytowki.txt");
    remove ("wizytowkiTemp.txt");
}
void aktualizujPoEdycji (vector <Osoba>& osoby, int nrAdresata) {

    zapisywanieOsobyDoPlikuPoEdycji(osoby, nrAdresata);

    fstream plik, plikTemp, plikTemp2;
    string linia, liniaTemp2;
    int idAdresata, idAdresataTemp;

    idAdresataTemp = osoby[nrAdresata].id;

    plik.open("wizytowki.txt", ios::in);
    plikTemp.open("wizytowkiTemp.txt", ios::out);
    plikTemp2.open("wizytowkiTemp2.txt", ios::in);

    getline(plikTemp2, liniaTemp2);

    while(getline(plik, linia)) {
        idAdresata = atoi(linia.c_str());
        if (idAdresata == idAdresataTemp) plikTemp << liniaTemp2 << endl;
        else plikTemp << linia << endl;
    }

    plik.close();
    plikTemp.close();
    plikTemp2.close();

    remove( "wizytowki.txt" );
    remove ("wizytowkiTemp2.txt");
    rename ("wizytowkiTemp.txt", "wizytowki.txt");
    remove ("wizytowkiTemp.txt");

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
            aktualizujPoEdycji(osoby, nrAdresata);
            cout << "Zmieniono Imie na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '2': {
            cout << "\nPodaj nowe nazwisko: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].nazwisko = nowaDana;
            aktualizujPoEdycji(osoby, nrAdresata);
            cout << "Zmieniono Nazwisko na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '3': {
            cout << "\nPodaj nowy nr Telefonu: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].nrTelefonu = nowaDana;
            aktualizujPoEdycji(osoby, nrAdresata);
            cout << "Zmieniono nr Telefonu na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '4': {
            cout << "\nPodaj nowy adres eMail: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].eMail = nowaDana;
            aktualizujPoEdycji(osoby, nrAdresata);
            cout << "Zmieniono adres eMail na: " << nowaDana << " !";
            Sleep(1500);
            break;
        }
        case '5': {
            cout << "\nPodaj nowy adres Zamieszkania: ";
            string nowaDana = wczytajLinie();
            osoby[nrAdresata].adresZamieszkania = nowaDana;
            aktualizujPoEdycji(osoby, nrAdresata);
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
void menuKsiazkiAdresowej(int idUzytkownika, vector <Uzytkownik>& uzytkownicy) {

    vector <Osoba> osoby;
    int iloscOsob = wczytanieDanychzPliku(osoby, idUzytkownika);
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
        cout << "6. Zmien haslo." << endl;
        cout << "7. Wyloguj sie." << endl;
        cout << "9. Zamknij program." << endl;
        cout << "----------------------------------------" << endl;
        wybor = getch();

        switch(wybor) {
        case '1':
            iloscOsob = zapisNowejOsoby(osoby, idUzytkownika);
            break;
        case '2':
            wyszukajOsobe(osoby);
            break;
        case '3':
            wyswietlWszystkichAdresatow(osoby);
            break;
        case '4':
            usunAdresata(osoby);
            break;
        case '5':
            edytujAdresata(osoby, iloscOsob);
            break;
        case '6':
            zmianaHasla(idUzytkownika, uzytkownicy);
            break;
        case '7':
            menuLogowania();
            break;
        case '9':
            exit (0);
        }
    }
}
int liczenieLiniTekstuPliku() {

    string line;
    int count = 0;

    ifstream f("wizytowki.txt");

    while(getline(f, line))
        count++;

    return count;
}
int podanieIdOstatniegoAdresata() {

    int liczba = liczenieLiniTekstuPliku();
    fstream plik;
    string linia;

    plik.open("wizytowki.txt", ios::in);

    for(int i = 0; i < liczba-1; ++i) {
        getline(plik, linia);
    }

    getline(plik, linia, '|');

    int idOstatniegoAdresata = atoi(linia.c_str());

    plik.close();

    return idOstatniegoAdresata;

}
//-------------LOGOWANIE UZYTKOWNIKOW--------------
string zakrywanieHasla() {

    constexpr char c_enter  = 13;
    constexpr char c_backspace = 8;

    string passwd;
    char input_character;

    input_character = getch();

    while(input_character != c_enter) {

        if(input_character == c_backspace && passwd.size()) {
            cout << "\b \b";
            passwd.pop_back();
        } else if(input_character != c_backspace) {
            cout.put('*');
            passwd += input_character;
        }

        input_character = getch();
    }
    return passwd;
}
void logowanie(vector <Uzytkownik>& uzytkownicy) {

    string login, haslo;
    int iloscOsob = uzytkownicy.size();

    if(iloscOsob == 0) {
        cout << "Brak Zarejestrowanych Uzytkownikow"<<endl;
        system("Pause");
        return;
    }

    cout << "Podaj Login: ";
    cin >> login;
    cout << "\nPodaj Haslo: ";
    haslo = zakrywanieHasla();

    auto i = 0;
    while (i <= iloscOsob) {
        if ((uzytkownicy[i].login == login) && (uzytkownicy[i].haslo == haslo)) {
            cout << "\nPoprawnie Zalogowano!\n";
            system("Pause");
            menuKsiazkiAdresowej(uzytkownicy[i].id, uzytkownicy);
        } else {
            i++;
        }
        if ( i == iloscOsob) {
            cout << "Podano bledne dane!\n";
            system("Pause");
        }
    }

}
void zapisywanieUzytkownikaDoPliku(vector <Uzytkownik>& uzytkownicy, int nrUzytkownika) {

    string login, haslo;
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    plik << uzytkownicy[nrUzytkownika].id << '|';
    plik << uzytkownicy[nrUzytkownika].login << '|';
    plik << uzytkownicy[nrUzytkownika].haslo << '|' << endl;

    plik.close();
}
void rejestrowanieNowejOsoby(vector <Uzytkownik>& uzytkownicy) {

    int iloscOsob = uzytkownicy.size();
    string login, haslo;

    cout << "Prosze o podanie danych osoby do zarejestrowania nowego uzytkownika:\n";
    cout << "Podaj Login: ";
    login = wczytajLinie();

    int i = 0;
    while (i < iloscOsob) {
        if (uzytkownicy[i].login == login)  {
            cout << "Taka osoba juz jest w bazie.\n";
            system("Pause");
            return;
        } else {
            i++;
        }
    }

    cout << "\nPodaj haslo: ";
    haslo = zakrywanieHasla();

    Uzytkownik uzytkownikTemp;

    uzytkownikTemp.login = login;
    uzytkownikTemp.haslo = haslo;

    if(uzytkownicy.size() == 0) {
        uzytkownikTemp.id = 1;
    } else {
        uzytkownikTemp.id = uzytkownicy[uzytkownicy.size() - 1].id + 1;
    }

    uzytkownicy.push_back(uzytkownikTemp);

    zapisywanieUzytkownikaDoPliku(uzytkownicy, iloscOsob);

    cout << "\nDodano Uzytkownika";

    Sleep(1000);

}
void wczytanieUzytkownikowzPliku (vector <Uzytkownik>& uzytkownicy) {

    string daneUzytkownika{};
    fstream plik;
    int pozycjaDanychUzytkownika;
    int iloscOsob = 0;

    Uzytkownik uzytkownicyTemp;

    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good()) {
        while(getline(plik,daneUzytkownika)) {
            string danePojedynczegoUzytkownika{};
            pozycjaDanychUzytkownika = 1;

            for (size_t i{}; i < daneUzytkownika.length(); ++i) {
                if (daneUzytkownika[i] != '|') {
                    danePojedynczegoUzytkownika += daneUzytkownika[i];
                } else {
                    switch(pozycjaDanychUzytkownika) {
                    case 1:
                        uzytkownicyTemp.id = atoi(danePojedynczegoUzytkownika.c_str());
                        break;
                    case 2:
                        uzytkownicyTemp.login = danePojedynczegoUzytkownika;
                        break;
                    case 3:
                        uzytkownicyTemp.haslo = danePojedynczegoUzytkownika;
                        break;
                    }
                    danePojedynczegoUzytkownika = "";
                    pozycjaDanychUzytkownika ++;
                }
            }
            uzytkownicy.push_back(uzytkownicyTemp);
            iloscOsob++;
        }
    }
    plik.close();
}
void menuLogowania() {

    vector <Uzytkownik> uzytkownicy;

    wczytanieUzytkownikowzPliku(uzytkownicy);

    char wybor;

    for(;;) {
        system("cls");
        cout << "Witaj w Menu Ksiazki Adresowej" << endl << endl;
        cout << "Wybierz opcje z Menu" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Zaloguj." << endl;
        cout << "2. Zarejestruj sie." << endl;
        cout << "9. Zamknij program." << endl;
        cout << "----------------------------------------" << endl;

        wybor = getch();

        switch(wybor) {
        case '1':
            logowanie(uzytkownicy);
            break;
        case '2':
            rejestrowanieNowejOsoby(uzytkownicy);
            break;
        case '9':
            exit (0);
        }
    }
}
void aktualizujUzytkownikowPoZmianieHasla(vector <Uzytkownik>& uzytkownicy) {

    int iloscOsob = uzytkownicy.size();

    remove( "Uzytkownicy.txt" );

    for (int i = 0; i < iloscOsob; i++) {
        zapisywanieUzytkownikaDoPliku(uzytkownicy, i);
    }
}
void zmianaHasla(int idUzytkownia, vector <Uzytkownik>& uzytkownicy) {

    string noweHaslo;

    cout << "Podaj Nowe Haslo: ";
    noweHaslo = zakrywanieHasla();
    uzytkownicy[idUzytkownia - 1].haslo = noweHaslo;

    cout << "\nZmieniono Haslo!\n";
    system("Pause");

    aktualizujUzytkownikowPoZmianieHasla(uzytkownicy);
}
