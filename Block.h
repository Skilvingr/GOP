#ifndef BLOCK_H //Blocco
#define BLOCK_H

#include <QGraphicsRectItem> //Disegno rettangoli
#include <QBrush> //Controllo delle caratteristiche del blocco
#include <QPen> //Bordi
#include <functional>
#include <QIcon>





class Block : public QGraphicsRectItem
{

public:
    
    Block(int ext_x = 0, int ext_y = 0, int ext_type = 0, int dim = 9); //Costruttore

    int *Block_Position();

    int x; //Dimensione in x interna

    int y; //Dimensione in y interna
    
    bool full_slot[4];   // Verifica se gli slot della casella sono pieni o no

//    std::function <void (void)> Effect;

    int type; //Tipo del blocco




private:
    
    void Block_Type(); //Assegna un colore ad un blocco in base al risltato del randomizzatore    
    
    // Variables
    


    int coordinates [2];


    //Special

    QPen Pen; //Serve per selezionare le caratteristiche dei bordi dei blocchi

    QBrush Brush = QBrush(Qt::SolidPattern); //Riempimento





};


#endif
