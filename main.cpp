#include "Window.h"
#include <QFontDatabase>


int main(int argc, char** argv)
{
   
    QApplication app(argc, argv); //Crea l'applicazione

    QFontDatabase::addApplicationFont(":/font/multimedia/Skyrim_Font.otf"); //Carica il file del font

    QFont *Skyrim = new QFont("Planewalker", 12, 1); //Definisce un oggetto 'Skyrim' contenente il font

    QApplication::setFont(*Skyrim); //Setta il font 'Skyrim' per l'applicazione corrente

    app.setWindowIcon(QIcon(":/misc/multimedia/Escape_From_GOP.png"));

    app.setApplicationDisplayName("Escape From GOP");

    Window *mainWindow = new Window(nullptr); //Crea una finestra principale(Menù)

    mainWindow -> showMaximized(); //Mostra la finestra massimizzata

    return(app.exec());
    
}
