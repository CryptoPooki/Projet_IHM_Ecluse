//Bibliothèques nécessaires
#include "Modèle/Vanne.h"
#include <QEventLoop>
#include <QMainWindow>
#include <iostream>
#include <QTimer>
/////////////////////////////////////    Méthodes     ///////////////////////////////////////////
//Constructeur
Vanne::Vanne(int id)
{
    Vanneid = id;               //ID de la vanne
    is_open = false;            //vanne initialement fermée
    emergency_status = false;   //État de fonctionnement normal
    breakdown_status = false;
    alarm_status = false;
    transition = 100;
}

//Destructeur
Vanne::~Vanne()
{
}

void Vanne::run()
{
    QEventLoop loop  ;
    loop.exec();
}


void Vanne::connexion(QMainWindow* W)
{
    connect(W, SIGNAL(show_state_vanne_sig(int,int)), this, SLOT(show_state(int,int))  );
    connect(W, SIGNAL(change_vanne_sig(int,int)), this, SLOT(vanne_change_state(int,int))  );
    connect(W, SIGNAL(emergency_sig()), this, SLOT(emergency_event(void )));
    connect(W, SIGNAL(panne_vanne(int)), this, SLOT(panne(int))  );
    connect(W, SIGNAL(sortie_panne_sig()), this, SLOT(sortie_panne())  );
}

/////////////////////////////////////    Slots       ///////////////////////////////////////////
//Renvoie des états
void Vanne::show_state(int i,int id)
{
    if (id != Vanneid) // cette porte n'est pas concernée
        return ;
    std::cout << "je suis là"<< std::endl;
    bool state[4] = {is_open, emergency_status, breakdown_status, alarm_status};
    if ( i == 0 ) // demande d'ouverture
        emit show_state_open_vanne_sig(state,Vanneid);
    else if (i == 1)
        emit show_state_close_vanne_sig(state,Vanneid);

}

void Vanne::vanne_change_state(int state, int id )
{
    if(id!=Vanneid)
        return;
    is_open = !is_open;

    timer = new QTimer();
    if (state == 0)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update_open_vanne()));
    }
    else
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update_close_vanne()));
    }
    timer->start(1000);
}

void Vanne::update_open_vanne()
{
    if(transition == 0)
    {
        timer->stop();
        timer = 0;
        emit open_vanne_sig(1,Vanneid);
    }
    else
    {
        transition -=10;
        std::cout << "Vanne open++" << std::endl;
    }
}

void Vanne::update_close_vanne()
{
    if(transition == 100)
    {
        timer->stop();
        timer = 0;
        emit close_vanne_sig(0,Vanneid);
    }
    else
    {
        std::cout << "Vanne close --" << std::endl;
        transition +=10;
    }
}

void Vanne::emergency_event(void )
{
    if(!emergency_status)
        std::cout << "ALERTE VANNE" << std::endl;
    else
        std::cout << "ALERTE VANNE TERMINEE" << std::endl;

    emergency_status = !emergency_status;
    alarm_status = !alarm_status;

}

void Vanne::panne(int id)
{
    if (id == Vanneid)
        breakdown_status = !breakdown_status;               //Mis en état de panne
}

void Vanne::sortie_panne()
{
    breakdown_status = false;                               //Reprise sur panne
}
