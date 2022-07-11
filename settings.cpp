#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    settingsFile.setFileName("settings.json");

    Game *game_1_19 = new Game("1.19", "file:/home/redbear/SMC_Minecraft_Launcher/pure_background.png", "2G");
    gameList.append(game_1_19);
}
