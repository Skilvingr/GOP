#include "RNG.h"

using namespace std;


int rng::roll()
{
    return (rand() % 6 + 1);
}


int rng::general_rng(int min, int max)
{
    return(rand() % (max - min) + min);
}


int rng::blocks_rng()
{
        
    return(rand() % 36 + 40); //Assegna a blocks un numero che va da 40 a 78

}


//---------------------------- Inizio Randomizzazione tipo casella -------------------------------------------

int rng::type_rng()
{
        
    block_type = rand() % 99; //Genera un numero da 0 a 6 per estrarre i tipi di caselle
    
    if(block_type >= 0 && block_type <= 39)
    {
        was_Red = false;
        
        return(0); //Casella vuota; colore NERO
    }
    
    if(block_type >= 40 && block_type <= 59)
    {
        was_Red = false;
        
        return(1); //Pesca una carta; colore MAGENTA
    }
    
    if(block_type >= 60 && block_type <= 69)
    {
        was_Red = false;
        
        return(2); //Avanza di n caselle; colore VERDE
    }
    
    if(block_type >= 70 && block_type <= 79)
    {
        if(!was_Red)
        {
            was_Red = true; //Setta il flag a "true" per evitare che il prossimo blocco sia ROSSO o GIALLO
            
            return(3); //Indietreggia di n caselle; colore ROSSO
        }
        
        else
        {
            was_Red = false;
            
            return(0);
        }
    }
    
    if(block_type >= 80 && block_type <= 89)
    {
        was_Red = false;
        
        return(4); //Vai alla casella x; colore BLU
    }
    
    if(block_type >= 90 && block_type <= 99)
    {   
        was_Red = false;

        return(5);
    }
    
    return(42); //Errore
    
}
                
//---------------------------- Fine Randomizzazione tipo casella -------------------------------------------

   


void rng::delay( int millisecondsToWait )      // Delay per testing
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}






    
rng::rng()
{     
    srand(time(nullptr)); //Inizializza la gestione del randomizer
}
                
