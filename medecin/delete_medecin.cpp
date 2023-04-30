#include "delete_medecin.h"
#include "ui_delete_medecin.h"

delete_medecin::delete_medecin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_medecin)
{
    ui->setupUi(this);
}

delete_medecin::~delete_medecin()
{
    delete ui;
}
