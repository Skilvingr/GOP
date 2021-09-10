#ifndef FIELD_H //Campo di gioco
#define FIELD_H

#if defined (__ANDROID__)
    #define PLATFORM "Android"
#else
    #define PLATFORM "PC"
#endif

#include <stdlib.h> //Random
#include <time.h> //Random
#include <QGraphicsScene> //Scena per la rappresentazione dei blocchi
#include <QGraphicsView> //Visualizzazione dell scena
#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QTableWidget> //Gestione lista giocatori
#include <QFont>
#include <QBrush>


#include "RNG.h"
#include "Block.h"
#include "gamer_info.h"



class Field : public QGraphicsView //Ogni oggetto creato è una view
{
    Q_OBJECT //Segnali
    
public:

    QPushButton *Roll = nullptr;

    Field(QWidget *parent = nullptr); //Costruttore
    
    void draw_blocks();

    void Draw_Papera(Gamer *gamer = nullptr, int x = 0, int y = 0);

    int add_papera(Gamer *gamer = nullptr);  // Chiama Draw_Papera e la sistema nel primo dei quattro slot liberi

    void remove_papera(Gamer *gamer = nullptr);

    int get_blocks();

    // Da Togliere --------------
    QGraphicsScene *Camp_Scene = new QGraphicsScene(this); //Crea la scena su cui disegnarepo;

    QList <Block*> Blocks_Array;



    
private:
    //Inizio funzioni direzionali
    void Up();
    void Down();
    void Left();
    void Right();
    //Fine funzioni direzionali

    int Recursive_Drawer();

    // Variables
        
    int blocks_counter = 0; //Counter della creazione dei blocchi
    
    int operations = 0; //Blocchi da scrivere per chiamata

    int current_x, current_y; //Coordinate dei blocchi

    int *block_coordinates;

    int blocks; //Numero di blocchi che compone il campo

    void Draw_White_Blocks (int x, int y, QGraphicsScene *Campo); // Disegna i quadrati bianchi per il numero delle caselle

        
    
    //Special

    //Da togliere in public e scommentare qui ------------------
    // QGraphicsScene *Camp_Scene = new QGraphicsScene(this); //Crea la scena su cui disegnarepo;

    typedef struct Fun_Block //Struttura che compone il blocco per la selezione delle funzioni
    {
        int Fun_Selector; //Selettore(da 0 a 3)

        Fun_Block *next; //Puntatore al blocco successivo
    } Fun_Block;

    Fun_Block *Fun_Ptr; //Temp

    Fun_Block *Fun_Head; //Temp

    rng *RandomGen = new rng(); //Crea un randomizzatore

    void mousePressEvent(QMouseEvent *event);

    
};



#endif
