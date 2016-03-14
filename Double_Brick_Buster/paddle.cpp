/**
 * @file paddle.cpp
 * @brief Definintion of member functions for the Paddle class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#include "paddle.h"

/** Default constructor for Paddle
 */
Paddle::Paddle()
{

    //initialize animation settings
    width = 200;
    height = 15;
    starting_width = width;
    starting_height = height;
    pen_width = 1;

    //set movement distance for key events
    default_movement_distance = 20;
    starting_movement_distance = default_movement_distance;

    //set size_change_amount for shrinking and growing
    size_change_amount = 50;

    //set speed_change_amount for faster and slower
    speed_change_amount = 6;

    //give us starting position
    start_vector.setX(170);
    start_vector.setY(440);
    setPos(mapToParent(start_vector.x(), start_vector.y()));

}

/** Constructor for Paddle. Sets paddle at given x,y position.
 *  @param start_x_position starting x coordinate in scene
 *  @param start_y_position starting y coordinate in scene
 */
Paddle::Paddle(int start_x_position, int start_y_position)
{
    //initialize animation settings
    width = 200;
    height = 15;
    starting_width = width;
    starting_height = height;
    pen_width = 1;

    //set movement distance for key events
    default_movement_distance = 20;
    starting_movement_distance = default_movement_distance;

    //set size_change_amount for shrinking and growing
    size_change_amount = 50;

    //set speed_change_amount for faster and slower
    speed_change_amount = 6;

    //give us starting position
    start_vector.setX(start_x_position);
    start_vector.setY(start_y_position);
    setPos(mapToParent(start_vector.x(), start_vector.y()));
}

/** Set bounding rectangle for drawing and collisions
    @returns bounding rectange for shape
 */
QRectF Paddle::boundingRect() const
{
    return QRectF(0,
                  0,
                  width,
                  height);
}

/** Paints object with correct shape in local coordinates. Colors according to powerup.
    @param *painter QPainter object resposible for painting the object in the scene
    @param *option provides style options for the item, such as its state, exposed area and its level-of-detail hints
    @param *widget Optional. If provided, it points to the widget that is being painted on; otherwise, it is 0.
 */
void Paddle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{

    //color according to paddle speed

    //color faster paddle same color as faster powerup
    if(default_movement_distance > starting_movement_distance)
        painter->setBrush(Qt::green);

    //color slower paddle same color as slower powerup
    else if(default_movement_distance < starting_movement_distance)
        painter->setBrush(Qt::red);

    //color normal paddle
    else
        painter->setBrush(Qt::magenta);

    //should match shape in Paddle::shape
    painter->drawRect(0, 0, width, height);

    painter->setBrush(Qt::NoBrush);
}


/** Gives an accurate shape, which is used by QGraphicsScene to animate.
    @returns path QPainterPath to draw representing shape
 */
QPainterPath Paddle::shape() const
{
    QPainterPath path;
    //should match shape in Paddle::shape
    path.addRect(0, 0, width, height);
    return path;
}

/** Move the paddle default_movement_distance number of units to the left
*/
void Paddle::move_left()
{
    //update position based on moving to the left
    QPointF updated_position = mapToParent(-default_movement_distance,0);

    //if the new position would be out of bounds, don't allow the movement
    if(!scene()->sceneRect().contains((updated_position)))
    {
        return;
    }
    else
        setPos(updated_position);
}

/** Move the paddle default_movement_distance number of units to the right
 */
void Paddle::move_right()
{
    //update position based on moving to the right
    QPointF updated_position = mapToParent(default_movement_distance,0);

    //adjust for width of paddle
    QPointF updated_adjusted_position = mapToParent(default_movement_distance+width,0);

    //if the new position would be out of bounds, don't allow the movement
    if(!scene()->sceneRect().contains((updated_adjusted_position)))
    {
        return;
    }
    else
        setPos(updated_position);
}

/** Getter for width member variable
 * @return returns value of width member variable
 */
qreal Paddle::get_width()
{
    return width;
}

/** Getter for height member variable
 * @return returns value of height member variable
 */
qreal Paddle::get_height()
{
    return height;
}

/** Setter for width member variable
 * @param new_width new width value to set width to
 */
void Paddle::set_width(qreal new_width)
{
    width = new_width;
}

/** Setter for height member variable
 * @param new_height new height value to set height to
 */
void Paddle::set_height(qreal new_height)
{
    height = new_height;
}

/** Decrease width of paddle by size_change_amount
 */
void Paddle::shrink()
{
    width -= size_change_amount;
}

/** Increase width of paddle by size_change_amount
 */
void Paddle::grow()
{
    width += size_change_amount;
}

/** Decrease default_movement_distance of paddle by speed_change_amount
 */
void Paddle::slower()
{
    default_movement_distance -= speed_change_amount;
}

/** Increase default_movement_distance of paddle by speed_change_amount
 */
void Paddle::faster()
{
    default_movement_distance += speed_change_amount;
}

/** Undoes the effect of any powerups by returning paddle back to starting width, height, and movement_distance
 */
void Paddle::reset_powerups()
{
    width = starting_width;
    height = starting_height;
    default_movement_distance = starting_movement_distance;
}


