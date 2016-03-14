/**
 * @file level_1.h
 * @brief Declaration (of class and member functions) for the Level_1 class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QtGlobal>
#include <QMessageBox>
#include <QKeyEvent>


#include "ball.h"
#include "brick.h"
#include "paddle.h"

namespace Ui {
    class Level_1;
}

/**
    @class Level_1
    @brief Dervied class of QWidget based on Level_1.ui. Responsible for handling main game functionality such as level / paddle / ball / brick generation, checking for wins/losses, and more.
 */
class Level_1 : public QWidget
{
    Q_OBJECT

    public:

        explicit Level_1(QWidget *parent = 0);
        virtual ~Level_1();

        //Create losing lines for scene (not used for collisions)
        void set_losing_lines();

        //Create boundaries for scene
        void set_boundaries();

        //Create and place bricks for scene
        void set_bricks();

        //Go to next level
        void next_level();

        //Reset current level
        void reset_level();

        //Show screen when beat the game
        void beat_game();

        //New game (harder)
        void new_game();

        //Begin level
        void start_level();

        //Pause level
        void pause_level();

        //Unpause level
        void unpause_level();

        //Slow time
        void slow_time();

        //Speed up time
        void speed_up_time();

        //Trigger power ups
        void handle_powerups(Brick* hit_brick);

    public slots:

        //show instructions and controls
        void show_help();

        //Call appropriate functions for any collisions
        void handle_collisions();

        //check for loss
        //here 'losing' conditions are defined
        void check_for_loss();

        //check for win
        //here 'winning' conditions are defined
        void check_for_win();

        //execute appropriate actions for a loss
        void user_lost();

        //execute appropriate actions for a win
        void user_won();

        //Print for debugging
        void print_debug();

    private:

        //UI subset 'Level_1' as definted by ui file
        Ui::Level_1 *ui;

        //Create overall graphics scene
        QGraphicsScene *scene;

        //Create paddles
        Paddle *paddle_top;
        Paddle *paddle_bottom;

        //Create ball
        Ball *ball;

        //Create bricks
        QList<Brick*> bricks;

        //Timer for updating the scene
        QTimer timer;
        qreal max_frames_per_second;
        qreal frames_per_second;
        qreal time_change_amount;

        int boundary_margin;

        bool first_game;
        bool won_level;
        bool won_game;
        bool started;
        bool paused;
        bool time_warp;

        void keyPressEvent(QKeyEvent* key_event);

        int current_level;
        int current_game;

        //text to display for beating entire game
        QGraphicsTextItem* win_text;
};

#endif // LEVEL_1_H
