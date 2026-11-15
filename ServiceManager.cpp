#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <thread>
#include <chrono>
#include "ServiceManager.h"
#include "ValidatorCNP.h"
#include "AngajatFactory.h"
#include "ElectrocasnicFactory.h"
#include "Tehnician.h"
#include "Frigider.h"
#include "MasinaSpalat.h"
#include "Televizor.h"
#include "Receptioner.h"
#include "Supervizor.h"

using namespace std;

ServiceManager *ServiceManager::instance = nullptr;

ServiceManager::ServiceManager() {}

ServiceManager *ServiceManager::getInstance()
{
    if (instance == nullptr)
        instance = new ServiceManager();
    return instance;
}

void ServiceManager::adaugaAngajat(Angajat *a)
{
    this->angajati.push_back(a);
}

void ServiceManager::adaugaElectrocasnic(Electrocasnic *e)
{
    this->electrocasniceSuportate.push_back(e);
}

void ServiceManager::adaugaCerere(Cerere *c)
{
    this->cereri.push_back(c);
}

void ServiceManager::incarcaAngajati(string filePath)
{
    ifstream f(filePath);
    if (!f.is_open())
    {
        cout << "Eroare la deschiderea fisierului!" << endl;
        return;
    }
    string line;
    int numarLinie = 0;
    while (getline(f, line))
    {
        numarLinie++;
        if (line.empty())
            continue;

        Angajat *a = AngajatFactory::creeazaAngajat(line);
        if (a == nullptr)
        {
            cout << "Eroare la linia " << numarLinie << ": Format incorect." << endl;
            continue;
        }
        if (ValidatorCNP::eCNPValid(a->getCnp()) == false)
        {
            cout << "Eroare la linia " << numarLinie << ": CNP invalid matematic." << endl;
            delete a;
            continue;
        }
        string cnp = a->getCnp();
        int anNastere = 0;
        int prefix = cnp[0] - '0';
        int anCNP = stoi(cnp.substr(1, 2));
        if (prefix == 1 || prefix == 2)
            anNastere = 1900 + anCNP;
        else if (prefix == 5 || prefix == 6)
            anNastere = 2000 + anCNP;

        if (a->getDataAngajarii().eDataValida() == false)
        {
            cout << "Eroare la linia " << numarLinie << ": Data calendaristica invalida!" << endl;
            delete a;
            continue;
        }

        int anAngajare = a->getDataAngajarii().getAn();
        if ((anAngajare - anNastere) < 16)
        {
            cout << "Eroare la linia " << numarLinie << ": Angajat minor (<16 ani)!" << endl;
            delete a;
            continue;
        }

        bool existaProbleme = false;
        for (Angajat *existent : this->angajati)
        {
            if (existent->getId() == a->getId())
            {
                cout << "Eroare la linia " << numarLinie << ": ID-ul " << a->getId() << " este deja folosit de " << existent->getNume() << "!" << endl;
                existaProbleme = true;
                break;
            }
            if (existent->getCnp() == a->getCnp())
            {
                cout << "Eroare la linia " << numarLinie << ": CNP-ul " << a->getCnp() << " exista deja in sistem!" << endl;
                existaProbleme = true;
                break;
            }
        }
        if (existaProbleme)
        {
            delete a;
            continue;
        }
        this->adaugaAngajat(a);
    }
    f.close();
}

void ServiceManager::adaugaElectrocasnicSuportat(Electrocasnic* e)
{
    this->electrocasniceSuportate.push_back(e);
}

void ServiceManager::modificaNumeAngajat(int id, string numeNou)
{
    bool gasit = false;
    for (Angajat *a : this->angajati)
    {
        if (a->getId() == id)
        {
            a->setNume(numeNou);
            cout << "Numele angajatului cu ID " << id << " a fost schimbat in: " << numeNou << endl;
            gasit = true;
            break;
        }
    }
    if (!gasit)
        cout << "Eroare: Angajatul cu ID " << id << " nu a fost gasit." << endl;
}

bool ServiceManager::stergeAngajat(int id)
{
    for (auto it = this->angajati.begin(); it != this->angajati.end(); ++it)
    {
        if ((*it)->getId() == id)
        {
            delete *it;
            this->angajati.erase(it);
            cout << "Angajatul cu ID " << id << " a fost sters (demisie)!" << endl;
            return true;
        }
    }
    cout << "Angajatul cu ID " << id << " nu a fost gasit!" << endl;
    return false;
}

Angajat *ServiceManager::getAngajatDupaId(int idCautat)
{
    for (Angajat *a : this->angajati)
        if (a->getId() == idCautat)
            return a;
    return nullptr;
}

void ServiceManager::incarcaElectrocasnice(string filePath)
{
    ifstream f(filePath);

    if (!f.is_open())
    {
        cout << "Erroare la deschiderea fisierului!" << filePath << endl;
        return;
    }
    string linie;
    while (getline(f, linie))
    {
        if (linie.empty())
            continue;
        Electrocasnic *e = ElectrocasnicFactory::creeazaElectrocasnic(linie);
        if (e == nullptr)
            continue;
        else if (e != nullptr)
            this->adaugaElectrocasnic(e);
    }
    f.close();
}

int ServiceManager::getNrCereriActivePentruTehnician(int idTehnician)
{
    int nrr = 0;
    for (Cerere *c : this->cereri)
        if (c->getIdTehnician() == idTehnician && c->getStatus() == "In Lucru")
            nrr++;
    return nrr;
}

int ServiceManager::gasesteCelMaiBunTehnician(Cerere *c)
{
    int idCelMaiBun = -1;
    int minOreMuncite = 999999;

    Electrocasnic *aparat = c->getElectrocasnic();
    string marcaNecesara = aparat->getMarca();
    string tipNecesara = aparat->getTip();

    for (Angajat *a : this->angajati)
    {
        Tehnician *t = dynamic_cast<Tehnician *>(a);
        if (t != nullptr)
        {
            bool stieSaRepare = t->areCompetenta(marcaNecesara) || t->areCompetenta(tipNecesara);
            if (stieSaRepare)
            {
                int cereriActive = this->getNrCereriActivePentruTehnician(t->getId());
                if (cereriActive < 3)
                {
                    if (t->getTotalOreMuncite() < minOreMuncite)
                    {
                        minOreMuncite = t->getTotalOreMuncite();
                        idCelMaiBun = t->getId();
                    }
                }
            }
        }
    }
    return idCelMaiBun;
}

void ServiceManager::runSimulare()
{
    int nrTehnicieni = 0;
    int nrReceptioneri = 0;
    int nrSupervizori = 0;

    vector<Receptioner *> echipaReceptioneri;

    for (Angajat *a : this->angajati)
    {
        if (dynamic_cast<Tehnician *>(a))
            nrTehnicieni++;
        else if (Receptioner *r = dynamic_cast<Receptioner *>(a))
        {
            nrReceptioneri++;
            echipaReceptioneri.push_back(r);
        }
        else if (dynamic_cast<Supervizor *>(a))
            nrSupervizori++;
    }

    if (nrTehnicieni < 3 || nrReceptioneri < 1 || nrSupervizori < 1)
    {
        cout << "Eroare critica: Service-ul nu poate functiona!" << endl;
        return;
    }

    vector<Tehnician *> echipaTehnicieni;
    for (Angajat *a : this->angajati)
    {
        Tehnician *t = dynamic_cast<Tehnician *>(a);
        if (t != nullptr)
        {
            echipaTehnicieni.push_back(t);
            if (!t->areCompetenta("Frigider"))
                t->adaugaCompetenta("Frigider");
            if (!t->areCompetenta("Televizor"))
                t->adaugaCompetenta("Televizor");
            if (!t->areCompetenta("MasinaSpalat"))
                t->adaugaCompetenta("MasinaSpalat");
        }
    }

    if (!echipaTehnicieni.empty())
    {
        int indexTech = 0;
        for (Electrocasnic *e : this->electrocasniceSuportate)
        {
            string marca = e->getMarca();
            if (!echipaTehnicieni[indexTech]->areCompetenta(marca))
                echipaTehnicieni[indexTech]->adaugaCompetenta(marca);

            indexTech++;
            if (indexTech >= echipaTehnicieni.size())
                indexTech = 0;
        }
    }

    bool serviceActiv = true;
    int timpCurent = 0;
    int indexReceptioner = 0;

    while (serviceActiv)
    {
        timpCurent++;
        bool existaActivitate = false;

        cout << "\n[Timp " << timpCurent << "]" << endl;

        for (Cerere *c : this->cereri)
        {
            if (c->getOraDepunere() == timpCurent && c->getStatus() == "Neinregistrat")
            {
                if (!echipaReceptioneri.empty())
                {
                    Receptioner *r = echipaReceptioneri[indexReceptioner];
                    r->adaugaCerere(c->getId());
                    c->setStatus("In Asteptare");

                    cout << "   Receptioner " << r->getNume() << " a inregistrat cererea " << c->getId() << endl;

                    indexReceptioner++;
                    if (indexReceptioner >= echipaReceptioneri.size())
                        indexReceptioner = 0;

                    existaActivitate = true;
                }
            }
        }

        for (Cerere *c : this->cereri)
        {
            if (c->getStatus() == "In Asteptare")
            {
                existaActivitate = true;
                int idTehnician = this->gasesteCelMaiBunTehnician(c);
                if (idTehnician != -1)
                {
                    c->asigneazaTehnician(idTehnician);
                    for (Angajat *a : this->angajati)
                        if (a->getId() == idTehnician)
                            if (Tehnician *t = dynamic_cast<Tehnician *>(a))
                                t->adaugaOreMuncite(c->getDurataEstimata());
                    cout << "   Tehnician " << idTehnician << " primeste cererea " << c->getId() << endl;
                }
            }
        }

        for (Cerere *c : this->cereri)
        {
            if (c->getStatus() == "In Lucru")
            {
                existaActivitate = true;
                cout << "   Tehnician " << c->getIdTehnician() << " proceseaza cererea " << c->getId()
                     << " (raman " << c->getDurataRamasa() << " ore)" << endl;

                c->decrementeazaTimp();
                if (c->esteFinalizata())
                {
                    cout << "   Tehnician " << c->getIdTehnician() << " finalizeaza cererea " << c->getId() << endl;
                    int idT = c->getIdTehnician();
                    double valoareManopera = c->getPretReparatie();

                    for (Angajat *a : this->angajati)
                    {
                        if (a->getId() == idT)
                        {
                            Tehnician *t = dynamic_cast<Tehnician *>(a);
                            if (t != nullptr)
                                t->adaugaReparatie(valoareManopera);
                        }
                    }
                }
            }
        }

        vector<int> cereriInAsteptareIds;
        for (Cerere *c : this->cereri)
        {
            if (c->getStatus() == "In Asteptare")
            {
                cereriInAsteptareIds.push_back(c->getId());
            }
        }

        cout << "   Cereri in asteptare: ";
        if (cereriInAsteptareIds.empty())
        {
            cout << "-" << endl;
        }
        else
        {
            for (size_t i = 0; i < cereriInAsteptareIds.size(); i++)
            {
                cout << cereriInAsteptareIds[i];
                if (i < cereriInAsteptareIds.size() - 1)
                    cout << ", ";
            }
            cout << endl;
        }

        if (!existaActivitate)
        {
            bool toateFinalizate = true;
            for (Cerere *c : this->cereri)
            {
                if (c->getStatus() != "Finalizata")
                {
                    toateFinalizate = false;
                    break;
                }
            }
            if (toateFinalizate)
            {
                cout << "Toate comenzile au fost finalizate!" << endl;
                serviceActiv = false;
            }
            else if (timpCurent > 1000)
            {
                cout << "Limita de timp atinsa! Se opreste simularea." << endl;
                serviceActiv = false;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void ServiceManager::genereazaRapoarteCSV()
{
    ofstream fisier1("Rapoarte/Raport_Salarii_Complet.csv");
    fisier1 << "ID,Nume,Prenume,Functie,Salariu" << endl;
    vector<Angajat *> copieAngajati = this->angajati;
    sort(copieAngajati.begin(), copieAngajati.end(), [](Angajat *a, Angajat *b)
         { return a->calculeazaSalariu() > b->calculeazaSalariu(); });
    for (Angajat *a : copieAngajati)
        fisier1 << a->getId() << "," << a->getNume() << "," << a->getPrenume() << "," << "Angajat" << "," << a->calculeazaSalariu() << endl;
    fisier1.close();

    ofstream fisier2("Rapoarte/Raport_Cereri_Complet.csv");
    fisier2 << "ID_Cerere,Status,ID_Tehnician,Pret" << endl;
    for (Cerere *c : this->cereri)
        fisier2 << c->getId() << "," << c->getStatus() << "," << c->getIdTehnician() << "," << c->getElectrocasnic()->getPret() << endl;
    fisier2.close();

    ofstream fisier3("Rapoarte/Raport_Top3_Salarii.csv");
    fisier3 << "Loc,Nume,Prenume,Salariu" << endl;
    vector<Angajat *> topAngajati = this->angajati;
    sort(topAngajati.begin(), topAngajati.end(), [](Angajat *a, Angajat *b)
         {
        if (a->calculeazaSalariu() != b->calculeazaSalariu())
            return a->calculeazaSalariu() > b->calculeazaSalariu();
        return a->getNume() < b->getNume(); });
    int limita = (topAngajati.size() < 3) ? topAngajati.size() : 3;
    for (int i = 0; i < limita; i++)
        fisier3 << (i + 1) << "," << topAngajati[i]->getNume() << "," << topAngajati[i]->getPrenume() << "," << topAngajati[i]->calculeazaSalariu() << endl;
    fisier3.close();

    ofstream fisier4("Rapoarte/Raport_Tehnician_Max_Durata.csv");
    fisier4 << "ID_Tehnician,Nume,Prenume,Durata_Reparatie" << endl;
    int maxDurata = -1;
    Cerere *cerereMax = nullptr;
    for (Cerere *c : this->cereri)
    {
        if (c->getStatus() == "Finalizata")
        {
            if (c->getDurataEstimata() > maxDurata)
            {
                maxDurata = c->getDurataEstimata();
                cerereMax = c;
            }
        }
    }
    if (cerereMax != nullptr)
    {
        Angajat *tech = nullptr;
        for (Angajat *a : this->angajati)
        {
            if (a->getId() == cerereMax->getIdTehnician())
            {
                tech = a;
                break;
            }
        }
        if (tech != nullptr)
            fisier4 << tech->getId() << "," << tech->getNume() << "," << tech->getPrenume() << "," << maxDurata << endl;
    }
    fisier4.close();

    ofstream fisier5("Rapoarte/Raport_Cereri_Asteptare.csv");
    fisier5 << "Tip,Marca,Model,ID_Cerere,Ora_Depunere" << endl;
    vector<Cerere *> cereriAsteptare;
    for (Cerere *c : this->cereri)
    {
        if (c->getStatus() == "In Asteptare")
            cereriAsteptare.push_back(c);
    }
    sort(cereriAsteptare.begin(), cereriAsteptare.end(), [](Cerere *a, Cerere *b)
         {
        Electrocasnic *e1 = a->getElectrocasnic();
        Electrocasnic *e2 = b->getElectrocasnic();
        if (e1->getTip() != e2->getTip())
            return e1->getTip() < e2->getTip();
        if (e1->getMarca() != e2->getMarca())
            return e1->getMarca() < e2->getMarca();
        return e1->getModel() < e2->getModel(); });
    for (Cerere *c : cereriAsteptare)
        fisier5 << c->getElectrocasnic()->getTip() << "," << c->getElectrocasnic()->getMarca() << "," << c->getElectrocasnic()->getModel() << "," << c->getId() << endl;
    fisier5.close();

    ofstream fisier6("Rapoarte/Raport_Refuzate.csv");
    fisier6 << "Aparat_Refuzat,Numar_Aparitii" << endl;
    if (this->cereriRefuzate.empty())
        fisier6 << "Nicio cerere refuzata!" << endl;
    else
    {
        vector<pair<string, int>> listaSortata;
        for (auto const &element : this->cereriRefuzate)
            listaSortata.push_back(element);
        sort(listaSortata.begin(), listaSortata.end(),
             [](const pair<string, int> &a, const pair<string, int> &b)
             {
                 return a.second > b.second;
             });
        for (auto const &element : listaSortata)
            fisier6 << element.first << "," << element.second << endl;
    }
    fisier6.close();
    cout << "Toate rapoartele au fost generate cu succes in folderul Rapoarte!" << endl;
}

void ServiceManager::incarcaCereri(string caleFisier)
{
    ifstream f(caleFisier);
    if (!f.is_open())
    {
        cout << "Eroare deschidere fisier cereri." << endl;
        return;
    }
    string line;
    int count = 0;
    while (getline(f, line))
    {
        stringstream ss(line);
        string segment;
        vector<string> date;
        while (getline(ss, segment, ','))
        {
            segment.erase(0, segment.find_first_not_of(" \t\r\n"));
            segment.erase(segment.find_last_not_of(" \t\r\n") + 1);
            date.push_back(segment);
        }
        if (date.size() < 11)
            continue;

        try
        {
            string tip = date[0];
            string marca = date[1];
            string model = date[2];
            int complexitate = stoi(date[10]);

            if (complexitate == 0)
            {
                this->cereriRefuzate[tip + " " + marca + " (Defect Total)"]++;
                continue;
            }

            bool suportat = false;
            for (Electrocasnic *e : this->electrocasniceSuportate)
            {
                if (e->getMarca() == marca && e->getTip() == tip)
                {
                    suportat = true;
                    break;
                }
            }
            if (!suportat)
            {
                this->cereriRefuzate[tip + " " + marca + " (Nesuportat)"]++;
                continue;
            }

            int anFab = stoi(date[3]);
            double pret = stod(date[4]);
            double attr = stod(date[5]);
            Electrocasnic *e = nullptr;
            if (tip == "Frigider")
                e = new Frigider(marca, model, anFab, pret, attr != 0);
            else if (tip == "Televizor")
                e = new Televizor(marca, model, anFab, pret, attr);
            else if (tip == "MasinaSpalat")
                e = new MasinaSpalat(marca, model, anFab, pret, attr);

            if (e)
            {
                int zi = stoi(date[6]);
                int luna = stoi(date[7]);
                int an = stoi(date[8]);
                int durata = stoi(date[9]);
                int idNou = 500 + (int)this->cereri.size() + 1;
                this->cereri.push_back(new Cerere(idNou, e, Data(zi, luna, an), durata, complexitate));
                count++;
            }
        }
        catch (...)
        {
        }
    }
    f.close();
    cout << "Au fost incarcate " << count << " cereri valide." << endl;
}

void ServiceManager::afiseazaAngajatDupaCNP(string cnpCautat) const
{
    bool gasit = false;
    for (Angajat *a : this->angajati)
    {
        if (a->getCnp() == cnpCautat)
        {
            cout << "\nDetalii Angajat" << endl;
            a->afisare();
            cout << "Salariu curent: " << a->calculeazaSalariu() << endl;
            gasit = true;
            break;
        }
    }
    if (!gasit)
        cout << "Nu s-a gasit niciun angajat cu acest CNP." << endl;
}

void ServiceManager::stergeElectrocasnic(string marca, string model)
{
    bool sters = false;
    for (auto it = this->electrocasniceSuportate.begin(); it != this->electrocasniceSuportate.end();)
    {
        if ((*it)->getMarca() == marca && (*it)->getModel() == model)
        {
            delete *it;
            it = this->electrocasniceSuportate.erase(it);
            sters = true;
            cout << "Sters cu succes: " << marca << " " << model << endl;
        }
        else
            ++it;
    }
    if (!sters)
        cout << "Nu s-a gasit aparatul specificat." << endl;
}

void ServiceManager::afiseazaCereriRefuzatePeEcran() const
{
    cout << "\nTOP APARATE REFUZATE" << endl;
    if (this->cereriRefuzate.empty())
    {
        cout << "Lista este goala." << endl;
        return;
    }
    vector<pair<string, int>> lista;
    for (auto const &elem : this->cereriRefuzate)
        lista.push_back(elem);

    sort(lista.begin(), lista.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         {
             if (a.second != b.second) 
                 return a.second > b.second;
             return a.first > b.first; });

    cout << "Nr. Ap.\tDescriere" << endl;
    for (const auto &elem : lista)
        cout << elem.second << "\t" << elem.first << endl;
}

void ServiceManager::afiseazaTotiAngajatii() const
{
    cout << "Lista de angajati" << endl;
    for (Angajat *a : this->angajati)
    {
        a->afisare();
        cout << endl;
    }
}

void ServiceManager::afiseazaElectrocasnice() const
{
    cout << "Lista de electrocasnice" << endl;
    for (Electrocasnic *e : this->electrocasniceSuportate)
    {
        e->afisare();
        cout << endl;
    }
}

void ServiceManager::afiseazaToateCererile() const
{
    cout << "Lista de cereri" << endl;
    for (Cerere *c : this->cereri)
    {
        c->afisare();
        cout << endl;
    }
}

ServiceManager::~ServiceManager()
{
    for (Angajat *a : this->angajati)
        delete a;
    this->angajati.clear();

    for (Electrocasnic *e : this->electrocasniceSuportate)
        delete e;
    this->electrocasniceSuportate.clear();

    for (Cerere *c : this->cereri)
        delete c;
    this->cereri.clear();
}
