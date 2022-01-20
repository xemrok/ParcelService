#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QMessageBox>
#include <QDate>

namespace Ui {
class workspace;
}

class workspace : public QWidget
{
    Q_OBJECT

public:
    explicit workspace(QWidget *parent = nullptr);
    void on_stackedWidget_currentChanged(int arg1);
    void item_departament(int item);
    void FIO_workers(QString FIO_user);
    QSqlDatabase db;
    QSqlRelationalTableModel *workers;
    QSqlRelationalTableModel *departament;
    QSqlRelationalTableModel *package_data;
    QSqlRelationalTableModel *data_transfer;
    QSqlQueryModel *Search_worker;
    QSqlQueryModel *Search_user;
    QSqlQuery *query_worker;
    QSqlQuery *query_user;
    QSqlQuery *query_user1;
    QSqlQuery *query_user2;
    ~workspace();

private slots:
    void on_S1_p1_Button1_clicked();
    void on_S1_p1_Button2_clicked();
    void on_S1_p1_Button3_clicked();
    void on_S1_p1_Button4_clicked();
    void on_S1_p1_Button5_clicked();
    void on_S1_p2_Button1_clicked();
    void on_S1_p2_Button2_clicked();
    void on_S1_p2_Button3_clicked();
    void on_S1_p2_Button4_clicked();
    void on_S1_p2_Button5_clicked();
    void on_S1_p3_Button1_clicked();
    void on_S1_p3_Button2_clicked();
    void on_S1_p3_Button3_clicked();
    void on_S1_p3_Button5_clicked();
    void on_S1_p4_Button1_clicked();
    void on_S1_p4_Button2_clicked();
    void on_S1_p4_Button3_clicked();
    void on_S1_p4_Button4_clicked();
    void on_S1_p4_Button5_clicked();
    void on_S2_p1_Button1_clicked();
    void on_S2_p2_Button1_clicked();
    void on_S3_p1_Button1_clicked();
    void on_S2_p3_Button1_clicked();
    void on_S2_p3_Button2_clicked();
    void on_S2_p2_Button2_clicked();

private:
    Ui::workspace *ui;
    int level=0;
    int user=0;
};

#endif // WORKSPACE_H
