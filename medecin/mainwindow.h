#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "medecin.h"
#include "medicamant.h"
#include "consultation.h"
#include "bpm.h"
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_stackedWidget_currentChanged(int arg1);

    //void on_pushButton_27_clicked();

    void on_ajout_2_clicked();

    void on_lineEdit_parcour_medecin_cursorPositionChanged(int arg1, int arg2);

    void on_delet_botton_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_25_clicked();

    void on_quit_1_clicked();

    void on_quit_2_clicked();

    void on_pushButton_2_clicked();

    void on_quit_3_clicked();

    void on_ajout_3_clicked();

    void on_rechercher_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_clicked();

    void on_ajout_4_clicked();

    void on_view_stat_clicked();

    void on_lineEdit_ID_rechercher_textChanged(const QString &arg1);

    void on_comboBoxmed_tri_currentIndexChanged(const QString &arg1);

    void update_label();

private:
    Ui::MainWindow *ui;
    medecin M;
    medicamant ME;
    consultation CN;
    bpm B;
    QByteArray data;




};

#endif // MAINWINDOW_H
