#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // useful signal / slot connection between view & viewmodel
    connect(&viewmodel, &ViewModel::warningUnknownJSON, this, &MainWindow::handleUnknownJSON);
    connect(&viewmodel, &ViewModel::warningJSONParseError, this, &MainWindow::handleJSONParseError);
    connect(&viewmodel, &ViewModel::errorServerDisconnected, this, &MainWindow::handleServerDisconnected);
    connect(&viewmodel, &ViewModel::newGameStarted, this, &MainWindow::showGameWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void MainWindow::handleUnknownJSON()
{
    QMessageBox::warning(this, "Warning", "Unknown JSON from server");
}

void MainWindow::handleJSONParseError()
{
    QMessageBox::warning(this, "Warning", "JSON parse error from server");
}

void MainWindow::handleServerDisconnected()
{
    QMessageBox::critical(this, "Error", "Server isn`t connected");
}

void MainWindow::showGameWindow(int difficultyLevel)
{
    GameWindow *gameWindow = new GameWindow(this);
    connect(gameWindow, &GameWindow::cellClicked, &viewmodel, &ViewModel::handleCellClicked);
    connect(gameWindow, &GameWindow::numberEntered, &viewmodel, &ViewModel::handleNumberEntered);
    connect(&viewmodel, &ViewModel::redrawCell, gameWindow, &GameWindow::handleRedrawCell);
    gameWindow->setModal(true);
    gameWindow->show();
}

/*
 * PRIVATE SLOTS
 */
void MainWindow::on_pushButtonNewGame_clicked()
{
    DifficultyLevelDialog *difficultylevelDialog = new DifficultyLevelDialog(this);
    connect(difficultylevelDialog, &DifficultyLevelDialog::newGame, &viewmodel, &ViewModel::handleNewGame);

    difficultylevelDialog->setModal(true);
    difficultylevelDialog->show();
}

void MainWindow::on_pushButtonAuthorization_clicked()
{
    LoginDialog *loginDialog = new LoginDialog(this);

    // connect login dialog`s signals to viewmodel`s slots
    connect(loginDialog, &LoginDialog::signalLogIn, &viewmodel, &ViewModel::handleLogIn);
    connect(loginDialog, &LoginDialog::signalSignUp, &viewmodel, &ViewModel::handleSignUp);
    // emitted when authorization is successful
    connect(&viewmodel, &ViewModel::successfulLogIn, loginDialog, &LoginDialog::_success);
    connect(&viewmodel, &ViewModel::successfulSignUp, loginDialog, &LoginDialog::_success);
    // emitted when authorization errors occured
    connect(&viewmodel, &ViewModel::warningIncorrectPassword, loginDialog, &LoginDialog::_incorrectPassword);
    connect(&viewmodel, &ViewModel::warningTakenUsername, loginDialog, &LoginDialog::_takenUsername);
    connect(&viewmodel, &ViewModel::warningUsernameNotFound, loginDialog, &LoginDialog::_usernameNotFound);

    loginDialog->setModal(true);
    loginDialog->show();

    // if authorization is success, disable profile button
    if (loginDialog->exec() == QDialog::Accepted) {
        ui->pushButtonAuthorization->setEnabled(false);
    }
}
