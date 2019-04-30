## Informacje
* prowadzący: mgr inż. Konrad Grochowski, k.grochowski@ii.pw.edu.pl
* konsultacje: piątek 14:15 - 16:00, pok. 314
* termin oddania dokumentacji wstępnej: 1 kwietnia (5 pkt)
* termin oddania szkieletu aplikacji: 1 maja (5 pkt)
* dostarczenie implementacji i dokumentacji końcowej: 7 czerwca (40 pkt)
* punktacja 50 pkt
* przekroczenie terminów skutkuje zmniejszeniem maksymalnej puli punktów 
do 80% przy dowolnym opóźnieniu, nawet jednego dnia

## Treść zadania
Celem projektu jest stworzenie oprogramowania do monitorowania działania 
innych części systemu / innego oprogramowania i informowania o tym 
dedykowanych użytkowników. Na przykład: wysłanie maila gdy zużycie 
procesora przekroczy jakiś próg.

Serwer powinien być zaimplementowany w C++ i działać zarówno na systemie 
Linux jak i Windows.

Monitorowanie zasobów może dotyczyć całego systemu, albo np. pojedynczej 
aplikacji - wtedy program działał by w trybie "watchdog'a" i np. 
restartował obserwowaną aplikację, gdy jakieś jej parametry przekroczą 
zadane wartości.

Progi notyfikacji powinny być konfigurowalne - im mniej obserwowanych 
parametrów tym bardziej skomplikowane warunki powinny być wspierane.

Notyfikacje mogą być zrealizowane dowolnie - od wysyłania maila, przez 
dodanie wpisu na blogu, po wysyłanie SMS.

## Zasady oceniania projektów
* **Dokumentacja wstępna** - Należy opisać docelową funkcjonalność 
oprogramowania. Zakres realizowanych funkcji warto opisać biorąc pod 
uwagę faktyczne możliwości ich realizacji. Stopień realizacji jest brany 
pod uwagę przy ocenie końcowej wersji aplikacji lub biblioteki
* **Szkielet aplikacji** - Należy zadbać, aby szkielet zawierał istotne 
dla projektu biblioteki i narzędzia, kompilował się i uruchamiał na 
różnych środowiskach, zawierał skrypty do budowania aplikacji (np. 
SCons) oraz przykładowe testy jednostkowe. Kod źródłowy powinien być 
zarządzany przez repozytorium (np Bitbucket).
* **Dokumentacja końcowa i gotowy projekt**
	- czy program można poprawnie skompilować i uruchomić (warunek 
konieczny, bez tego kolejne podpunkty nie są sprawdzane)
	- (12p) zrealizowana funkcjonalność z dokumentacji wstępnej (co 
zostało zaimplementowane, a co nie; co sprawiło problemy, jakich 
problemów nie udało się przewidzieć, czy i jak można było się ich 
ustrzec)
	- (15p) jakość kodu, w tym:
		* (5p) poprawne stosowanie języka: struktura programu 
(biblioteki - przestrzenie nazw, moduły, klasy, funkcje, metody), 
przemyślany projekt współpracy pomiędzy obiektami, np. hierarchia klas 
/dziedziczenie/, poprawne użycie szablonów, brak powtórzeń (brak 
copy-paste-programming), brak wycieków pamięci, zakleszczeń i zagłodzeń 
itp.
		* (5p) nietrywialne techniki i rozwiązania 
programistyczne, użycie bibliotek i mechanizmów języka, w kontekście 
omawianym na wykładzie, przykładowo: wzorce projektowe, współbieżność i 
synchronizacja, szablony, STL, boost (np. boost::Python), inne 
biblioteki
		* (5p) czytelność kodu: jednorodny styl kodowania 
(przykładowy styl kodowania), komentarze w kodzie, komentarze do modułów 
(plików), komentarze do klas i metod publicznych, automatycznie 
generowana dokumentacja (np. Doxygen)
	- (5p) testy jednostkowe, badanie jakości testów (np. pokrycie 
kodu testami), automatyzacja testowania
	- (5p) poprawna kompilacja i działanie we wszystkich zadanych 
środowiskach (Linux, g++ oraz Windows, Visual C++)
	- (3p) dokumentacja końcowa zawierająca dokumentację 
użytkownika, liczbę linii kodu, liczbę testów, procentowe pokrycie kodu 
testami, liczbę godzin poświęconą na projekt. Ważnym elementem 
dokumentacji końcowej jest opis napotkanych problemów i popełnionych 
błędów. Krytyczne spojrzenie na własną pracę świadczy o tym, że zespół 
przyswoił sobie nową wiedzę i nie popełni podobnych błędów w 
przyszłości.

## Info z konsultacji

### Wskazówki co do dokumentacji

W dokumentacji mogą znajdować się:

* user stories
* use cases
* wypisanie funkcjonalności

Należy unikać *poetyckich* opisów.

Z dokumentacji powinnien znajdować sie opis architektury bez diagramu klas oraz informacje na temat tego jak będzie uruchamiana aplikacja.

### Wymagania co do projektu Monitor zasobów 2

* brak GUI
* monitor jednego procesu
* usługa + klient do sterowania nią (a'la *docker*), polecenia typu:
    * obserwuj proces
    * przestań obserwować proces
    * ustaw ograniczenia
* logowanie (np. SQLite) **lub** wysyłanie na maila powiadomień o przekroczeniu ograniczeń
* restartowanie procesu kiedy przekroczy ograniczenia
* przy wykorzystaniu sieci, należy odpowiednio reagować na nagły brak połączenia
