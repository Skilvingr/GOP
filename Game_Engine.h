#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Field.h"
#include "Init_Form.h"
#include "gamer_info.h"

#include <QTime>
#include <QSoundEffect>
#include <QShortcut>
#include <stdio.h>

class Game_Engine : public QWidget
{
    Q_OBJECT

public:
    Game_Engine(QWidget *parent = nullptr, Field *Campo = nullptr, QVector <Gamer*> Gamers_List = QVector <Gamer*> (), Info *Info_Widget = nullptr, Init_Form *Tmp_Form = nullptr);


private:

    Field *Campo = nullptr;

    QVector <Gamer*> Gamers_List;

    int Deck[40];

    void Init_Deck (int Deck[]);

    void Random_Deck (int Deck[]);

    int Deck_Counter = 0;

    Info *Info_Widget = nullptr;

    QSoundEffect *Quack = new QSoundEffect();

    QPushButton *Roll = nullptr;

    QMetaObject::Connection Roll_Connection;

    rng *dice = new rng;

    int player = 0;

    int spostamento = 0;

    void Gamers_Seq();

    void Effect(int block_type = 0);

    void Turno(); // Svolgimento del Turno di un giocatore

    void FlashaRandomPapere ();

    ~Game_Engine();

};






#endif // GAME_ENGINE_H
