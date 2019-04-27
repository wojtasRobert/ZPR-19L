# Projekt z przedmiotu ZPR, semestr letni 2019

## Kompilacja

### Linux

```bash
git clone --recurse-submodules  https://github.com/wojtasRobert/ZPR-19L.git
cd ZPR-19L/
mkdir build
cd build
cmake ..
make

# Test
./test_executable

# Daemon
./resource_monitor
```

### Windows

Przed przystąpieniem do kompilacji i uruchamiania należy pobrać i zainstalować:

* [Boost 1.69 Binary](https://sourceforge.net/projects/boost/files/boost-binaries/1.69.0/)
* [CMake Binary](https://cmake.org/download/#latest)
* Microsoft Visual Studio Community 2017

1. Pobierz lub sklonuj z opcją `--recurse-submodules` to repozytorium.
    - Jeśli pobrałeś repozytorium (bez `--recurse-submodules`), to pobierz również [Simple-Web-Server](https://gitlab.com/eidheim/Simple-Web-Server) do folderu `vendor/Simple-Web-Server` tak, aby w folderze `vendor/Simple-Web-Server` były foldery `tests`, `web` oraz pliki `CMakeLists.txt`, `server_http.hpp` i inne.
1. Uruchom `cmake-gui`.
1. Wskaż w *Where is the source code* ścieżkę repozytorium. Wskaż folder w którym znajdują się pliki `README.md`, `CMakeLists.txt` oraz folder `vendor` i inne.
1. Stwórz w folderze wskazanym w poprzednim kroku folder build i wskaż go w *Where to build the binaries*.
1. Wciśnij przycisk *Configure*.
1. W *Specify the generator for this project* wybierz generator zgodny z pobranymi bibliotekami Boost. np. *Visual Studio 15 2017 Win64*. **Pamiętaj** o *Win64* jeśli pobrałeś 64-bitową wersję Boost.
1. Wciśnij przycisk *Finish*.
1. Jeśli wystąpił błąd z powodu nieznalezionych bibliotek Boost, dodaj za pomocą przycisku *Add Entry* wpisy `BOOST_ROOT` i/lub `BOOST_LIBRARYDIR` wskazujące na ścieżkę do instalacji Boost.
1. Po pomyśnym zakończeniu konfiguracji (`Configuring done`) wciśnij przycisk *Generate*, a następnie *Open Project*. Projekt powinien otworzyć się w programie Visual Studio.
1. W *Solution Explorer* należy prawym przyciskiem myszy wybrać `test_executable` i kliknąć *Build*.
1. Jeśli wystąpił błąd konsolidacji podobny do `LINK : fatal error LNK1104: cannot open file 'libboost_date_time-vc141-mt-gd-x64-1_69.lib'`, należy w *Solution Explorer* wcisnąć przycisk *Properties* (ikona klucza płaskiego), a następnie w *Linker* -> *Additional Library Directories* dodać na początku ścieżkę do bibliotek w swojej instalacji Boost. W tym folderze powinny znajdować się pliki `libboost_...-1_69.lib`. Cała zawartość pola *Additional Library Directories* powinna wyglądać podobnie do `C:\local\boost_1_69_0\lib64-msvc-14.1;%(AdditionalLibraryDirectories)`.
1. Po wciśnięciu przycisku *Ok* należy spróbować ponownie skompilować target `test_executable`.
1. Po pomyślnej kompilacji należy uruchomić testy wciskając PPM na target `test_executable` i wybierając *Debug* -> *Start new instance*.
1. Jeśli widoczna jest wiadomość *No errors detected* można spróbować uruchomić target `resource_monitor` tym samym sposobem, co target `test_executable`.

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
