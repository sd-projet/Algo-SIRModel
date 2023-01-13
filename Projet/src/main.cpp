#include <iostream>
#include "ModelSIR.hpp"
#include "ModelSIR.cpp"

#include "variants/ModelSEIR.h"
#include "variants/ModelSEIR.cpp"

#include "variants/ModelSIRS.h"
#include "variants/ModelSIRS.cpp"

#include "variants/ModelSISR.h"
#include "variants/ModelSISR.cpp"

#include "variants/ModelSIRI.h"
#include "variants/ModelSIRI.cpp"

using namespace std;
#include "../include/sciplot/sciplot.hpp"
using namespace sciplot;



int main()
{
    ModelSIRClassique sir;
    ModelSEIR seir;
    ModelSISR sisr;
    ModelSIRS sirs;
    ModelSIRI siri;

    int choix;
    string confirm;


    do {

        cout << "\n            ________________________________________________________________________\n";
        cout << "\n            Resoudre les equations d'un modele epidemiologique SIR et des variantes";
        cout << "\n            ________________________________________________________________________\n";

        cout << "\n Veuillez choisir parmi les options suivantes : \n";
        cout << "\n 1 - Modele classique SIR (Susceptibles, Infected, Recovered)\n";
        cout << "\n 2 - Modele SEIR (Susceptibles, Exposed, Infected, Recovered) \n";
        cout << "\n 3 - Modele SISR (Susceptibles, Infected, Susceptibles, Recovered)\n";
        cout << "\n 4 - Modele SIRS (Susceptibles, Infected, Recovered, Susceptibles)\n";
        cout << "\n 5 - Modele SIRI (Susceptibles, Infected, Recovered, Infected)\n\n";

        //SISR : Un individu qui a ete infecte peut a nouveau devenir susceptible
        //SIRS : Un individu immunise perd son immunisation et redeviend susceptible
        //SIRI : Un individu gueri peut etre reinfecte


        cin >> choix;

        switch (choix)
        {
        case 1:
            sir.saisir();
            sir.resoudSIR();
            break;
        case 2:
            seir.saisir();
            seir.saisir2();
            seir.saisir3();
            seir.resoudSEIR();
            break;
        case 3:
            sisr.saisir();
            sisr.saisir2();
            sisr.resoudSISR();
            break;
        case 4:
            sirs.saisir();
            sisr.saisir2();
            sirs.resoudSIRS();
            break;
        case 5:
            siri.saisir();
            siri.saisir3();
            siri.resoudSIRI();
            break;
        default:
            cout << "Veuillez choisir une option !";
            break;
        }

        cout << "Vos resultats ont egalement ete telecharger dans le dossier graphs.\n";

        cout << "Pour selectionner un autre modele taper y ou Y sinon cliquer sur n'importe quelle lettres : ";
        cin >> confirm;
    } while (confirm == "y" || confirm == "Y");
    return 0;
}
