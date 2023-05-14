%średniki są opcjonalne
clear variables; %usuwa wszystkie poprzednio zadeklarowane zmienne
close all; %zamyka wykresy
clc; %clear command window

n=input('Podaj liczbe: ');
display(n); %analogicznie disp(n)

%generowanie wektorów
%1:2:10 -> generuje wektor od 1, z krokiem 2, do 10 wynik=[1,3,5,7,9]
czyJestPierwsza=true;
for i=2:n-1
    if mod(n,i)==0
        czyJestPierwsza=false;
        break
    end
end

%ans zmienna o wartości ostatniej operacji która nie została przypisana,
%generowana automatycznie

if czyJestPierwsza
    disp("Liczba jest pierwsza");
else
    disp("Nie jest pierwsza");
end

%cały ten program sprawdzania czy liczba jest pierwsza obsługuje wbudowana
%funkcja isprime(x)