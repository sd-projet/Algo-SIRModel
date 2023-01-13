#pragma once
#include <iostream>
#include "../ModelSIR.hpp"
#include <vector>

using namespace std;

class ModelSEIR : public ModelSIRClassique
{
private:
public:
    ModelSEIR(); // constructeur par defaut
    ModelSEIR(int newN, double newNday, double newDt, double newBeta, double newGamma, double newNu, double newMu, double newSigma); // constructeur avec parametre
    ModelSEIR(const ModelSEIR& copieModelSEIR); // constructeur de copie
    ~ModelSEIR(); //Destructeur 

    void resoudSEIR(); // methode  pour resoudre le modele SEIR
};