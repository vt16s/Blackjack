/******************************************************************************
 * file card.h
 * Declaration of the class Card
 * Class Card describes one playing card
 *   Properties:
 *     - m_init_pos_x - X coordinates of initial position of the card;
 *     - m_init_pos_y - Y coordinates of initial position of the card;
 *     - m_card_width - defines card width;
 *     - m_card_height - defines card height;
 *     - m_rank - defines the rank of the card;
 *     - m_suit - defines the suit of the card;
 *     - m_card_style - defines the drawing of the card;
 *     - m_hiden - defines the visible side of the card
 *       (true - back, false - front);
 *     - m_image - contains an image for the card;
 *     - m_no_image_str - text on the card, if image upload failed.
 *   Public Functions:
 *     - Card(QWidget *parent = nullptr, CardRank rank = MAX_RANK,
 *            CardSuit suit = MAX_SUIT) - constructor;
 *     - getCardValue() - returns the numeric value of the card;
 *     - getHiden() - returns the current side of the card;
 *     - setHiden(bool value) - sets the side of the card;
 *     - setView(CardStyle value) - sets the card drawing;
 *     - getImageFile() - returns an image filename;
 *     - cardAnimation(int x_end, int y_end) - make animation moving of the card
 *       from initial position to x_end, y_end;
 *     - paintEvent(QPaintEvent *) - virtual method for repaint of the card.
 *   Static Methods:
 *     - getInitPosX() - returns static data member m_init_pos_x;
 *     - getInitPosY() - returns static data member m_init_pos_y;
 *     - getCardWidth() - returns static data member m_card_width;
 *     - getCardHeight() - returns static data member m_card_height.
 *   Signals:
 *     - onHidenChanged() - emitted when the cards side has changed;
 *     - onViewChanged() - emitted when the cards drawing style has changed.
 *   Private Slots:
 *     - repaintCard() - repaints the image of the card.
 ******************************************************************************/

#ifndef CARD_H
#define CARD_H

#include <QWidget>

class Card : public QWidget
{
    Q_OBJECT
public:
    enum CardRank
    {
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8,
        RANK_9,
        RANK_10,
        RANK_JACK,
        RANK_QUEEN,
        RANK_KING,
        RANK_ACE,
        MAX_RANK
    };

    enum CardSuit
    {
        SUIT_CLUBS,
        SUIT_DIAMONDS,
        SUIT_HEARTS,
        SUIT_SPADES,
        MAX_SUIT
    };

    enum CardStyle
    {
        STYLE_CLASSIC,
        STYLE_LARGE_IMAGE
    };

private:
    static const int m_init_pos_x  = 50;
    static const int m_init_pos_y  = -50;
    static const int m_card_width  = 100;
    static const int m_card_height = 145;
    CardRank         m_rank;
    CardSuit         m_suit;
    CardStyle        m_card_style;
    bool             m_hiden;
    QPixmap          m_image;
    QString          m_no_image_str;

public:
    // Constructor
    explicit Card(QWidget *parent = nullptr, CardRank rank = MAX_RANK, CardSuit suit = MAX_SUIT);

    unsigned char getCardValue() const;
    bool getHiden() const {return m_hiden;}
    void setHiden(bool value);
    void setView(CardStyle value);
    QString getImageFile() const;
    void cardAnimation(int x_end, int y_end);
    static int getInitPosX() {return m_init_pos_x;}
    static int getInitPosY() {return m_init_pos_y;}
    static int getCardWidth() {return m_card_width;}
    static int getCardHeight() {return m_card_height;}

signals:
    void onHidenChanged();
    void onViewChanged();

private slots:
    void repaintCard();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // CARD_H
