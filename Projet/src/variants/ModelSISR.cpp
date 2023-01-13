#include "../ModelSIR.hpp"
#include "ModelSISR.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

ModelSISR::ModelSISR()
{
    N = 0;
    nday = 0.;
    dt = 0.;
    beta = 0.;
    gamma = 0.;
    nu = 0.;
    mu = 0.;
    sigma = 0.;
}

ModelSISR::ModelSISR(int newN, double newNday, double newDt, double newBeta, double newGamma, double newNu, double newMu, double newSigma) : ModelSIRClassique(newN, newNday, newDt, newBeta, newGamma)
{
    N = newN;
    nday = newNday;
    dt = newDt;
    beta = newBeta;
    gamma = newGamma;
    nu = newNu;
    mu = newMu;
}

ModelSISR::ModelSISR(const ModelSISR& copieModelSISR)
{
    N = copieModelSISR.N;
    nday = copieModelSISR.nday;
    dt = copieModelSISR.dt;
    beta = copieModelSISR.beta;
    gamma = copieModelSISR.gamma;
    nu = copieModelSISR.nu;
    mu = copieModelSISR.mu;
}

ModelSISR::~ModelSISR()
{
}

// Resolution du modele ou un individu qui a été infecte peut à nouveau devenir susceptible 
// SISR : Suscepties Infected Suscepties Recovered
void ModelSISR::resoudSISR()
{
    N1 = 1000;   // population
    nday1 = 100; // duree de l'epidemie
    dt1 = 1;     // time step

    beta1 = 0.8; // taux d'infection
    gama1 = 0.1; // taux de guerison

    nu1 = 0.009; // taux de naissance
    mu1 = 0.2;   // taux de mortalité

    vector<double> S(nday); // Suscepties
    vector<double> I(nday); // infecte
    vector<double> R(nday); // recovered
    vector<double> t;       // temps

    I.at(0) = 0.001;     // Initial infective proportion
    S.at(0) = N - I[0]; // initial susceptible
    R.at(0) = beta / (mu + gamma);

    // Definir les ODE du modele et les resoudre numeriquement par la methode d'Euler

    for (double i = 0; i < nday; i += dt)
    {
        t.push_back(i);

        S[i + 1] = S[i] + ((-beta / N) * (S[i] * I[i]) + (mu * I[i])) * dt;
        I[i + 1] = I[i] + ((beta / N) * S[i] * I[i] - (mu + gamma) * I[i]) * dt;
        R[i + 1] = R[i] + (gamma * I[i]) * dt;

        if (S[i + 1] < 0 || S[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Suscepties est soit inferieur a 0 soit superieur a la population totale." << endl;
        }
        else if (I[i + 1] < 0 || I[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Infected est soit inferieur a 0 soit superieur a la population totale." << endl;
        }
        else if (R[i + 1] < 0 || R[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Recovered est soit inferieur a 0 soit superieur a la population totale." << endl;
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
    Figure fig = { {plot} };

    // Creation d'un canvas pour afficher la figure
    Canvas canvas = { {fig} };
    canvas.size(750, 750); //taille du canvas

    // Affichage du canvas dans une fenetre
    canvas.show();

    // Graphe enregistre dans le dossier graphs
    canvas.save("../graphs/modelSISR.pdf");
}
