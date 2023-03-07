# ParcelService
Parcel management application (Study Project)

## Концепция
Данное приложение предоставляет графический интерфейс для обслуживания и автоматизации работы почтовых отделений в рамках одной компании

## Основные возможности
1) Поддерживается три роли пользователя admin, worker (менеджер), user
2) Admin может просматривать, добавлять, удалять записи и редактировать содержимое уже имеющейся информации в базе данных.
3) Worker может вносить данные о новом отправлении, осуществлять поиск по номеру отправления, регистрировать выдачу отправления
   и отмечать прибытие и убытие отправления из отделения если отделение не является целевым.
4) User может просматривать данные о своём отправлении находя его либо по трек-номеру, либо по адресу отправителя.

## Установка
Для запуска и корректной работы приложения необходимо локально развернуть СУБД MySQL на порту 3306. Пользователь root, пароль ""/пустой (Стандартные настройки MySQL).
После развёртывания СУБД, необходимо выполнить SQL скрипт -> SQL-BD.sql для первоначальной настройки БД.
Для удобства рекомендуется использовать OpenServer.

## Скриншоты
1) Окно входа в систему
<img width="113" alt="Логин" src="https://user-images.githubusercontent.com/98114232/223373900-62c649ff-74af-49c1-9917-5b816d6639e5.png">

2) Панель администратора
<img width="859" alt="Панель админа" src="https://user-images.githubusercontent.com/98114232/223374001-511be038-c5cf-4d3a-b74f-b4eadaa4fe78.png">

3) Пример адаптивного дизайна (Панель администратора)
<img width="1922" alt="Пример адаптивного окна" src="https://user-images.githubusercontent.com/98114232/223374109-b5c1e84f-b26f-4794-bf52-2885368869de.png">

4) Панель менеджера/worker (отправка посылки)
<img width="693" alt="Панель менеджера (отправка посылки)" src="https://user-images.githubusercontent.com/98114232/223374316-bcb99f01-8ebc-486c-bf7f-623b6aa457a4.png">

5) Панель менеджера/worker (перемещение посылки между отделениями)
<img width="694" alt="Панель менеджера (перемещение посылки между отделениями)" src="https://user-images.githubusercontent.com/98114232/223374433-91a1a534-e223-42a6-b3f6-431644b89466.png">

6) Панель менеджера/worker (поиск и выдача посылки)
<img width="693" alt="Панель менеджера (Поиск и выдача посылки)" src="https://user-images.githubusercontent.com/98114232/223374602-cc3f2ba3-1ddf-4b34-ad5f-a7272ca34f97.png">

7) Панель пользователя/user (поиск и проверка статуса отправления)
<img width="694" alt="Панель пользователя (Поиск и проверка статуса посылки)" src="https://user-images.githubusercontent.com/98114232/223374787-04fb0b64-fd6e-469d-8342-28f9945d9c81.png">
