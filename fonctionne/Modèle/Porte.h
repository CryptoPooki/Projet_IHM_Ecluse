#ifndef PORTE_H
#define PORTE_H

#include <QThread>
#include <QMainWindow>
#include <QTimer>

class Porte : public QThread
{
    Q_OBJECT
public:
    Porte(int id);
    void connexion (QMainWindow *W);
    void run();
    ~Porte();
    void closing(int percent);
    void opening(int percent);

    bool is_open ;
    bool emergency_status;
    bool breakdown_status;
    bool alarm_status;
    int transition; //état de transition en % (0% ==> début; 100% ==> fin)
    QTimer * timer;
    int Porteid;

public slots:
    void door_change_state(int state, int id );
    void show_state(int, int );
    void update_open_door();
    void update_close_door();
    void arret_porte();
    void emergency_event(void );
    void panne(int);
    void sortie_panne();

signals :
    void show_state_open_sig(bool*,int);
    void open_door_sig(int,int);
    void show_state_close_sig(bool*,int);
    void close_door_sig(int,int);
    void show_state_arret_sig(bool*,int);
    void control_door_sig(int ,int);
    void position_sig(int,int);
    void emergency_status_porte_sig();


};


#endif // PORTE_H


