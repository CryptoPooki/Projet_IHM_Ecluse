#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Bibliothèques nécessaires
#include <QMainWindow>
#include "Modèle/Porte.h"
#include "Modèle/Vanne.h"
#include "Modèle/Signal.h"

namespace Ui {
class MainWindow;
}
//Configuration par défaut de QtCreator
class MainWindow : public QMainWindow
{
    Q_OBJECT                                    //

public:
    //Attributs
    Ui::MainWindow *ui;                         //Instance d'interface
    bool mode_auto;                             //Flag indiquant si l'interface est en mode automatique ou pas
    Vanne* vanne_remplissage ;                  //Instancation des différentes classes modélisant notre écluse
    Vanne* vanne_vidage ;
    Porte* porte_amont ;
    Porte* porte_aval ;
    Signal* signal_amont ;
    Signal* signal_aval ;

    int niveau_eau;                             //Entier modélisant le niveau d'eau. N'ayant aucune information, nous choisissons un notation arbitraire
                                                // ==> 0 : niveau aval, 1 : niveau milieu, 2 : niveau amont
    bool emergency_status ;                     //Flag modélisant l'état d'urgence général
    int porte_amont_stat;                       //Etat de la porte amont ==> 0 : close, 1 : open, 2 : closing, 3 : opening, 4 : stop
    int porte_aval_stat;                        //Etat de la porte aval  ==> 0 : close, 1 : open, 2 : closing, 3 : opening, 4 : stop
    int vanne_remplissage_stat;                 //Etat de la vanne de remplissage ==> 0 : close, 1 : open
    int vanne_vidage_stat;                      //Etat de la vanne de vidage ==> 0 : close, 1 : open
    bool signal_amont_stat;                     //Flag
    bool signal_aval_stat;
    int transit_vanne_remplissage;              //Entier
    int transit_vanne_vidage;

    //Méthodes                                  //Pas de méthodes
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Slots
private slots:
    //Slots recevant une information depuis l'interface (Slots liés à un bouton de l'interface
    //Section Etat
    void on_Panne_globale_clicked();
    void on_Panne_Vanne_remplissage_clicked();
    void on_Panne_Vanne_vidage_clicked();
    void on_Panne_Porte_aval_clicked();
    void on_Panne_Porte_amont_clicked();
    //Section Commandes
    void on_Feu_amont_rouge_clicked();
    void on_Feu_amont_vert_clicked();
    void on_Feu_aval_rouge_clicked();
    void on_Feu_aval_vert_clicked();
    void on_Ouvrir_Vanne_remplissage_clicked();
    void on_Fermer_Vanne_remplissage_clicked();
    void on_Ouvrir_Vanne_vidage_clicked();
    void on_Fermer_Vanne_vidage_clicked();
    void on_Ouvrir_Porte_amont_clicked();
    void on_Fermer_Porte_amont_clicked();
    void on_Arret_Porte_Amont_clicked();
    void on_Fermer_Porte_aval_clicked();
    void on_Ouvrir_Porte_aval_clicked();
    void on_Arret_Porte_Aval_clicked();
    //Section Annexe
    void on_URGENCE_clicked();

    //Slots supplémentaires
    //Gestion de portes
    void control_open_door(bool * status, int id);
    void open_door(int state, int id);
    void control_close_door(bool * status,int);
    void close_door(int state, int id);
    void arret_door(bool * status, int id);
    void Controle_door(int etat,int id);
    void position(int pos, int id);
    //Gestion de vannes
    void control_open_vanne(bool * status, int vanne);
    void open_vanne(int state,int id);
    void close_vanne(int state);
    void control_close_vanne(bool * status,int vanne);
    //Gestion de modes
    void change_mode();
    void block_interface();
    void unblock_interface();

    //Signaux
signals:
    //Gestion de porte
    void show_state_sig(int i, int id);
    void change_door_sig(int i,int id);
    //Gestion de vanne
    void show_state_vanne_sig(int,int);
    void change_vanne_sig(int,int);
    //Gestion de signaux
    void feu_vert(int);
    void feu_rouge(int);
    //Autres
    void panne_vanne(int);
    void panne_porte(int);
    void emergency_sig();
    void sortie_panne_sig();
};

#endif // MAINWINDOW_H
