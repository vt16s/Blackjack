/******************************************************************************
 * file deck.h
 * Declaration of the class Deck
 * Class Deck presents a deck of cards
 *   Data Members:
 *     - m_deck - vector of shared pointers on cards;
 *     - m_cardIndex - index of the current card in vector (deck);
 *   Public Functions:
 *     - Deck(QWidget *parent = nullptr) - constructor;
 *     - initDeck() - moves cards at initial position;
 *     - setView(Card::CardStyle value) - sets the cards drawing style;
 *     - shuffleDeck() - shuffles the cards;
 *     - dealCard() - returns the next card from the deck.
 *   Static Methods:
 *     - getRandomNumber(int min, int max) - returns random number
 *       from min to max.
 ******************************************************************************/

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <QVector>

typedef std::shared_ptr<Card> card_t;

class Deck
{
private:
    enum {CARDS_COUNT = 52};
    QVector<card_t> m_deck;
    int m_cardIndex;

    static int getRandomNumber(int min, int max);

public:
    Deck(QWidget *parent = nullptr);
    void initDeck();
    void setView(Card::CardStyle value);
    void shuffleDeck();
    const card_t& dealCard();
};

#endif // DECK_H
