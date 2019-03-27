% Monitor zasobów -- dokumentacja wstępna
% Robert Wojtaś, Krystian Chachuła
% 27 marca 2019

## Docelowa funkcjonalność aplikacji

Celem projektu jest stworzenie aplikacji służącej do monitorowania procesów działających w systemie. Aplikacja zostanie napisana w architekturze klient-serwer. Oba moduły będą pracowały lokalnie w obrębie jednego komputera i będą uruchamiane odzielnie.  Komunikacja między klientem i serwerem realizowana będzie z wykorzystaniem protokołu TCP, służącego do przyjmowania poleceń od klienta. Założeniem projektu jest stworzenie programu, z którego użytkownik będzie mógł w sposób wygodny oraz wydajny czerpać informacje na temat zużycia zasobów przez poszczególne procesy. 

Główną funkcją programu będzie monitorowanie poziomu zużycia pamięci RAM oraz czasu procesora, a także realizacja żądań użytkownika.

### Zakres realizowanych funkcji
* uruchamianie lub wyłączanie procesu
* dodawanie lub usuwanie procesów z listy obserwowanych
* monitorowanie zasobów procesów obserwowanych 
* zbieranie informacji i statystyk dotyczących procesów
* pilnowanie ograniczeń nałożonych na poszczególne procesy
* resetowanie procesów w przypadku przekroczenia ograniczeń
* informowanie użytkownika o przekroczeniu ograniczeń przez proces

## Architektura aplikacji

![Diagram architektury](diagram.png)

Oprogramowanie będzie składało się z serwera (usługi) i klienta. Poprzez klienta możliwe będzie pobieranie i wyświetlanie informacji o działaniu usługi oraz wydawanie poleceń.

### Serwer (usługa)

Napisany w C++ serwer będzie składał się z kilku modułów. Odpowiedzialność każdego z nich umieszczona jest na diagramie.

### Klient

Klient, napisany w języku Python, będzie stanowił konsolowy interfejs użytkownika do usługi.

## Uruchamianie aplikacji

Aby uruchomić serwer, trzeba będzie uruchomić wiersz poleceń i uruchomić proces serwera. Podanie konfiguracji środowiskowej będzie możliwe poprzez argumenty wykonania lub tekstowy plik konfiguracyjny. Po uruchomieniu, serwer kontynuuje działanie.

Każde uruchomienie klienta z wiersza poleceń będzie miało charakter jednorazowy. Każde polecenie do serwera będzie miało przyporządkowany argument wykonania (podobnie jak *Docker*). Np. `client set-mem-limit proces1 1024M`.
