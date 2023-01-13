#include "ModelSIR.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

#include "../include/sciplot/sciplot.hpp"
using namespace sciplot;

ModelSIRClassique::ModelSIRClassique()
{
    N = 0;
    nday = 0.0;
    dt = 0.0;
    beta = 0.0;
    gamma = 0.0;
}

ModelSIRClassique::ModelSIRClassique(int newN, double newNday, double newDt, double newBeta, double newGamma)
{
    N = newN;
    nday = newNday;
    dt = newDt;
    beta = newBeta;
    gamma = newGamma;
}

ModelSIRClassique::ModelSIRClassique(const ModelSIRClassique &copieModelSIRClassique)
{
    N = copieModelSIRClassique.N;
    nday = copieModelSIRClassique.nday;
    dt = copieModelSIRClassique.dt;
    beta = copieModelSIRClassique.beta;
    gamma = copieModelSIRClassique.gamma;
}

ModelSIRClassique::~ModelSIRClassique() {}

int ModelSIRClassique::getN() const { return N; }

double ModelSIRClassique::getNday() const { return nday; }

double ModelSIRClassique::getDt() const { return dt; }

double ModelSIRClassique::getBeta() const { return beta; }

double ModelSIRClassique::getGamma() const { return gamma; }

double ModelSIRClassique::getNu() const { return nu; }

double ModelSIRClassique::getMu() const { return mu; }

double ModelSIRClassique::getSigma() const { return sigma; }

void ModelSIRClassique::setN(int newN)
{
    N = newN;
}

void ModelSIRClassique::setNday(double newNday)
{
    nday = newNday;
}

void ModelSIRClassique::setDt(double newDt)
{
    dt = newDt;
}

void ModelSIRClassique::setBeta(double newBeta)
{
    beta = newBeta;
}

void ModelSIRClassique::setGamma(double newGamma)
{
    gamma = newGamma;
}

void ModelSIRClassique::setNu(double newNu)
{
    nu = newNu;
}

void ModelSIRClassique::setMu(double newMu)
{
    mu = newMu;
}

void ModelSIRClassique::setSigma(double newSigma)
{
    sigma = newSigma;
}

// recupere les valeurs saisies par l'utilisateur
void ModelSIRClassique::saisir()
{
    cout << "\nEntrez la valeur total de la population : ";
    cin >> N;

    cout << "\nEntrez la duree estime du temps de l'epidemie :  ";
    cin >> nday;

    cout << "\nEntrez le pas d'iterations (time step: 1) : ";
    cin >> dt;

    cout << "Entrez la valeur du taux d'infection (beta: 0.1) : ";
    cin >> beta;

    cout << "Entrez la valeur du taux de guerison (gamma: 0.1) : ";
    cin >> gamma;
}

// recupere les valeurs saisies par l'utilisateur
void ModelSIRClassique::saisir2()
{
    cout << "Entrez la valeur du taux de naissance (nu) : ";
    cin >> nu;

    cout << "Entrez la valeur du taux taux de progression de l'exposition à l'infection : (sigma) ";
    cin >> sigma;
}

// recupere les valeurs saisies par l'utilisateur
void ModelSIRClassique::saisir3()
{
    cout << "Entrez la valeur du taux de mortalite (mu) : ";
    cin >> mu;
}

// resoud le modele SIR
void ModelSIRClassique::resoudSIR()
{
    beta = (beta / N);
    gamma = (gamma / N);

    vector<double> S(nday); // suscepties
    vector<double> I(nday); // infected
    vector<double> R(nday); // recovered
    vector<double> t;       // temps

    I.at(0) = 0.001;    // Initial infective proportion
    S.at(0) = N - I[0]; // initial susceptible
    R.at(0) = 0.;

    // Definir les ODE du modele et les resoudre numeriquement par la methode d'Euler

    for (double i = 0; i < nday; i += dt)
    {
        t.push_back(i);

        S[i + 1] = S[i] + (-beta * (S[i] * I[i])) * dt;
        I[i + 1] = I[i] + (beta * S[i] * I[i] - gamma * I[i]) * dt;
        R[i + 1] = R[i] + (gamma * I[i]) * dt;

        if (S[i] < 0 || S[i] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre de Suscepties est soit inferieur a 0 soit superieur a la population totale." << endl;
            //break;
        }
        else if (I[i] < 0 || I[i] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre des Infected est soit inferieur a 0 soit superieur a la population totale." << endl;
            //break;
        }
        else if (R[i] < 0 || R[i] > N)
        {
            cout << "Attention ! " << endl;
            cout << "Le nombre de Recovered est soit inferieur a 0 soit superieur a la population totale." << endl;
            //break;
        }
        cout << "Jour numero : " << i + 1 << "  Sucespties : " << S[i + 1] << "  Infected : " << I[i + 1] << "  Recovered : " << R[i + 1] << endl;
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
    canvas.save("../graphs/modelSIR.pdf");
}