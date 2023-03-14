#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(this->size());

    ui->rbClassic->setChecked(true);

    game = new Game(this);
    initGame();

    connect(game, &Game::playerWon, this, &MainWindow::onPlayerWon);
    connect(game, &Game::dealerWon, this, &MainWindow::onDealerWon);
    connect(game, &Game::gamePush, this, &MainWindow::onGamePush);
    connect(game, &Game::changePlayerScore, this, &MainWindow::showPlayerScore);
    connect(game, &Game::changeDealerScore, this, &MainWindow::showDealerScore);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::initGame()
{
    game->m_deck.initDeck();
    ui->plbl->setText("0");
    ui->dlbl->setText("0");
    ui->cashlbl->setText("$" + QString::number(game->getCash()));
    ui->btnDeal->setEnabled(true);
    ui->btnHit->setEnabled(false);
    ui->btnStand->setEnabled(false);
    ui->betBox->setEnabled(true);

    ui->cashlbl->setText("$: " + QString::number(game->getCash()));
}

void MainWindow::on_btnDeal_clicked()
{
    // Checking the correctnes of the bet
    if(ui->betBox->value() == 0)
    {
        QSound::play(":/wav/sound/error.wav");
        QApplication::processEvents();
        QMessageBox::information(this, "Information", "Place your bet!");
        return;
    }
    if(static_cast<unsigned long>(ui->betBox->value()) > game->getCash())
    {
        QSound::play(":/wav/sound/nomoney.wav");
        QApplication::processEvents();
        QMessageBox::information(this, "Information", "Not enough money!");
        return;
    }

    QSound::play(":/wav/sound/deal.wav");
    QApplication::processEvents();
    ui->btnDeal->setEnabled(false);
    ui->betBox->setEnabled(false);
    game->setBet(ui->betBox->value());
    game->init();
    ui->cashlbl->setText("$: " + QString::number(game->getCash()));

    // Start deal
    game->dealCardToPlayer();
    game->dealCardToPlayer();
    game->dealCardToDealer();
    game->dealHidenCardToDealer();

    if(game->getPlayerScore() == 21)
    {
        game->m_hiden_card->setHiden(false);
        game->addScore(game->m_hiden_card, Game::DEALER);
        ui->dlbl->setText(QString::number(game->getDealerScore()));
    }
    game->checkResult(false);

    ui->btnHit->setEnabled(true);
    ui->btnStand->setEnabled(true);
}

void MainWindow::on_btnHit_clicked()
{
    game->dealCardToPlayer();
    if(game->getPlayerScore() >= 21)
    {
        game->m_hiden_card->setHiden(false);
        game->addScore(game->m_hiden_card, Game::DEALER);
        ui->dlbl->setText(QString::number(game->getDealerScore()));
    }
    game->checkResult(false);
}

void MainWindow::on_btnStand_clicked()
{
    QSound::play(":/wav/sound/stand.wav");
    QApplication::processEvents();
    ui->btnHit->setEnabled(false);
    ui->btnStand->setEnabled(false);
    game->m_hiden_card->setHiden(false);
    game->addScore(game->m_hiden_card, Game::DEALER);
    ui->dlbl->setText(QString::number(game->getDealerScore()));
    while(game->getDealerScore() < 17)
        game->dealCardToDealer();
    game->checkResult(true);
}

void MainWindow::onPlayerWon()
{
    QSound::play(":/wav/sound/win.wav");
    QApplication::processEvents();
    QMessageBox::information(this, "Game result", "Congratulations! You win!");
    game->changeCash(game->getBet() * 2);
    initGame();
}

void MainWindow::onDealerWon()
{
    QSound::play(":/wav/sound/loose.wav");
    QApplication::processEvents();
    QMessageBox::information(this, "Game result", "Dealer Win! Try again");
    initGame();
}

void MainWindow::onGamePush()
{
    QSound::play(":/wav/sound/draw.wav");
    QApplication::processEvents();
    QMessageBox::information(this, "Game result", "   It's a push!   ");
    game->changeCash(game->getBet());
    initGame();
}

void MainWindow::showPlayerScore()
{
    ui->plbl->setText(QString::number(game->getPlayerScore()));
}

void MainWindow::showDealerScore()
{
    ui->dlbl->setText(QString::number(game->getDealerScore()));
}

void MainWindow::on_rbClassic_clicked()
{
    game->m_deck.setView(Card::STYLE_CLASSIC);
}

void MainWindow::on_rbLarge_clicked()
{
    game->m_deck.setView(Card::STYLE_LARGE_IMAGE);
}
