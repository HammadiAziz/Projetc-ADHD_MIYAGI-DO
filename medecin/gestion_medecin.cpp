include "gestion_medecin.h"
#include "ui_gestion_medecin.h"

gestion_medecin::gestion_medecin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_medecin)
{
    ui->setupUi(this);
}

gestion_medecin::~gestion_medecin()
{
    delete ui;
}
