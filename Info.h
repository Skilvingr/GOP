#ifndef INFO_H //Finestra per info di gioco
#define INFO_H

#if defined (__ANDROID__)
    #define PLATFORM "Android"
#else
    #define PLATFORM "PC"
#endif

#include <QSplitter> //Gestione layout widget
#include <QTableWidget> //Gestione lista giocatori
#include <QVBoxLayout> //Gestione layout verticale
#include <QString> //Gestione stringhe giocatori
#include <QTextEdit>
#include <QMouseEvent>
#include <QScrollBar>
#include "gamer_info.h"

class Log_Widget : public QTextEdit{

public:
    Log_Widget(QWidget *parent = nullptr);

private:
    int delta_y = 0;

    int old_y = 0;

    bool scrolling = false;

    void mousePressEvent(QMouseEvent *event = nullptr);

    void mouseReleaseEvent(QMouseEvent *event = nullptr);

    void mouseMoveEvent(QMouseEvent *event = nullptr);


};

class Info : public QWidget
{
    
    Q_OBJECT //Ereditarietà

public:
    
    Info(QWidget *parent = nullptr, QTableWidget *List_Widget = nullptr); //Costruttore

    QTableWidget *List_Widget = nullptr;

    Log_Widget *Log_Wid = new Log_Widget(this);

private:

    QVBoxLayout *VLayout = new QVBoxLayout(this); //Creazione layout verticale

    QSplitter *InfoSplitter = new QSplitter(this); //Creazione splitter(layout globale)

};


#endif
