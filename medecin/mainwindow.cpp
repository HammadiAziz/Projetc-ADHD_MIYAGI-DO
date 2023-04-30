#include "mainwindow.h"
#include "medecin.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QSqlTableModel>
#include <QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QTextTableCell>
#include <QTableWidget>
#include <QTextDocument>
#include "medicamant.h"
#include "consultation.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->lineEdit_ID_medecin->setMaxLength(10);
    ui->tableView_med->setModel(M.afficher());

    ui->comboBoxdelete->setModel(M.afficher());
    ui->comboBoxupdate->setModel(M.afficher());

    ui->comboBoxmed_consul->setModel(M.afficher());

    ui->comboBoxenfant_consul->setModel(ME.afficherenfant());
    ui->comboBoxmedeca_consul->setModel(ME.affichermedi());


    ui->lineEdit_qte_medic->setValidator(new QIntValidator(0,999999999,this));
    ui->tableView_medic->setModel(ME.affichermedi());

    ui->tableView_cons->setModel(CN.afficher_cons());

    ui->comboBoxmedeca_consul->addItem("NULL");





    int ret=B.connect_arduino();
    switch (ret) {
    case(0):qDebug()<< "arduino is available and connected to : "<< B.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<B.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";

    }
    QObject::connect(B.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_label()
{
    data=B.read_from_arduino();

    //QByteArray data ="3A"; // your byte array data
    int value = data.toInt();
    qDebug("Value: %d", value);
    if(value>=50)

    //QString str = QString::number(value);




 //if(data=="0")
    //ui->label_21->setText("0");
    //if(data>="1")
    //{
    if(value>=0)
    {
        ui->label_21->setNum(value); // si les données reçues de arduino via la liaison série sont égales à 1
        ui->lcdNumber->display(data.toInt());
    }
        //delay_ms(20);
   // }
    //else
      //  ui->label_21->setText("0");
}





void MainWindow::on_ajout_2_clicked()
{
    QString ID_medecin=ui->lineEdit_ID_medecin->text();
    QString nom_medecin=ui->lineEdit_Nom_medecin->text();
    QString prenom_medecin=ui->lineEdit_Prenom_medein->text();
    QString adresse_medecin=ui->lineEdit_adress_medecin->text();
    QString adressemainl_medecin=ui->lineEdit_adress_mail_medecin->text();
    QString parcour_medecin=ui->lineEdit_parcour_medecin->text();


    medecin M(ID_medecin,nom_medecin,prenom_medecin,adresse_medecin,adressemainl_medecin,parcour_medecin);

    bool test=M.ajouter();
    if(test)
    {
        ui->tableView_med->setModel(M.afficher());
        ui->comboBoxdelete->setModel(M.afficher());
        ui->comboBoxupdate->setModel(M.afficher());
        QMessageBox::information(nullptr,QObject::tr("OIK"),
                                            QObject::tr("Ajout nice \n"
                                                        "clic cancel"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_delet_botton_clicked()
{
    medecin M;
    //M.setID_medecin(ui->lineEdit_ID_medecin_D_2->text());

    QString id=ui->comboBoxdelete->currentText();

        bool test=M.supprimer(id);
        QMessageBox msgBox;
if(test)
{
    msgBox.setText("suppression nej7A");
    ui->tableView_med->setModel(M.afficher());
    ui->comboBoxdelete->setModel(M.afficher());

    ui->comboBoxupdate->setModel(M.afficher());


}
else {
    msgBox.setText("ma tfasa5ech");

}
msgBox.exec();


}









void MainWindow::on_pushButton_update_clicked()
{
    QString id_medecin=ui->comboBoxupdate->currentText();

    //QString ID_medecin=ui->lineEdit_ID_medecin->text();
    QString nom_medecin=ui->lineEdit_Nom_medecin->text();
    QString prenom_medecin=ui->lineEdit_Prenom_medein->text();
    QString adresse_medecin=ui->lineEdit_adress_medecin->text();
    QString adressemainl_medecin=ui->lineEdit_adress_mail_medecin->text();
    QString parcour_medecin=ui->lineEdit_parcour_modif->text();


    medecin M(id_medecin,nom_medecin,prenom_medecin,adresse_medecin,adressemainl_medecin,parcour_medecin);

    if(parcour_medecin.isEmpty())
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout un parcour.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        bool test=M.update(id_medecin);
        if(test)
        {
            QMessageBox msgbox;
            ui->tableView_med->setModel(M.afficher());
            ui->comboBoxupdate->setModel(M.afficher());
            ui->comboBoxdelete->setModel(M.afficher());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("changement effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);



        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("modification non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);
        }
    }

}
//********* rechercher ***********

void MainWindow::on_lineEdit_ID_rechercher_textChanged(const QString &arg1)
{
    QString rech =ui->lineEdit_ID_rechercher->text();

        ui->tableView_med->setModel(M.rechercher(rech));
}



// *************** medicamant ***************







//********* ajout medic ***********
void MainWindow::on_ajout_3_clicked()
{
    QString id_medicamant=ui->lineEdit_ID_medic->text();
    QString nom_medicamant=ui->lineEdit_Nom_medic->text();
    QString qte_medicamant=ui->lineEdit_qte_medic->text();

    medicamant ME(id_medicamant,nom_medicamant,qte_medicamant);

    bool test=ME.ajouter_medi();

    if(test)
    {
        ui->tableView_medic->setModel(ME.affichermedi());

           QMessageBox:: information(nullptr, QObject::tr("OK"),
                                              QObject::tr("Ajout effectué\n"
                                                          "click cancel to exit."),QMessageBox::Cancel);
           }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Ajout non effectué.\n"
                                             "click Cancel to exit."),QMessageBox::Cancel);




}




void MainWindow::on_comboBoxmed_tri_currentIndexChanged(const QString &arg1)
{
    QString selectionvalue= ui->comboBoxmed_tri->currentText();
        if (selectionvalue=="ID"){ui->tableView_medic->setModel(ME.trid());}
        else if (selectionvalue=="Nom"){ui->tableView_medic->setModel(ME.trinom());}
        else if (selectionvalue=="QTE"){ui->tableView_medic->setModel(ME.tritype());}
        else if    (selectionvalue=="non trier"){ui->tableView_medic->setModel(ME.affichermedi());}
}



//********* PDF ***********
void MainWindow::on_pushButton_clicked()
{

    QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName("medecin.pdf");

            QTableView* tableView = ui->tableView_med; // replace with the name of your QTableView

            // create a QTextDocument with the contents of the QTableView
            QTextDocument doc;
            QTextCursor cursor(&doc);
            doc.setPageSize(printer.pageRect().size());
               doc.setDocumentMargin(10.0);

            // insert the title in the middle
                QTextBlockFormat blockFormat;
                blockFormat.setAlignment(Qt::AlignCenter);
                cursor.insertBlock(blockFormat);
                QTextCharFormat titleFormat;
                titleFormat.setFontWeight(QFont::Bold);
                titleFormat.setFontPointSize(14);
                cursor.insertText("tab medecin", titleFormat);

                // insert the image in the top left corner
                QImage image("C:/Users/rayen/Desktop/logodevsn.webp"); // replace with the name and path of your image
                if (!image.isNull()) {
                    QPixmap pixmap = QPixmap::fromImage(image);
                    if (!pixmap.isNull()) {
                        pixmap = pixmap.scaled(QSize(200, 50), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        QTextImageFormat imageFormat;
                        imageFormat.setWidth(pixmap.width());
                        imageFormat.setHeight(pixmap.height());
                        imageFormat.setName("medecin.pdf");
                        cursor.movePosition(QTextCursor::Start);
                        cursor.insertImage(imageFormat);
                        doc.addResource(QTextDocument::ImageResource, QUrl("medecin.pdf"), QVariant(pixmap));
                    }
                }

                // insert the table
                cursor.insertBlock();
                QTextBlockFormat tableBlockFormat;
                    tableBlockFormat.setAlignment(Qt::AlignCenter);
                    cursor.insertBlock(tableBlockFormat);
            cursor.insertText("Table View Data\n\n");
            int rows = tableView->model()->rowCount();
            int columns = tableView->model()->columnCount();
            QTableWidget table(rows + 1, columns);
            table.setHorizontalHeaderLabels(QStringList() << "ID_medecin" << "Nom" << "prenom" << "adresse" << "mail" << "parcour"); // replace with your column headers
            for (int row = 0; row < rows; row++) {
                for (int column = 0; column < columns; column++) {
                    table.setItem(row + 1, column, new QTableWidgetItem(tableView->model()->data(tableView->model()->index(row, column)).toString()));
                }
            }
            QTextTableFormat tableFormat;
            tableFormat.setHeaderRowCount(1);
            QTextTable* textTable = cursor.insertTable(rows + 1, columns, tableFormat);

            for (int column = 0; column < columns; column++) {
                QTextTableCell headerCell = textTable->cellAt(0, column);
                QTextCursor headerCursor = headerCell.firstCursorPosition();
                headerCursor.insertText(table.horizontalHeaderItem(column)->text());
            }

            QTextCharFormat cellFormat;
            cellFormat.setFont(QFont("Helvetica", 10, QFont::Bold));
            for (int row = 0; row < rows; row++) {
                for (int column = 0; column < columns; column++) {
                    QTextTableCell cell = textTable->cellAt(row + 1, column);
                    cell.setFormat(cellFormat);
                    cell.firstCursorPosition().insertText(tableView->model()->data(tableView->model()->index(row, column)).toString());
                }
            }
            //la date ou le pdf a ete generer
            cursor.movePosition(QTextCursor::PreviousBlock);
                QTextBlockFormat dateBlockFormat;
                dateBlockFormat.setAlignment(Qt::AlignRight);
                cursor.insertBlock(dateBlockFormat);
                QTextCharFormat dateFormat;
                dateFormat.setFontPointSize(8);
                cursor.insertText("Generated on " + QDate::currentDate().toString("dd/MM/yyyy"), dateFormat);

            // print the QTextDocument to the PDF printer
            QPainter painter(&printer);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::TextAntialiasing);
            doc.setPageSize(printer.pageRect().size());
            doc.drawContents(&painter);





            QMessageBox::information(nullptr,QObject::tr("pdf"),
            QObject::tr("pdf is printed.\n"
                        "click cancel and exit"),QMessageBox::Cancel);


}








// ********** CONSULTATION *************



void MainWindow::on_ajout_4_clicked()
{
    QString ID_cons=ui->lineEdit_ID_consul->text();
    QString temps_cons=ui->temps->text();
    QString salle_cons=ui->salle->text();

    QString diag_cons=ui->diag->text();

    QString id_medecin=ui->comboBoxmed_consul->currentText();

    QString id_medica=ui->comboBoxmedeca_consul->currentText();


    QString id_enfant=ui->comboBoxenfant_consul->currentText();

    ui->comboBoxmedeca_consul->addItem("NULL");

    consultation CN(ID_cons,temps_cons,salle_cons,diag_cons,id_medecin,id_medica,id_enfant);



    bool test=CN.ajouter_cons();

    if(test)
    {
        // ME.takeone(id_medica);
        ui->tableView_medic->setModel(ME.affichermedi());

        ui->tableView_cons->setModel(CN.afficher_cons());

        QSqlQuery query;
        query.prepare("UPDATE MEDICAMENTS SET QTE_MEDIC=QTE_MEDIC-1 WHERE ID_MEDIC = '"+id_medica+"%");
        //query.bindValue(":val",take);
        query.exec();

        ui->tableView_medic->setModel(ME.affichermedi());


        //ui->comboBoxmedeca_consul->addItem("NULL");

           QMessageBox:: information(nullptr, QObject::tr("OK"),
                                              QObject::tr("Ajout effectué\n"
                                                          "click cancel to exit."),QMessageBox::Cancel);
           }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Ajout non effectué.\n"
                                             "click Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_view_stat_clicked()
{
    QSqlQuery q1,q2,q3;
    qreal tot=0,c1=0,c2=0,c3=0;
    q1.prepare("SELECT * FROM CONSULTATION");
    q1.exec();
    q2.prepare("SELECT * FROM CONSULTATION WHERE ID_MEDECA='NULL'");
    q2.exec();
    q3.prepare("SELECT * FROM CONSULTATION WHERE ID_MEDECA!='NULL'");
    q3.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    QPieSeries *series = new QPieSeries();
    series->append("utiliser med",c2);
    series->append("utiliser med non",c1);
    series->setHoleSize(0.35);
    QChart *Chart = new QChart();
    Chart ->addSeries(series);
    Chart->setTitle("chart med");

    QChartView *chartview = new QChartView(Chart);
    Chart->setAnimationOptions(QChart::SeriesAnimations);
    chartview->setRenderHint(QPainter::Antialiasing);
     Chart->setBackgroundVisible(true);
    chartview->setMinimumSize(400,400);
    chartview->show();
}



















void MainWindow::on_quit_1_clicked()
{
    this->close();
}

void MainWindow::on_quit_2_clicked()
{
    this->close();
}

void MainWindow::on_quit_3_clicked()
{
    this->close();

}










