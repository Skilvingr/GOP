#include "Block.h"

#define FIXED_SIZE 10 //Dimensione in x e in y del blocco


Block::Block(int ext_x, int ext_y, int ext_type, int dim)
{
    
    x = ext_x * dim; //Adatto le coordinate esterne a quelle interne
    
    y = ext_y * dim;

    coordinates [0] = x;

    coordinates [1] = y;
    
    type = ext_type; //Tipo del blocco(passato dal randomizzatore)
    
    this -> Block_Type(); //Richiama la funzinoe per assegnare il colore

    setRect(QRect(x, y, FIXED_SIZE * dim, FIXED_SIZE * dim)); //Costruisce il blocco

    for (int i=0; i<4; i++) // Inizializza gli slot delle caselle a "Vuoto"
    {
        full_slot[i] = false;
    }
}

void Block::Block_Type()
{

    switch(type)
    {
        case 0: //Casella vuota
        {            
            setOpacity(1);

//            Effect = [&] {setOpacity(1);}; //Associazione della funzione lambda, il "puntatore" Effect è generato da std::function nella private
            
            break;
        }
        
        case 1: //Pesca una carta
        {
            Brush.setColor(Qt::magenta);
            
            break;
        }
        
        case 2: //Avanza di n caselle
        {
            Brush.setColor(Qt::green);
            
            break;
        }
        
        case 3: //Indietreggia di n caselle
        {
            Brush.setColor(Qt::red);
            
            break;
        }
        
        case 4: //Vai alla casella x
        {
            Brush.setColor(Qt::blue);
            
            break;
        }
        
        case 5: //Stai fermo un turno
        {
            Brush.setColor(Qt::yellow);
            
            break;
        }

        case 6:
        {
            Brush.setColor(Qt::white);

            break;
        }

        default:
        {   
            break;
        }
    }


    Pen.setColor(Qt::white); //Bordo bianco

    this -> setPen(Pen); //Setta la penna

    this -> setBrush(Brush); //Setta il riempimento

}





int* Block::Block_Position()
{
    return (coordinates);
}
