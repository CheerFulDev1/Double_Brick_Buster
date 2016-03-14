/**
 * @file introwindow.cpp
 * @brief Definintion of member functions for the IntroWindow class
 * @author Bronson Schoen
 * @date 3/6/2016
 */

#include "introwindow.h"
#include "ui_introwindow.h"

/** Constructor for IntroWindow. Creates itself as a child of QMainWindow and bases itself on the introwindow.ui file.
    @param parent QWidget parent object of IntroWindow
 */
IntroWindow::IntroWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntroWindow)
{
    ui->setupUi(this);

    //make connections
    connect(ui->start_push_button,SIGNAL(clicked()),this,SLOT(show_level_1()));
}

/** Virtual destructor for IntroWindow deleting ui
 */
IntroWindow::~IntroWindow()
{
    delete ui;
}

/** Show's the Level_1 member variable (a window based on level_1.ui) and hides the IntroWindow
 */
void IntroWindow::show_level_1()
{
    level_one.show();
    this->hide();
}
