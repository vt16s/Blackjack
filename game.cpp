/******************************************************************************
 * file game.cpp
 * Dfinition of the class Game methods
 * Detailed description of the class Game is in the file game.h
 ******************************************************************************/

#include "game.h"
#include <QApplication>

Game::Game(QWidget *parent)
{
    m_hiden_card         = std::make_shared<Card>();
    m_deck               = Deck(parent);
}

void Game::init()
{
    m_player_score       = 0;
    m_dealer_score       = 0;
    m_player_cards_count = 0;
    m_dealer_cards_count = 0;
    m_cash              -= m_bet;
    m_deck.shuffleDeck();
}

void Game::addScore(const card_t card, Game::Hand hand)
{
    switch (hand)
    {
        case PLAYER:
        {
            if(m_player_score > 10 && card->getCardValue() == 11)
                m_player_score += 1;
            else
                m_player_score += card->getCardValue();
            break;
        }
        case DEALER:
        {
            if(m_dealer_score > 10 && card->getCardValue() == 11)
                m_dealer_score += 1;
            else
                m_dealer_score += card->getCardValue();
            break;
        }
    }
}

card_t Game::dealCardToPlayer()
{
    card_t current_card(m_deck.dealCard());
    current_card->setHiden(false);

    int x_end = m_player_card_pos_x + (Card::getCardWidth() + m_card_spacing) * m_player_cards_count;
    current_card->cardAnimation(x_end, m_player_card_pos_y);
    QApplication::processEvents();
    m_player_cards_count++;

    addScore(current_card, PLAYER);
    emit changePlayerScore();
    return  current_card;
}

card_t Game::dealCardToDealer()
{
    card_t current_card = m_deck.dealCard();
    current_card->setHiden(false);

    int x_end = m_dealer_card_pos_x - (Card::getCardWidth() + m_card_spacing) * m_dealer_cards_count;
    current_card->cardAnimation(x_end, m_dealer_card_pos_y);
    QApplication::processEvents();
    m_dealer_cards_count++;

    addScore(current_card, DEALER);
    emit changeDealerScore();
    return  current_card;
}

void Game::dealHidenCardToDealer()
{
    m_hiden_card = m_deck.dealCard();

    int x_end = m_dealer_card_pos_x - (Card::getCardWidth() + m_card_spacing) * m_dealer_cards_count;
    m_hiden_card->cardAnimation(x_end, m_dealer_card_pos_y);
    QApplication::processEvents();
    m_dealer_cards_count++;
}

void Game::checkResult(bool stand)
{
    if(m_player_score > 21)
    {
        emit dealerWon();
        return;
    }
    if(m_dealer_score > 21)
    {
        emit playerWon();
        return;
    }
    if(stand)
    {
        if(m_player_score > m_dealer_score)
            emit playerWon();
        else if(m_player_score < m_dealer_score)
            emit dealerWon();
        else
            emit gamePush();
    }
    else
    {
        if(m_player_score == 21)
        {
            if(m_dealer_score == 21)
                emit gamePush();
            else
                emit playerWon();
        }
    }
}
