clear variables; %usuwa wszystkie poprzednio zadeklarowane zmienne
close all; %zamyka wykresy
clc; %clear command window

n=input('Podaj liczbe: ');
display(n);

for i=2:n
    if mod(n,i)==0
        disp("Dzielnik "+i)
    end
end
