/**
 * @file ball.h
 * @brief Declaration (of class and member functions) for the Ball class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QtGlobal>
#include <QDebug>
#include <QtGlobal>
#include <QVector2D>

#include "brick.h"

/**
    @class Ball
    @brief Dervied class of QGraphicsItem representing the Ball in the game.
 */
class Ball : public QGraphicsItem
{

    public:
        Ball();
        virtual ~Ball() {qDebug()<<"Deleted a ball";};

        //Must implement as QGraphicsItem is an abstract class w/ these two pure virtual
        QRectF boundingRect() const;
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

        //Reimplement to return shape other than bounding rectangle (circular shape)
        QPainterPath shape() const;

        //Update animation when graphics scene updates
        void advance(int step);

        //for starting movement
        void launch_ball();

        //appropriately change movement vector for a ball collision
        void bounce(double degrees_to_rotate);

        //helper for bounce - rotate vector degrees_to_rotate about (0,0) relative to vector
        QVector2D rotate_vector(QVector2D original_vector, qreal degrees_to_rotate);

        qreal get_radius();

        QVector2D get_movement_vector();

        void set_position(QVector2D new_position);
        void set_movement(QVector2D new_movement_vector);
        void set_launch(QVector2D new_launch_vector);

        void slower();
        void faster();


    private:

        //shape / bounding / animation settings
        qreal pen_width;
        qreal radius;

        //parameters for physics
        QVector2D movement_vector;
        QVector2D start_vector;
        QVector2D launch_vector;
        qreal speed_change_factor;
};

#endif // BALL_H
