#pragma once
#include <iostream>
#include "../ModelSIR.hpp"
#include <vector>

using namespace std;

class ModelSIRS : public ModelSIRClassique
{
private:
public:
    ModelSIRS(); // constructeur par defaut
    ModelSIRS(int newN, double newNday, double newDt, double newBeta, double newGamma, double newNu, double newMu, double newSigma); //constructeur avec paramétres
    ModelSIRS(const ModelSIRS& copieModelSIRS); // constructeur de copie
    ~ModelSIRS(); //Destructeur 

    void resoudSIRS(); // methode  pour resoudre le modele SIRS
};
