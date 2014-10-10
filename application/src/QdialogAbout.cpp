#include "QdialogAbout.hpp"
#include "ui_about.h"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief About::About
 * @param parent
 */
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

/*******************************************************************************
 * Destructors
 ******************************************************************************/
/**
 * @brief About::~About
 */
About::~About()
{
    delete ui;
}
