#include "affichage.h"
#include "ui_affichage.h"

affichage::affichage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affichage)
{
    ui->setupUi(this);
}

affichage::~affichage()
{
    delete ui;
}
