#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayerWon();
    void onDealerWon();
    void onGamePush();
    void showPlayerScore();
    void showDealerScore();

    void on_btnDeal_clicked();
    void on_btnHit_clicked();
    void on_btnStand_clicked();
    void on_rbClassic_clicked();
    void on_rbLarge_clicked();

private:
    Ui::MainWindow *ui;
    Game           *game;

    void initGame();
};
#endif // MAINWINDOW_H
