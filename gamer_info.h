#ifndef GAMER_INFO_H
#define GAMER_INFO_H

#include <QString>
#include <QIcon>
#include <QGraphicsPixmapItem>

typedef struct Gamer //Struttura di descrizione del giocatore
{
    QString Name;

    QIcon Avatar;

    QGraphicsPixmapItem *papera = nullptr;

    int gamer_position_old = 0;

    int gamer_position_new = 0;

    bool stop = false;

    bool double_play = false;
}Gamer;

#endif // GAMER_INFO_H
