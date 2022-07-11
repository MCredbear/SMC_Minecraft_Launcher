#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QString version, QString background, QString maxMemory,QObject *parent = nullptr);

    Q_PROPERTY(QString version READ getVersion);
    QString version;
    QString getVersion();
    Q_PROPERTY(QString background READ getBackground);
    QString background;
    QString getBackground();
    Q_PROPERTY(QString maxMemory READ getMaxMemory WRITE setMaxMemory NOTIFY onMaxMemoryChanged);
    QString maxMemory;
    QString getMaxMemory();
    void setMaxMemory(QString maxMemory);

signals:
    void onMaxMemoryChanged();
};

#endif // GAME_H
