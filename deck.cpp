/******************************************************************************
 * file deck.cpp
 * Dfinition of the class Deck methods
 * Detailed description of the class Deck is in the file deck.h
 ******************************************************************************/

#include "deck.h"

Deck::Deck(QWidget *parent)
{
    m_cardIndex = 0;
    for(int suit = 0; suit < Card::MAX_SUIT; ++suit)
        for(int rank = 0; rank < Card::MAX_RANK; ++rank)
            m_deck.push_back(std::make_shared<Card>(parent, static_cast<Card::CardRank>(rank), static_cast<Card::CardSuit>(suit)));
}

int Deck::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Deck::initDeck()
{
    for(int i = 0; i < CARDS_COUNT; ++i)
    {
        m_deck[i]->setHiden(true);
        m_deck[i]->move(Card::getInitPosX(), Card::getInitPosY());
    }
}

void Deck::setView(Card::CardStyle value)
{
    for(int i = 0; i < CARDS_COUNT; ++i)
        m_deck[i]->setView(value);
}

void Deck::shuffleDeck()
{
    for(int i = 0; i < CARDS_COUNT; ++i)
        qSwap(m_deck[i], m_deck[getRandomNumber(0, CARDS_COUNT-1)]);

    m_cardIndex = 0;
}

const card_t& Deck::dealCard()
{
    assert(m_cardIndex < CARDS_COUNT && "No cards in the deck!");

    return m_deck[m_cardIndex++];
}
