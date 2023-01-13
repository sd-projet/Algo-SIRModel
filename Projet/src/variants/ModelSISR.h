#pragma once
#include <iostream>
#include "../ModelSIR.hpp"
#include <vector>

using namespace std;

class ModelSISR : public ModelSIRClassique
{
private:
public:
    ModelSISR(); // constructeur par defaut
    ModelSISR(int newN, double newNday, double newDt, double newBeta, double newGamma, double newNu, double newMu, double newSigma); //constructeur avec parametres
    ModelSISR(const ModelSISR& copieModelSISR); // constructeur de copie
    ~ModelSISR(); //Destructeur

    void resoudSISR(); // methode  pour resoudre le modele SISR
};