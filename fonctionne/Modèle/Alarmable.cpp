#include "Modèle/Alarmable.h"

//Constructeur
Alarmable::Alarmable()
{

}

//Destructeur
Alarmable::~Alarmable()
{
}

//Activation de l'état d'urgence
void Alarmable::emergency()
{
    emergency_status = false;
    alarm_status = true; //Activation de l'alarme
}

//Désactivation de l'état d'urgence
void Alarmable::stop_emergency()
{
    emergency_status = true;
    alarm_status = false; //Désactivation de l'alarme
}

//Panne
void Alarmable::breakdown()
{
    breakdown_status = false;
    alarm_status = true;
}

//Reprise sur panne
void Alarmable::restart()
{
    breakdown_status = true;
    alarm_status = false;
}
