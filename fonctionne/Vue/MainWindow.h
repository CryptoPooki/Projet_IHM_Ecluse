#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Modèle/Porte.h"
#include "Modèle/Vanne.h"
#include "Modèle/Signal.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    bool mode_auto;
    Vanne* vanne_remplissage ;
    Vanne* vanne_vidage ;
    Porte* porte_amont ;
    Porte* porte_aval ;
    //Signal* signal_amont ;
    //Signal* signal_aval ;

    int porte_amont_stat; // 0 : close, 1 : open, 2 : closing, 3 : opening, 4 : stop
    int porte_aval_stat;
    bool emergency_status ;

    int vanne_remplissage_stat; // 0 : close, 1 : open
    int vanne_vidage_stat;

    bool signal_amont_stat;
    bool signal_aval_stat;

    int niveau_eau;

    int transit_vanne_remplissage;
    int transit_vanne_vidage;
    //Liste des Qobjets concernés par le changement de mode de fonctionnement auto/manu
    QObject Hidden[];



private slots:
    void on_Ouvrir_Porte_amont_clicked();
    void control_open_door(bool * status, int id);
    void open_door(int state, int id);

    void on_Fermer_Porte_amont_clicked();
    void control_close_door(bool * status,int);
    void close_door(int state, int id);

    void on_Arret_Porte_Amont_clicked();
    void arret_door(bool * status, int id);
    void Controle_door(int etat,int id);
    void position(int pos, int id);

    void on_URGENCE_clicked();

    void on_Fermer_Porte_aval_clicked();

    void on_Ouvrir_Porte_aval_clicked();

    void on_Arret_Porte_Aval_clicked();

    void on_Ouvrir_Vanne_remplissage_clicked();
    void control_open_vanne(bool * status, int vanne);
    void open_vanne(int state,int id);
    void close_vanne(int state,int id);

    void control_close_vanne(bool * status,int vanne);

    void on_Fermer_Vanne_remplissage_clicked();

    void on_Fermer_Vanne_vidage_clicked();

    void on_Ouvrir_Vanne_vidage_clicked();

    void on_Feu_amont_rouge_clicked();

    void on_Feu_amont_vert_clicked();

    void on_Feu_aval_rouge_clicked();

    void on_Feu_aval_vert_clicked();

    void change_mode();
    void block_interface();
    void unblock_interface();

    void on_Panne_Vanne_remplissage_clicked();

    void on_Panne_Vanne_vidage_clicked();

    void on_Panne_Porte_aval_clicked();

    void on_Panne_Porte_amont_clicked();

    void on_Panne_globale_clicked();

signals:
    void show_state_sig(int i, int id);
    void change_door_sig(int i,int id);
    void emergency_sig();

    void show_state_vanne_sig(int,int);
    void change_vanne_sig(int,int);

    void feu_vert(int);
    void feu_rouge(int);

    void panne_vanne(int);
    void panne_porte(int);
    void sortie_panne_sig();
};



#endif // MAINWINDOW_H


