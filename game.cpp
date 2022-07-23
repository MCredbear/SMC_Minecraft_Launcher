#include "game.h"

Game::Game(QString version, QString maxMemory, QString width, QString height, QByteArray hash, QByteArray jsonHash, QObject *parent)
    : QObject{parent}, version(version), maxMemory(maxMemory), width(width), height(height), hash(hash), jsonHash(jsonHash)
{
}

QString Game::getVersion()
{
    return version;
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

QString Game::getWidth()
{
    return width;
}

void Game::setWidth(QString width)
{
    this->width = width;
    emit onWidthChanged();
}

QString Game::getHeight()
{
    return height;
}

void Game::setHeight(QString height)
{
    this->height = height;
    emit onHeightChanged();
}

QString Game::getJavaPath()
{
    return javaPath;
}

void Game::setJavaPath(QString javaPath)
{
    this->javaPath = javaPath;
    emit onJavaPathChanged();
}