#include "difficultyleveldialog.h"
#include "ui_difficultyleveldialog.h"

DifficultyLevelDialog::DifficultyLevelDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DifficultyLevelDialog)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/dialog-background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // set "Select difficulty level" pixmap
    QPixmap labelPixmap(":/icons/images/difficulty_0010_Select-difficulty_.png");
    ui->label->setPixmap(labelPixmap);
    ui->label->setFixedSize(300, 40);

    // set buttons icons
    QIcon confirmIcon(QPixmap(":/icons/images/confirm.png"));
    ui->pushButtonConfirm->setIcon(confirmIcon);
    ui->pushButtonConfirm->setIconSize(QSize(130, 40));
    ui->pushButtonConfirm->setFixedSize(QSize(130, 40));
    QIcon cancelIcon(QPixmap(":/icons/images/cancel.png"));
    ui->pushButtonCancel->setIcon(cancelIcon);
    ui->pushButtonCancel->setIconSize(QSize(130, 40));
    ui->pushButtonCancel->setFixedSize(QSize(130, 40));

    // set pixmaps to comboBox
    QPixmap pixmapLow(":/icons/images/difficultyLow.png");
    QPixmap pixmapMedium(":/icons/images/difficultyMedium.png");
    QPixmap pixmapHigh(":/icons/images/difficultyHigh.png");

    ui->comboBox->addItem(QIcon(pixmapLow), "");
    ui->comboBox->addItem(QIcon(pixmapMedium), "");
    ui->comboBox->addItem(QIcon(pixmapHigh), "");
    ui->comboBox->setIconSize(QSize(102, 20));
}

DifficultyLevelDialog::~DifficultyLevelDialog()
{
    delete ui;
}


void DifficultyLevelDialog::on_pushButtonConfirm_clicked()
{
    emit newGame(ui->comboBox->currentIndex());
    accept();
}


void DifficultyLevelDialog::on_pushButtonCancel_clicked()
{
    reject();
}

