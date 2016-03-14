/**
 * @file brick.cpp
 * @brief Definintion of member functions for the Brick class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#include "brick.h"

/** Default constructor for Brick.
 */
Brick::Brick()
{
    //set to not hit yet
    hit = false;

    //initialize animation settings
    width = 60;
    height = 20;
    pen_width = 1;

    //set powerups
    shrink_powerup = false;
    grow_powerup = false;
    slower_powerup = false;
    faster_powerup = false;

    //give us starting position
    start_vector.setX(250);
    start_vector.setY(250);
    setPos(mapToParent(start_vector.x(), start_vector.y()));

}

/** Constructor for Brick. Sets brick at given x,y position.
 *  @param start_x_position starting x coordinate in scene
 *  @param start_y_position starting y coordinate in scene
 */
Brick::Brick(int start_x_position, int start_y_position)
{
    //set to not hit yet
    hit = false;

    //initialize animation settings
    width = 60;
    height = 20;
    pen_width = 1;

    //set powerups
    shrink_powerup = false;
    grow_powerup = false;
    slower_powerup = false;
    faster_powerup = false;

    //give us starting position
    start_vector.setX(start_x_position);
    start_vector.setY(start_y_position);
    setPos(mapToParent(start_vector.x(), start_vector.y()));
}

/** Constructor for Brick. Sets brick at given x,y position. Sets powerups for Brick.
 *  @param start_x_position starting x coordinate in scene
 *  @param start_y_position starting y coordinate in scene
 *  @param shrink_powerup_brick boolean value for whether or not brick contains the shrink powerup
 *  @param grow_powerup_brick boolean value for whether or not brick contains the grow powerup
 *  @param slower_powerup_brick boolean value for whether or not brick contains the slower powerup
 *  @param faster_powerup_brick boolean value for whether or not brick contains the faster powerup
 */
Brick::Brick(int start_x_position, int start_y_position,
      bool shrink_powerup_brick,
      bool grow_powerup_brick,
      bool slower_powerup_brick,
      bool faster_powerup_brick)
{
    //set to not hit yet
    hit = false;

    //initialize animation settings
    width = 60;
    height = 20;
    pen_width = 1;

    //set powerups
    shrink_powerup = shrink_powerup_brick;
    grow_powerup = grow_powerup_brick;
    slower_powerup = slower_powerup_brick;
    faster_powerup = faster_powerup_brick;

    //give us starting position
    start_vector.setX(start_x_position);
    start_vector.setY(start_y_position);
    setPos(mapToParent(start_vector.x(), start_vector.y()));
}

/** Set bounding rectangle for drawing and collisions
    @returns bounding rectange for shape
 */
QRectF Brick::boundingRect() const
{
    return QRectF(0,
                  0,
                  width + pen_width,
                  height + pen_width);
}


/** Paints object with correct shape in local coordinates. Determines if hit and colors according to powerup.
    @param *painter QPainter object resposible for painting the object in the scene
    @param *option provides style options for the item, such as its state, exposed area and its level-of-detail hints
    @param *widget Optional. If provided, it points to the widget that is being painted on; otherwise, it is 0.
 */
void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->setBrush(Qt::black);

    if(scene()->collidingItems(this).isEmpty() && !hit)
    {
        //color according to powerup
        if(shrink_powerup)
            painter->setBrush(Qt::yellow);
        else if(grow_powerup)
            painter->setBrush(Qt::cyan);
        else if(slower_powerup)
            painter->setBrush(Qt::red);
        else if(faster_powerup)
            painter->setBrush(Qt::green);
        //color normal bricks blue
        else
            painter->setBrush(Qt::blue);
    }
    else
    {
        hit=true;
    }

    //should match shape in Brick::shape
    painter->drawRect(0, 0, width, height);

    painter->setBrush(Qt::NoBrush);
}


/** Gives an accurate shape, which is used by QGraphicsScene to animate.
    @returns path QPainterPath to draw representing shape
 */
//Gives an accurate shape, which is used by QGraphicsScene to animate
QPainterPath Brick::shape() const
{
    QPainterPath path;
    //should match shape in Brick::shape
    path.addRect(0, 0, width, height);
    return path;
}

/** Getter for width member variable
 * @return returns value of width member variable
 */
qreal Brick::get_width()
{
    return width;
}

/** Getter for height member variable
 * @return returns value of height member variable
 */
qreal Brick::get_height()
{
    return height;
}

/** Set hit member variable to hit_value
 * @param hit_value value to set member variable hit to
 */
void Brick::set_hit(bool hit_value)
{
    hit=hit_value;
}

/** Getter for hit member variable
 * @return boolean value of hit
 */
bool Brick::is_hit()
{
    return hit;
}

/** Getter for shrink_powerup member variable
 * @return boolean value of shrink_powerup
 */
bool Brick::is_shrink_powerup()
{
    return shrink_powerup;
}

/** Getter for grow_powerup member variable
 * @return boolean value of grow_powerup
 */
bool Brick::is_grow_powerup()
{
    return grow_powerup;
}

/** Getter for slower_powerup member variable
 * @return boolean value of slower_powerup
 */
bool Brick::is_slower_powerup()
{
    return slower_powerup;
}

/** Getter for faster_powerup member variable
 * @return boolean value of faster_powerup
 */
bool Brick::is_faster_powerup()
{
    return faster_powerup;
}
