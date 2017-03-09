#ifndef VANNE_H
#define VANNE_H

//Bibliothèques nécessaires
#include <QMainWindow>                          //Nécessaire pour interagir avec l'interface
#include <QThread>                              //Nécessaire pour pouvoir manipuler les threads

class Vanne : public QThread                    //La classe Vanne hérite de la classe QThread pour pouvoir être un thread
{
    Q_OBJECT                                    //Les objets vanne doivent être des QObject pour pouvoir être un QThread

public:
    //Attributs
    int Vanneid;                                //Entier définissant un ID pour chaque vanne
    bool is_open ;                              //Flag indiquant si la vanne est totalement ouverte ou non
    bool emergency_status;                      //Flag indiquant si la vanne est en état d'urgence ou non
    bool breakdown_status;                      //Flag indiquant si la vanne est en panne ou non
    bool alarm_status;                          //Falg indiquant si l'alarme est allumée ou non
    int transition;                             //Etat de transition en % (0 ==> début; 100 ==> fin)
    QTimer * timer;                             //Timer necessaire pour (au moins) implémenter l'ouverture de la porte en 10s

    //Méthodes
    Vanne(int id);                              //Constructeur
    ~Vanne();                                   //Destructeur
    void connexion (QMainWindow *W);            //Fonction regroupant tous les connects
    void run();                                 //Fonction de lancement du thread en boucle

    //Slots
public slots:
    void show_state(int i,int id);              //Slot renvoyant l'état de la vanne
    void vanne_change_state(int state, int id );//Slot de gestion de l'état de la vanne
    void update_open_vanne();                   //Slot de ouverture de la vanne
    void update_close_vanne();                  //Slot de fermeture de la vanne
    void emergency_event(void );                //Slot de gestion de l'état d'urgence de la vanne
    void panne(int);                            //Slot de panne
    void sortie_panne();                        //Slot de reprise sur panne


    //Signaux
signals :
    void show_state_open_vanne_sig(bool*,int);  //Signal d'affichage de l'état de la vanne lors de son ouverture
    void open_vanne_sig(int,int);               //Signal d'ouverture de la vanne
    void show_state_close_vanne_sig(bool*,int); //Signal d'affichage de l'état de la vanne lors de sa fermeture
    void close_vanne_sig(int,int);              //Signal de fermeture de la vanne
    void change_vanne_sig(int,int);             //Signal de changement d'état de la vanne
};

#endif // VANNE_H
