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

// modele ou un individu qui a été infecte peut à nouveau devenir susceptible
void ModelSISR::resoudSISR()
{
    N1 = 1000;   // population
    nday1 = 100; // duree de l'epidemie
    dt1 = 1;     // time step

    beta1 = 0.8; // taux d'infection
    gama1 = 0.1; // taux de guerison

    nu1 = 0.009; // taux de naissance
    mu1 = 0.2;   // taux de mortalité

    vector<double> S(nday1); // susceptible
    vector<double> I(nday1); // infecte
    vector<double> R(nday1); // recovered
    vector<double> t;        // temps

    I.at(0) = 0.001;     // Initial infective proportion
    S.at(0) = N1 - I[0]; // initial susceptible
    R.at(0) = beta1 / (mu1 + gama1);
    // R.at(0) = 8 / 3;

    //  Define the ODE’s of the model and solve numerically by Euler’s method:

    for (double i = 0; i < nday1; i += dt1)
    {
        t.push_back(i);

        S[i + 1] = S[i] + ((-beta1 / N1) * (S[i] * I[i]) + (mu1 * I[i])) * dt1;
        I[i + 1] = I[i] + ((beta1 / N1) * S[i] * I[i] - (mu1 + gama1) * I[i]) * dt1;
        R[i + 1] = R[i] + (gama1 * I[i]) * dt1;

        if (S[i + 1] < 0 || S[i + 1] > N1)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Susceptible est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        else if (I[i + 1] < 0 || I[i + 1] > N1)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Infecte est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        else if (R[i + 1] < 0 || R[i + 1] > N1)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Guerri est soit inferieur a 0 soit superieur a la population totale." << endl;
            // break;
        }
        cout << "Jour numero : " << i + 1 << "  Sucesptible : " << S[i + 1] << "  Infected : " << I[i + 1] << "  Recovered : " << R[i + 1] << endl;
    }
    Plot2D plot;
    plot.size(700, 700);

    // This disables the deletion of the created gnuplot script and data file.
    plot.autoclean(false);
    plot.xlabel("Temps");
    plot.ylabel("Population");
    // Change its palette
    plot.palette("dark2");

    // Plot two functions
    plot.drawCurve(t, S).label("Suscepties");
    plot.drawCurve(t, I).label("Infected");
    plot.drawCurve(t, R).label("Recovered");
    plot.legend()
        .atOutsideRightBottom()
        .displayVertical();

    // Create figure to hold plot
    Figure fig = { {plot} };
    // Create canvas to hold figure
    Canvas canvas = { {fig} };
    fig.title("Modele SISR");


    // Show the plot in a pop-up window
    canvas.show();

    // Save the plot to a PDF file
    canvas.save("../graphs/modelSISR.pdf");
}