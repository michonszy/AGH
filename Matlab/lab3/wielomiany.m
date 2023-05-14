clear variables;
close all;
clc;

%p=[1,0,-1] %wielomian x2 + 0x -1
%p=[2,1,-2,-1]

%wyznacz wielomian z punktami zerowymi 0,0,1
dr=[0;0;0;1]
dp=poly(dr) %poly wyznacza wielomian na podstawie punktów zerowych, odwrotność roots
p=polyint(dp)




w=polyval(p,-1) %policz wartość wielomianu p w punkcie -1

w1=polyval(p,-1:0.5:1) %policz wartośc wielomianu w kilku punktach

x=-2:0.1:2
y=polyval(p,x)

x1=linspace(-0.5,1.5,100) %punkty od 1 arg do 2arg, 100 punktów
y=polyval(p,x1)

%miejsca zerowe funkcji czerwonymi x
r=roots(p)


% pętla która sprawdza krotność miejsc zerowych, usuwa powtarzające się wartości
i=1
while length(dr) ~=length(unique(dr))
   if nnz(dr(i)==dr) >1
        indx=find(dr(i)==dr)
        if mod(nnz(dr(i)==dr),2)==1
            dr(indx(2:end)) = []
        else
            dr(indx)=[]
        end
        i=0
   end
   i=i+1
end

subplot(2,1,2)
dp = polyder(p)
dy = polyval(dp,x1)
plot(x1,dy)
hold on

subplot(2,1,1) %podzielenie okna na wyświetlenie kilku wykresów, tutaj podzielenie na dwie wiersze, jedna kolumna, rysuj na pozycji 1 czyli u góry

plot(x1,y,'b','LineWidth',5,'MarkerSize',15) %rysuj wykres, z przykładowymi stylami np r-- to linia czerwona przerywana. 
% gx to zielona z zaznaczonymi x punktami, gx- to punkty i linia

hold on %domyslnie poprzedni wykres jest zastępowany kolejnym, za pomocą hold on wykresy się nachodzą
%dorysowanie miejsc zerowych na wykresie
plot(r,0,'rx','LineWidth',2,'MarkerSize',15)
xlabel('x podpis')
ylabel('y podpis')
title('wykres tytularny: y=2x^3+x^2-2x-1')

grid on %wrzucenie siatki na wykres
hold on
%narysuj wykres pochodnej na dole w tym samym oknie
dr = roots(dp)
plot(dr,polyval(p,dr),'gs','LineWidth',2,'MarkerSize',15)

unique(dr) %zwraca tablice bez powtórzeń




