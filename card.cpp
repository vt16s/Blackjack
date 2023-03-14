/******************************************************************************
 * file card.cpp
 * Dfinition of the class Card methods
 * Detailed description of the class Card is in the file card.h
 ******************************************************************************/
#include "card.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSound>

// Constructor
Card::Card(QWidget *parent, CardRank rank, CardSuit suit)
    : QWidget(parent), m_rank(rank), m_suit(suit)
{
    m_no_image_str = "NO IMAGE";
    m_card_style   = Card::STYLE_CLASSIC;
    m_hiden        = true;
    m_image        = QPixmap(":/set1/images/set1/shirt.png");
    this->setGeometry(m_init_pos_x, m_init_pos_y, m_card_width, m_card_height);

    connect(this, &Card::onHidenChanged, &Card::repaintCard);
    connect(this, &Card::onViewChanged, &Card::repaintCard);
}

// Definition of the numeric value of the card
unsigned char Card::getCardValue() const
  {
    switch(m_rank)
    {
        case RANK_2:     return 2;
        case RANK_3:     return 3;
        case RANK_4:     return 4;
        case RANK_5:     return 5;
        case RANK_6:     return 6;
        case RANK_7:     return 7;
        case RANK_8:     return 8;
        case RANK_9:     return 9;
        case RANK_10:
        case RANK_JACK:
        case RANK_QUEEN:
        case RANK_KING:  return 10;
        case RANK_ACE:   return 11;
        default:         return 0;
    }
}

// Setting the side of the card
void Card::setHiden(bool value)
{
    m_hiden = value;
    emit onHidenChanged();
}

// Setting the drawing style of the card
void Card::setView(Card::CardStyle value)
{
    m_card_style = value;
    emit onViewChanged();
}

// Formation an image filename
QString Card::getImageFile() const
{
    QString image_filename;

    if(m_card_style == Card::STYLE_CLASSIC)
        image_filename = ":/set1/images/set1/";
    else if(m_card_style == Card::STYLE_LARGE_IMAGE)
        image_filename = ":/set2/images/set2/";

    if(m_hiden)
        image_filename += "shirt.png";
    else
    {
        switch(m_rank)
        {
            case RANK_2:     image_filename += "2";  break;
            case RANK_3:     image_filename += "3";  break;
            case RANK_4:     image_filename += "4";  break;
            case RANK_5:     image_filename += "5";  break;
            case RANK_6:     image_filename += "6";  break;
            case RANK_7:     image_filename += "7";  break;
            case RANK_8:     image_filename += "8";  break;
            case RANK_9:     image_filename += "9";  break;
            case RANK_10:    image_filename += "10"; break;
            case RANK_JACK:  image_filename += "J";  break;
            case RANK_QUEEN: image_filename += "Q";  break;
            case RANK_KING:  image_filename += "K";  break;
            case RANK_ACE:   image_filename += "A";  break;
            default: break;
        }
        switch(m_suit)
        {
            case SUIT_CLUBS:    image_filename += "C.png"; break;
            case SUIT_DIAMONDS: image_filename += "D.png"; break;
            case SUIT_HEARTS:   image_filename += "H.png"; break;
            case SUIT_SPADES:   image_filename += "S.png"; break;
            default: break;
        }
    }

    return image_filename;
}

// Animation moving of the card
void Card::cardAnimation(int x_end, int y_end)
{
    QPropertyAnimation *panim = new QPropertyAnimation(this, "pos");
    panim->setDuration(500);
    panim->setStartValue(QPoint(m_init_pos_x, m_init_pos_y));
    panim->setEndValue(QPoint(x_end, y_end));
    panim->setLoopCount(1);
    panim->start();
    QSound::play(":/wav/sound/card.wav");
}

// Changing cards image
void Card::repaintCard()
{
    m_image = QPixmap(getImageFile());
    this->repaint(rect());
}

// Image displaying
void Card::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(m_image.isNull())
    {
        painter.setBrush(Qt::white);
        painter.drawRect(rect());
        painter.drawText(rect(), Qt::AlignCenter, m_no_image_str);
    }
    else
        painter.drawPixmap(rect(), m_image);
}
