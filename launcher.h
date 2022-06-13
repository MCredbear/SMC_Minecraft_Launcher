#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <private/qzipreader_p.h>
#include <private/qzipwriter_p.h>

#include "asset_checker.h"

class Launcher : public QObject
{
    Q_OBJECT
public:
    explicit Launcher(AssetChecker *assetChecker, QObject *parent = nullptr);

    AssetChecker *assetChecker;

    Q_INVOKABLE void uncompressNativeLibraries();

signals:
};

#endif // LAUNCHER_H
