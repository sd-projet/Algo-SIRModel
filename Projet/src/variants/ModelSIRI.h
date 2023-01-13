#pragma once
#include <iostream>
#include "../ModelSIR.hpp"
#include <vector>

using namespace std;

class ModelSIRI : public ModelSIRClassique
{
private:
public:
    ModelSIRI(); // constructeur par defaut
    ModelSIRI(int newN, double newNday, double newDt, double newBeta, double newGamma, double newMu, double newSigma); //constructeur avec paramétres
    ModelSIRI(const ModelSIRI& copieModelSIRI); // constructeur de copie
    ~ModelSIRI(); //Destructeur 

    void resoudSIRI(); // methode  pour resoudre le modele SIRI
};
