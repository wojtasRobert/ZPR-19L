% Monitor zasobów -- dokumentacja wstępna
% Robert Wojtaś, Krystian Chachuła
% 27 marca 2019

## Docelowa funkcjonalność aplikacji

Celem projektu jest stworzenie aplikacji służącej do monitorowania procesów działających w systemie. Aplikacja zostanie napisana w architekturze klient-serwer. Oba moduły będą pracowały lokalnie w obrębie jednego komputera i będą uruchamiane odzielnie.  Komunikacja między klientem i serwerem realizowana będzie z wykorzystaniem udostępnianego przez usługę gniazda sieci TCP, służącego do przyjmowania poleceń od klienta. Założeniem projektu jest stworzenie programu, z którego użytkownik będzie mógł w sposób wygodny oraz wydajny czerpać informacje na temat zużycia zasobów przez poszczególne procesy. 

Główną funkcją programu będzie monitorowanie poziomu zużycia pamięci RAM oraz czasu procesora, a także realizacja żądań użytkownika.

*, który będzie miał możliwość dodania i usunięcia procesów do obserwowanych, narzucenia ograniczeń na zasoby wykorzystywane przez procesy oraz wyświetlania informacji na temat obserwowanych procesow. Ważnym elementem monitora zasobów będzie funkcja zawiadamiania użytkownika o naruszeniu ograniczeń przez procesy. W założeniu, taka sytuacja skutkować będzie wysłaniem wiadomości e-mail na adres użytkownika.*

### Zakres realizowanych funkcji
* uruchamianie lub wyłączanie procesu
* dodawanie lub usuwanie procesów z listy obserwowanych
* monitorowanie zasobów procesów obserwowanych 
* zbieranie informacji i statystyk dotyczących procesów
* pilnowanie ograniczeń nałożonych na poszczególne procesy
* resetowanie procesów w przypadku przekroczenia ograniczeń
* informowanie użytkownika o przekroczeniu ograniczeń przez proces

## Opis architektury

![Diagram architektury](diagram.png)

Oprogramowanie będzie składało się z serwera (usługi) i klienta. Poprzez klienta możliwe będzie pobieranie i wyświetlanie informacji o działaniu usługi oraz wydawanie poleceń.

### Serwer (usługa)

Napisany w C++ serwer będzie składał się z kilku modułów. Odpowiedzialność każdego z nich umieszczona jest na diagramie.

### Klient

Klient, napisany w języku Python, będzie stanowił konsolowy interfejs użytkownika do usługi.

### Klient

### Usługa

#### Moduł akwizycji danych

 TODO: to są różne pomysły, należy coś wybrać
 
 
##### Linux

* `ps -p $PID -o %cpu,%mem,cmd`
* https://stackoverflow.com/a/64166



# TODO
* opis architektury
  * serwer
    * moduł akwizycji danych
    * moduł kom z klientem
    * moduł zarządzania procesami
    * moduł wysyłania maili
    * moduł zarządzania konfiguracją (wczytywanie z pliku?)
    * moduł sprawdzania ograniczeń
* diagram: klient, serwer, procesy, lista procesów i jakie informacje są wymieniane
* fork czy podpinanie procesu
* serwer uruchamiany oddzielnie i klient oddzielnie
