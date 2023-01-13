#include "../ModelSIR.hpp"
#include "ModelSIRI.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>


ModelSIRI::ModelSIRI()
{
    N = 0;
    nday = 0.;
    dt = 0.;
    beta = 0.;
    gamma = 0.;
    mu = 0.;
}

ModelSIRI::ModelSIRI(int newN, double newNday, double newDt, double newBeta, double newGamma, double newMu, double newSigma) : ModelSIRClassique(newN, newNday, newDt, newBeta, newGamma)
{
    N = newN;
    nday = newNday;
    dt = newDt;
    beta = newBeta;
    gamma = newGamma;
    mu = newMu;
}

ModelSIRI::ModelSIRI(const ModelSIRI& copieModelSIRI)
{
    N = copieModelSIRI.N;
    nday = copieModelSIRI.nday;
    dt = copieModelSIRI.dt;
    beta = copieModelSIRI.beta;
    gamma = copieModelSIRI.gamma;
    mu = copieModelSIRI.mu;
}

ModelSIRI::~ModelSIRI()
{
}

// resoud le modele ou un individu gueri peut etre reinfecte
// SIRI : Suscepties Infected Recovered Infected
void ModelSIRI::resoudSIRI()
{
    N1 = 100;    // population
    nday1 = 100; // duree de l'epidemie
    dt1 = 1;     // time step

    beta1 = 0.8; // taux d'infection
    gama1 = 0.3; // taux de guerison

    mu1 = 0.1;  // taux de mortalité

    vector<double> S(nday); // susceptible
    vector<double> I(nday); // infecte
    vector<double> R(nday); // recovered
    vector<double> t;       // temps

    I.at(0) = 0.001;     // Initial infective proportion
    S.at(0) = N1 - I[0]; // initial susceptible
    // R.at(0) = beta1 / (mu1 + gama1);
    R.at(0) = 0.;

    // Definir les ODE du modele et les resoudre numeriquement par la methode d'Euler

    for (double i = 0; i < nday; i += dt)
    {
        t.push_back(i);

        S[i + 1] = S[i] + ((-beta / N) * (S[i] * I[i])) * dt;
        I[i + 1] = I[i] + ((beta / N) * S[i] * I[i] - gamma * I[i]) + (mu/N) * (I[i] * R[i]) * dt;
        R[i + 1] = R[i] + (gamma * I[i]) - ((mu/N) * (I[i] * R[i])) * dt;

        if (S[i + 1] < 0 || S[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Suscepties est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        else if (I[i + 1] < 0 || I[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Infecte est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        else if (R[i + 1] < 0 || R[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Recovered est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        cout << "Jour numero : " << i + 1 << "  Suscepties : " << S[i + 1] << "  Infected : " << I[i + 1] << "  Recovered : " << R[i + 1] << endl;
    }

    Plot2D plot; // creation d'un graphe

    plot.autoclean(false); // desactive la suppression du script gnuplot cree et du fichier de donnees
    plot.palette("dark2"); // changement de palette

    plot.xlabel("Temps"); // legende de l'axe x
    plot.ylabel("Population"); // legende de l'axe y

    // trace les courbes
    plot.drawCurve(t, S).label("Suscepties");
    plot.drawCurve(t, I).label("Infected");
    plot.drawCurve(t, R).label("Recovered");

    // legende des courbes
    plot.legend()
        .atOutsideRightBottom()
        .displayVertical();

    // Creation d'une figure qui contient les courbes cree
    Figure fig = {{plot}};
    
    // Creation d'un canvas pour afficher la figure
    Canvas canvas = {{fig}};
    canvas.size(750, 750); //taille du canvas

    // Affichage du canvas dans une fenetre
    canvas.show();

    // Graphe enregistre dans le dossier graphs
    canvas.save("../graphs/modelSIRI.pdf");
}
