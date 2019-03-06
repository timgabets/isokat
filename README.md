## ISOClient

ISOClient преобразует полученные http-запросы в финансовые сообщения в формате [ISO8583](https://en.wikipedia.org/wiki/ISO_8583), специфичные для различных платёжных систем (VISA, Mastercard, МИР). Основное предназначение - тестирование авторизационных систем банков-эмитентов.

                       +------------------+                    +--------------------+
                       |                  | <--  ISO 8583  --> |    Issuer Bank     |
HTTP client <--JSON--> |    IsoClient     | <--VISA SMS/DMS--> |   Authorization    |  
                       |                  | <-- Mastercard --> |        Host        |  
                       +------------------+                    +--------------------+

### Используемые библиотеки
* meson
* libconfig
* [kcgi](https://kristaps.bsd.lv/kcgi/)
* [libuv](http://libuv.org/)