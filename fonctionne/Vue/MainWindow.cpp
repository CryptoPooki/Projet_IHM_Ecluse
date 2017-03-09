//Bibliothèques nécessaires
#include "Vue/MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>

////////////////////////////////////////////////    Méthodes    //////////////////////////////////////////////////
//Constructeur
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Setup
    ui->setupUi(this);

    //Initialisation
    ui->Fermer_Porte_amont->setChecked(true);
    ui->Fermer_Porte_aval->setChecked(true);
    ui->Fermer_Vanne_remplissage->setChecked(true);
    ui->Fermer_Vanne_vidage->setChecked(true);
    ui->Feu_aval_rouge->setChecked(true);
    ui->Feu_amont_rouge->setChecked(true);
    emergency_status = false;
    //Partie Etat
    ui->Panne_Porte_amont->hide();
    ui->Panne_Porte_aval->hide();
    ui->Fermer_Porte_amont->setChecked(true);
    ui->Fermer_Porte_aval->setChecked(true);
    ui->Panne_Vanne_remplissage->hide();
    ui->Vanne1->hide();
    ui->Vanne2->hide();
    ui->Panne_Vanne_vidage->hide();
    ui->Barre_de_transition->hide();
    ui->Transition->hide();
    ui->Transition_Porte_amont->hide();
    ui->Transition_Porte_aval->hide();
    ui->Etat->hide();
    ui->Panne->hide();
    ui->Porte_amont->hide();
    ui->Porte_aval->hide();
    ui->Panne_globale->hide();
    ui->Transition_Vanne_remplissage->hide();
    ui->Transition_Vanne_vidage->hide();
    ui->Barre_de_transition->setValue(100);
    //Partie Commandes
    ui->Fermer_Vanne_remplissage->hide();
    ui->Fermer_Vanne_vidage->hide();
    ui->Feu_amont_rouge->setDisabled(true);
    ui->Feu_amont_vert->setDisabled(true);
    ui->Feu_aval_rouge->setDisabled(true);
    ui->Feu_aval_vert->setDisabled(true);
    ui->Vanne1_2->setText("Montee");
    ui->Vanne2_2->setText("Descente");
    ui->Porte_aval_2->setText("Entree sas");
    ui->Porte_amont_2->setText("Sortie Sas");
    ui->Fermer_Porte_amont->hide();
    ui->Fermer_Porte_aval->hide();
    ui->Ouvrir_Vanne_remplissage->setText("");
    ui->Ouvrir_Vanne_vidage->setText("");
    ui->Ouvrir_Porte_amont->setText("");
    ui->Ouvrir_Porte_aval->setText("");
    ui->Arret_Porte_Amont->hide();
    ui->Arret_Porte_Aval->hide();
    //Partie annexe
    ui->Saisie_ID->show();
    ui->Saisie_MdP->show();
    ui->MdP->show();
    ui->ID->show();
    //MAJ mode
    mode_auto = true;
    ui->De_connexion->setText("Connexion");

    //Création de pointeurs vers les objets du modèle
    vanne_remplissage = new Vanne(1);
    vanne_vidage = new Vanne(0);
    porte_amont = new Porte(0);
    porte_aval = new Porte(1);
    Signal* signal_amont = new Signal(0);
    Signal* signal_aval = new Signal(1);


    porte_amont->connexion(this);
    porte_amont->start();
    porte_amont_stat = 0;

    porte_aval->connexion(this);
    porte_aval->start();
    porte_aval_stat = 0;


    vanne_remplissage->connexion(this);
    vanne_remplissage_stat =0;
    vanne_vidage_stat = 0;
    vanne_vidage->connexion(this);
    vanne_remplissage->start();
    vanne_vidage->start();

    transit_vanne_remplissage = 0;
    transit_vanne_vidage = 0;

    signal_aval_stat = false;
    signal_amont_stat= false;
    signal_amont->connexion(this);
    signal_amont->start();

    signal_aval->connexion(this);
    signal_aval->start();

    niveau_eau = 0;
    //Connexions


    //Ouverture porte amont
    connect(this->porte_amont, SIGNAL(show_state_open_sig(bool*,int)), this, SLOT(control_open_door(bool*,int)) );
    connect(this->porte_amont, SIGNAL(open_door_sig(int,int)), this, SLOT(open_door(int,int)) );

    //Fermeture porte amont
    connect(this->porte_amont, SIGNAL(show_state_close_sig(bool*,int)), this, SLOT(control_close_door(bool*,int)) );
    connect(this->porte_amont, SIGNAL(close_door_sig(int,int)), this, SLOT(close_door(int,int)) );

    // Arrêt porte
    connect(this->porte_amont, SIGNAL(show_state_arret_sig(bool*,int)), this, SLOT(arret_door(bool*,int)));

    // Contrôle d'état
    connect(this->porte_amont, SIGNAL(control_door_sig(int,int)), this, SLOT(Controle_door(int,int)));

    // Position
    connect(this->porte_amont, SIGNAL(position_sig(int,int)), this, SLOT(position(int,int )));

    // Ouverture porte aval
    connect(this->porte_aval, SIGNAL(show_state_open_sig(bool*,int)), this, SLOT(control_open_door(bool*,int)) );
    connect(this->porte_aval, SIGNAL(open_door_sig(int,int)), this, SLOT(open_door(int,int)) );

    //Fermeture porte aval
    connect(this->porte_aval, SIGNAL(show_state_close_sig(bool*,int)), this, SLOT(control_close_door(bool*,int)) );
    connect(this->porte_aval, SIGNAL(close_door_sig(int,int)), this, SLOT(close_door(int,int)) );

    // Arrêt porte
    connect(this->porte_aval, SIGNAL(show_state_arret_sig(bool*,int)), this, SLOT(arret_door(bool*,int)));

    // Contrôle d'état
    connect(this->porte_aval, SIGNAL(control_door_sig(int,int)), this, SLOT(Controle_door(int,int)));

    // Position
    connect(this->porte_aval, SIGNAL(position_sig(int,int)), this, SLOT(position(int,int)));



    // Vanne
    connect(vanne_remplissage,SIGNAL(show_state_open_vanne_sig(bool*,int)), this, SLOT(control_open_vanne(bool*,int))  );
    connect(vanne_remplissage,SIGNAL(open_vanne_sig(int,int)), this, SLOT(open_vanne(int,int))  );

    connect(vanne_remplissage,SIGNAL(show_state_close_vanne_sig(bool*,int)), this, SLOT(control_close_vanne(bool*,int))  );
    connect(vanne_remplissage,SIGNAL(close_vanne_sig(int,int)), this, SLOT(close_vanne(int))  );

    connect(vanne_vidage,SIGNAL(show_state_open_vanne_sig(bool*,int)), this, SLOT(control_open_vanne(bool*,int))  );
    connect(vanne_vidage,SIGNAL(open_vanne_sig(int,int)), this, SLOT(open_vanne(int,int)) );

    connect(vanne_vidage,SIGNAL(show_state_close_vanne_sig(bool*,int)), this, SLOT(control_close_vanne(bool*,int))  );
    connect(vanne_vidage,SIGNAL(close_vanne_sig(int,int)), this, SLOT(close_vanne(int)) );

    //Mode de fonctionnement
    QObject::connect(ui->De_connexion, SIGNAL(clicked(bool)), this, SLOT(change_mode()));
}

//Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

////////////////////////////////////////////////    Slots    /////////////////////////////////////////////////////
//Partie Etat
void MainWindow::on_Panne_Vanne_remplissage_clicked()
{
    emit panne_vanne(1);                                    //Mettre la vanne en panne
    on_URGENCE_clicked();                                   //Clic automatique sur le bouton état d'urgence car le comportement est le même
    ui->Panne_globale->setChecked(true);                    //Allumage de l'indicateur de panne
    ui->Panne_globale->setEnabled(true);                    //Rendre disponible le bouton pour réaliser une reprise sur panne
}

void MainWindow::on_Panne_Vanne_vidage_clicked()
{
    emit panne_vanne(0);
    on_URGENCE_clicked();
    ui->Panne_globale->setChecked(true);
    ui->Panne_globale->setEnabled(true);
}

void MainWindow::on_Panne_Porte_aval_clicked()
{
    emit panne_porte(0);
    on_URGENCE_clicked();
    ui->Panne_globale->setChecked(true);
    ui->Panne_globale->setEnabled(true);
}

void MainWindow::on_Panne_Porte_amont_clicked()
{
    emit panne_porte(1);
    on_URGENCE_clicked();
    ui->Panne_globale->setChecked(true);
    ui->Panne_globale->setEnabled(true);
}

void MainWindow::on_Panne_globale_clicked()
{
    emit sortie_panne_sig();
    on_URGENCE_clicked();
    ui->Panne_Porte_amont->setChecked(false);
    ui->Panne_Porte_aval->setChecked(false);
    ui->Panne_Vanne_remplissage->setChecked(false);
    ui->Panne_Vanne_vidage->setChecked(false);
}

//Partie Commandes
void MainWindow::on_Ouvrir_Porte_amont_clicked()
{
    if (mode_auto)
    {
        ui->Ouvrir_Vanne_remplissage->setChecked(false);
        ui->Ouvrir_Vanne_vidage->setChecked(false);
        std::cout << " entre porte amont clicked" << std::endl;
        if(niveau_eau == 1) // on peut rien faire
            return; // faire un pop-up
        else if (niveau_eau == 0) // en bas -> ouvrir la porte d'en-bas
        {
            std::cout << " en-bas " << std::endl;
            mode_auto = false;
            if (porte_aval_stat == 1 || porte_aval_stat == 3)
            {
                std::cout << "Porte déjà ouverte" << std::endl;
                ui->Ouvrir_Porte_aval->setChecked(false);
                unblock_interface(); // pb pas cii
            }
            else
            {
                on_Ouvrir_Porte_aval_clicked();
                ui->Ouvrir_Porte_aval->setChecked(false);
                block_interface();
            }
            mode_auto = true;
        }
        else if(niveau_eau == 2)
        {
            mode_auto = false;
            if (porte_amont_stat == 1 || porte_amont_stat == 3)
            {
                std::cout << "Porte déjà ouverte" << std::endl;
                ui->Ouvrir_Porte_aval->setChecked(false);// pb pas ici
                unblock_interface();
            }
            else
            {
                on_Ouvrir_Porte_amont_clicked();
                ui->Ouvrir_Porte_aval->setChecked(false);
                block_interface();
            }
            mode_auto = true;
        }
    }
    else
    {
        if( niveau_eau == 0 || niveau_eau == 1 || transit_vanne_remplissage || transit_vanne_vidage)
        {
            std::cout << "Niveau eau pas bon !!" << std::endl;
            ui->Ouvrir_Porte_amont->setChecked(false);
            ui->Fermer_Porte_amont->setChecked(true);
            return;
        }
        if (porte_amont_stat == 1 || porte_amont_stat == 3)
        {
            std::cout << "Porte déjà ouverte" << std::endl;
            ui->Ouvrir_Porte_amont->setChecked(true);
            return ;
        }

        emit show_state_sig(0,0) ; // Ouverture
    }

}

void MainWindow::on_Fermer_Porte_amont_clicked()
{
    if (porte_amont_stat == 0 || porte_amont_stat == 2)
    {
        std::cout << "Porte amont déjà fermée !" << std::endl;
        ui->Fermer_Porte_amont->setChecked(true);
        if(mode_auto)
        {std::cout << "Porte amont déjà fermée !" << std::endl;
            mode_auto=false;
            on_Ouvrir_Vanne_vidage_clicked();
            ui->Ouvrir_Vanne_vidage->setChecked(true);
            mode_auto=true;
            unblock_interface(); // pb pas ici
        }
        return ;
    }

    emit show_state_sig(1,0) ;
}

void MainWindow::on_Arret_Porte_Amont_clicked()
{
    if (porte_amont_stat == 4)
    {
        std::cout << "Porte déjà arrêtée" << std::endl;
        ui->Arret_Porte_Amont->setChecked(true);
        return ;
    }
    emit show_state_sig(2,0) ;
}

void MainWindow::on_Ouvrir_Porte_aval_clicked()
{
    if (mode_auto)
    {
        ui->Ouvrir_Vanne_remplissage->setChecked(false);
        ui->Ouvrir_Vanne_vidage->setChecked(false);
        std::cout << " mode auto " << std::endl;
        if(niveau_eau == 1) // on peut rien faire
        {
            std::cout << " milieu " << std::endl;
            return; // faire un pop-up
        }
        else if (niveau_eau == 0) // en bas -> ouvrir la porte d'en-bas
        {
            mode_auto = false;
            if (porte_aval_stat == 1 || porte_aval_stat == 3)
            {
                std::cout << "Porte déjà ouverte" << std::endl;
                unblock_interface(); // pb pas ici
                ui->Ouvrir_Porte_amont->setChecked(false);
            }
            else
            {
                on_Ouvrir_Porte_aval_clicked();
                ui->Ouvrir_Porte_amont->setChecked(false);
                block_interface();
            }
            mode_auto = true;
        }
        else if(niveau_eau == 2)
        {
            mode_auto = false;
            if (porte_amont_stat == 1 || porte_amont_stat == 3)
            {
                std::cout << "Porte déjà ouverte" << std::endl;
                unblock_interface(); // pb pas ici
                ui->Ouvrir_Porte_amont->setChecked(false);
            }
            else
            {
                on_Ouvrir_Porte_amont_clicked();
                ui->Ouvrir_Porte_amont->setChecked(false);
                block_interface();
            }
            mode_auto = true;
        }
    }
    else
    {
        if(niveau_eau == 1 || niveau_eau == 2 || transit_vanne_remplissage || transit_vanne_vidage)
        {
            std::cout << "Niveau eau pas bon" << std::endl;
            ui->Ouvrir_Porte_aval->setChecked(false);
            ui->Fermer_Porte_aval->setChecked(true);
            return;
        }
        if (porte_aval_stat == 1 || porte_aval_stat == 3)
        {
            std::cout << "Porte déjà ouverte" << std::endl;
            ui->Ouvrir_Porte_aval->setChecked(true);
            return ;
        }

        emit show_state_sig(0,1) ; // Ouverture
    }
}

void MainWindow::on_Fermer_Porte_aval_clicked()
{
    if (porte_aval_stat == 0 || porte_aval_stat == 2)
    {
        std::cout << "Porte aval déjà fermée" << std::endl;
        ui->Fermer_Porte_aval->setChecked(true);
        if(mode_auto)
        {
            mode_auto=false;
            on_Ouvrir_Vanne_remplissage_clicked();
            ui->Ouvrir_Vanne_remplissage->setChecked(true);
            mode_auto=true;
            unblock_interface(); // pb pas ici
        }
        return ;
    }
    emit show_state_sig(1,1) ;
}

void MainWindow::on_Arret_Porte_Aval_clicked()
{
    if (porte_aval_stat == 4)
    {
        std::cout << "Porte déjà arrêtée" << std::endl;
        ui->Arret_Porte_Aval->setChecked(true);
        return ;
    }
    emit show_state_sig(2,1) ;
}

void MainWindow::on_Ouvrir_Vanne_remplissage_clicked()
{
    if(mode_auto)
    {
        ui->Ouvrir_Vanne_vidage->setChecked(false);
        mode_auto = false;
        on_Fermer_Vanne_vidage_clicked();
        mode_auto = true;
        vanne_vidage_stat = 0;
        ui->Ouvrir_Porte_aval->setChecked(false);
        ui->Ouvrir_Porte_amont->setChecked(false);
        if(niveau_eau == 1) // on peut rien faire
        {
            std::cout << " milieu " << std::endl;
            return; // faire un pop-up
        }
        else if (niveau_eau == 0) // en bas -> ouvrir la porte d'en-bas
        {
            std::cout << " en-bas " << std::endl;
            on_Feu_aval_rouge_clicked();
            ui->Feu_aval_rouge->setChecked(true);
            on_Fermer_Porte_aval_clicked();
            block_interface();
        }
        else if(niveau_eau == 2)
        {
            std::cout << "déjà en haut" << std::endl;
            ui->Ouvrir_Vanne_remplissage->setChecked(true);
        }
    }
    else
    {
        if(porte_aval_stat == 1 || porte_aval_stat== 3)
        {
            std::cout << "Porte aval ouverte !!" << std::endl;
            ui->Ouvrir_Vanne_remplissage->setChecked(false);
            return;
        }
        if(vanne_remplissage_stat == 1) // vanne open
        {
            std::cout << "Vanne déjà remplie" << std::endl;
            ui->Ouvrir_Vanne_remplissage->setChecked(true);
            return ;
        }
        ui->Transition_Vanne_remplissage->setChecked(true);
        emit show_state_vanne_sig(0,1);
    }
}

void MainWindow::on_Fermer_Vanne_remplissage_clicked()
{
    if(vanne_remplissage_stat == 0) // vanne fermée
    {
        std::cout << "Vanne déjà fermée" << std::endl;
        ui->Fermer_Vanne_remplissage->setChecked(true);
        return ;
    }
    emit show_state_vanne_sig(1,1); // demande de fermeture (1) de la vanne remplissage (2ème 1)
}

void MainWindow::on_Ouvrir_Vanne_vidage_clicked()
{
    if(mode_auto)
    {
        ui->Ouvrir_Vanne_remplissage->setChecked(false);
        mode_auto = false;
        on_Fermer_Vanne_remplissage_clicked();
        mode_auto = true;
        vanne_remplissage_stat = 0;
        ui->Ouvrir_Porte_aval->setChecked(false);
        ui->Ouvrir_Porte_amont->setChecked(false);
        if(niveau_eau == 1) // on peut rien faire
            return; // faire un pop-up
        else if (niveau_eau == 0) // en bas -> ouvrir la porte d'en-bas
        {
            std::cout << "déjà en-bas " << std::endl;
            ui->Ouvrir_Vanne_vidage->setChecked(true);
        }
        else if(niveau_eau == 2)
        {
            on_Feu_amont_rouge_clicked();
            ui->Feu_amont_rouge->setChecked(true);
            on_Fermer_Porte_amont_clicked();
            block_interface();
        }
    }
    else
    {
        if(porte_amont_stat == 1 || porte_amont_stat== 3)
        {
            std::cout << "Porte amont ouverte !!" << std::endl;
            ui->Ouvrir_Vanne_vidage->setChecked(false);
            return;
        }
        if(vanne_vidage_stat == 1) // vanne open
        {
            std::cout << "Vanne déjà remplie" << std::endl;
            ui->Ouvrir_Vanne_vidage->setChecked(true);
            return ;
        }
        emit show_state_vanne_sig(0,0);
        ui->Transition_Vanne_vidage->setChecked(true);
    }

}

void MainWindow::on_Fermer_Vanne_vidage_clicked()
{
    if(vanne_vidage_stat == 0) // vanne fermée
    {
        std::cout << "Vanne déjà fermée" << std::endl;
        ui->Fermer_Vanne_vidage->setChecked(true);
        return ;
    }
    emit show_state_vanne_sig(1,0); // demande de fermeture (1) de la vanne remplissage (2ème 1)
}

void MainWindow::on_Feu_amont_vert_clicked()
{
    if(signal_amont_stat )
    {
        std::cout << "Feu amont déjà vert" << std::endl;
        ui->Feu_amont_vert->setChecked(true);
        return;
    }
    emit feu_vert(0);
    signal_amont_stat = true;
    ui->Feu_amont_rouge->setChecked(false);
}

void MainWindow::on_Feu_amont_rouge_clicked()
{
    if(!signal_amont_stat )
    {
        std::cout << "Feu amont déjà rouge" << std::endl;
        ui->Feu_amont_rouge->setChecked(true);
        return;
    }
    emit feu_rouge(0);
    signal_amont_stat = false;
    ui->Feu_amont_vert->setChecked(false);
}

void MainWindow::on_Feu_aval_rouge_clicked()
{
    if(!signal_aval_stat )
    {
        std::cout << "Feu aval déjà rouge" << std::endl;
        ui->Feu_aval_rouge->setChecked(true);
        return;
    }
    emit feu_rouge(1);
    signal_aval_stat = false;
    ui->Feu_aval_vert->setChecked(false);
}

void MainWindow::on_Feu_aval_vert_clicked()
{
    if(signal_aval_stat )
    {
        std::cout << "Feu aval déjà vert" << std::endl;
        ui->Feu_aval_vert->setChecked(true);
        return;
    }
    emit feu_vert(1);
    signal_aval_stat = true;
    ui->Feu_aval_rouge->setChecked(false);
}



//Partie annexe
void MainWindow::on_URGENCE_clicked()
{
    emergency_status = !emergency_status;

    if(emergency_status)
    {
        if (porte_aval_stat == 2 || porte_aval_stat == 3)
        {
            ui->Fermer_Porte_aval->setChecked((false));
            ui->Ouvrir_Porte_aval->setChecked((false));
            ui->Arret_Porte_Aval->setChecked((true));
            porte_aval_stat = 4;
        }
        if (porte_amont_stat == 2 || porte_amont_stat == 3)
        {
            ui->Fermer_Porte_amont->setChecked((false));
            ui->Ouvrir_Porte_amont->setChecked((false));
            ui->Arret_Porte_Amont->setChecked((true));
            porte_amont_stat = 4;
        }

        on_Fermer_Vanne_remplissage_clicked(); // fermeture vanne remplissage
        ui->Fermer_Vanne_remplissage->setChecked(true);
        on_Fermer_Vanne_vidage_clicked(); // fermeture vanne vidage
        ui->Fermer_Vanne_vidage->setChecked(true);

        on_Feu_amont_rouge_clicked();
        on_Feu_aval_rouge_clicked();
        ui->Feu_aval_vert->setChecked(false);
        ui->Feu_aval_rouge->setChecked(true);
        ui->Feu_amont_vert->setChecked(false);
        ui->Feu_amont_rouge->setChecked(true);

        QList<QWidget*> All = ui->centralWidget->findChildren<QWidget *>();
        for (int i = 0 ; i < All.size(); i++)
            All.at(i)->setDisabled(true);
        ui->horizontalLayoutWidget->setEnabled(true);
        ui->URGENCE->setEnabled(true);
        ui->Saisie_ID->setEnabled(true);
        ui->Saisie_MdP->setEnabled(true);
        ui->De_connexion->setEnabled(true);

    }
    else if (!mode_auto)
    {
        QList<QWidget*> All = ui->centralWidget->findChildren<QWidget *>();
        for (int i = 0 ; i < All.size(); i++)
            All.at(i)->setEnabled(true);
    }
    emit emergency_sig();
}


//Slots supplémentaires


void MainWindow::control_open_door(bool * status, int porte)
{
    if( status[1])
    {
        std::cout << "emergency" << std::endl;
        if(porte== 0)
            ui->Ouvrir_Porte_amont->setChecked(!ui->Ouvrir_Porte_amont->isChecked());
        else
            ui->Ouvrir_Porte_aval->setChecked(!ui->Ouvrir_Porte_aval->isChecked());
    }
    else if (status[2])
    {
        std::cout << "breakdown" << std::endl;
        if (porte == 0)
            ui->Ouvrir_Porte_amont->setChecked(!ui->Ouvrir_Porte_amont->isChecked());
        else
            ui->Ouvrir_Porte_aval->setChecked(!ui->Ouvrir_Porte_aval->isChecked());
    }
    else if (status[3])
    {
        std::cout << "alarm" << std::endl;
        if (porte == 0)
            ui->Ouvrir_Porte_amont->setChecked(!ui->Ouvrir_Porte_amont->isChecked());
        else
            ui->Ouvrir_Porte_aval->setChecked(!ui->Ouvrir_Porte_aval->isChecked());
    }
    else if (porte == 0 &&porte_amont_stat == 1)
    {
        std::cout << "porte déjà ouverte" << std::endl;
        ui->Ouvrir_Porte_amont->setChecked(!ui->Ouvrir_Porte_amont->isChecked());
    }
    else if( porte == 1 && porte_aval_stat == 1)
    {
            std::cout << "porte déjà ouverte" << std::endl;
            ui->Ouvrir_Porte_aval->setChecked(!ui->Ouvrir_Porte_aval->isChecked());
    }
    else
    {
        if (porte == 0 ) // amont
        {
            ui->Fermer_Porte_amont->setChecked(false);
            ui->Transition_Porte_amont->setChecked(true);
            ui->Arret_Porte_Amont->setChecked(false);
            porte_amont_stat = 3;
            emit change_door_sig(0,porte);
        }
        else
        {
            ui->Fermer_Porte_aval->setChecked(false);
            ui->Transition_Porte_aval->setChecked(true);
            ui->Arret_Porte_Aval->setChecked(false);
            porte_aval_stat = 3;
            emit change_door_sig(0,porte);
        }
    }
}

void MainWindow::control_close_door(bool * status,int porte)
{
    if( status[1])
    {
        std::cout << "emergency" << std::endl;
        if (porte == 0)
            ui->Fermer_Porte_amont->setChecked(!ui->Fermer_Porte_amont->isChecked());
        else
            ui->Fermer_Porte_aval->setChecked(!ui->Fermer_Porte_aval->isChecked());
    }
    else if (status[2])
    {
        std::cout << "breakdown" << std::endl;
        if (porte == 0)
            ui->Fermer_Porte_amont->setChecked(!ui->Fermer_Porte_amont->isChecked());
        else
            ui->Fermer_Porte_aval->setChecked(!ui->Fermer_Porte_aval->isChecked());
    }
    else if (status[3])
    {
        std::cout << "alarm" << std::endl;
        if (porte == 0)
            ui->Fermer_Porte_amont->setChecked(!ui->Fermer_Porte_amont->isChecked());
        else
            ui->Fermer_Porte_aval->setChecked(!ui->Fermer_Porte_aval->isChecked());
    }
    else if (!status[0])
    {
        std::cout << "porte déjà fermée" << std::endl;
        if (porte == 0)
            ui->Fermer_Porte_amont->setChecked(!ui->Fermer_Porte_amont->isChecked());
        else
            ui->Fermer_Porte_aval->setChecked(!ui->Fermer_Porte_aval->isChecked());
    }
    else
    {
        if (porte == 0)
        {
            ui->Ouvrir_Porte_amont->setChecked(false);
            ui->Arret_Porte_Amont->setChecked(false);
            ui->Transition_Porte_amont->setChecked(true);
            porte_amont_stat = 2;
            emit change_door_sig(1,porte);
        }
        else
        {
            ui->Ouvrir_Porte_aval->setChecked(false);
            ui->Arret_Porte_Aval->setChecked(false);
            ui->Transition_Porte_aval->setChecked(true);
            porte_aval_stat = 2;
            emit change_door_sig(1,porte);
        }
    }
}

void MainWindow::open_door(int state,int id)
{
    if (id == 0)
    {
        ui->Transition_Porte_amont->setChecked(false);
        porte_amont_stat = 2;
        if(mode_auto)
        {
            on_Feu_amont_vert_clicked();
            ui->Feu_amont_vert->setChecked(true);
            unblock_interface();
        }
    }
    else
    {
        ui->Transition_Porte_aval->setChecked(false);
        porte_aval_stat = 2;
        if(mode_auto)
        {
            on_Feu_aval_vert_clicked();
            ui->Feu_aval_vert->setChecked(true);
            unblock_interface();
        }
    }

    if (state == 1 )
        std::cout << "tout a bien marché" << std::endl;
    else
        std::cout << "error" << std::endl;
}

void MainWindow::close_door(int state, int id)
{
    if (id == 0)
    {
        ui->Transition_Porte_amont->setChecked(false);
        porte_amont_stat = 1;
        if(mode_auto)
        {
            mode_auto = false;
            on_Ouvrir_Vanne_vidage_clicked();
            mode_auto = true;
            ui->Ouvrir_Vanne_vidage->setChecked(true);
            unblock_interface();
        }
    }
    else
    {
        ui->Transition_Porte_aval->setChecked(false);
        porte_aval_stat = 1;
        if(mode_auto)
        {
            mode_auto = false;
            on_Ouvrir_Vanne_remplissage_clicked();
            mode_auto = true;
            ui->Ouvrir_Vanne_remplissage->setChecked(true);
            unblock_interface();
        }
    }
    if (state == 0 )
        std::cout << "tout a bien marché" << std::endl;
    else
        std::cout << "error" << std::endl;
}

void MainWindow::arret_door(bool * status,int id)
{
    if( status[1])
    {
        std::cout << "emergency" << std::endl;
        if (id == 0)
            ui->Arret_Porte_Amont->setChecked(!ui->Arret_Porte_Amont->isChecked());
        else
            ui->Arret_Porte_Aval->setChecked(!ui->Arret_Porte_Aval->isChecked());
    }
    else if (status[2])
    {
        std::cout << "breakdown" << std::endl;
        if (id == 0)
            ui->Arret_Porte_Amont->setChecked(!ui->Arret_Porte_Amont->isChecked());
        else
            ui->Arret_Porte_Aval->setChecked(!ui->Arret_Porte_Aval->isChecked());
    }
    else if (status[3])
    {
        std::cout << "alarm" << std::endl;
        if (id == 0)
            ui->Arret_Porte_Amont->setChecked(!ui->Arret_Porte_Amont->isChecked());
        else
            ui->Arret_Porte_Aval->setChecked(!ui->Arret_Porte_Aval->isChecked());
    }
    else
    {
        if (id == 0)
        {
            ui->Ouvrir_Porte_amont->setChecked(false);
            ui->Fermer_Porte_amont->setChecked(false);
            ui->Transition_Porte_amont->setChecked(false);
            porte_amont_stat = 4;
            std::cout << "Porte arrêtée" << std::endl;
        }
        else
        {
            ui->Ouvrir_Porte_aval->setChecked(false);
            ui->Fermer_Porte_aval->setChecked(false);
            ui->Transition_Porte_aval->setChecked(false);
            porte_aval_stat = 4;
            std::cout << "Porte arrêtée" << std::endl;

        }
    }
}

// fonction à laquelle on envoie les signaux réguliers et qui contrôle si tout se passe comme prévu
void MainWindow::Controle_door(int etat, int id)
{
    if (id == 0)
    {
        porte_amont_stat = etat;
        if(etat != porte_amont_stat)
            std::cout << "Problème" << std::endl;
        else
            std::cout << "Good status" << std::endl;
    }
    else
    {
        porte_aval_stat = etat;
        if(etat != porte_aval_stat)
            std::cout << "Problème" << std::endl;
        else
            std::cout << "Good status" << std::endl;
    }
}

void MainWindow::position(int pos, int id)
{
    int max = pos;
    if (id == 0) // porte amont
    {
        if(porte_amont_stat == 1 || porte_amont_stat == 3)
            max = 100 - pos;
    }
    else if (id == 1) // porte aval
    {
        if(porte_aval_stat == 1 || porte_aval_stat == 3)
            max = 100 - pos;
    }

    std::cout << QString::number(pos).toStdString() << std::endl;
    ui->Barre_de_transition->setValue(max);
}

void MainWindow::control_open_vanne(bool * status, int vanne)
{
    if( status[1])
    {
        std::cout << "emergency" << std::endl;
        if(vanne== 1)
            ui->Ouvrir_Vanne_remplissage->setChecked(!ui->Ouvrir_Vanne_remplissage->isChecked());
        else
            ui->Ouvrir_Vanne_vidage->setChecked(!ui->Ouvrir_Vanne_vidage->isChecked());
    }
    else if (status[2])
    {
        std::cout << "breakdown" << std::endl;
        if(vanne== 1)
            ui->Ouvrir_Vanne_remplissage->setChecked(!ui->Ouvrir_Vanne_remplissage->isChecked());
        else
            ui->Ouvrir_Vanne_vidage->setChecked(!ui->Ouvrir_Vanne_vidage->isChecked());
    }
    else if (status[3])
    {
        std::cout << "alarm" << std::endl;
        if(vanne== 1)
            ui->Ouvrir_Vanne_remplissage->setChecked(!ui->Ouvrir_Vanne_remplissage->isChecked());
        else
            ui->Ouvrir_Vanne_vidage->setChecked(!ui->Ouvrir_Vanne_vidage->isChecked());
    }
    else if (vanne == 1 &&vanne_remplissage_stat == 1)
    {
        std::cout << "vanne déjà ouverte" << std::endl;
        ui->Ouvrir_Vanne_remplissage->setChecked(!ui->Ouvrir_Vanne_remplissage->isChecked());
    }
    else if( vanne == 0 && vanne_vidage_stat == 1)
    {
        std::cout << "vanne déjà ouverte" << std::endl;
        ui->Ouvrir_Vanne_vidage->setChecked(!ui->Ouvrir_Vanne_vidage->isChecked());
    }
    else
    {
        if (vanne == 1 ) // remplissage
        {
            ui->Fermer_Vanne_remplissage->setChecked(false);
            vanne_remplissage_stat = 1;
            transit_vanne_remplissage = 1;
            emit change_vanne_sig(0,vanne);
        }
        else
        {
            ui->Fermer_Vanne_vidage->setChecked(false);
            vanne_vidage_stat = 1;
            transit_vanne_vidage = 1;
            emit change_vanne_sig(0,vanne);
        }
    }
}

void MainWindow::open_vanne(int state,int id)
{
    if (state == 1 )
        std::cout << "tout a bien marché" << std::endl;
    else
        std::cout << "error" << std::endl;

    if (vanne_vidage_stat == 1 && vanne_remplissage_stat == 1)
    {
        niveau_eau = 1 ;
        ui->Transition_Vanne_vidage->setChecked(false);
        ui->Transition_Vanne_remplissage->setChecked(false);
    }
    else if ( id == 1 )
    {
        niveau_eau = 2 ;
        transit_vanne_remplissage = 0;
        vanne_vidage->transition = 100;
        ui->Transition_Vanne_remplissage->setChecked(false);
    }
    else
    {
        niveau_eau = 0 ;
        transit_vanne_vidage = 0;
        vanne_remplissage->transition = 100;
        ui->Transition_Vanne_vidage->setChecked(false);
    }
    if (mode_auto)
        unblock_interface();
}

void MainWindow::close_vanne(int state)
{
    if (state == 0 )
        std::cout << "tout a bien marché" << std::endl;
    else
        std::cout << "error" << std::endl;
}

void MainWindow::control_close_vanne(bool * status,int vanne)
{
    if( status[1])
    {
        std::cout << "emergency" << std::endl;
        if (vanne == 1)
            ui->Fermer_Vanne_remplissage->setChecked(!ui->Fermer_Vanne_remplissage->isChecked());
        else
            ui->Fermer_Vanne_vidage->setChecked(!ui->Fermer_Vanne_vidage->isChecked());
    }
    else if (status[2])
    {
        std::cout << "breakdown" << std::endl;
        if (vanne == 1)
            ui->Fermer_Vanne_remplissage->setChecked(!ui->Fermer_Vanne_remplissage->isChecked());
        else
            ui->Fermer_Vanne_vidage->setChecked(!ui->Fermer_Vanne_vidage->isChecked());
    }
    else if (status[3])
    {
        std::cout << "alarm" << std::endl;
        if (vanne == 1 )
            ui->Fermer_Vanne_remplissage->setChecked(!ui->Fermer_Vanne_remplissage->isChecked());
        else
            ui->Fermer_Vanne_vidage->setChecked(!ui->Fermer_Vanne_vidage->isChecked());
    }
    else if (!status[0])
    {
        std::cout << "vanne déjà fermée" << std::endl;
        if (vanne == 1)
            ui->Fermer_Vanne_remplissage->setChecked(!ui->Fermer_Vanne_remplissage->isChecked());
        else
            ui->Fermer_Vanne_vidage->setChecked(!ui->Fermer_Vanne_vidage->isChecked());
    }
    else
    {
        if (vanne == 1)
        {
            ui->Ouvrir_Vanne_remplissage->setChecked(false);
            vanne_remplissage_stat = 0;
            emit change_vanne_sig(0,vanne);
        }
        else
        {
            ui->Ouvrir_Vanne_vidage->setChecked(false);
            vanne_vidage_stat = 0;
            emit change_vanne_sig(0,vanne);
        }
    }
}

void MainWindow::change_mode()
{
    if (mode_auto) //De automatique vers manuel
    {
        //Récupération des données indiquées dans les LineEdit
        QString ID = ui->Saisie_ID->text();
        ui->Saisie_ID->setText("");
        QString MdP = ui->Saisie_MdP->text();
        ui->Saisie_MdP->setText("");

        if (ID == QString::fromStdString("admin") && MdP == QString::fromStdString("")) //Success
        {
            //Partie Etat
            ui->Panne_Porte_amont->show();
            ui->Panne_Porte_aval->show();
            ui->Panne_Vanne_remplissage->show();
            ui->Panne_Vanne_vidage->show();
            ui->Barre_de_transition->show();
            ui->Transition->show();
            ui->Transition_Porte_amont->show();
            ui->Transition_Porte_aval->show();
            ui->Transition_Vanne_remplissage->show();
            ui->Transition_Vanne_vidage->show();
            ui->Etat->show();
            ui->Panne->show();
            ui->Porte_amont->show();
            ui->Porte_aval->show();
            ui->Vanne1->show();
            ui->Vanne2->show();
            ui->Panne_globale->show();

            //Partie Commandes
            ui->Fermer_Vanne_remplissage->show();
            ui->Fermer_Vanne_vidage->show();
            ui->Ouvrir_Vanne_remplissage->setText("Ouvert");
            ui->Ouvrir_Vanne_vidage->setText("Ouvert");
            ui->Vanne1_2->setText("Remplissage");
            ui->Vanne2_2->setText("Vidage");
            ui->Porte_amont_2->setText("Porte amont");
            ui->Porte_aval_2->setText("Porte aval");
            ui->Fermer_Porte_amont->show();
            ui->Fermer_Porte_aval->show();
            ui->Ouvrir_Porte_amont->setText("Ouvert");
            ui->Ouvrir_Porte_aval->setText("Ouvert");
            ui->Arret_Porte_Amont->show();
            ui->Arret_Porte_Aval->show();
            if (!emergency_status)
            {
                ui->Feu_amont_rouge->setEnabled(true);
                ui->Feu_amont_vert->setEnabled(true);
                ui->Feu_aval_rouge->setEnabled(true);
                ui->Feu_aval_vert->setEnabled(true);
            }
            //Partie annexe
            ui->Saisie_ID->hide();
            ui->Saisie_MdP->hide();
            ui->MdP->hide();
            ui->ID->hide();

            //MAJ mode
            mode_auto = false;
            ui->De_connexion->setText("Deconnexion");

        }
        //Debug
        if (ID != QString::fromStdString("admin"))
        {
            ui->Saisie_ID->setText("Mauvais ID");
        }
        if (MdP != QString::fromStdString(""))
        {
            ui->Saisie_MdP->setText("Mauvais MdP");
        }

    } else //De manuel vers automatique
    {
        //Partie Etat
        ui->Panne_Porte_amont->hide();
        ui->Panne_Porte_aval->hide();
        ui->Fermer_Porte_amont->setChecked(true);
        ui->Fermer_Porte_aval->setChecked(true);
        ui->Panne_Vanne_remplissage->hide();
        ui->Vanne1->hide();
        ui->Vanne2->hide();
        ui->Panne_Vanne_vidage->hide();
        ui->Barre_de_transition->hide();
        ui->Transition->hide();
        ui->Transition_Porte_amont->hide();
        ui->Transition_Porte_aval->hide();
        ui->Transition_Vanne_remplissage->hide();
        ui->Transition_Vanne_vidage->hide();
        ui->Etat->hide();
        ui->Panne->hide();
        ui->Porte_amont->hide();
        ui->Porte_aval->hide();
        ui->Panne_globale->hide();

        //Partie Commandes
        ui->Fermer_Vanne_remplissage->hide();
        ui->Fermer_Vanne_vidage->hide();
        ui->Feu_amont_rouge->setDisabled(true);
        ui->Feu_amont_vert->setDisabled(true);
        ui->Feu_aval_rouge->setDisabled(true);
        ui->Feu_aval_vert->setDisabled(true);
        ui->Vanne1_2->setText("Montee");
        ui->Vanne2_2->setText("Descente");
        ui->Porte_aval_2->setText("Entree sas");
        ui->Porte_amont_2->setText("Sortie Sas");
        ui->Fermer_Porte_amont->hide();
        ui->Fermer_Porte_aval->hide();
        ui->Ouvrir_Vanne_remplissage->setText("");
        ui->Ouvrir_Vanne_vidage->setText("");
        ui->Ouvrir_Porte_amont->setText("");
        ui->Ouvrir_Porte_aval->setText("");
        ui->Arret_Porte_Amont->hide();
        ui->Arret_Porte_Aval->hide();


        //Partie annexe
        ui->Saisie_ID->show();
        ui->Saisie_MdP->show();
        ui->MdP->show();
        ui->ID->show();

        //MAJ mode
        mode_auto = true;
        ui->De_connexion->setText("Connexion");

    }

}

void MainWindow::block_interface()
{
    QList<QWidget*> All = ui->centralWidget->findChildren<QWidget *>();
    for (int i = 0 ; i < All.size(); i++)
        All.at(i)->setDisabled(true);
    ui->horizontalLayoutWidget->setEnabled(true);
    ui->URGENCE->setEnabled(true);
}

void MainWindow::unblock_interface()
{
    QList<QWidget*> All = ui->centralWidget->findChildren<QWidget *>();
    for (int i = 0 ; i < All.size(); i++)
        All.at(i)->setEnabled(true);
    ui->Feu_amont_rouge->setEnabled(false);
    ui->Feu_amont_vert->setEnabled(false);
    ui->Feu_aval_rouge->setEnabled(false);
    ui->Feu_aval_vert->setEnabled(false);
}

