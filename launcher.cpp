#include "launcher.h"

Launcher::Launcher(Settings *settings, AssetChecker *assetChecker, QObject *parent)
    : QObject{parent}, settings(settings), assetChecker(assetChecker)
{
}

Launcher::~Launcher()
{
    if (!gameProcess) gameProcess->kill();
}

void Launcher::login(QString username, QString password)
{
    QByteArray jsonData = Logger::loginSMC(username, password);
    QJsonDocument json = QJsonDocument::fromJson(jsonData);
    uuid = json.object()["selectedProfile"].toObject()["id"].toString();
    accessToken = json.object()["accessToken"].toString();
}

void Launcher::uncompressNativeLibraries(int index)
{
#ifdef Q_OS_LINUX
    const QString nativeOS = "natives-linux";
#endif
#ifdef Q_OS_WINDOWS
    const QString nativeOS = "natives-windows";
#endif
#ifdef Q_OS_OSX
    const QString nativeOS = "natives-macos";
#endif

    QDir nativeDir;
    if (!nativeDir.exists(".minecraft/versions/" + settings->gameList.at(index)->version + "/natives/"))
        nativeDir.mkdir(".minecraft/versions/" + settings->gameList.at(index)->version + "/natives/");
    QFile gameJsonFile("./.minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".json");
    gameJsonFile.open(QIODevice::ReadOnly);
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonFile.readAll());
    gameJsonFile.close();
    for (int i = 0; i < gameJson.object().value("libraries").toArray().count(); i++)
    {
        if (gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().contains("classifiers"))
            if (gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("classifiers").toObject().contains(nativeOS))
            {
                QZipReader zipReader(".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("classifiers").toObject().value(nativeOS).toObject().value("path").toString());
                zipReader.extractAll(".minecraft/versions/" + settings->gameList.at(index)->version + "/natives/");
            }
    }
}

void Launcher::launchGame(int index)
{
    gameProcess = new QProcess();
    connect(gameProcess, &QProcess::readyReadStandardOutput, this, &Launcher::onNewOutput);
    connect(gameProcess, &QProcess::readyReadStandardError, this, &Launcher::onNewOutput);
    login(settings->account, settings->password);
    uncompressNativeLibraries(index);
    gameProcess->start(javaPath, generateArguments(index));
}

QString Launcher::gamePath(int index)
{
    return ".minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".jar";
}

QString Launcher::mx(int index)
{
    return settings->gameList.at(index)->maxMemory;
}

QString Launcher::javaLibraryPath(int index)
{
    return ".minecraft/versions/" + settings->gameList.at(index)->version + "/natives/";
}

QString Launcher::username()
{
    return settings->account;
}

QString Launcher::assetIndex(int index)
{
    QFile gameJsonFile("./.minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".json");
    gameJsonFile.open(QIODevice::ReadOnly);
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonFile.readAll());
    gameJsonFile.close();
    return gameJson.object()["assetIndex"].toObject()["id"].toString();
}

QString Launcher::width(int index)
{
    return settings->gameList.at(index)->width;
}

QString Launcher::height(int index)
{
    return settings->gameList.at(index)->height;
}

QStringList Launcher::generateArguments(int index)
{
    QStringList arguments;

    // JVM arguments
    arguments << "-XX:HeapDumpPath=" + HeapDumpPath
              << "-Xmx" + mx(index)
              << "-Xmn128m"
              << "-XX:+UnlockExperimentalVMOptions"
              << "-XX:+UseG1GC"
              << "-XX:G1NewSizePercent=20"
              << "-XX:G1ReservePercent=20"
              << "-XX:MaxGCPauseMillis=50"
              << "-XX:G1HeapRegionSize=16m"
              << "-XX:-UseAdaptiveSizePolicy"
              << "-XX:-OmitStackTraceInFastThrow"
              << "-XX:-DontCompileHugeMethods";

    // System arguments DO NOT USE DOUBLE-BYTE ENCODE IN THE PATH
    arguments << "-Djava.library.path=" + javaLibraryPath(index)
              << "-Dminecraft.launcher.brand=" + minecraftLauncherBrand
              << "-Dminecraft.launcher.version=" + minecraftLauncherVersion
              << "-Dminecraft.client.jar=.minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".jar"
              << "-Dfile.encoding=UTF-8"
              << "-Duser.home=null"
              << "-Dfml.ignoreInvalidMinecraftCertificates=true"
              << "-Dfml.ignorePatchDiscrepancies=true"
              << "-Djava.rmi.server.useCodebaseOnly=true"
              << "-Dcom.sun.jndi.rmi.object.trustURLCodebase=false"
              << "-Dcom.sun.jndi.cosnaming.object.trustURLCodebase=false";

    // class path
    QString classPath;
    QStringList classPathList;
    QFile gameJsonFile("./.minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".json");
    gameJsonFile.open(QIODevice::ReadOnly);
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonFile.readAll());
    gameJsonFile.close();
    for (int i = 0; i < gameJson.object().value("libraries").toArray().count(); i++)
    {
        if (!gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().contains("classifiers"))
            classPathList.append(".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("path").toString());
    }
    for (int i = 0; i < classPathList.length(); i++)
    {
#ifdef Q_OS_LINUX
        if (classPathList.at(i).contains("3.2.1"))
            classPathList.removeAt(i);
#endif
#ifdef Q_OS_WINDOWS
        if (classPathList.at(i).contains("3.2.1"))
            classPathList.removeAt(i);
#endif
#ifdef Q_OS_OSX
        if (classPathList.at(i).contains("3.3.2"))
            classPathList.removeAt(i);
#endif
    }
    classPathList.append(".minecraft/versions/" + settings->gameList.at(index)->version +"/" + settings->gameList.at(index)->version + ".jar");
    classPath = classPathList.join(":");
    arguments << "-cp" << classPath;

    // Java agent arguments
    arguments << "-javaagent:./authlib-injector.jar=http://ddns.smcserver.cn:9010/api/yggdrasil/"
              << "-Dauthlibinjector.side=client";

    // Minecraft arguments
    arguments << mainClass
              << "--username" << username()
              << "--version" << version
              << "--gameDir" << gameDir
              << "--assetsDir" << assetsDir
              << "--assetIndex" << assetIndex(index)
              << "--uuid" << uuid
              << "--accessToken" << accessToken
              << "--userType" << userType
              << "--versionType" << versionType;
              qDebug()<<arguments;
    return arguments;
}

void Launcher::onNewOutput()
{
    qDebug() << gameProcess->readAll();
}
