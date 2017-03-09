#ifndef SIGNAL_H
#define SIGNAL_H

#include "Modèle/Ecluse.h"
#include <QThread>
#include <QMainWindow>

class Signal : public QThread
{
    Q_OBJECT
public:
    explicit Signal(int);
    ~Signal();
    int id;
    //Feux
    bool green;
    bool red;

public slots:
    void connexion(QMainWindow *W);
    void set_green(int id);
    void set_red(int id);

};

#endif // SIGNAL_H
