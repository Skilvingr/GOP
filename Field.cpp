#include "Field.h"

Field::Field(QWidget *parent) : QGraphicsView(parent)
{

    // Background
    
    this -> setStyleSheet("background-image: url(:/backgrounds/multimedia/backgrounds/Background_42.png);" "background-position: center");

    this -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //Fissa lo stile dell'oggetto espandendolo il più possibile

    if (PLATFORM == "Android"){
        Roll = new QPushButton(this);
        Roll -> setVisible(false);
    }

}


void Field::mousePressEvent(QMouseEvent *event){
    if(PLATFORM == "Android")
        Roll -> click();
    else
        QGraphicsView::mousePressEvent(event);
}


void Field::Draw_White_Blocks (int x, int y, QGraphicsScene *Campo) {

    QGraphicsRectItem *rect = new QGraphicsRectItem(x, y, 18, 18);

    rect -> setBrush(QBrush(Qt::white));

    rect -> setPen(QPen(Qt::white));

    Campo->addItem(rect);
}

//Inizio Funzioni direzionali

void Field::Up()
{
    current_y += 10;
}

void Field::Left()
{
    current_x -= 10;
}

void Field::Down()
{
    current_y -= 10;
}

void Field::Right()
{
    current_x += 10;
}

//Fine funzioni direzionali


int Field::Recursive_Drawer()
{

    if(blocks_counter == blocks) //Controllo della ricorsione
    {
        return 0;
    }

    if(blocks_counter == 0) //Controllo della ricorsione
    {
        Blocks_Array.push_back(new Block(current_x, current_y, 0)); //Crea un nuovo blocco e lo aggiunge all'Blocks_Array

        Camp_Scene -> addItem(Blocks_Array [blocks_counter]); //Aggiunge la cella attuale dell'Blocks_Array alla scena

        QGraphicsSimpleTextItem *Block_Number = new QGraphicsSimpleTextItem ();

        block_coordinates = Blocks_Array.last() -> Block_Position();

        Draw_White_Blocks (block_coordinates[0] + (block_coordinates[0]/2), block_coordinates[1] + (block_coordinates[1]/2), Camp_Scene);

        block_coordinates [0] += 2;
                                        //Da rivedere ---------__________-------_---__--__---
        block_coordinates [1] += 4;

        Block_Number -> setPos(block_coordinates [0], block_coordinates [1]);

        QString numstring = QString::number(blocks_counter);

        Block_Number -> setText(numstring);

        Camp_Scene -> addItem(Block_Number);

        blocks_counter++; //Incrementa il counter

        current_x += 10;

        operations++; //Nella prossima chiamata disegnerà un blocco in più

        Fun_Ptr = Fun_Ptr -> next; //Avanzamento lista

    }

    else
    {

        for(int i = operations; i >= 0 &&(blocks_counter != blocks); i--)
        {
            Blocks_Array.push_back(new Block(current_x, current_y, RandomGen -> type_rng())); //Crea un nuovo blocco e lo aggiunge all'Blocks_Array

            Camp_Scene -> addItem(Blocks_Array [blocks_counter]); //Aggiunge la cella attuale dell'Blocks_Array alla scena

            QGraphicsSimpleTextItem *Block_Number = new QGraphicsSimpleTextItem ();

            block_coordinates = Blocks_Array.last() -> Block_Position();

            Draw_White_Blocks (block_coordinates[0], block_coordinates[1], Camp_Scene);

            block_coordinates [0] += 2;
                                        //Da rivedere ---------__________-------_---__--__---
            block_coordinates [1] += 4;

            Block_Number -> setPos(block_coordinates [0], block_coordinates [1]);

            QString numstring = QString::number(blocks_counter);

            Block_Number -> setText(numstring);

            Camp_Scene -> addItem(Block_Number);

            blocks_counter++; //Incrementa il counter

            //Inizio ciclo lista funzioni

            switch(Fun_Ptr -> Fun_Selector)
            {
            case 0:
            {
                this -> Up();

                break;
            }

            case 1:
            {
                this -> Left();

                break;
            }

            case 2:
            {
                this -> Down();

                break;
            }

            case 3:
            {
                this -> Right();

                break;
            }
            }
        }

        //Fine ciclo lista funzioni

        operations++; //Nella prossima chiamata disegnerà un blocco in più

        Fun_Ptr = Fun_Ptr -> next; //Avanzamento lista
    }
    return(Recursive_Drawer()); //Chiamata ricorsiva
}


void Field::draw_blocks()
{
    //Inizio gestione funzioni      //Assegno un intero ad ogni funzione in modo da far ciclare una lista di interi e utilizzare
                                    //le funzioni in modo alternato
    Fun_Head = new Fun_Block;

    Fun_Ptr = Fun_Head;

    Fun_Ptr -> Fun_Selector = 0;

    Fun_Ptr -> next = new Fun_Block;

    Fun_Ptr = Fun_Ptr -> next;

    Fun_Ptr -> Fun_Selector = 1;

    Fun_Ptr -> next = new Fun_Block;

    Fun_Ptr = Fun_Ptr -> next;

    Fun_Ptr -> Fun_Selector = 2;

    Fun_Ptr -> next = new Fun_Block;

    Fun_Ptr = Fun_Ptr -> next;

    Fun_Ptr -> Fun_Selector = 3;

    Fun_Ptr -> next = Fun_Head;

    //Fine gestione funzioni

    blocks = RandomGen -> blocks_rng(); //Assegna a blocks il numero di blocchi da creare

    current_x = 0; //Fisso le coordinate iniziali per far partire la spirale dall'origine degli assi

    current_y = 0;

    blocks_counter = 0;

    Recursive_Drawer(); //Richiama la funzione di disegno ricorsiva

    this -> setScene(Camp_Scene); //Setta la scena per l'oggetto corrente

}


void Field::Draw_Papera(Gamer *gamer, int x, int y)
{
    QGraphicsPixmapItem *papera = new QGraphicsPixmapItem ();

    block_coordinates = Blocks_Array.at(gamer -> gamer_position_new) -> Block_Position();

    papera -> setPos(block_coordinates[0] + x*40 +5, block_coordinates [1] + y*40 +5);

    papera -> setPixmap(gamer -> Avatar.pixmap(40, 40)); //Rendere variabile il giocatore

    gamer -> papera = papera;

    Camp_Scene -> addItem(papera);
}



int Field::add_papera(Gamer *gamer)
{
    if (Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[0] == false)
    {
        Draw_Papera (gamer, 0, 0);

        Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[0] = true;

        return (0);
    }

    else
            if (Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[1] == false)
            {
                 Draw_Papera (gamer,1 , 0);

                 Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[1] = true;

                 return (0);
            }
    else
            if (Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[2] == false)
            {
                 Draw_Papera (gamer, 0, 1);

                 Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[2] = true;

                 return (0);
            }

    else
            {
                 Draw_Papera (gamer, 1, 1);

                 Blocks_Array.at(gamer -> gamer_position_new) -> full_slot[3] = true;

                 return (0);
            }



}

void Field::remove_papera(Gamer *gamer)
{
    Camp_Scene -> removeItem(gamer -> papera);    
}


int Field::get_blocks()
{
    return (blocks);
}




//// --------------------------------- Fare in modo che la prima casella non sia indietreggia o pesca

