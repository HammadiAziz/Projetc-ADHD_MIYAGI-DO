include "editer_medecin.h"
#include "ui_editer_medecin.h"

editer_medecin::editer_medecin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editer_medecin)
{
    ui->setupUi(this);
}

editer_medecin::~editer_medecin()
{
    delete ui;
}
