/**
 * @file level_1.cpp
 * @brief Definintion of member functions for the Level_1 class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#include "ui_level_1.h"
#include "level_1.h"

/** Default constructor for Level_1
 *  @param parent QWidget parent object of Level_1
 */
Level_1::Level_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level_1)
{
    //setup the ui elements from the ui file
    ui->setupUi(this);

    //Connect instructions/controls pushbutton to show_help()
    QObject::connect(ui->help_button, SIGNAL(clicked()), this, SLOT(show_help()));

    //create a new graphics scene to display
    scene = new QGraphicsScene(this);

    //set the graphics view to show this scene
    ui->level1_graphicsView->setScene(scene);

    //set framerate related parameters
    //numbers found through experimentation of what felt like the right play speed
    max_frames_per_second = 50;
    frames_per_second = 33;
    time_change_amount = 7;

    //set scene boundaries to those of the qgraphicsview
    boundary_margin = 5;

    int view_width = ui->level1_graphicsView->geometry().width()-boundary_margin;
    int view_height = ui->level1_graphicsView->geometry().height()-boundary_margin;

    scene->setSceneRect(0,0,view_width,view_height);

    //set our boolean values

    // first game hasn't yet been played
    first_game = true;

    // not yet started
    started=false;

    // set current level and current game to one
    current_level=1;
    current_game=1;

    // haven't just won a level
    won_level=false;

    // haven't yet beat entire game
    won_game=false;

    // time warp is bonus feature (in which ball moves faster when paddle moves right, slower when paddle moves left)
    time_warp=false;

    // create our paddle objects and add them to the scene
    paddle_top = new Paddle(170,25);
    paddle_bottom = new Paddle(170,440);
    scene->addItem(paddle_top);
    scene->addItem(paddle_bottom);

    // create our ball object and add it to the scene
    ball = new Ball();
    scene->addItem(ball);

    // set losing lines (and draw them)
    set_losing_lines();

    // create bricks
    set_bricks();

    // set boundaries (and draw them) for these scene, thus collisions against the sides will be detected
    set_boundaries();

    // create text item to display when beat entire game
    win_text = new QGraphicsTextItem;
    win_text->setPos(50,200);
    win_text->setPlainText("You won!!!!!!!");
    win_text->setScale(5);
}

/** Virtual destructor to delete ui
 */
Level_1::~Level_1()
{
    delete ui;
}

/** Draw the red lines representing losing.
 */
void Level_1::set_losing_lines()
{

    //Create pens to designate losing line
    QPen losing_line_pen = QPen(Qt::red);

    qreal bottom_y = (scene->sceneRect().bottomLeft().ry()-paddle_top->pos().y())+boundary_margin;
    qreal top_y = (scene->sceneRect().topLeft().ry()+paddle_top->pos().y())-boundary_margin;

    QPointF bottom_left_of_losing_line = QPointF(scene->sceneRect().bottomLeft().rx(),bottom_y);
    QPointF bottom_right_of_losing_line = QPointF(scene->sceneRect().bottomRight().rx(),bottom_y);

    QPointF top_left_of_losing_line = QPointF(scene->sceneRect().topLeft().rx(),top_y);
    QPointF top_right_of_losing_line = QPointF(scene->sceneRect().topRight().rx(),top_y);

    QLineF bottom_losing_line(bottom_left_of_losing_line, bottom_right_of_losing_line);
    QLineF top_losing_line(top_left_of_losing_line, top_right_of_losing_line);

    scene->addLine(bottom_losing_line, losing_line_pen);
    scene->addLine(top_losing_line, losing_line_pen);

}

/** Draws the boundaries of the current scene so collisions against the boundaries can be detected.
 */
void Level_1::set_boundaries()
{
    //Create pens to designate "type" of boundary
    QPen losing_boundary_pen = QPen(Qt::red);
    QPen side_boundary_pen = QPen(Qt::blue);

    //Draw top and bottom boundaries of scene
    QLineF top_line(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF bottom_line(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(top_line, losing_boundary_pen);
    scene->addLine(bottom_line, losing_boundary_pen);

    //Draw left and right sides of scene
    QLineF left_line(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF right_line(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());

    scene->addLine(left_line, side_boundary_pen);
    scene->addLine(right_line, side_boundary_pen);

}

/** Creates bricks, adds them to 'bricks' and the scene (according to the current level).
 */
void Level_1::set_bricks()
{

    // create bricks for level 1
    if(current_level==1)
    {

        //row 1
        bricks.append(new Brick(400,250));
        bricks.append(new Brick(300,250));
        bricks.append(new Brick(200,250, false, true, false, false));
        bricks.append(new Brick(100,250));

        //row 2
        bricks.append(new Brick(350,200));
        bricks.append(new Brick(250,200));
        bricks.append(new Brick(150,200, true, false, false, false));
        bricks.append(new Brick(50,200));

        //row 3
        bricks.append(new Brick(400,150));
        bricks.append(new Brick(300,150, true, false, false, false));
        bricks.append(new Brick(200,150));
        bricks.append(new Brick(100,150));

    }

    // create bricks for level 2
    else if(current_level==2)
    {

        //row 1
        bricks.append(new Brick(400,250));
        bricks.append(new Brick(100,250));

        //row 2
        bricks.append(new Brick(450,200));
        bricks.append(new Brick(350,200, false, false, true, false));
        bricks.append(new Brick(150,200));
        bricks.append(new Brick(50,200));

        //row 3
        bricks.append(new Brick(400,150));
        bricks.append(new Brick(100,150, false, false, false, true));

        //top I
        bricks.append(new Brick(170,140));
        bricks.append(new Brick(250,140));
        bricks.append(new Brick(330,140));

        //middle I
        bricks.append(new Brick(250,180));
        bricks.append(new Brick(250,220, false, false, true, false));
        bricks.append(new Brick(250,260));

        //bottom I
        bricks.append(new Brick(170,300));
        bricks.append(new Brick(250,300));
        bricks.append(new Brick(330,300, false, false, false, true));
    }

    // create bricks for level 3
    else if(current_level==3)
    {
        //row 1
        bricks.append(new Brick(400,250));
        bricks.append(new Brick(300,250, true, false, false, false));
        bricks.append(new Brick(200,250, false, false, true, false));
        bricks.append(new Brick(100,250));

        //row 2
        bricks.append(new Brick(350,200, false, false, false, true));
        bricks.append(new Brick(250,200));
        bricks.append(new Brick(150,200, true, false, false, false));
        bricks.append(new Brick(50,200));

        //row 3
        bricks.append(new Brick(300,150));
        bricks.append(new Brick(200,150));
        bricks.append(new Brick(100,150, false, false, false, true));
        bricks.append(new Brick(400,150, false, false, true, false));
    }


    // add bricks to scene
    foreach(Brick* item, bricks)
    {
        scene->addItem(item);
    }
}

/** If haven't beaten current game yet, resets the ball, paddles, and sets up new bricks for the next level
 */
void Level_1::next_level()
{

    //check for having beat game
    if(current_level>2)
    {
        beat_game();
        return;
    }

    //increase the level count
    current_level++;

    //reset 'started' so can start again
    started=false;

    //reset ball
    scene->removeItem(ball);
    delete ball;
    ball = new Ball();
    scene->addItem(ball);

    //reset paddles
    paddle_top->reset_powerups();
    paddle_bottom->reset_powerups();

    //set new bricks
    set_bricks();
}

/** Resets the current level. Destroys remaining bricks and sets up level just like next_level(). (resets ball, paddles, and sets up new bricks)
 */
void Level_1::reset_level()
{
    //reset 'started' so can start again
    started=false;

    //reset ball
    scene->removeItem(ball);
    delete ball;
    ball = new Ball();
    scene->addItem(ball);

    //reset paddles
    paddle_top->reset_powerups();
    paddle_bottom->reset_powerups();

    //clear existing bricks

    // get an iterator for iterating through the list
    QList<Brick*>::iterator bricks_iterator = bricks.begin();

    while(bricks_iterator!=bricks.end())
    {
        // scene no longer has ownership, doesn't call delete
        scene->removeItem(*bricks_iterator);

        // erase from QList bricks, return the iterator at the new correct position
        // does call delete
        delete (*bricks_iterator);
        bricks_iterator = bricks.erase(bricks_iterator);
    }

    //set new bricks
    set_bricks();
}

/** Notifies the user of beating the game and starts a new game.
 */
void Level_1::beat_game()
{   
    pause_level();

    QMessageBox::information(this, tr("Double Brick Breaker"),tr("You beat every level! \n \n Press 'Okay' to play again at a faster speed!"));

    new_game();
}

/** Starts the game over from level 1 with a faster timer.
 */
void Level_1::new_game()
{
    //increase the game count
    current_game++;

    //check for being at max speed (final game)
    if(current_game==3)
        QMessageBox::information(this, tr("Double Brick Breaker"),tr("MAX SPEED UNLOCKED!!!!!!! \n Get ready!"));

    //check for beating entire game
    if(current_game==4)
    {
        //notify the user
        QMessageBox::information(this, tr("Double Brick Breaker"),tr("You beat all levels on max speed! You win the game! \n Please exit the game and celebrate your status as one of the greatest Double Brick Buster players in the world."));

        //mark won_game as true so other functions know not to take action anymore (ex: can't unpause)
        won_game=true;

        //add winning text to scene (to show user they won)
        scene->addItem(win_text);

        return;
    }

    //increase framerate
    speed_up_time();

    //reset the current level to 1
    current_level=0;

    //setup level
    next_level();
}

/** Connects functions for handling animations, collisions, and checking for win/loss to a timer. Starts that timer.
 */
void Level_1::start_level()
{
    paused=false;

    //Connect timer to handle animations (done by the advance function in QGraphicsScene)
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));

    //Connect timer to handle collisions
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(handle_collisions()));

    //Connect timer to check for loss
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(check_for_loss()));

    //Connect timer to check for win
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(check_for_win()));

    //start the timer, updating at frames_per_second times per second
    timer.start(1000 / frames_per_second);
}

/** Stops the timer game functions are connected to
 */
void Level_1::pause_level()
{
    timer.stop();
    paused=true;
}

/** Starts the timer game functions are connected to
 */
void Level_1::unpause_level()
{
    //don't allow pausing/unpausing before starting
    if(!started)
        return;

    //don't allow pausing/unpausing if beat game
    if(won_game)
        return;

    timer.start();
    paused=false;
}

/** Decreases speed of timer game functions are connected to.
 */
void Level_1::slow_time()
{
    //decrease the speed of the clock
    frames_per_second -= time_change_amount;
    timer.start(1000/frames_per_second);

    //stop the clock
    timer.stop();
    paused=true;
}

/** Increases speed of timer game functions are connected to up to a predetermined maximum.
 */
void Level_1::speed_up_time()
{
    //don't go above the maximum framerate
    if(frames_per_second >= max_frames_per_second)
        return;

    //increase the speed of the timer
    frames_per_second += time_change_amount;
    timer.start(1000/frames_per_second);

    //stop the clock
    timer.stop();
    paused=true;
}

/** Adjusts the paddle depending on the powerup of a hit brick.
    @param hit_brick pointer to Brick that has hit as true (has been hit)
 */
void Level_1::handle_powerups(Brick* hit_brick)
{
    if(hit_brick->is_shrink_powerup())
    {
        paddle_top->shrink();
        paddle_bottom->shrink();
    }
    else if(hit_brick->is_grow_powerup())
    {
        paddle_top->grow();
        paddle_bottom->grow();
    }
    else if(hit_brick->is_slower_powerup())
    {
        paddle_top->slower();
        paddle_bottom->slower();
    }
    else if(hit_brick->is_faster_powerup())
    {
        paddle_top->faster();
        paddle_bottom->faster();
    }
}


/** Show instructions and controls. Pauses game while displaying, unpauses game after.
 */
void Level_1::show_help()
{
    pause_level();
    QMessageBox::information(this,
                             tr("Instructions and Controls"),
                             tr("Instructions: \n \n - Use your paddles and the ball to bust all the bricks! \n - Both top and bottom paddles move together \n - Don't let the ball go past your paddles! \n - Break powerup bricks to modify your paddles! \n - Break all the bricks to win! \n - Press the 'Instructions / Controls' button during gameplay to see all this again! \n - Close the game window (using the 'x' in the top left of the window) to exit the game! \n \n Controls: \n \n - Use 'space' on your keyboard to launch the ball \n - Use 'a' or 'd' on your keyboard to move around \n - Use 'p' on your keyboard to pause / unpause \n \n Powerups: \n \n - Blue blocks are normal \n - Yellow blocks shrink your paddle \n - Cyan blocks grow your paddle \n - Red blocks slow down your paddle \n - Green blocks speed up your paddle"));
    unpause_level();
}


/** Checks all the currently existing bricks to see if they've been hit. If they have, it removes them from 'bricks', the scene, and deletes them.
 */
void Level_1::handle_collisions()
{
    // get an iterator for iterating through the list
    QList<Brick*>::iterator bricks_iterator = bricks.begin();

    // for each brick in bricks
    //NOTE: Not using foreach because am deleting from list while iterating over it
    while(bricks_iterator!=bricks.end())
    {
        // if something collides with the brick
        if((*bricks_iterator)->is_hit())
        {
            //handle direction of ball bounce
            //duplicate cases bouncing 270 for clarity of division between cases

            //bouncing off bottom of brick going left / up
            if(((ball->pos().y()) > (*bricks_iterator)->pos().y()) && (ball->get_movement_vector().x() < 0) && (ball->get_movement_vector().y() < 0))
            {
                ball->bounce(270);
            }

            //bouncing off top of brick going right / down
            else if(((ball->pos().y()+(0.5)*ball->get_radius()) < (*bricks_iterator)->pos().y()) && (ball->get_movement_vector().x() > 0) && (ball->get_movement_vector().y() > 0))
            {
                ball->bounce(270);
            }

            //bouncing off left of brick going left / up
            else if((ball->pos().x()+(0.5)*ball->get_radius() < (*bricks_iterator)->pos().x()) && (ball->get_movement_vector().x() > 0) && (ball->get_movement_vector().y() < 0))
            {
                ball->bounce(270);
            }


            //otherwise just bounce the ball
            else
            {
                ball->bounce(90);
            }

            //handle powerups from brick
            handle_powerups(*bricks_iterator);

            // scene no longer has ownership, doesn't call delete
            scene->removeItem(*bricks_iterator);

            // erase from QList bricks, return the iterator at the new correct position
            // does call delete
            delete (*bricks_iterator);
            bricks_iterator = bricks.erase(bricks_iterator);

        }
        // else move on to next brick
        else
            ++bricks_iterator;
    }
}

/** If ball is above top paddle or below bottom paddle, calls user_lost() to handle a loss.
 */
void Level_1::check_for_loss()
{
    if( ball->pos().y() > paddle_bottom->pos().y() ||  ball->pos().y() < paddle_top->pos().y())
        user_lost();
}


/** If there are no bricks left, calls user_won() to handle a win.
 */
void Level_1::check_for_win()
{
    //check for !won_level because don't want to count multiple wins for the same level
    if(bricks.isEmpty() && !won_level)
        user_won();
}


/** Handle a loss. Pause level, notify user of loss, wait for user acknowledgement, and reset the level.
 */
void Level_1::user_lost()
{
    //stop the game while we handle the loss
    pause_level();

    //Prompt user to take action on loss
    QMessageBox::information(this, tr("Double Brick Breaker"),tr("Loss :( \n Press 'Okay' to try again or exit the program to quit."));

    //If the user pressed okay, set up the same level again
    reset_level();
}

/** Handle a win. Pause level, notify user of win, wait for user acknowledgement, and setup the next level.
 */
void Level_1::user_won()
{
    //stop the game while we handle the current win
    pause_level();

    //set just won_level to be true
    won_level = true;

    //Prompt user to start next level
    QMessageBox::information(this, tr("Double Brick Breaker"),tr("Winner!!! \n Press 'Okay' to move on to the next level! "));

    //Setup next level
    next_level();
}

/** Outputs to QDebug for debugging purposes. Can be filled with any QDebug output calls.
 */
void Level_1::print_debug()
{
    //DEBUG
    qDebug()<<"Ball position is: "<<ball->pos().y();
    qDebug()<<"Top paddle position is: "<<paddle_top->pos().y();
    qDebug()<<"Bottom paddle position is: "<<paddle_bottom->pos().y();
}

/** Slot connected to keyPressEvents. Catches QKeyEvent's and processes them. Essentially responsible for handling keyboard input.
    @param key_event QKeyEvent of recent keyboard input by the player
 */
void Level_1::keyPressEvent(QKeyEvent* key_event)
{

    //use key 'a' for moving both paddles left
    if((key_event->key() == Qt::Key_A) && !paused)
    {
        //don't allow movement before starting
        if(!started)
            return;

        //move both paddles left
        paddle_top->move_left();
        paddle_bottom->move_left();

        //if time warp mode is enabled, the ball moves slower the further left the paddle gets
        if(time_warp)
            ball->slower();
    }

    //use key 'd' for moving both paddles right
    if((key_event->key() == Qt::Key_D) && !paused)
    {
        //don't allow movement before starting
        if(!started)
            return;

        //move both paddles right
        paddle_top->move_right();
        paddle_bottom->move_right();

        //if time warp mode is enabled, the ball moves faster the further right the paddle gets
        if(time_warp)
            ball->faster();

    }

    //toggle paused with the 'P' key
    if(key_event->key() == Qt::Key_P)
    {
        if(paused)
            unpause_level();
        else
            pause_level();
    }

    //start the game with the 'Space' key
    if(key_event->key() == Qt::Key_Space)
    {
        //start the game
        if(!started)
        {
            //set started to true because just started the game
            started=true;

            //won_level false because starting a new level which we have not yet won
            won_level=false;

            //if it's the first game, make all the connections
            if(first_game)
            {
                this->start_level();
                first_game=false;
            }
            //otherwise just unpause the level
            else
                unpause_level();

            //launch the ball to start the game
            ball->launch_ball();
        }
    }
}
