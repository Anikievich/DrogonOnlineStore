# DrogonOnlineStore
<h3 align="left">Инструменты:</h3>
<p align="left">

- <p><a href="#dbTable">Таблицы в базе данных</a></p>
- <p><a href="#structure">Структура проекта</a></p>
  
## Таблицы в базе данных
  <a id="dbTable"></a>
База данных содержит следующие сущности

```
-user
-cart
-cart_device
-device
-device_info
-type
-brand
-type_brand
-rating
```
## Структура проекта

<a id="structure"></a>
```
--/middleware
--/controllers
--/database
--/decorators
--/entities
--/errors
--/external
--/filters
--/sql
--/utils
/config.json
```
### `--/middlewares`
В данной папке хранятся миддлваер `ErrorHandlingMiddeware`, принимающий `ApiError`.
### `--/controllers`
Контроллеры обрабатывают запрос, отправленный браузером, а затем генерирует ответ. Каждый контроллер содержит CRUD для своей каждой сущности таблицы.

- `cartCotroller` - Корзина пользователя 
- `deviceInfoCotroller` - Информация об устройстве
- `ratingCotroller` - Рейтинг устройства
- `brandCotroller` - Бренды устройств
- `deviceCotroller` - Устройства
- `typeCotroller` - Типы устройств
- `userCotroller` - Пользователь
### `--/database`
Содержит обработчик запросов к базе данных PostgreSQl `DataBaseHelper`.
### `--/decorators`
Декораторы для запроса PUT к `device`, `deviceInfo`, `user`.
### `--/entities`
В папке находися DTO для создания RESTful интерфейсов к всем сущностям. 
### `--/errors`
Обрабатывание ошибок осуществляется через класс `ApiError`. На данный момент можно существует обработка ошибок `unauthorised`, `badRequest`, `forbidden`, `internal`.
### `--/external`
Внешние библиотеки для хэширования пароля `libbcrypt` и работы с JWT токеном `jwt-cpp`.
### `--/filters`
Фильтры для проверки ауторизации `authFilter` и роли пользователя `adminRoleFilter`.  
### `--/sql`
Содержит `Data` файл для миграции таблиц.
### `--/utils`
В данной папке содержится класс `jwtService`, обеспечивающий работу с JWT токенами. 
### `/config.json`
Файл кофигурации.
