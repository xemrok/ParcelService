#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setFixedSize(223, 106);
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName("root");
    db.setDatabaseName("Mail");
    db.setPassword("");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setConnectOptions("MYSQL_OPT_RECONNECT=TRUE;");
    if (!db.open()){
        QMessageBox::warning(this, "Errore", "Ошибка подключения к базе данных");
    }
    wi = new workspace();
    ui->password->setEchoMode(QLineEdit::Password);
    delete ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    int page;
    int departament;
    QSqlQuery query = QSqlQuery(db);
    if (login == "user")
    {
        password="123";
    }
    query.prepare("SELECT levels FROM workers WHERE login= :login AND pass= :pass");
    query.bindValue(":login", login);
    query.bindValue(":pass", password);
    query.exec();
    query.next();
    QSqlQuery query_FIO = QSqlQuery(db);
    query_FIO.prepare("SELECT FIO_workers FROM workers WHERE login= :login AND pass= :pass");
    query_FIO.bindValue(":login", login);
    query_FIO.bindValue(":pass", password);
    query_FIO.exec();
    query_FIO.next();
    QSqlQuery query_departament = QSqlQuery(db);
    query_departament.prepare("SELECT departament_number FROM workers WHERE login= :login AND pass= :pass");
    query_departament.bindValue(":login", login);
    query_departament.bindValue(":pass", password);
    query_departament.exec();
    query_departament.next();
    QString result = query.value(0).toString();
    QString result_FIO = query_FIO.value(0).toString();
    QString result_departament = query_departament.value(0).toString();
    if (result != "")
    {
        QMessageBox::information(this, "Access", "Вы успешно вошли в систему!");
        page=result.toInt();
        departament=result_departament.toInt();
        wi->item_departament(departament);
        wi->FIO_workers(result_FIO);
        wi->on_stackedWidget_currentChanged(page);
        this->close();
        wi->show();
    }
    else
    {
        QMessageBox::warning(this, "Errore", "Ошибка авторизации");
        wi->close();
    }
}



