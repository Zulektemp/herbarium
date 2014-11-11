#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include<QSqlError>
#include <algorithm>
#include <memory>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Herbarium.sqlite3");
    if (!db.open()) {
            qDebug()<<db.lastError().text();
    }
    else{
        qDebug()<<"ok!";
    }

    QSqlQuery query;
    query.exec("DROP TABLE main;");
    query.exec("CREATE TABLE main(department_name char(255),class char(255),number_box int,family char(255),genus char(255),latin_name char(255),rus_name char(255),sinonim_vida char(255),date_collect int,regoin char(255),district char(255),position char(255),mestoobitania char(255),kollektor char(255),who_opredelil char(255),note char(255),data_voda_v_katalog int;");


    QFileDialog dg;
    dg.setFileMode(QFileDialog::ExistingFile);

    QStringList Qs;
    if(dg.exec() != QDialog::Accepted) {
        return;
    }
    Qs  = dg.selectedFiles();
    QString myString = Qs.at(0);

    QFile f(myString);
     qDebug()<<"1";
    if (f.open (QIODevice::ReadOnly)){
        qDebug()<<"2";
        QTextStream ts(&f);

        while(!ts.atEnd()){
            QStringList line = ts.readLine().split('\n');
            QString lineintoword = line.at(0);
            QStringList word = lineintoword.split(",");
            qDebug()<<word;

                QString z = "INSERT INTO main(department_name,class,number_box,family,genus,latin_name,rus_name,sinonim_vida,date_collect,regoin,district,position,mestoobitania,kollektor,who_opredelil,note,data_voda_v_katalog)"
                        "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17');";
                QString x;
                x = z.arg(word.at(0))
                        .arg(word.at(1))
                        .arg(word.at(2))
                        .arg(word.at(3))
                        .arg(word.at(4))
                        .arg(word.at(5))
                        .arg(word.at(6))
                        .arg(word.at(7))
                        .arg(word.at(8))
                        .arg(word.at(9))
                        .arg(word.at(10))
                        .arg(word.at(11))
                        .arg(word.at(12))
                        .arg(word.at(13))
                        .arg(word.at(14))
                        .arg(word.at(15))
                        .arg(word.at(16));
            }

        }

f.close ();
fillTableView();
}


void MainWindow::fillTableView()
{
ui->tableView->clearSpans();
m_csvModel = new QSqlTableModel(this);
m_csvModel->setTable("main");
m_csvModel->select();
ui->tableView->setModel(m_csvModel);
}



MainWindow::~MainWindow()
  {
   delete ui;
  }
