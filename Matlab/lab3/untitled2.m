clear variables;
close all;
clc;

X=linspace(-1,1,10)
Y=X.^2+0.1*randn(size(X))


p=polyfit(X,Y,5)
x=linspace(-1,1,1000)
y=polyval(p,x)

plot(x,y,'b','LineWidth',2,'MarkerSize',5)
hold on

plot(X,Y,'rx','LineWidth',2,'MarkerSize',15)