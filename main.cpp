#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QVariant>
#include <QLocale>
#include <QTranslator>

#include "downloader.h"
#include "asset_checker.h"
#include "launcher.h"
#include "logger.h"
#include "settings.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QQuickWindow::setGraphicsApi(QSGRendererInterface::Vulkan);
    QGuiApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SMC_Minecraft_Launcher_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }


    Settings settings;
    AssetChecker assetChecker(&settings);
    Logger logger;
    Launcher launcher(&settings, &assetChecker);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("settings", &settings);
    engine.rootContext()->setContextProperty("assetChecker", &assetChecker);
    engine.rootContext()->setContextProperty("launcher", &launcher);
    engine.rootContext()->setContextProperty("gameListModel", QVariant::fromValue(settings.gameList));;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
