/**
 * @file paddle.h
 * @brief Declaration (of class and member functions) for the Paddle class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QtGlobal>
#include <QDebug>
#include <QtGlobal>
#include <QVector2D>
#include <QBrush>
#include <QColor>

/**
    @class Paddle
    @brief Dervied class of QGraphicsItem representing a Paddle in the game.
 */
class Paddle : public QGraphicsItem
{
    public:
        Paddle();
        Paddle(int start_x_position, int start_y_position);
        virtual ~Paddle() {qDebug()<<"Deleting Paddle";};

        QRectF boundingRect() const;

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

        QPainterPath shape() const;

        void move_left();
        void move_right();

        qreal get_width();
        qreal get_height();

        void set_width(qreal new_width);
        void set_height(qreal new_height);

        void shrink();
        void grow();

        void slower();
        void faster();

        void reset_powerups();

    private:

        qreal pen_width;

        qreal starting_width;
        qreal starting_height;
        qreal width;
        qreal height;

        qreal starting_movement_distance;
        qreal default_movement_distance;

        qreal size_change_amount;
        qreal speed_change_amount;

        QVector2D start_vector;
};

#endif // PADDLE_H
