#include "Window.h"


Window::Window(QWidget *parent) : QWidget(parent)
{    
    //Creazione partita

    New_Game = new QPushButton("&New Game", this); //Crea un pulsante per avviare una nuova partita

    Credits = new QPushButton("&Credits", this);

    Quit = new QPushButton("&Exit", this);

    VLayout -> addWidget(New_Game, 1, Qt::AlignCenter);

    VLayout -> addWidget(Credits, 1, Qt::AlignCenter);

    VLayout -> addWidget(Quit, 1, Qt::AlignCenter);

    this -> setLayout(VLayout);

    connect(New_Game, &QPushButton::clicked, this, &Window::NewGame_Init); //Connette il pulsante con il segnale "clicked" allo slot per la nuova partita

    connect(Credits, &QPushButton::clicked, this, &Window::Show_Credits);

    connect(Quit, &QPushButton::clicked, this, &Window::quit);

}


Window::~Window() //Distruttore
{
}


void Window::NewGame_Init()
{
    this -> ~Window(); //Forse da rimuovere (distrugge preventivamente la finestra di menù per mostrare il gioco)

    Init_Form *Form = new Init_Form(); //Crea l'oggetto Form per definire le proprietà dei giocatori
}


void Window::quit()
{
    this -> ~Window(); //Richiama il distruttore padre

    exit(0);
}


void Window::Show_Credits()
{
    QDialog Credits (this);
    QLabel Credits_Label(&Credits);
    Credits_Label.setAlignment(Qt::AlignCenter);
    Credits_Label.setText(QString("Escape From Gop\nThis game was developed by:\nNico Giambi\nYari Polla\nAll Rights Reserved ©"));
    Credits_Label.setStyleSheet("font: 18pt;");
    Credits.resize(Credits_Label.sizeHint());
    Credits.setModal(true);
    Credits.setFixedSize(Credits.size());
    Credits.exec();
}
