#ifndef PORTE_H
#define PORTE_H

//Bibliothèques nécessaires
#include <QMainWindow>                          //Nécessaire pour interagir avec l'interface
#include <QThread>                              //Nécessaire pour pouvoir manipuler les threads
#include <QTimer>                               //Nécessaire pour pouvoir implémenter les timer

class Porte : public QThread                    //La classe Porte hérite de la classe QThread pour pouvoir être un thread
{
    Q_OBJECT                                    //Les objets Porte doivent être des QObject pour pouvoir être un QThread

public:
    //Attributs
    int Porteid;                                //Entier définissant un ID pour chaque porte
    bool is_open ;                              //Flag indiquant si la porte est totalement ouverte ou non
    bool emergency_status;                      //Flag indiquant si la porte est en état d'urgence ou non
    bool breakdown_status;                      //Flag indiquant si la porte est en panne ou non
    bool alarm_status;                          //Falg indiquant si l'alarme est allumée ou non
    int transition;                             //Etat de transition en % (0 ==> début; 100 ==> fin)
    QTimer * timer;                             //Timer necessaire pour (au moins) implémenter l'ouverture de la porte en 10s


    //Méthodes
    Porte(int id);                              //Constructeur
    ~Porte();                                   //Destructeur
    void connexion (QMainWindow *W);            //Fonction regroupant tous les connects
    void run();                                 //Fonction de lancement du thread en boucle
    void closing(int percent);                  //Fonction de fermeture de la porte
    void opening(int percent);                  //Fonction d'ouverture de la porte


    //Slots
public slots:
    void door_change_state(int state, int id);  //Slot de gestion du mode de fonctionnement de la porte
    void show_state(int, int);                  //Slot d'affichage de l'état de la porte
    void update_open_door();                    //Slot de mise à jour de l'état de la porte pendant l'ouverture de celle-ci
    void update_close_door();                   //Slot de mise à jour de l'état de la porte pendant la fermeture de celle-ci
    void arret_porte();                         //Slot d'arrêt immédiat de la porte
    void emergency_event(void);                 //Slot de gesttion de l'état d'urgence
    void panne(int);                            //Slot de passage en état de panne
    void sortie_panne();                        //Slot de sorte de panne (reprise sur panne)

    //Signaux
signals :
    void show_state_open_sig(bool*,int);        //Signal d'affichage de l'état ouvert
    void open_door_sig(int,int);                //Signal d'ouverture
    void show_state_close_sig(bool*,int);       //Signal d'affichage de l'état fermé
    void close_door_sig(int,int);               //Signal de fermeture
    void show_state_arret_sig(bool*,int);       //Signal d'affichage de l'état d'arrêt
    void control_door_sig(int ,int);            //Signal
    void position_sig(int,int);                 //Signal indiquant la position de la porte
    void emergency_status_porte_sig();          //Signal portant le message d'arrêt d'urgence


};


#endif // PORTE_H


