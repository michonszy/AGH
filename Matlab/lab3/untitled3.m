clear variables;
close all;
clc;

X=linspace(-1,1,20)
P = 10*rand(1,randi(10)+5)-5 %losowy wielomian losowego stopnia
Y=polyval(P,X)

% p2 = polyfit(X,Y,2)
% x=linspace(-1,1,100)
% y2=polyval(p2,x)
% 
% e2=mean(abs(Y-polyval(p2,X)))


%wykres jak zależy błąd od stopnia wielomianu, do stopnia 16
odchylenia=[]
for i=0:15
     p2 = polyfit(X,Y,i)
     x=linspace(-1,1,100)
     y2=polyval(p2,x)
     e2=mean(abs(Y-polyval(p2,X)))
     odchylenia=[odchylenia;e2]
end
 

% plot(X,Y,'rx','LineWidth',2,'MarkerSize',15)
% hold on
% plot(x,y2,'b','LineWidth',2)

bar(0:15,odchylenia); 
set(gca,'YScale','log') %gca uchwyt do białego pola, gcf uchwyt do całej figury