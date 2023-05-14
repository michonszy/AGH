clear variables;
close all;
clc;

p1=[2,1,-2,-1]
p2=[0,-2,0,1]

x=linspace(-2,2,100)
y1=polyval(p1,x)
y2=polyval(p2,x)

plot(x,y1,'b',x,y2,'r')

%obliczanie punktów przecięcie
%teoretycznie z określoną dokładnością możemy sprawdzić ile jest takich
%samych wartości w dwóch tablicach: nnz(abs(y1-y2)<1e-1)

%1.doprowadzamy do tego samego stopnia, za pomocą dopisywania zer w danych
%na poczatku

%liczymy różnicę
r=p1-p2

%miejsca zerowe
mz=roots(r)

hold on

%rysujemy je na wykresie
plot(mz,polyval(p1,mz),'kx','LineWidth',2,'MarkerSize',15)

