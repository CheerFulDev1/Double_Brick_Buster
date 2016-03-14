/**
 * @file ball.cpp
 * @brief Definintion of member functions for the Ball class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#include "ball.h"
#include <QtMath>

/** Default constructor for Ball.
 */
Ball::Ball()
{
    //initialize animation settings
    radius = 25;
    pen_width = 1;

    //initialize physics settings (at start of game)
    movement_vector.setX(0);
    movement_vector.setY(0);

    //give us starting position
    start_vector.setX(250);
    start_vector.setY(410);
    setPos(mapToParent(start_vector.x(), start_vector.y()));

    //set launch speed
    launch_vector.setX(4);
    launch_vector.setY(-4);

    //set amount to change for faster and slower functions
    speed_change_factor = 1.035;

}

/** Set bounding rectangle for drawing and collisions
    @returns bounding rectange for shape
 */
QRectF Ball::boundingRect() const
{
    return QRectF(0,
                  0,
                  radius + pen_width,
                  radius + pen_width);
}


/** Paints object with correct shape in local coordinates. This is where ball handles reacting to collisions.
    @param *painter QPainter object resposible for painting the object in the scene
    @param *option provides style options for the item, such as its state, exposed area and its level-of-detail hints
    @param *widget Optional. If provided, it points to the widget that is being painted on; otherwise, it is 0.
 */
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->setBrush(Qt::black);

    //if there are no collisions with this object
    if(scene()->collidingItems(this).isEmpty())
    {
        painter->setBrush(Qt::black);
    }

    //if there are collisisons with this object
    else
    {
        //paint ball as red when hitting something
        painter->setBrush(Qt::red);

        //get a list of all colliding graphics items in the scene (all items colliding with ball)
        QList<QGraphicsItem*> hit_items = collidingItems();

        //mark any bricks come into contact with as 'hit'
        foreach(QGraphicsItem* hit_item, hit_items)
        {

            Brick* potential_brick = dynamic_cast<Brick*>(hit_item);

            //if it is a brick
            if(potential_brick!=NULL)
            {
                //and it hasn't been hit yet
                if(!potential_brick->is_hit())
                {
                    //mark it as hit
                    potential_brick->set_hit(true);
                }
            }

            //bounce off of anything else
            else
            {
                bounce(90);
            }
        }
    }

    //should match shape in Ball::shape
    painter->drawEllipse(0, 0, radius, radius);

    //set brush back to none
    painter->setBrush(Qt::NoBrush);
}


/** Gives an accurate shape, which is used by QGraphicsScene to animate. Reimplement to return shape other than bounding rectangle (circular shape).
    @returns path QPainterPath to draw representing shape
 */
QPainterPath Ball::shape() const
{
    QPainterPath path;

    //should match shape to draw in Ball::Paint
    path.addRect(0, 0, radius, radius);

    return path;
}

/** Update animation when graphics scene updates
    @param step step of animation, 0 for preparing to update, 1 for actually updating
 */
void Ball::advance(int step)
{
    //advance is called with arg step==0 when the QGraphicsScene is preparing to update
    //so want to wait until actually updating (when step==1)
    if(step == 0) return;

    //move ball in the direction of it's movement vector
    QPointF updated_position = mapToParent(movement_vector.x(),movement_vector.y());

    if(!scene()->sceneRect().contains((updated_position)))
    {
        qDebug()<<"Was going out of bounds";
        //bounce(181);
        updated_position = mapToParent(movement_vector.x(),movement_vector.y());
    }

    setPos(updated_position);

}

/** Launch the ball by setting the movement vector to the same as the launch vector
 */
void Ball::launch_ball()
{
    movement_vector.setX(launch_vector.x());
    movement_vector.setY(launch_vector.y());
}


/** Rotates movement_vector by degrees_to_rotate, thus causing the ball to change direction as if it 'bounced' off something
    @param degrees_to_rotate degress to rotate movement_vector
 */
void Ball::bounce(double degrees_to_rotate)
{
    //Get resulting vector
    QVector2D new_vector = rotate_vector(movement_vector, degrees_to_rotate);

    //set movement vector to new vector
    movement_vector.setX(new_vector.x());
    movement_vector.setY(new_vector.y());

}

/** Rotate the original_vector by degrees_to_rotate. For use in the bounce function.
    @param original_vector vector to be rotated
    @param degrees_to_rotate degress to rotate original_vector by
    @returns new_vector the original vector rotated by degrees_to_rotate degrees
 */
QVector2D Ball::rotate_vector(QVector2D original_vector, qreal degrees_to_rotate)
{
    QVector2D new_vector;

    double radians_to_rotate = qDegreesToRadians(degrees_to_rotate);

    double cos = qCos(radians_to_rotate);
    double sin = qSin(radians_to_rotate);

    double new_x = original_vector.x()*cos - original_vector.y()*sin;
    double new_y = original_vector.x()*sin + original_vector.y()*cos;

    new_vector.setX(new_x);
    new_vector.setY(new_y);

    return new_vector;
}

/** Getter for radius member variable
 * @return radius member variable value
 */
qreal Ball::get_radius()
{
    return radius;
}

/** Getter for movement_vector member variable
 * @return movement_vector member variable value
 */
QVector2D Ball::get_movement_vector()
{
    return movement_vector;
}

/** Set position of ball in scene
 * @param new_position new position in scene to set ball at
 */
void Ball::set_position(QVector2D new_position)
{
    setPos(mapToParent(new_position.x(), new_position.y()));
}

/** Set movement_vector of ball
 * @param new_movement_vector new movement vector to set movement_vector to
 */
void Ball::set_movement(QVector2D new_movement_vector)
{
    movement_vector.setX(new_movement_vector.x());
    movement_vector.setY(new_movement_vector.y());
}

/** Set launch vector of ball
 * @param new_launch_vector new launch vector to set launch_vector to
 */
void Ball::set_launch(QVector2D new_launch_vector)
{
    launch_vector.setX(new_launch_vector.x());
    launch_vector.setY(new_launch_vector.y());
}

/** Decrease ball speed by multiplying current movement_vector by 1/speed_change_factor (assuming speed_change_factor > 0)
 */
void Ball::slower()
{
    movement_vector *= (1.0 / speed_change_factor);
}

/** Increase ball speed by multiplying current movement_vector by speed_change_factor (assuming speed_change_factor > 0)
 */
void Ball::faster()
{
    movement_vector *= speed_change_factor;
}
