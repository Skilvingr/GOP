#include "Game_Engine.h"


Game_Engine::Game_Engine (QWidget *parent, Field *Campo, QVector <Gamer*> Gamers_List, Info *Info_Widget, Init_Form *Tmp_Form) : QWidget(parent)
{
    this -> Campo = Campo;

    this -> Gamers_List = Gamers_List;

    this -> Info_Widget = Info_Widget;
    
    Init_Deck (Deck);

    Tmp_Form->~Init_Form();

    Quack -> setSource(QUrl::fromLocalFile(":/audio/multimedia/audio/quack.wav"));

    for (int i = 0; i < Gamers_List.size(); i++)
    {
        Campo -> add_papera(Gamers_List[i]);
    }

    if(PLATFORM != "Android"){
        Roll = new QPushButton ("&Roll!", Info_Widget->List_Widget);

        Roll -> show();
    }

    else{
        Roll = Campo->Roll;
    }

    Roll_Connection = QObject::connect(Roll, &QPushButton::clicked, [this] {Gamers_Seq();});

    connect(this->parent(), &QObject::destroyed, [this] {this -> ~Game_Engine();});
}


void Game_Engine::Gamers_Seq ()
{   
    Info_Widget -> Log_Wid -> append("\n---------------\n");

    if (player >= Gamers_List.size())
    {
        player = 0;
    }

    if(Gamers_List [player] -> stop)
    {
        Gamers_List [player] -> stop = false;

        Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::yellow));

        Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" has to wait for the next turn to play.");

        player++;

        return;

    }

    spostamento = dice -> general_rng(1, 6);

    Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::white));

    Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" rolled the dice and got " +QString::number(spostamento) +" -> " +QString::number(Gamers_List[player] -> gamer_position_new + spostamento));

    Turno();

    if(!Gamers_List [player] -> double_play)

    {
        player++;
    }

    else
    {
        Gamers_List [player] -> double_play = false;
    }

    Roll_Connection = QObject::connect(Roll, &QPushButton::clicked, [this] {Gamers_Seq();});
}

void Game_Engine::Turno ()
{
    disconnect(Roll_Connection);

    if (Gamers_List[player] -> gamer_position_new + spostamento >= Campo -> get_blocks())
    {
        Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" WON!");

        FlashaRandomPapere();

        exit (0);
    }

    if (Gamers_List[player] -> gamer_position_new + spostamento < 0)
    {
        Gamers_List[player] -> gamer_position_new = 0;

        Gamers_List[player] -> gamer_position_old = 0;

        spostamento = 0;
    }

    Campo -> remove_papera(Gamers_List [player]);

    Gamers_List [player] -> gamer_position_old = Gamers_List [player] -> gamer_position_new;

    Gamers_List [player] -> gamer_position_new = Gamers_List [player] -> gamer_position_old + spostamento;

    if(PLATFORM != "Android")
        Info_Widget -> List_Widget -> setItem(player, 1, new QTableWidgetItem(QString::number(Gamers_List[player] -> gamer_position_new)));

    Campo -> add_papera (Gamers_List [player]);

    Quack -> play();

    dice -> delay(700);

    Effect(Campo -> Blocks_Array.at(Gamers_List[player] -> gamer_position_new) -> type);
}

void Game_Engine::Effect(int block_type)
{
    switch(block_type)
    {
        case 0: //Casella vuota
        {
            break;
        }

        case 1: //  Pesca una carta
        {
        Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::magenta));

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" draws a card.");

            Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::lightGray));

            Effect(Deck[Deck_Counter]);

            Deck_Counter ++;

            if (Deck_Counter == 40)
            {
                Random_Deck(Deck);
                
                Deck_Counter = 0;
            }

            break;
        }

        case 2: //  Avanza di n caselle
        {
            spostamento = dice -> general_rng(1, 4);

            Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::green));

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" goes on by " +QString::number(spostamento) +" blocks. -> " +QString::number(Gamers_List[player] -> gamer_position_new + spostamento));

            Turno();

            break;
        }

        case 3: //  Indietreggia di n caselle
        {
            spostamento = dice -> general_rng(-4, -1);

            Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::red));

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" goes back by " +QString::number(-spostamento) +" blocks. -> " +QString::number(Gamers_List[player] -> gamer_position_new + spostamento));

            Turno();

            break;
        }

        case 4: //  Vai alla casella x
        {
            spostamento = dice -> general_rng(0, Gamers_List[player] -> gamer_position_new + 10) - Gamers_List[player] -> gamer_position_new;

            Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::cyan));

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" goes to the block: " +QString::number(Gamers_List[player] -> gamer_position_new + spostamento) +" -> " +QString::number(Gamers_List[player] -> gamer_position_new + spostamento));

            Turno();

            break;
        }

        case 5: //  Stai fermo un turno
        {
            Gamers_List[player] -> stop = true;

            Info_Widget -> Log_Wid -> setTextColor(QColor(Qt::yellow));

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" won't play the next turn.");

            break;
        }


        case 6: //  Fai un turno in più
        {

            Gamers_List [player] -> double_play = true;

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" will play an extra turn.");

            break;
        }

        case 7: //  Avanza di 15 caselle
        {
            spostamento = 15;

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" goes on by 15 blocks. -> " +QString::number(Gamers_List[player] -> gamer_position_new + 15));

            Turno();

            break;
        }

        case 8: //  Avanza di 25 caselle
        {
            spostamento = 25;

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" goes on by 25 blocks. -> " +QString::number(Gamers_List[player] -> gamer_position_new + 25));

            Turno();

            break;
        }

         case 9: // Torna al Via
        {
            spostamento = - Gamers_List[player] -> gamer_position_new;

            Info_Widget -> Log_Wid -> append(Gamers_List[player] -> Name +" goes back to the start.");

            Turno();

            break;
        }

        default:
        {
            break;
        }
    }
}

void Game_Engine::FlashaRandomPapere ()
{
    rng dice;

    QIcon Avatar = QIcon(":/avatars/multimedia/avatars/Red_Duck.png");

    QObject::disconnect(Roll_Connection);

    for (int i = 0; i<1000; i++)
    {
        int a = rand() % 4;

        if (a == 0)      Avatar = QIcon(":/avatars/multimedia/avatars/Red_Duck.png");
        if (a == 1)      Avatar = QIcon(":/avatars/multimedia/avatars/Violet_Duck.png");
        if (a == 2)      Avatar = QIcon(":/avatars/multimedia/avatars/Blue_Duck.png");
        if (a == 3)      Avatar = QIcon(":/avatars/multimedia/avatars/Yellow_Duck.png");


        QGraphicsPixmapItem *papera = new QGraphicsPixmapItem ();

        papera -> setPos(rand()%1500-800,rand()%1000-500);

        int duck_size = dice.general_rng(50, 500);

        papera -> setPixmap(Avatar.pixmap(duck_size, duck_size)); //Rendere variabile il giocatore

        Campo -> Camp_Scene -> addItem(papera);

        Quack -> play();

        dice.delay(200);
     }



}


void Game_Engine::Random_Deck (int Deck[])
{
    int tmp;
    int rand_temp;

    rng *swap = new rng();

    for (int i=0; i<40; i++)
    {
        rand_temp = swap -> general_rng(1,40);

        tmp = Deck [i];

        Deck [i] = Deck[rand_temp];

        Deck [rand_temp] = tmp;
    }

}



void Game_Engine::Init_Deck (int Deck[])
{
    int i;

    for (i=0; i<10; i++)
    {
        Deck[i]=2;  // 10 Carte "Avanza di n Caselle"
    }

    for (i=10; i<20; i++)
    {
        Deck[i]=3;  // 10 Carte "Indietreggia di n Caselle"
    }

    for (i=20; i<25; i++)
    {
        Deck[i]=4;  // 5 Carte "Vai alla casella x"
    }

    for (i=25; i<30; i++)
    {
        Deck[i]=5;  // 5 Carte "Stai fermo un turno"
    }

    for (i=30; i<35; i++)
    {
        Deck[i]=6;  // 5 Carte "Gioca un turno in più"
    }

    for (i=35; i<37; i++)
    {
        Deck[i]=7;  // 2 Carte "Avanza di 15 caselle"
    }

    for (i=37; i<39; i++)
    {
        Deck[i]=8;  // 2 Carte "Avanza di 25 caselle"
    }

    for (i=39; i<40; i++)
    {
        Deck[i]=9;  // 1 Carta "Torna al Via"
    }


    Random_Deck (Deck);

}

Game_Engine::~Game_Engine()
{
}
