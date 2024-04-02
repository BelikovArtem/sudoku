#include "view-models/clientviewmodel.h"

#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/sudoku/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    // data binding with view-model
    ClientViewModel cViewModel;
    engine.rootContext()->setContextProperty("cViewModel", &cViewModel);

    engine.load(url);

    return app.exec();
}
