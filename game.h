/******************************************************************************
 * file game.h
 * Declaration of the class Game
 * Class Game describes the games logic
 *   Data Members:
 *     - m_deck - object of Deck (deck of cards);
 *     - m_hiden_card - shared pointer on the hiden Dealers card.
 *   Public Functions:
 *     - Card(QWidget *parent = nullptr, CardRank rank = MAX_RANK,
 *            CardSuit suit = MAX_SUIT) - constructor;
 *     - getCash() - returns the Player money;
 *     - changeCash(unsigned long value) - increases or decreases
 *       Player money value depending on the game result;
 *     - getBet() - returns current bet;
 *     - setBet(unsigned long value) - sets current bet;
 *     - getPlayerScore() - returns current Player score;
 *     - getDealerScore() - returns current Dealer score;
 *     - getPlayerCardsCount() - returns Player cards count at the moment;
 *     - getDealerCardsCount() - returns Dealer cards count at the moment;
 *     - addScore(const card_t card, Hand hand) - add new card value to
 *       Player or Dealer score depending on hand;
 *     - dealCardToPlayer() - deal a new card in to the Player hand;
 *     - dealCardToDealer() - deal a new card in to the Dealer hand;
 *     - dealHidenCardToDealer() - deal a hiden card in to the Dealer hand;
 *     - checkResult(bool stand) - check who wins. If stand = true - the player
 *       said enough.
 *   Signals:
 *     - playerWon() - emitted when Player won;
 *     - dealerWon() - emitted when Dealer won;
 *     - gamePush() - emitted when game is draw;
 *     - changePlayerScore() - emitted when Players score was changed;
 *     - changeDealerScore() - emitted when Dealers score was changed.
 ******************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "deck.h"

class Game : public QObject
{
    Q_OBJECT
public:
    enum Hand
    {
        PLAYER,
        DEALER
    };

private:
    unsigned long m_cash                 = 1000;
    unsigned long m_bet                  = 0;
    unsigned char m_player_score         = 0;
    unsigned char m_dealer_score         = 0;
    unsigned char m_player_cards_count   = 0;
    unsigned char m_dealer_cards_count   = 0;
    static const int m_player_card_pos_x = 10;
    static const int m_player_card_pos_y = 260;
    static const int m_dealer_card_pos_x = 690;
    static const int m_dealer_card_pos_y = 100;
    static const int m_card_spacing      = 10;

public:
    Deck m_deck;
    card_t m_hiden_card;

    Game(QWidget *parent);

    void init();

    unsigned long getCash() const {return m_cash;}
    void changeCash(unsigned long value) {m_cash += value;}
    unsigned long getBet() const {return m_bet;}
    void setBet(unsigned long value) {m_bet = value;}
    unsigned char getPlayerScore() {return m_player_score;}
    unsigned char getDealerScore() {return m_dealer_score;}
    unsigned char getPlayerCardsCount() {return m_player_cards_count;}
    unsigned char getDealerCardsCount() {return m_dealer_cards_count;}
    void addScore(const card_t card, Hand hand);
    card_t dealCardToPlayer();
    card_t dealCardToDealer();
    void dealHidenCardToDealer();
    void checkResult(bool stand);

signals:
    void playerWon();
    void dealerWon();
    void gamePush();
    void changePlayerScore();
    void changeDealerScore();
};

#endif // GAME_H
