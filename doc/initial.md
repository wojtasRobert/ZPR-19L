# Monitor zasobów

## Usługa

* udostępnia w sieci gniazdo TCP, służące do przyjmowania poleceń od klienta
* monitorowanie %MEM oraz %CPU

### Akwizycja danych

TODO: to są różne pomysły, należy coś wybrać

#### Linux

* `ps -p $PID -o %cpu,%mem,cmd`
* https://stackoverflow.com/a/64166

## Klient

Funkcje klienta, służące do kontrolowania usługi:

* dodaj proces do obserwowanych
* usuń proces z obserwowanych
* pokaż informacje na temat obserwowanego procesu
* ustaw/zmień ograniczenia wykorzystania zasobów przez obserwowany proces
