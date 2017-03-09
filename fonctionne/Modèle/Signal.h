//Pour éviter les confusions, nous parlerons de "feux" pour l'écluse plutôt que de signaux
#ifndef SIGNAL_H
#define SIGNAL_H

//Bibliothèques nécessaires
#include <QMainWindow>              //Nécessaire pour interagir avec l'interface
#include <QThread>                  //Nécessaire pour pouvoir manipuler les threads

class Signal : public QThread       //La classe Signal hérite de la classe QThread pour pouvoir être un thread
{
    Q_OBJECT                        //Les objets signal doivent être des QObject pour pouvoir être un QThread

public:
    //Attributs
    int Signalid;                   //Entier définissant un ID pour chaque feu
    bool green;                     //Lampe/Diode verte
    bool red;                       //Lampe/Diode rouge

    //Méthodes
    Signal(int);                    //Constructeur
    ~Signal();                      //Destructeur
    void connexion(QMainWindow *W); //Fonction regroupant tous les connects

    //Slots
public slots:
    void set_green(int id);         //Allumer la lampe/diode verte
    void set_red(int id);           //Allumer la diode/lampe rouge

   //Signaux                        //Pas de signaux
};

#endif // SIGNAL_H
