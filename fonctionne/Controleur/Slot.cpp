#include "Controleur/Slot.h"
#include "Modèle/Vanne.h"
#include "Modèle/Porte.h"
#include "Modèle/Signal.h"
#include "Vue/MainWindow.h"

#include <QObject>

Slot::Slot()
{
}

//Définitions des slots
void open_gate(Porte myGate)
{
    if (!myGate.is_open)
    {
        //Thread d'ouverture de la porte
    }
}

void close_gate(Porte myGate)
{
    if (myGate.is_open)
    {
        //Thread de fermeture de la porte
    }
}

void open_valve(Vanne myValve)
{
    if (!myValve.is_open)
    {
        //Thread d'ouverture de la valve
    }
}

void close_valve(Vanne myValve)
{
    if (myValve.is_open)
    {
        //Thread de fermeture de la valve
    }
}

void red_signal(Signal mySignal)
{
    if(mySignal.green && !mySignal.red)
    {
        //Thread de changement de signal ->mySignal.set_red();
    }
}

void green_signal(Signal mySignal)
{
    if(mySignal.red && !mySignal.green)
    {
        //Thread de changement de signal ->mySignal.set_green();
    }
}

//Surcharge de breakdown
void breakdown(Porte myGate)
{
    //Thread de breakdown;
}

void breakdown(Vanne myValve)
{
    //Thread de breakdown;
}

void breakdown(Signal mySignal)
{
    //Thread de breakdown;
}

void alarm(Porte myGate)
{
    //Thread d'alarm;
}

void alarm(Vanne myValve)
{
    //Thread d'alarm;
}

void alarm(Signal mySignal)
{
    //Thread d'alarm;
}

void emergency()
{
    //Etat d'urgence sur les vannes

    //Etat d'urgence sur les portes

    //Blocage des touches
}

void go_up() //Auto
{
    //Réfléchir sur l'enchainement des fonctions
}

void go_down() //Auto
{
    //Réflechir sur l'enchainement des fonctions
}

void change_mode()
{
    /*if (mode_auto) //De automatique vers manuel
    {
        //Récupération des données indiquées dans les LineEdit
        QString ID = ui->saisie_ID->text(); ui->saisie_ID->setClear(true);
        QString MdP = ui->saisie_MdP->text(); ui->saisie_MdP->setClear(true);

        //Manque de database

        if (ID == QString::fromStdString("admin") && MdP == QString::fromStdString("")) //Success
        {
            foreach object in Hidden
            {
                object.show(); //Afficher les boutons du mode Manuel
            }
        }
    } else //De manuel vers automatique
    {

        foreach object in Hidden
        {
            object.hide(); //Cacher les boutons du mode Manuel
        }

    }*/

}
