---
title: Monitor zasobów (RESMOND) -- dokumentacja końcowa
author: Krystian Chachuła, Robert Wojtaś
date: 27 marca 2019
lang: pl-PL
geometry:
    - margin=1in
---

# Dokumentacja użytkownika
## Przedstawienie aplikacji Resmond
Resmond (ang. **Res**ource **Mon**itor **D**eamon) jest oprogramowaniem służącym do monitorowania 
procesów działających w systemie. Program rejestruje wartości zasobów zużywanych przez procesy i 
informuje o nich dedykowanych użytkowników. Aplikacja została napisana w architekturze klient-serwer. 
Oba moduły pracują lokalnie w obrębie jednego komputera. Komunikacja między klientem i 
serwerem realizowana jest z wykorzystaniem protokołu TCP, służącego do przyjmowania poleceń od 
klienta. 

## Przygotowanie do pracy z programem
### Wymagania systemowe
Przed pobraniem programu należy zainstalować oprogramowanie kluczowe do jego uruchomienia. W skład 
wspomnianego oprogramowania wchodzą:

* ```CMake (wersja przynajmniej 3.10)```
* ```boost (wersja przynajmniej 1.56.0)```

### Pobranie aplikacji z repozytorium Git
W celu rozpoczęcia pobrania monitora zasobów na swój komputer należy uruchomić terminal i w określonym 
 przez nas katalogu docelowym wykonać poniższe komendy:

```bash
git clone --recurse-submodules  https://github.com/wojtasRobert/ZPR-19L.git
```

### Budowanie plików
Następnie należy zbudować pliki w utworzonym ręcznie katalogu ```build```:

```
cd ZPR-19L/
mkdir build
cd build
cmake ..
make
```

## Praca z programem
### Uruchamianie
Po wykonaniu komend z poprzedniej sekcji i prawidłowej konfiguracji, możemy uruchomić poszczególne elementy programu: monitor
 zasobów, testy, pokrycie kodu testami:

```bash
   # Deamon
   ./resmond
```

```bash
   # Test
   ./test_executable
```

```bash
   # Coverage
   make ctest_coverage
```


