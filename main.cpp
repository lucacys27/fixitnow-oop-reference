#include <iostream>
#include <limits>
#include "ServiceManager.h"
#include "Tehnician.h"
#include "Receptioner.h"
#include "Supervizor.h"
#include "Data.h"
#include "ValidatorCNP.h"
#include "Frigider.h"
#include "Televizor.h"
#include "MasinaSpalat.h"

using namespace std;

void curataBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void meniuAngajati(ServiceManager *manager)
{
    int optiune = -1;
    while (optiune != 0)
    {
        cout << "\nGestiune Angajati" << endl;
        cout << "Press 1 Adaugare Angajat Manual" << endl;
        cout << "Press 2 Stergere Angajat (Demisie)" << endl;
        cout << "Press 3 Modificare Nume Angajat" << endl;
        cout << "Press 4 Incarca Angajati" << endl;
        cout << "Press 5 Afisare Toti Angajatii" << endl;
        cout << "Press 6 Cautare Angajat dupa CNP" << endl;
        cout << "Press 0 Inapoi la Meniul Principal" << endl;
        cout << "Optiunea aleasa: ";

        if (!(cin >> optiune))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (optiune == 1)
        {
            cout << "Angajare Personala Noua" << endl;
            int tipAngajat;
            cout << "Functie (1-Tehnician, 2-Receptioner, 3-Supervizor): ";
            if (!(cin >> tipAngajat))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Trebuie numar!" << endl;
                continue;
            }
            if (tipAngajat < 1 || tipAngajat > 3)
            {
                cout << "Optiune invalida!" << endl;
                continue;
            }

            int id;
            cout << "ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "ID invalid!" << endl;
                continue;
            }
            if (manager->getAngajatDupaId(id) != nullptr)
            {
                cout << "ID deja existent!" << endl;
                continue;
            }

            string nume, prenume, cnp, oras;
            cout << "Nume: ";
            cin >> nume;
            cout << "Prenume: ";
            cin >> prenume;
            cout << "CNP: ";
            cin >> cnp;

            if (!ValidatorCNP::eCNPValid(cnp))
            {
                cout << "CNP Invalid!" << endl;
                continue;
            }

            int zi, luna, an;
            cout << "Data Angajarii (zi luna an): ";
            if (!(cin >> zi >> luna >> an))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Format data gresit!" << endl;
                continue;
            }

            Data dataAngajarii(zi, luna, an);
            if (!dataAngajarii.eDataValida())
            {
                cout << "Data invalida!" << endl;
                continue;
            }
            int anNastere = 0;
            if (cnp.length() == 13)
            {
                int prefix = cnp[0] - '0';
                int anCNP = stoi(cnp.substr(1, 2));

                if (prefix == 5 || prefix == 6)
                    anNastere = 2000 + anCNP;
                else
                    anNastere = 1900 + anCNP;
            }

            if ((an - anNastere) < 16)
            {
                cout << "Angajatul este minor (" << (an - anNastere) << " ani)!" << endl;
                continue;
            }

            cout << "Oras: ";
            cin >> oras;

            Angajat *nouAngajat = nullptr;
            if (tipAngajat == 1)
                nouAngajat = new Tehnician(id, nume, prenume, cnp, dataAngajarii, oras);
            else if (tipAngajat == 2)
                nouAngajat = new Receptioner(id, nume, prenume, cnp, dataAngajarii, oras);
            else if (tipAngajat == 3)
                nouAngajat = new Supervizor(id, nume, prenume, cnp, dataAngajarii, oras);

            if (nouAngajat)
            {
                manager->adaugaAngajat(nouAngajat);
                cout << "Adaugat!" << endl;
            }
        }
        else if (optiune == 2)
        {
            int id;
            cout << "ID de sters: ";
            if (cin >> id)
                manager->stergeAngajat(id);
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        else if (optiune == 3)
        {
            int id;
            string nume;
            cout << "ID: ";
            if (cin >> id)
            {
                cout << "Nume nou: ";
                cin.ignore();
                getline(cin, nume);
                manager->modificaNumeAngajat(id, nume);
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        else if (optiune == 4)
        {
            manager->incarcaAngajati("tests/angajati.txt");
            cout << "Incarcat." << endl;
        }
        else if (optiune == 5)
        {
            manager->afiseazaTotiAngajatii();
        }
        else if (optiune == 6)
        {
            string cnp;
            cout << "CNP Cautat: ";
            cin >> cnp;
            manager->afiseazaAngajatDupaCNP(cnp);
        }
    }
}

void meniuElectrocasnice(ServiceManager *manager)
{
    int optiune = -1;
    while (optiune != 0)
    {
        cout << "\nGestiune Electrocasnice" << endl;
        cout << "Press 1 Incarca Electrocasnice" << endl;
        cout << "Press 2 Afiseaza Electrocasnice Suportate" << endl;
        cout << "Press 3 Stergere Electrocasnic" << endl;
        cout << "Press 4 Top Refuzate" << endl;
        cout << "Press 5 Adaugare Manuala Electrocasnic" << endl;
        cout << "Press 0 Inapoi" << endl;
        cout << "Optiunea aleasa: ";

        if (!(cin >> optiune))
        {
            curataBuffer();
            continue;
        }

        if (optiune == 1)
        {
            manager->incarcaElectrocasnice("tests/electrocasnice.txt");
            cout << "Incarcat." << endl;
        }
        else if (optiune == 2)
        {
            manager->afiseazaElectrocasnice();
        }
        else if (optiune == 3)
        {
            string m, mod;
            cout << "Marca: ";
            cin >> m;
            cout << "Model: ";
            cin >> mod;
            manager->stergeElectrocasnic(m, mod);
        }
        else if (optiune == 4)
        {
            manager->afiseazaCereriRefuzatePeEcran();
        }
        else if (optiune == 5)
        {
            cout << "\nAdaugare Electrocasnic Nou" << endl;
            cout << "Tip aparat (1-Frigider, 2-Televizor, 3-MasinaSpalat): ";
            
            int tip;
            if (!(cin >> tip)) 
            {
                cout << "Input invalid! Trebuie numar." << endl;
                curataBuffer();
                continue;
            }
            
            if (tip < 1 || tip > 3)
            {
                cout << "Tip invalid! Alege intre 1 si 3." << endl;
                continue;
            }

            string marca, model;
            int an;
            double pret;

            cout << "Marca: "; 
            cin >> marca;
            cout << "Model: "; 
            cin >> model;
            
            cout << "An Fabricatie: ";
            if (!(cin >> an)) 
            {
                cout << "Anul trebuie sa fie numar." << endl;
                curataBuffer();
                continue;
            }
            
            cout << "Pret: ";
            if (!(cin >> pret)) 
            {
                cout << "Pretul trebuie sa fie numar." << endl;
                curataBuffer();
                continue;
            }

            Electrocasnic* nouEl = nullptr;

            if (tip == 1)
            {
                bool areCongelator;
                cout << "Are Congelator? (1-Da, 0-Nu): ";
                if (!(cin >> areCongelator)) 
                {
                    cout << "Input invalid, se seteaza implicit NU." << endl;
                    curataBuffer();
                    areCongelator = false;
                }
                nouEl = new Frigider(marca, model, an, pret, areCongelator);
            }
            else if (tip == 2)
            {
                double diag;
                cout << "Diagonala (cm): ";
                if (!(cin >> diag)) 
                {
                    cout << "Input invalid, se seteaza 0." << endl;
                    curataBuffer();
                    diag = 0;
                }
                nouEl = new Televizor(marca, model, an, pret, diag);
            }
            else if (tip == 3)
            {
                double cap;
                cout << "Capacitate (kg): ";
                if (!(cin >> cap)) 
                {
                    cout << "Input invalid, se seteaza 0." << endl;
                    curataBuffer();
                    cap = 0;
                }
                nouEl = new MasinaSpalat(marca, model, an, pret, cap);
            }

            if (nouEl != nullptr)
            {
                manager->adaugaElectrocasnicSuportat(nouEl);
                cout << "Succes! Electrocasnicul a fost adaugat in lista suportata." << endl;
            }
        }
    }
}

void meniuCereri(ServiceManager *manager)
{
    int optiune = -1;
    while (optiune != 0)
    {
        cout << "\nGestiune Cereri" << endl;
        cout << "Press 1 Incarca Cererile" << endl;
        cout << "Press 2 Afiseaza Lista Cereri" << endl;
        cout << "Press 3 Porneste Simularea In Timp Real" << endl;
        cout << "Press 4 Generare Rapoarte CSV" << endl;
        cout << "Press 0 Inapoi" << endl;
        cout << "Optiunea aleasa: ";
        if (!(cin >> optiune))
        {
            curataBuffer();
            continue;
        }

        if (optiune == 1)
        {
            manager->incarcaCereri("tests/cereri.txt");
        }
        else if (optiune == 2)
        {
            manager->afiseazaToateCererile();
        }
        else if (optiune == 3)
        {
            manager->runSimulare();
        }
        else if (optiune == 4)
        {
            manager->genereazaRapoarteCSV();
        }
    }
}

int main()
{
    ServiceManager *manager = ServiceManager::getInstance();
    int optiune = -1;

    while (optiune != 0)
    {
        cout << "\nFIX IT NOW--Meniul Principal" << endl;
        cout << "Press 1 Gestiune Angajati" << endl;
        cout << "Press 2 Gestiune Electrocasnice" << endl;
        cout << "Press 3 Procesare Cereri & Simulare" << endl;
        cout << "Press 0 Iesire" << endl;
        cout << "Optiunea aleasa: ";

        if (!(cin >> optiune))
        {
            curataBuffer();
            continue;
        }

        switch (optiune)
        {
        case 1:
            meniuAngajati(manager);
            break;
        case 2:
            meniuElectrocasnice(manager);
            break;
        case 3:
            meniuCereri(manager);
            break;
        case 0:
            cout << "La revedere!" << endl;
            break;
        default:
            cout << "Optiune invalida!" << endl;
        }
    }
    return 0;
}
