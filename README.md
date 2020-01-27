## ISOKat

ISOKat преобразует полученные http-запросы в финансовые сообщения в формате [ISO8583](https://en.wikipedia.org/wiki/ISO_8583), специфичные для различных платёжных систем (VISA, Mastercard, МИР). Основное предназначение - тестирование авторизационных систем банков-эмитентов.

                           +-----------------+                    +--------------------+
                           |                 | <--  ISO 8583  --> |    Issuer Bank     |
    HTTP client <--JSON--> |     ISOKat      | <--VISA SMS/DMS--> |   Authorization    |
                           |                 | <-- Mastercard --> |        Host        |
                           +-----------------+                    +--------------------+

### Build
    meson build
    cd build
    ninja

## Testing with curl
> curl --header "Content-Type: application/json" --request GET --data '{"i000":"0100","i002":"4444000011112222"}' localhost:8080


### Используемые библиотеки
* meson
* libconfig
* [criterion](https://github.com/Snaipe/Criterion)
* [zflog](https://github.com/wonder-mice/zf_log)
* [cJSON](https://github.com/DaveGamble/cJSON)
