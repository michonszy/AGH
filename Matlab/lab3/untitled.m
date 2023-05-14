clear variables;
close all;
clc;

licznik=[-2,0,1]
mianownik=[2,1,-2,-1]

[f,r]=deconv(licznik,mianownik)

x=linspace(-2,2,100)
yl=polyval(licznik,x)
ym=polyval(mianownik,x)
y=yl./ym

plot(x,y)