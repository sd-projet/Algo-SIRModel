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
    vector<double> t;        // temps

    I.at(0) = 0.001;     // Initial infective proportion
    S.at(0) = N1 - I[0]; // initial susceptible
    // R.at(0) = beta1 / (mu1 + gama1);
    R.at(0) = 0.;

    //  Define the ODE’s of the model and solve numerically by Euler’s method:

    for (double i = 0; i < nday; i += dt)
    {
        t.push_back(i);

        S[i + 1] = S[i] + ((-beta / N) * (S[i] * I[i])) * dt;
        I[i + 1] = I[i] + ((beta / N) * S[i] * I[i] - gamma * I[i]) + (mu/N) * (I[i] * R[i]) * dt;
        R[i + 1] = R[i] + (gamma * I[i]) - ((mu/N) * (I[i] * R[i])) * dt;

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
        cout << "Jour numero : " << i + 1 << "  Suscepties : " << S[i + 1] << "  Infected : " << I[i + 1] << "  Recovered : " << R[i + 1] << endl;
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

    // Show the plot in a pop-up window
    canvas.show();

    // Save the plot to a PDF file
    canvas.save("../graphs/modelSIRI.pdf");
}