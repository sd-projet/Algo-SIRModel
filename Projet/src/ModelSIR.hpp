#pragma once
#include <iostream>
#include <vector>

using namespace std;
class ModelSIRClassique
{
protected:
    int N;        // population
    double nday;  // duree de l'epidemie
    double dt;    // nombre d'iteration
    double beta;  // taux d'infection
    double gamma; // taux de guerrison
    double nu;    // taux de naissance
    double mu;    // taux de mortalite
    double sigma; // taux de progression de l'exposition a l'infection
    
public:
    
    ModelSIRClassique();                                                                        // constructeur par defaut
    ModelSIRClassique(int newN, double newNday, double newDt, double newBeta, double newGamma); // constructeur avec parametre
    ModelSIRClassique(const ModelSIRClassique &copieModelSIRClassique);                         // constructeur de copie
    ~ModelSIRClassique();                                                                       // destructeur

    // getters
    int getN() const;
    double getNday() const;
    double getDt() const;
    double getBeta() const;
    double getGamma() const;
    double getNu() const;
    double getMu() const;
    double getSigma() const;

    // setters
    void setN(int newN);
    void setNday(double newNday);
    void setDt(double newDt);
    void setBeta(double newBeta);
    void setGamma(double newGamma);
    void setNu(double newNu);
    void setMu(double newMu);
    void setSigma(double newSigma);

    void resoudSIR(); // methode  pour resoudre le modele SIR
    void saisir();    // methode pour recuperer les valeurs du modeles SIR saisies par l'utilisateur
    void saisir2();   // methode pour recuperer les valeurs du modeles SIRS ou SISR ou SEIR ou SIRI saisies par l'utilisateur
    void saisir3();   // methode pour recuperer les valeurs du modeles SIRS ou SISR ou SEIR ou SIRI saisies par l'utilisateur
};
