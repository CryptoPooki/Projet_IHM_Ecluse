#include "Modèle/Porte.h"
#include <QEventLoop>

#include <QMainWindow>
#include <QBasicTimer>

#include <iostream>


//Constructeur
Porte::Porte(int id)//
{
    is_open = false;            //Porte initialement fermée
    emergency_status = false;   //Etat de fonctionnement normale
    breakdown_status = false;
    alarm_status = false;
    transition = 100;           //Fin de transition
    timer = 0;
    Porteid =id;
}

//Destructeur
Porte::~Porte()
{
}

//Fermeture de la porte
void Porte::closing(int percent)
{
    transition = percent; //Pourcentage de transition
    if (transition == 100) //Une fois que la transition est finie ...
    {
        is_open = false; //... la porte est fermée
    }
}
void Porte::run()
{
    QEventLoop loop  ;
    loop.exec();
}

void Porte::panne(int id)
{
    if (id == Porteid)
        breakdown_status = !breakdown_status;
}
void Porte::connexion(QMainWindow *W)
{
    connect(W,SIGNAL(show_state_sig(int,int)), this,SLOT(show_state(int,int )) );
    connect(W,SIGNAL(change_door_sig(int,int)), this, SLOT(door_change_state(int,int)) );
    connect(W,SIGNAL(emergency_sig()), this, SLOT(emergency_event(void )));
    connect(W, SIGNAL(sortie_panne_sig()), this, SLOT(sortie_panne())  );
}



//Ouverture de la porte
void Porte::opening(int percent)
{
    transition = percent;
    if (transition == 100)// Une fois que la transition est finie ...
    {
        is_open = true; //... la porte est ouverte
    }
}

//Renvoie des états
void Porte::show_state(int i,int id)
{
    if (!id == Porteid) // cette porte n'est pas concernée
        return ;
    bool state[4] = {is_open, emergency_status, breakdown_status, alarm_status};
    if ( i == 0 ) // demande d'ouverture
    {
        std::cout << "signal parti" << std::endl;
        emit show_state_open_sig(state,Porteid);
    }
    else if (i == 1)
    {
        emit show_state_close_sig(state,Porteid);
    }
    else
    {
        arret_porte();
        emit show_state_arret_sig(state,Porteid);
    }
}

void Porte::arret_porte()
{
    if (timer != 0)
    {
        timer->stop();
        timer = 0;
    }
}

void Porte::update_open_door()
{
    if (transition == 0)
    {
       timer->stop();
       timer = 0;
       emit open_door_sig(1,Porteid);
       emit control_door_sig(1,Porteid);
    }
    else
    {
        transition -=10;
        emit control_door_sig(3,Porteid);
        emit position_sig(transition,Porteid);
    }
}

void Porte::update_close_door()
{
    if (transition == 100)
    {
        timer->stop();
        timer = 0;
        emit close_door_sig(0,Porteid);
        emit control_door_sig(0,Porteid);
    }
    else
    {
        transition +=10;
        emit position_sig(transition,Porteid);
        emit control_door_sig(2,Porteid);
    }
}


// On peut ouvrir et fermer les portes à tout moment (même lors d'une transition)
void Porte::door_change_state(int state, int id )
{
    if(!id==Porteid)
        return;
    if(timer != 0)
    {
        if(timer->isActive())
            timer->stop();
    }
    timer = new QTimer();
    is_open = !is_open;
    if(state == 0)
    {
        connect(timer,SIGNAL(timeout()), this, SLOT( update_open_door() ) );
        timer->start(1000);
    }
    else if (state == 1)
    {
        connect(timer,SIGNAL(timeout()), this, SLOT(update_close_door() ) );
        timer->start(1000);
    }
}

void Porte::emergency_event(void )
{
    if(!emergency_status)
        std::cout << "ALERTE PORTE" << std::endl;
    else
        std::cout << "ALERTE PORTE TERMINEE" << std::endl;

    arret_porte();
    emergency_status = !emergency_status;
    alarm_status = !alarm_status;

}
void Porte::sortie_panne()
{
    breakdown_status = false;
}

