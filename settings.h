#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class settings : public QObject
{
    Q_OBJECT
public:
    explicit settings(QObject *parent = nullptr);

signals:

};

#endif // SETTINGS_H
