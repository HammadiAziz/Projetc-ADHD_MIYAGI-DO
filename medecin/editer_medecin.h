#ifndef EDITER_MEDECIN_H
#define EDITER_MEDECIN_H

#include <QDialog>

namespace Ui {
class editer_medecin;
}

class editer_medecin : public QDialog
{
    Q_OBJECT

public:
    explicit editer_medecin(QWidget *parent = nullptr);
    ~editer_medecin();

private:
    Ui::editer_medecin *ui;
};

#endif // EDITER_MEDECIN_H
