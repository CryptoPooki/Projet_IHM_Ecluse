#ifndef VANNE_H
#define VANNE_H

#include <QThread>
#include <QMainWindow>

class Vanne : public QThread
{
    Q_OBJECT

public:
    explicit Vanne(int);
    ~Vanne();
    void run();

    bool is_open ;
    bool emergency_status;
    bool breakdown_status;
    bool alarm_status;

    int Vanneid;
    int transition;
    QTimer* timer;
    void connexion(QMainWindow* W);


public slots:
    void show_state(int i,int id);
    void vanne_change_state(int state, int id );
    void emergency_event(void );
    void panne(int);
    void sortie_panne();
    void update_open_vanne();
    void update_close_vanne();

signals :
    void show_state_open_vanne_sig(bool*,int);
    void change_vanne_sig(int,int);
    void open_vanne_sig(int,int);

    void show_state_close_vanne_sig(bool*,int);
    void close_vanne_sig(int,int);
};

#endif // VANNE_H
