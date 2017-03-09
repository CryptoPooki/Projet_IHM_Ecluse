//Bibliothèques nécessaires
#include "Modèle/Porte.h"
#include <QEventLoop>
#include <QMainWindow>
#include <QBasicTimer>

//////////////////////////////////////////    Méthodes    ////////////////////////////////////////////////
//Constructeur
Porte::Porte(int id)
{
    Porteid = id;               //Paramètrage de l'ID de la porte
    is_open = false;            //Porte initialement fermée
    emergency_status = false;   //Etat de fonctionnement normal
    breakdown_status = false;
    alarm_status = false;
    transition = 100;           //Fin de transition
    timer = 0;                  //Intialisation du timer

}

//Destructeur
Porte::~Porte()
{
}

void Porte::connexion(QMainWindow *W)
{
    connect(W,SIGNAL(show_state_sig(int,int)), this,SLOT(show_state(int,int )) );
    connect(W,SIGNAL(change_door_sig(int,int)), this, SLOT(door_change_state(int,int)) );
    connect(W,SIGNAL(emergency_sig()), this, SLOT(emergency_event(void )));
    connect(W, SIGNAL(sortie_panne_sig()), this, SLOT(sortie_panne())  );
}

//Lancement du thread en boucle
void Porte::run()
{
    QEventLoop loop  ;
    loop.exec();
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

//Ouverture de la porte
void Porte::opening(int percent)
{
    transition = percent;
    if (transition == 100)// Une fois que la transition est finie ...
    {
        is_open = true; //... la porte est ouverte
    }
}

//////////////////////////////////////////   Slots    //////////////////////////////////////////////////

// On peut ouvrir et fermer les portes à tout moment (même lors d'une transition)
void Porte::door_change_state(int state, int id )
{
    if(id != Porteid)                                                       //Si l'ID est bien celui attendu
        return;
    if(timer != 0)
    {
        if(timer->isActive())
            timer->stop();                                                  //Arrêt du timer si celui-ci n'est pas terminé
    }
    timer = new QTimer();                                                   //Réinitialisation du timer
    is_open = !is_open;                                                     //Changement d'état
    if(state == 0)                                                          //Si la porte est complétement fermée ...
    {
        connect(timer,SIGNAL(timeout()), this, SLOT(update_open_door()));   //... on l'ouvre
        timer->start(1000);
    }
    else if (state == 1)                                                    //Si la porte est completement ouverte ...
    {
        connect(timer,SIGNAL(timeout()), this, SLOT(update_close_door()));  //... on la fermer
        timer->start(1000);
    }
}

void Porte::show_state(int i, int id)
{
    if (id != Porteid)                                                      //Si l'ID est bien celui attendu
        return ;
    bool state[4] = {is_open, emergency_status, breakdown_status, alarm_status};
    if ( i == 0 )                                                           //Si une ouverture est demandée
    {
        emit show_state_open_sig(state,Porteid);                            //on envoie le signal donnant les états de la porte
    }
    else if (i == 1)                                                        //Si une fermeture est demandée
    {
        emit show_state_close_sig(state,Porteid);                           //on envoie le signal donnant les états de la porte
    }
    else                                                                    //par défaut
    {
        arret_porte();
        emit show_state_arret_sig(state,Porteid);                           //on arrête la porte
    }
}

void Porte::update_open_door() //Bug
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
        transition +=10;
        emit control_door_sig(3,Porteid);
        emit position_sig(transition,Porteid);
    }
}

void Porte::update_close_door() //Bug
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

void Porte::arret_porte()
{
    if (timer != 0)                                                         //Si le timer a fini, on l'arrête
    {
        timer->stop();
        timer = 0;
    }
}

void Porte::emergency_event(void)
{
    arret_porte();                                                          //Arrêt de la porte (si celle ci est en transition)
    emergency_status = !emergency_status;                                   //Changement de l'état d'urgence
    alarm_status = !alarm_status;                                           //Changement de l'état d'alarme
}

void Porte::panne(int id)
{
    if (id == Porteid)
        breakdown_status = !breakdown_status;                               //Mise en état de panne
}

void Porte::sortie_panne()
{
    breakdown_status = false;
}
