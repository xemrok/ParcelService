#include "workspace.h"
#include "ui_workspace.h"
#include "mainwindow.h"

workspace::workspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::workspace)
{
    ui->setupUi(this);
    if(level == 0){
        //Таблица работников
        workers = new QSqlRelationalTableModel;
        workers->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        ui->S1_p1_tableView1->resizeColumnsToContents();
        workers->setEditStrategy(QSqlTableModel::OnManualSubmit);
        workers->setTable("workers");
        workers->setRelation(workers->fieldIndex("departament_number"),QSqlRelation("departament","departament_number","departament_city"));
        workers->select();
        ui->S1_p1_tableView1->setModel(workers);
        workers->setHeaderData(0,Qt::Horizontal,tr("ID"));
        workers->setHeaderData(1,Qt::Horizontal,tr("Логин"));
        workers->setHeaderData(2,Qt::Horizontal,tr("Пароль"));
        workers->setHeaderData(3,Qt::Horizontal,tr("Ф.И.О. работника"));
        workers->setHeaderData(4,Qt::Horizontal,tr("Должность"));
        workers->setHeaderData(5,Qt::Horizontal,tr("Место работы"));
        workers->setHeaderData(6,Qt::Horizontal,tr("Уровень доступа"));
        ui->S1_p1_tableView1->setItemDelegate(new QSqlRelationalDelegate(ui->S1_p1_tableView1));
        ui->S1_p1_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //Таблица отделений
        departament = new QSqlRelationalTableModel;
        departament->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        ui->S1_p2_tableView1->resizeColumnsToContents();
        departament->setEditStrategy(QSqlTableModel::OnManualSubmit);
        departament->setTable("departament");
        departament->select();
        ui->S1_p2_tableView1->setModel(departament);
        departament->setHeaderData(0,Qt::Horizontal,tr("Номер отделения"));
        departament->setHeaderData(1,Qt::Horizontal,tr("Улица"));
        departament->setHeaderData(2,Qt::Horizontal,tr("Город"));
        ui->S1_p2_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //Таблица посылок
        package_data = new QSqlRelationalTableModel;
        ui->S1_p3_tableView1->resizeColumnsToContents();
        package_data->setEditStrategy(QSqlTableModel::OnManualSubmit);
        package_data->setTable("package_data");
        package_data->select();
        ui->S1_p3_tableView1->setModel(package_data);
        package_data->setHeaderData(0,Qt::Horizontal,tr("Номер посылки"));
        package_data->setHeaderData(1,Qt::Horizontal,tr("Дата отправления"));
        package_data->setHeaderData(2,Qt::Horizontal,tr("Ф.И.О. отправителя"));
        package_data->setHeaderData(3,Qt::Horizontal,tr("Адрес отправителя"));
        package_data->setHeaderData(4,Qt::Horizontal,tr("Ф.И.О. получателя"));
        package_data->setHeaderData(5,Qt::Horizontal,tr("Адрес получателя"));
        package_data->setHeaderData(6,Qt::Horizontal,tr("Статус"));
        package_data->setHeaderData(7,Qt::Horizontal,tr("Дата выдачи"));
        ui->S1_p3_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //Таблица пересылок
        data_transfer = new QSqlRelationalTableModel;
        data_transfer->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        ui->S1_p4_tableView1->resizeColumnsToContents();
        data_transfer->setEditStrategy(QSqlTableModel::OnManualSubmit);
        data_transfer->setTable("data_transfer");
        data_transfer->setRelation(data_transfer->fieldIndex("departament_number"),QSqlRelation("departament","departament_number","departament_city"));
        data_transfer->select();
        ui->S1_p4_tableView1->setModel(data_transfer);
        data_transfer->setHeaderData(0,Qt::Horizontal,tr("ID"));
        data_transfer->setHeaderData(1,Qt::Horizontal,tr("Отделение в городе"));
        data_transfer->setHeaderData(2,Qt::Horizontal,tr("Номер посылки"));
        data_transfer->setHeaderData(3,Qt::Horizontal,tr("Дата прибытия"));
        data_transfer->setHeaderData(4,Qt::Horizontal,tr("Дата убытия"));
        ui->S1_p4_tableView1->setItemDelegate(new QSqlRelationalDelegate(ui->S1_p4_tableView1));
        ui->S1_p4_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

workspace::~workspace()
{
    delete ui;
    delete workers;
    delete departament;
    delete package_data;
    delete data_transfer;
    delete Search_worker;
    delete Search_user;
}

void workspace::on_stackedWidget_currentChanged(int arg1)
{
    ui->stackedWidget->setCurrentIndex(arg1);
    level=arg1;
}

void workspace::item_departament(int item)
{
    user=item;
}

void workspace::FIO_workers(QString FIO_user)
{
    ui->S1_label_1->setText(QString::number(user));
    ui->S1_label_2->setText(FIO_user);
    ui->S1_label_3->setText(QString::number(user));
    ui->S1_label_4->setText(FIO_user);
    ui->S1_label_5->setText(QString::number(user));
    ui->S1_label_6->setText(FIO_user);
    ui->S1_label_7->setText(QString::number(user));
    ui->S1_label_8->setText(FIO_user);
    ui->S2_label_1->setText(QString::number(user));
    ui->S2_label_2->setText(FIO_user);
}

void workspace::on_S1_p1_Button1_clicked()
{
    QString search = ui->S1_p1_lineEdit1->text();
    if(search == "")
    {
        QMessageBox::information(this,"Поиск","Запрос не введён");
    }
    else
    {
        bool lable =false;
        const int rowCount = workers->rowCount();
        const int columnCount = workers->columnCount();
        for (int i=0; i<rowCount; i++){
            for (int j=0; j<columnCount; j++){
                QModelIndex index = workers->index(i, j);
                QString text = index.data(Qt::DisplayRole).toString();
                if (text == search){
                    ui->S1_p1_tableView1->selectionModel()->select(ui->S1_p1_tableView1->model()->index(i,j), QItemSelectionModel::Select);
                    lable=true;
                }
            }
        }
        if (lable == false){
            QMessageBox::information(this,"Поиск","Указанное значение не найдено");
        }
    }
    ui->S1_p1_lineEdit1->setText("");
}

void workspace::on_S1_p1_Button2_clicked()
{
    workers->submitAll();
}

void workspace::on_S1_p1_Button3_clicked()
{
    workers->revertAll();
}

void workspace::on_S1_p1_Button4_clicked()
{
    workers->insertRow(workers->rowCount());
}

void workspace::on_S1_p1_Button5_clicked()
{
    int selectdRow = ui->S1_p1_tableView1->currentIndex().row();
    if (selectdRow>=0){
        qDebug() << "Строка удалина:" <<  workers->removeRow(selectdRow);
    }
    else{
        qDebug() << "Строка не выбрана";
    }
}

void workspace::on_S1_p2_Button1_clicked()
{
    QString search = ui->S1_p2_lineEdit1->text();
    if(search == "")
    {
        QMessageBox::information(this,"Поиск","Запрос не введён");
    }
    else
    {
        bool lable =false;
        const int rowCount = departament->rowCount();
        const int columnCount = departament->columnCount();
        for (int i=0; i<rowCount; i++){
            for (int j=0; j<columnCount; j++){
                QModelIndex index = departament->index(i, j);
                QString text = index.data(Qt::DisplayRole).toString();
                if (text == search){
                    ui->S1_p2_tableView1->selectionModel()->select(ui->S1_p2_tableView1->model()->index(i,j), QItemSelectionModel::Select);
                    lable=true;
                }
            }
        }
        if (lable == false){
            QMessageBox::information(this,"Поиск","Указанное значение не найдено");
        }
    }
    ui->S1_p2_lineEdit1->setText("");
}

void workspace::on_S1_p2_Button2_clicked()
{
    departament->submitAll();
}

void workspace::on_S1_p2_Button3_clicked()
{
    departament->revertAll();
}

void workspace::on_S1_p2_Button4_clicked()
{
    departament->insertRow(departament->rowCount());
}

void workspace::on_S1_p2_Button5_clicked()
{
    int selectdRow = ui->S1_p2_tableView1->currentIndex().row();
    if (selectdRow>=0){
        qDebug() << "Строка удалина:" <<  departament->removeRow(selectdRow);
    }
    else{
        qDebug() << "Строка не выбрана";
    }
}

void workspace::on_S1_p3_Button1_clicked()
{
    QString search = ui->S1_p3_lineEdit1->text();
    if(search == "")
    {
        QMessageBox::information(this,"Поиск","Запрос не введён");
    }
    else
    {
        bool lable =false;
        const int rowCount = package_data->rowCount();
        const int columnCount = package_data->columnCount();
        for (int i=0; i<rowCount; i++){
            for (int j=0; j<columnCount; j++){
                QModelIndex index = package_data->index(i, j);
                QString text = index.data(Qt::DisplayRole).toString();
                if (text == search){
                    ui->S1_p3_tableView1->selectionModel()->select(ui->S1_p3_tableView1->model()->index(i,j), QItemSelectionModel::Select);
                    lable=true;
                }
            }
        }
        if (lable == false){
            QMessageBox::information(this,"Поиск","Указанное значение не найдено");
        }
    }
    ui->S1_p3_lineEdit1->setText("");
}

void workspace::on_S1_p3_Button2_clicked()
{
    package_data->submitAll();
}

void workspace::on_S1_p3_Button3_clicked()
{
    package_data->revertAll();
}

void workspace::on_S1_p3_Button5_clicked()
{
    int selectdRow = ui->S1_p3_tableView1->currentIndex().row();
    if (selectdRow >= 0){
        qDebug() << "Строка удалина:" <<  package_data->removeRow(selectdRow);
    }
    else{
        qDebug() << "Строка не выбрана";
    }
}

void workspace::on_S1_p4_Button1_clicked()
{    
    QString search = ui->S1_p4_lineEdit1->text();
    if(search == "")
    {
        QMessageBox::information(this,"Поиск","Запрос не введён");
    }
    else
    {
        bool lable = false;
        const int rowCount = data_transfer->rowCount();
        const int columnCount = data_transfer->columnCount();
        for (int i=0; i<rowCount; i++){
            for (int j=0; j<columnCount; j++){
                QModelIndex index = data_transfer->index(i, j);
                QString text = index.data(Qt::DisplayRole).toString();
                if (text == search){
                    ui->S1_p4_tableView1->selectionModel()->select(ui->S1_p4_tableView1->model()->index(i,j), QItemSelectionModel::Select);
                    lable=true;
                }
            }
        }
        if (lable == false){
            QMessageBox::information(this,"Поиск","Указанное значение не найдено");
        }
    }
    ui->S1_p4_lineEdit1->setText("");
}

void workspace::on_S1_p4_Button2_clicked()
{
    data_transfer->submitAll();
}

void workspace::on_S1_p4_Button3_clicked()
{
    data_transfer->revertAll();
}

void workspace::on_S1_p4_Button4_clicked()
{
    data_transfer->insertRow(data_transfer->rowCount());
}

void workspace::on_S1_p4_Button5_clicked()
{
    int selectdRow = ui->S1_p4_tableView1->currentIndex().row();
    if (selectdRow>=0){
        qDebug() << "Строка удалина:" <<  data_transfer->removeRow(selectdRow);
    }
    else{
        qDebug() << "Строка не выбрана";
    }
}

void workspace::on_S2_p1_Button1_clicked()
{
    QString FIO_sender = ui->S2_p1_lineEdit1->text();
    QString address_sender = ui->S2_p1_lineEdit2->text();
    QString FIO_recipient = ui->S2_p1_lineEdit3->text();
    QString address_recipient = ui->S2_p1_lineEdit4->text();
    if(FIO_sender == "" || address_sender == "" || FIO_recipient == "" || address_recipient == "")
    {
        QMessageBox::warning(this,"Ошибка","Не заполнено поле");
    }
    else
    {
        QDate dateToday= QDate::currentDate();
        QString date=dateToday.toString("yy/MM/dd");
        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES(:date,:FIO_sender,:address_sender,:FIO_recipient,:address_recipient)");
        query.bindValue(":FIO_sender", FIO_sender);
        query.bindValue(":address_sender", address_sender);
        query.bindValue(":FIO_recipient", FIO_recipient);
        query.bindValue(":address_recipient", address_recipient);
        query.bindValue(":date", date);
        if(query.exec()){
            QSqlQuery query1 = QSqlQuery(db);
            query1.prepare("SELECT package_number FROM package_data WHERE delivery_date= :date AND FIO_sender= :FIO_sender AND address_sender= :address_sender AND FIO_recipient= :FIO_recipient AND address_recipient= :address_recipient");
            query1.bindValue(":FIO_sender", FIO_sender);
            query1.bindValue(":address_sender", address_sender);
            query1.bindValue(":FIO_recipient", FIO_recipient);
            query1.bindValue(":address_recipient", address_recipient);
            query1.bindValue(":date", date);
            query1.exec();
            query1.last();
            int result = query1.value(0).toInt();
            QMessageBox::information(this,"Успешно",QString("Посылка успешно внесена\nНомер посылки: %1").arg(result));
        }
        else{
            QMessageBox::warning(this,"Ошибка","Что-то пошло не так!");
        }
    }
}

void workspace::on_S2_p2_Button1_clicked()
{
    Search_worker = new QSqlQueryModel;
    QString number = ui->S2_p2_lineEdit1->text();
    if(number == "")
    {
        QMessageBox::information(this,"Сообщение","Пустое поле");
    }
    else
    {
        query_worker = new QSqlQuery(db);
        query_worker->prepare("SELECT * FROM package_data WHERE package_number= :number OR FIO_sender= :number OR FIO_recipient= :number");
        query_worker->bindValue(":number", number);
        query_worker->exec();
        Search_worker->setQuery(*query_worker);
        ui->S2_p2_tableView1->setModel(Search_worker);
        ui->S2_p2_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        Search_worker->setHeaderData(0,Qt::Horizontal,tr("№ посылки"));
        Search_worker->setHeaderData(1,Qt::Horizontal,tr("Дата отправки"));
        Search_worker->setHeaderData(2,Qt::Horizontal,tr("Ф.И.О. отправителя"));
        Search_worker->setHeaderData(3,Qt::Horizontal,tr("Адрес отправителя"));
        Search_worker->setHeaderData(4,Qt::Horizontal,tr("Ф.И.О. получателя"));
        Search_worker->setHeaderData(5,Qt::Horizontal,tr("Адрес получателя"));
        Search_worker->setHeaderData(6,Qt::Horizontal,tr("Статус"));
        Search_worker->setHeaderData(7,Qt::Horizontal,tr("Дата выдачи"));
        ui->S2_p2_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    ui->S2_p2_lineEdit1->setText("");
}

void workspace::on_S3_p1_Button1_clicked()
{
    Search_user = new QSqlQueryModel;
    int number = ui->S3_p1_lineEdit1->text().toInt();
    if (number != 0)
    {
        query_user = new QSqlQuery(db);
        query_user->prepare("SELECT package_number,delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient FROM package_data WHERE package_number= :number");
        query_user->bindValue(":number", number);
        query_user->exec();
        Search_user->setQuery(*query_user);
        ui->S3_p1_tableView1->setModel(Search_user);
        ui->S3_p1_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        Search_user->setHeaderData(0,Qt::Horizontal,tr("№ отправления"));
        Search_user->setHeaderData(1,Qt::Horizontal,tr("Дата отправки"));
        Search_user->setHeaderData(2,Qt::Horizontal,tr("Ф.И.О. отправителя"));
        Search_user->setHeaderData(3,Qt::Horizontal,tr("Адрес отправителя"));
        Search_user->setHeaderData(4,Qt::Horizontal,tr("Ф.И.О. получателя"));
        Search_user->setHeaderData(5,Qt::Horizontal,tr("Адрес получателя"));
        Search_user->setHeaderData(6,Qt::Horizontal,tr("Состояние"));
        ui->S3_p1_tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSqlQuery query_user1 = QSqlQuery(db);
        query_user1.prepare("SELECT departament_number FROM data_transfer WHERE package_number= :number");
        query_user1.bindValue(":number", number);
        query_user1.exec();
        query_user1.last();
        QString result = query_user1.value(0).toString();
        ui->label->setText(result);
        QSqlQuery query_user2 =  QSqlQuery(db);
        query_user2.prepare("SELECT concat('город ',departament_city,', улица ',departament_street) FROM departament WHERE departament_number= :result");
        query_user2.bindValue(":result", result);
        query_user2.exec();
        query_user2.next();
        QString city = query_user2.value(0).toString();
        if (city == "")
        {
            QMessageBox::information(this,"Ошибка","Указанное значение не найдено");
        }
        else
        {
            ui->label->setText(city);
        }
    }
    else
    {
        QMessageBox::information(this,"Ошибка","Запрос не введён");
    }
    ui->S3_p1_lineEdit1->setText("");
}


void workspace::on_S2_p3_Button1_clicked()
{
    int number = ui->S2_p3_lineEdit1->text().toInt();
    if (number != 0)
    {
        QDate dateToday= QDate::currentDate();
        QString date=dateToday.toString("yy/MM/dd");
        QSqlQuery query1= QSqlQuery(db);
        query1.prepare("SELECT id FROM data_transfer WHERE departament_number= :departament AND package_number= :number");
        query1.bindValue(":number", number);
        query1.bindValue(":departament", user);
        query1.exec();
        query1.next();
        int result = query1.value(0).toInt();
        if (result > 0)
        {
            QMessageBox::warning(this,"Ошибка","Прибытие посылки уже было отмечено");
        }
        else
        {
            QSqlQuery query= QSqlQuery(db);
            query.prepare("INSERT INTO data_transfer (departament_number,package_number,time_in) VALUES(:user,:number,:date)");
            query.bindValue(":number", number);
            query.bindValue(":user", user);
            query.bindValue(":date", date);
            if (query.exec()){
                QMessageBox::information(this,"Успешно","Посылка внесена");
            }
            else{
                QMessageBox::warning(this,"Ошибка","Что-то пошло не так!");
            }
        }
    }
    else
    {
        QMessageBox::information(this,"Ошибка","Некорректное значение");
    }
    ui->S2_p3_lineEdit1->setText("");
}

void workspace::on_S2_p3_Button2_clicked()
{
    int number = ui->S2_p3_lineEdit2->text().toInt();
    if (number != 0)
    {
        QDate dateToday= QDate::currentDate();
        QString date=dateToday.toString("yy/MM/dd");
        QSqlQuery query1= QSqlQuery(db);
        query1.prepare("SELECT id FROM data_transfer WHERE departament_number= :departament AND package_number= :number AND time_out<>0");
        query1.bindValue(":number", number);
        query1.bindValue(":departament", user);
        query1.exec();
        query1.next();
        int result = query1.value(0).toInt();
        if (result >0)
        {
            QMessageBox::warning(this,"Ошибка","Убытие посылки уже было отмечено");
        }
        else
        {
            QSqlQuery query= QSqlQuery(db);
            query.prepare("UPDATE data_transfer SET time_out= :date WHERE package_number= :number AND time_out IS NULL");
            query.bindValue(":number", number);
            query.bindValue(":date", date);
            if (query.exec()){
                QMessageBox::information(this,"Успешно","Посылка внесена");
            }
            else{
                QMessageBox::warning(this,"Ошибка","Что-то пошло не так!");
            }
        }
    }
    else
    {
        QMessageBox::information(this,"Ошибка","Некорректное значение");
    }
    ui->S2_p3_lineEdit2->setText("");
}

void workspace::on_S2_p2_Button2_clicked()
{
    QString number = ui->S2_p2_lineEdit2->text();
    if(number == "")
    {
        QMessageBox::information(this,"Сообщение","Пустое поле");
    }
    else
    {
        QDate dateToday= QDate::currentDate();
        QString date=dateToday.toString("yy/MM/dd");
        QSqlQuery query_er= QSqlQuery(db);
        query_er.prepare("SELECT package_number FROM package_data where  package_number= :number AND status_package= 'Выдано';");
        query_er.bindValue(":number", number);
        query_er.exec();
        query_er.next();
        int result = query_er.value(0).toInt();
        if (result != 0)
        {
            QMessageBox::information(this,"Сообщение","Данная посылка уже выдана!");
        }
        else
        {
            QSqlQuery query_delivery= QSqlQuery(db);
            QString delivery = "Выдано";
            query_delivery.prepare("UPDATE package_data SET status_package= 'Выдано' WHERE package_number= :number; UPDATE package_data SET data_delivery= :date WHERE package_number= :number; UPDATE data_transfer SET time_out= :date WHERE package_number= :number AND time_out IS NULL ");
            query_delivery.bindValue(":number", number);
            query_delivery.bindValue(":delivery", delivery);
            query_delivery.bindValue(":date", date);
            if (query_delivery.exec())
            {
                QMessageBox::information(this,"Успешно","Посылка выдана");
            }
            else
            {
                QMessageBox::warning(this,"Ошибка","Что-то пошло не так!");
            }
        }
    }
    ui->S2_p2_lineEdit2->setText("");
}


