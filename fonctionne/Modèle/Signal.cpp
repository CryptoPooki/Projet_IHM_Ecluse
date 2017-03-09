//Bibliothèques nécessaires
#include "Modèle/Signal.h"
#include <QMainWindow>
#include <iostream>

//Constructeur
Signal::Signal(int id)
{
    //À l'initialisation, les feux sont rouges
    green = false;
    red = true;

    this->Signalid = id;
}

//Destructeur
Signal::~Signal()
{
}

//Méthodes
void Signal::connexion(QMainWindow *W)
{
    connect(W, SIGNAL(feu_vert(int)), this, SLOT(set_green(int)));
    connect(W, SIGNAL(feu_rouge(int)), this, SLOT(set_red(int)));
}

void Signal::set_green(int id)
{
    if (id != this->Signalid)                         //Test pour vérifier le l'ID est bien celui attendu
        return;
    green = true;                               //Allumer la lampe/diode verte
    red = false;                                //Éteindre la lampe/diode rouge
    std::cout << "Feu mis à vert" << std::endl; //Information de fonctionnement dans la console de QtCreator
}

void Signal::set_red(int id)
{
    if (id != this->Signalid)                         //Test pour vérifier le l'ID est bien celui attendu
        return;
    green = false;                              //Éteindre la lampe/diode verte
    red = true;                                 //Allumer la lampe/diode rouge
    std::cout << "Feu mis à rouge" << std::endl;//Information de fonctionnement dans la console de QtCreator
}
