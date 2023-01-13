#include "../ModelSIR.hpp"
#include "ModelSEIR.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

ModelSEIR::ModelSEIR()
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

ModelSEIR::ModelSEIR(int newN, double newNday, double newDt, double newBeta, double newGamma, double newNu, double newMu, double newSigma) : ModelSIRClassique(newN, newNday, newDt, newBeta, newGamma)
{
    N = newN;
    nday = newNday;
    dt = newDt;
    beta = newBeta;
    gamma = newGamma;
    nu = newNu;
    mu = newMu;
    sigma = newSigma;
}


ModelSEIR::ModelSEIR(const ModelSEIR& copieModelSEIR)
{
    N = copieModelSEIR.N;
    nday = copieModelSEIR.nday;
    dt = copieModelSEIR.dt;
    beta = copieModelSEIR.beta;
    gamma = copieModelSEIR.gamma;
    nu = copieModelSEIR.nu;
    mu = copieModelSEIR.mu;
    sigma = copieModelSEIR.sigma;
}

ModelSEIR::~ModelSEIR()
{
}

void ModelSEIR::resoudSEIR()
{
    N1 = 30;     // population
    nday1 = 100; // duree de l'epidemie
    dt1 = 1;     // time step

    beta1 = 0.1;  // taux d'infection
    gama1 = 0.05; // taux de guerison

    nu1 = 0.009;  // taux de naissance
    mu1 = 0.01;   // taux de mortalité
    sigma1 = 0.7; // taux de progression de l'exposition à l'infection
    double n;

    vector<double> S(nday); // suscepties
    vector<double> E(nday); // exposed
    vector<double> I(nday); // infecte
    vector<double> R(nday); // recovered
    vector<double> t;        // temps

    I.at(0) = 0.001;     // Initial infective proportion
    S.at(0) = N - I[0]; // initial susceptible
    E.at(0) = 0.;
    R.at(0) = 0.;

    // Definir les ODE du modele et les resoudre numeriquement par la methode d'Euler

    for (double i = 0; i < nday; i += dt)
    {
        t.push_back(i);
        n = S[i] + E[i] + I[i] + R[i];

        S[i + 1] = S[i] + (-beta * S[i] * I[i] + nu * n - mu * S[i]) * dt;
        E[i + 1] = E[i] + (beta * S[i] * I[i] - sigma * E[i] - mu * E[i]) * dt;
        I[i + 1] = I[i] + (sigma * E[i] - gamma * I[i] - nu * I[i]) * dt;
        R[i + 1] = R[i] + (gamma * I[i] - nu * R[i]) * dt;

        if (S[i + 1] < 0 || S[i + 1] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Susceptible est soit inferieur a 0 soit superieur a la population totale." << endl;
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
            cout << "Le nombre des Guerri est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        else if (E[i + 1] < 0 || E[i + 1] > N)
        {
            E.at(0) = 0.;
            cout << "Attention ! " << endl;
            cout << "Le nombre des Guerri est soit inferieur a 0 soit superieur a la population totale." << endl;
            //break;
        }
        cout << "Jour numero : " << i + 1 << "  Sucesptible : " << S[i + 1] << "  Infected : " << I[i + 1] << "  Exposed : " << E[i + 1] << "  Recovered : " << R[i + 1] << endl;
    }

    Plot2D plot; // creation d'un graphe

    plot.autoclean(false); // desactive la suppression du script gnuplot cree et du fichier de donnees
    plot.palette("dark2"); // changement de palette

    plot.xlabel("Temps"); // legende de l'axe x
    plot.ylabel("Population"); // legende de l'axe y

    // trace les courbes
    plot.drawCurve(t, S).label("Suscepties");
    plot.drawCurve(t, E).label("Exposed");
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
    canvas.save("../graphs/modelSEIR.pdf");

}