#ifndef RNG_H //Random Number Generator
#define RNG_H

#include <ctime> //LIbrerie per la randomizzazione
#include <cstdlib>
#include <QTime>
#include <QCoreApplication>



class rng
{
    
public:
    
    rng(); //Costruttore
    
    
    // Variables
    
    int general_rng(int min = 0, int max = 0);

    int blocks_rng(); //Randomizza i blocchi e richiama le funzioni per l'inizializzazione del campo
    
    int type_rng(); //Randomizza e restituisce il tipo del blocco corrente

    int roll(); // Lancio del Dado

    void delay( int millisecondsToWait );   // Delay per Testing Grafico


    

private:

    bool was_Red = true; //Segnala se il blocco che precede quello corrente è ROSSO o GIALLO
        
    int block_type; //Variabile contenente il tipo del blocco
    
    
};









#endif
