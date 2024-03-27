#ifndef DIFFICULTYLEVELDIALOG_H
#define DIFFICULTYLEVELDIALOG_H

#include <QDialog>

namespace Ui {
class DifficultyLevelDialog;
}

class DifficultyLevelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultyLevelDialog(QWidget *parent = nullptr);
    ~DifficultyLevelDialog();

signals:
    void newGame(int difficultyLevel);

private slots:


    void on_pushButtonConfirm_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DifficultyLevelDialog *ui;
    int selectedLevel;
};

#endif // DIFFICULTYLEVELDIALOG_H
