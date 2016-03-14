/**
 * @file brick.h
 * @brief Declaration (of class and member functions) for the Brick class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QtGlobal>
#include <QDebug>
#include <QtGlobal>
#include <QVector2D>

/**
    @class Brick
    @brief Dervied class of QGraphicsItem representing a Brick in the game.
 */
class Brick : public QGraphicsItem
{
    public:

        Brick();
        Brick(int start_x_position, int start_y_position);
        Brick(int start_x_position, int start_y_position,
              bool shrink_powerup_brick,
              bool grow_powerup_brick,
              bool slower_powerup_brick,
              bool faster_powerup_brick);

        virtual ~Brick() {qDebug()<<"Deleted a brick";};

        //Must implement as QGraphicsItem is an abstract class w/ these two pure virtual
        QRectF boundingRect() const;
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

        //Reimplement to return shape other than bounding rectangle (circular shape)
        QPainterPath shape() const;

        //getters
        qreal get_width();
        qreal get_height();

        //Get and set hit value
        void set_hit(bool hit_value);
        bool is_hit();

        bool is_shrink_powerup();
        bool is_grow_powerup();
        bool is_slower_powerup();
        bool is_faster_powerup();

    private:

        bool hit;

        //powerbrick markers
        bool shrink_powerup;
        bool grow_powerup;
        bool slower_powerup;
        bool faster_powerup;

        qreal pen_width;

        qreal width;
        qreal height;

        QVector2D start_vector;

};

#endif // BRICK_H
