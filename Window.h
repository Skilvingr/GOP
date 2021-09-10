#ifndef WINDOW_H //Finestra principale
#define WINDOW_H

#include <QLabel>
#include "Init_Form.h"

class Window : public QWidget
{
    
    Q_OBJECT //Ereditarietà
    
public:
    
    Window(QWidget *parent = nullptr); //Costruttore
        
            
private:    
    
    ~Window(); //Distruttore
    
    
    // Special

    QVBoxLayout *VLayout = new QVBoxLayout (this);
    
    QPushButton *New_Game = nullptr; //Pulsante per "Nuovo gioco"

    QPushButton *Credits = nullptr;

    QPushButton *Quit = nullptr;

        
        
private slots:

    void NewGame_Init(); //Slot per avviare una nuova partita

    void quit(); //Slot per l'uscita

    void Show_Credits(); //Slot per caricare un nuovo mazzo
    
};

#endif
