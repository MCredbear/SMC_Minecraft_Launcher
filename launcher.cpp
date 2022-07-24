#include "launcher.h"

Launcher::Launcher(Settings *settings, AssetChecker *assetChecker, QObject *parent)
    : QObject{parent}, settings(settings), assetChecker(assetChecker)
{
    gameProcess = nullptr;
}

Launcher::~Launcher()
{
    if (gameProcess)
        if (gameProcess->state() == QProcess::Running)
            gameProcess->kill();
}

bool Launcher::login(QString username, QString password)
{
    QByteArray jsonData = Logger::loginSMC(username, password);
    if (jsonData != "")
    {
        QJsonDocument json = QJsonDocument::fromJson(jsonData);
        if (json.object()["error"].isNull())
        {
            uuid = json.object()["selectedProfile"].toObject()["id"].toString();
            accessToken = json.object()["accessToken"].toString();
            return true;
        }
        else
        {
            emit onLoginFailed();
            return false;
        }
    }
    else
    {
        onLoginFailed();
        return false;
    }
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

QString Launcher::mainClass(int index)
{
    QFile gameJsonFile("./.minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".json");
    gameJsonFile.open(QIODevice::ReadOnly);
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonFile.readAll());
    gameJsonFile.close();
    return gameJson.object()["mainClass"].toString();
}

QString Launcher::username()
{
    return settings->account;
}

QString Launcher::version(int index)
{
    return settings->gameList.at(index)->version;
}

QString Launcher::gameDir(int index)
{
    return ".minecraft/versions/" + settings->gameList.at(index)->version;
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

QStringList Launcher::forgeArguments(int index)
{
    QStringList arguments;
    QFile gameJsonFile("./.minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".json");
    gameJsonFile.open(QIODevice::ReadOnly);
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonFile.readAll());
    gameJsonFile.close();
    for (int i = 0; i < gameJson.object()["patches"].toArray().count(); i++)
    {
        if (gameJson.object()["patches"].toArray().at(i).toObject()["id"].toString() == "forge")
        {
            for (int j = 0; j < gameJson.object()["patches"].toArray().at(i).toObject()["arguments"].toObject()["game"].toArray().count(); j++)
            {
                arguments.append(gameJson.object()["patches"].toArray().at(i).toObject()["arguments"].toObject()["game"].toArray().at(j).toString());
            }
        }
    }
    return arguments;
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
    if (settings->gameList.at(index)->modLoader == Game::Fabric)
    {
        for (int i = 0; i < gameJson.object()["patches"].toArray().count(); i++)
        {
            if (gameJson.object()["patches"].toArray().at(i).toObject()["id"].toString() == "fabric")
            {
                for (int j = 0; j < gameJson.object()["patches"].toArray().at(i).toObject()["libraries"].toArray().count(); j++)
                {
                    QStringList paths = gameJson.object()["patches"].toArray().at(i).toObject()["libraries"].toArray().at(j).toObject()["name"].toString().split(":");
                    QString path = ".minecraft/libraries/" + paths[0].replace(".", "/") + "/" + paths.at(1) + "/" + paths.at(2) + "/" + paths.at(1) + "-" + paths.at(2) + ".jar";
                    classPathList << path;
                }
            }
        }
    }
    for (int i = 0; i < gameJson.object().value("libraries").toArray().count(); i++)
    {
        if (!gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().contains("classifiers"))
            classPathList.append(".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("path").toString());
    }
    for (int i = 0; i < classPathList.length(); i++)
    {
#ifdef Q_OS_LINUX
        if (classPathList.at(i).contains("3.2.1") | classPathList.at(i).contains("macos") | classPathList.at(i).contains("windows"))
            classPathList.removeAt(i);
#endif
#ifdef Q_OS_WINDOWS
        if (classPathList.at(i).contains("3.2.1") | classPathList.at(i).contains("macos") | classPathList.at(i).contains("linux"))
            classPathList.removeAt(i);
#endif
#ifdef Q_OS_OSX
        if (classPathList.at(i).contains("3.3.2") | classPathList.at(i).contains("linux") | classPathList.at(i).contains("windows"))
            classPathList.removeAt(i);
#endif
    }
    classPathList.append(".minecraft/versions/" + settings->gameList.at(index)->version + "/" + settings->gameList.at(index)->version + ".jar");
    classPath = classPathList.join(":");
    arguments << "-cp" << classPath;

    if (settings->gameList.at(index)->modLoader == Game::Forge)
    {
        arguments << "-DignoreList=bootstraplauncher,securejarhandler,asm-commons,asm-util,asm-analysis,asm-tree,asm,client-extra,fmlcore,javafmllanguage,lowcodelanguage,mclanguage,forge-," + settings->gameList.at(index)->version + ".jar," + settings->gameList.at(index)->version + ".jar"
                  << "-DmergeModules=jna-5.10.0.jar,jna-platform-5.10.0.jar,java-objc-bridge-1.0.0.jar"
                  << "-DlibraryDirectory=.minecraft/libraries/"
                  << "-p"
                  << ".minecraft/libraries/cpw/mods/bootstraplauncher/1.0.0/bootstraplauncher-1.0.0.jar:.minecraft/libraries/cpw/mods/securejarhandler/1.0.3/securejarhandler-1.0.3.jar:.minecraft/libraries/org/ow2/asm/asm-commons/9.2/asm-commons-9.2.jar:.minecraft/libraries/org/ow2/asm/asm-util/9.2/asm-util-9.2.jar:.minecraft/libraries/org/ow2/asm/asm-analysis/9.2/asm-analysis-9.2.jar:.minecraft/libraries/org/ow2/asm/asm-tree/9.2/asm-tree-9.2.jar:.minecraft/libraries/org/ow2/asm/asm/9.2/asm-9.2.jar"
                  << "--add-modules"
                  << "ALL-MODULE-PATH"
                  << "--add-opens"
                  << "java.base/java.util.jar=cpw.mods.securejarhandler"
                  << "--add-exports"
                  << "java.base/sun.security.util=cpw.mods.securejarhandler"
                  << "--add-exports"
                  << "jdk.naming.dns/com.sun.jndi.dns=java.naming";
    }

    // Java agent arguments
    arguments << "-javaagent:./authlib-injector.jar=http://ddns.smcserver.cn:9010/api/yggdrasil/"
              << "-Dauthlibinjector.side=client";

    // Minecraft arguments
    arguments << mainClass(index)
              << "--username" << username()
              << "--version" << version(index)
              << "--gameDir" << gameDir(index)
              << "--assetsDir" << assetsDir
              << "--assetIndex" << assetIndex(index)
              << "--uuid" << uuid
              << "--accessToken" << accessToken
              << "--userType" << userType
              << "--versionType" << versionType;

    if (settings->gameList.at(index)->modLoader == Game::Forge)
    {
        arguments << forgeArguments(index);
    }

    qDebug() << arguments.join(" ");
    return arguments;
}

void Launcher::onNewOutput()
{
    qDebug() << gameProcess->readAll();
}
