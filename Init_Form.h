#ifndef INIT_FORM_H
#define INIT_FORM_H


#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QScreen>
#include <QApplication>
#include <QInputDialog>
#include <QAction>
#include <QHeaderView>
#include <QFileDialog>
#include "Field.h"
#include "Info.h"
#include "gamer_info.h"

class Init_Form; //Prototipo per rendere accessibile Init_Form da Gamer_Properties

class Gamer_Properties : public QWidget
{

    Q_OBJECT

public:
    Gamer_Properties(QWidget *parent = nullptr, Init_Form *Tmp_Form = nullptr);

    void Edit_Gamer(QTableWidget *List_Widget = nullptr, QVector <Gamer *> *Gamers_List = nullptr);


private:
    QFormLayout *Form_Layout = new QFormLayout(this);

    QLineEdit *Name_Editor = new QLineEdit(this);

    QPushButton *Avatar_Chooser = new QPushButton(QIcon(":/icons/multimedia/icons/list-add.svg"), "Click to select an avatar", this);

    QMetaObject::Connection File_Connection;

    Init_Form *Init = nullptr;
};


class Init_Form : public QWidget
{

    Q_OBJECT

public:
    Init_Form();

    ~Init_Form();

    //Variables
    int gamers_counter = 1; //Il numero minimo di giocatori è 1

    QTableWidget *List_Widget = new QTableWidget(1, 1); //No parentela

    QVector <Gamer*> Gamers_List;

    void Init_Call();


private:
    void Lists_Creator();

    void Gamers_Editor(); //Editor dei giocatori

    //Special
    QScreen *Screen = QGuiApplication::primaryScreen(); //La variabile Scrren contiene le informazioni del display

    QInputDialog *Gamers_Input = new QInputDialog (this);

    QHBoxLayout *HLayout = new QHBoxLayout(); //Non dichiaro un padre perché verrà incluso in VLayout

    QVBoxLayout *VLayout = new QVBoxLayout(this); //Layout verticale

    QPushButton *Finish = new QPushButton("&Finish", this); //Pulsante per terminare l'aggiunta

    Gamer_Properties *Gamer_Prop = new Gamer_Properties(this, this);

    QSplitter *Game_Window = new QSplitter (nullptr);

    Field *Campo = new Field (Game_Window);


};

#endif
