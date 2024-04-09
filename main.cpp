#include "view-models/clientviewmodel.h"
#include "view-models/serverviewmodel.h"

#include <QIcon>
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


    QIcon icon(":/sudoku/views/images/sudokuIcon.png");
    app.setWindowIcon(icon);

    // data binding with client view-model
    ClientViewModel cViewModel;
    engine.rootContext()->setContextProperty("cViewModel", &cViewModel);

    // data binding with server view-model
    ServerViewModel sViewModel;
    engine.rootContext()->setContextProperty("sViewModel", &sViewModel);

    engine.load(url);

    return app.exec();
}
