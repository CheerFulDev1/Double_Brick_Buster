/**
 * @file introwindow.h
 * @brief Declaration (of class and member functions) for the IntroWindow class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include <QMainWindow>

#include "level_1.h"

namespace Ui {
class IntroWindow;
}

/**
    @class IntroWindow
    @brief Dervied class of QMainWindow based on IntroWindow.ui. This is our Main Window and the first window shown. It creates the Level_1 instance, shows it, and hides itself while the game is being played.
 */
class IntroWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit IntroWindow(QWidget *parent = 0);
        ~IntroWindow();

    public slots:

        void show_level_1();

    private:
        Ui::IntroWindow *ui;

        Level_1 level_one;
};

#endif // INTROWINDOW_H
