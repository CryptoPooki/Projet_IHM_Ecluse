#include "Modèle/Signal.h"

#include <QMainWindow>
#include <iostream>

//Constructeur


Signal::Signal(int id)
{
    //Au début, les feux sont rouges
    green = false;
    red = true;

    this->id = id;
}

//Destructeur
Signal::~Signal()
{
}

void Signal::set_green(int id)
{
    if (id != this->id)
        return;
    green = true;   //allumer vert
    red = false;    //éteindre rouge
    std::cout << "Feu mis à vert" << std::endl;
}

void Signal::set_red(int id)
{
    if (id != this->id)
        return;
    green = false;  //éteindre rouge
    red = true;     //allumer vert
    std::cout << "Feu mis à rouge" << std::endl;
}


void Signal::connexion(QMainWindow *W)
{
    connect(W, SIGNAL(feu_vert(int)), this, SLOT(set_green(int)));
    connect(W, SIGNAL(feu_rouge(int)), this, SLOT(set_red(int)));
}
