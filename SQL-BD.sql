CREATE DATABASE Mail;
USE Mail;
CREATE TABLE workers (id INTEGER auto_increment PRIMARY KEY NOT NULL,
	login VARCHAR(30) UNIQUE NOT NULL,
	pass VARCHAR(30) NOT NULL,
	FIO_workers VARCHAR(30) NOT NULL,
	positions VARCHAR(30) NOT NULL,
	departament_number INTEGER NOT NULL,
	levels INTEGER, CONSTRAINT access CHECK(levels>0 AND levels<=2));

CREATE TABLE departament (departament_number INTEGER auto_increment PRIMARY KEY NOT NULL,
	departament_street VARCHAR(30),
	departament_city VARCHAR(30));

CREATE TABLE data_transfer (id INTEGER auto_increment PRIMARY KEY NOT NULL,
	departament_number INTEGER, 
	package_number INTEGER,
	time_in DATE,CONSTRAINT TIME_in CHECK (time_in<=NOW()),
	time_out DATE,CONSTRAINT TIME_out CHECK (time_out<=NOW()));

CREATE TABLE package_data (package_number INTEGER auto_increment PRIMARY KEY NOT NULL,
	delivery_date DATE, CONSTRAINT Date_of_shipment CHECK (delivery_date<=NOW()),
	FIO_sender VARCHAR(30),
	address_sender VARCHAR(100), 
	FIO_recipient VARCHAR(30),
	address_recipient VARCHAR(100),
	status_package VARCHAR(10) NOT NULL DEFAULT 'Не вручена', CONSTRAINT stat CHECK(status_package ='Не вручена'OR status_package = 'Выдано'),
	data_delivery DATE, CONSTRAINT Date_of_issue CHECK (data_delivery<=NOW() OR data_delivery IS NULL));
	
ALTER TABLE workers ADD FOREIGN KEY (departament_number) REFERENCES departament (departament_number);
ALTER TABLE data_transfer ADD FOREIGN KEY (package_number) REFERENCES package_data (package_number);
ALTER TABLE data_transfer ADD FOREIGN KEY (departament_number) REFERENCES departament (departament_number);

INSERT INTO departament (departament_street,departament_city) VALUES('Подбельского 2','Владимир');
INSERT INTO departament (departament_street,departament_city) VALUES('Куйбышева 57','Нижний Новгород');
INSERT INTO departament (departament_street,departament_city) VALUES('Кирова 58','Пенза');
INSERT INTO departament (departament_street,departament_city) VALUES('Московская 109','Саратов');
INSERT INTO departament (departament_street,departament_city) VALUES('Ленина 20','Москва');

INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('admin','123','Жданов В.Ю.','Администратор',1,0);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker1','123','Бореев К.К.','Менеджер',1,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker2','123','Стариков Г.Е.','Менеджер',1,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker3','123','Цицианова А.В.','Менеджер',1,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker4','123','Густокашина И.П','Менеджер',2,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker5','123','Немова А.Е.','Менеджер',2,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker6','123','Лачкова В.Г.','Менеджер',2,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker7','123','Голубкина М.А','Менеджер',3,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker8','123','Катькин Р.А.','Менеджер',3,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker9','123','Косинова Э.С.','Менеджер',3,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker10','123','Чернецкая Е.В.','Менеджер',4,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker11','123','Берков К.Е.','Менеджер',4,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker12','123','Дёмина И.А','Менеджер',4,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker13','123','Иванов А.Н.','Менеджер',5,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker14','123','Агафонов А.Н.','Менеджер',5,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('worker15','123','Пастух П.М.','Менеджер',5,1);
INSERT INTO workers (login,pass,FIO_workers,positions,departament_number,levels) VALUES('user','123','Пользователь','Клиент',1,2);

INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2018.04.18','Волкова К.С.','г. Саратов ул. Разина д. 36','Гагарин Я.П.','г. Пенза ул. Плеханова д.15');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2017.01.29','Карадапольцев В.И.','г. Владимир ул. Бебеля д. 94','Михальченко Л.М.','г. Москва ул. Баррикадная д. 3');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2017.12.21','Щедров С.Е.','г. Нижний Новгород ул. Автомоторная д. 15','Лазуткина Л.А.','г. Саратов ул. ул. Барвихинская д. 22');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2018.04.15','Сарайкин С.А.','г. Пенза ул. Завокзальная д. 4','Касыгин О.Е.','г. Владимир ул. Заречная д. 44');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2017.12.31','Кочергов Т.Е.','г. Саратов ул. Садовая д. 37','Головченко А.П.','г. Владимир ул. Авиамоторная д. 14');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2018.07.07','Бугайчук И.П.','г. Нижний Новогород ул. Бауманская д. 2','Юдин А.Н.','г. Москва ул. Голландская д. 11');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2018.08.05','Гринина З.В.','г. Саратов ул. Бахрушина д. 5','Волков Ф.Н.','г. Москва ул. Глинки д. 24');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2017.09.03','Диденкова Р.Е.','г. Москва ул. Авиаторов д. 5','Пушкарёва Д.С.','г. Пенза ул. Ленина д. 7');
INSERT INTO package_data (delivery_date,FIO_sender,address_sender,FIO_recipient,address_recipient) VALUES
('2017.03.16','Еремеева И.С.','г. Пенза ул. Барболина д. 28','Шалупова Н.К.','г. Нижний Новгород ул. Достоевского д. 29');

INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(5,1,'2018.09.30','2018.10.01');
INSERT INTO data_transfer (departament_number,package_number,time_in) VALUES(4,1,'2018.10.02');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(2,2,'2017.01.29','2017.01.30');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(1,2,'2017.01.31','2017.02.03');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,3,'2017.12.21','2017.12.22');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(4,3,'2017.12.23','2017.12.25');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(5,3,'2017.12.26','2017.12.28');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(4,4,'2018.04.15','2018.04.16');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,4,'2018.04.17','2018.04.20');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(2,4,'2018.04.21','2018.04.25');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(5,5,'2017.12.31','2018.01.07');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(4,5,'2018.01.08','2018.01.10');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,5,'2018.01.11','2018.01.13');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(2,5,'2018.01.14','2018.01.23');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,6,'2018.07.07','2018.07.08');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(2,6,'2018.07.09','2018.07.13');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(1,6,'2018.07.14','2018.07.20');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(5,7,'2018.08.05','2018.08.06');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(4,7,'2018.08.07','2018.08.10');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,7,'2018.08.11','2018.08.17');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(2,7,'2018.08.18','2018.08.19');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(1,7,'2018.08.20','2018.08.25');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(1,8,'2017.09.03','2017.09.04');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(2,8,'2017.09.05','2017.09.10');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,8,'2017.09.11','2017.09.15');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(4,9,'2017.03.16','2017.03.17');
INSERT INTO data_transfer (departament_number,package_number,time_in,time_out) VALUES(3,9,'2017.03.18','2017.03.23');

/*CREATE TRIGGER `Del_package`
BEFORE DELETE ON `package_data`
FOR EACH ROW
DELETE FROM data_transfer WHERE OLD.package_number = package_number

CREATE TRIGGER `Del_departament1` 
BEFORE DELETE ON `departament` 
FOR EACH ROW 
DELETE FROM workers WHERE OLD.departament_number = departament_number

CREATE TRIGGER `Del_departament2` 
BEFORE DELETE ON `departament` 
FOR EACH ROW 
DELETE FROM data_transfer WHERE OLD.departament_number = departament_number*/


