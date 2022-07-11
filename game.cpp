#include "game.h"

Game::Game(QString version, QString background, QString maxMemory,QObject *parent)
    : QObject{parent},version(version),background(background),maxMemory(maxMemory)
{
}

QString Game::getVersion()
{
    return version;
}

QString Game::getBackground()
{
    return background;
}

QString Game::getMaxMemory()
{
    return maxMemory;
}

void Game::setMaxMemory(QString maxMemory)
{
    this->maxMemory = maxMemory;
    emit onMaxMemoryChanged();
}