#ifndef GAME_LIST_H
#define GAME_LIST_H

#include <QObject>
#include "game.h"

Game *game_1_19 = new Game("1.19", "file:/home/redbear/SMC_Minecraft_Launcher/pure_background.png", "2G");

QList<Game*> gameList{game_1_19};

#endif // GAME_LIST_H
