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
./resmond

# Coverage
make ctest_coverage
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
