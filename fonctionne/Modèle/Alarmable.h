#ifndef ALARMABLE_H
#define ALARMABLE_H

#include "Modèle/Ecluse.h"

class Alarmable : public Ecluse //Héritage protégé de la classe Ecluse
{
public:
    Alarmable();
    ~Alarmable();

public:
    void emergency();
    void stop_emergency();
    void breakdown();
    void restart();

    bool is_open;           //état ouvert ou fermé
    bool emergency_status;  //état d'urgence
    bool breakdown_status;  //état de panne
    bool alarm_status;      //alarme
};

#endif // ALARMABLE_H
