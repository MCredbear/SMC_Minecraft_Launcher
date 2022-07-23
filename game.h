#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QString version, QString maxMemory, QString width, QString height,QByteArray hash,QByteArray jsonHash,QObject *parent = nullptr);

    Q_PROPERTY(QString version READ getVersion);
    QString version;
    QString getVersion();
    Q_PROPERTY(QString maxMemory READ getMaxMemory WRITE setMaxMemory NOTIFY onMaxMemoryChanged);
    QString maxMemory;
    QString getMaxMemory();
    void setMaxMemory(QString maxMemory);
    Q_PROPERTY(QString width READ getWidth WRITE setWidth NOTIFY onWidthChanged)
    QString width;
    QString getWidth();
    void setWidth(QString width);
    Q_PROPERTY(QString height READ getHeight WRITE setHeight NOTIFY onHeightChanged)
    QString height;
    QString getHeight();
    void setHeight(QString height);
    Q_PROPERTY(QString javaPath READ getJavaPath WRITE setJavaPath NOTIFY onJavaPathChanged)
    QString javaPath;
    QString getJavaPath();
    void setJavaPath(QString javaPath);
    
    QByteArray hash;
    QByteArray jsonHash;

signals:
    void onMaxMemoryChanged();
    void onWidthChanged();
    void onHeightChanged();
    void onJavaPathChanged();
};

#endif // GAME_H
