## Wymagania
- python3
- python3-dev
- cmake
- kompilator c++

## Uruchamianie
```bash
cmake .
cmake --build .
./my_program
```
Wszystkie wymagane zaleności pythonowe zainstalują się automatycznie. 

## Uwaga
Program działa na globalnej wersji Pythona - niestety cmake nie wykrywa wirtualnych środowisk pythonowych (a przynajmniej nie udało mi się go pod to skonfigurować) 
```