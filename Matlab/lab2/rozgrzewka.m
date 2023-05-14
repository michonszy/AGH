clear variables;
clc;

%macierz zawierająca macierz 4x4 z danymi 1-10 randomowymi
A=randi(10,4); %pierwszy argument mówi z jakiego zakresu, druga to wymiar macierzy
display(A);

%tablice indeksowane są od 1 a nie od 0!!
A(2,3) %odwołanie się do elementu macierzy, argumenty (wiersz,kolumna)
A([1,2],4) %odwołanie się do dwóch wierszy, zwraca dwie wartości

% : oznacza odwołanie się do wszystkich elementów
A(2,:)

A(2,2:end-1) %drugi wiersz, kolummy od drugiego do przedostatniego

x=1:2:10 %od:z krokiem: do, czyli od 1 do 10 z krokiem 2 ( 1     3     5     7     9)

s=sum(A) %z każdej kolumny oddzielnie liczy sume

m = max(s)
s==m
A(:,s==m) %przekazujemy pokazanie całej kolumny gdzie znajduje się najwyższa wartość
%jeżeli suma będzie taka sama w dwóch kolumnach to dostaniemy obydwie,
%indeksowanie logiczne

[m,i]=max(s) %funkcja max może zwrócić dwa elementy, wartość maksymalna m oraz i zwracająca położenie, 
% nie ma potrzeby indeksowania logicznego
% jeżeli jednak zdarzą się dwie takie same max wartości to zwróci tylko
% jedną (pierwsze wystąpienie)

A(:,i)


