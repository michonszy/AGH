clear variables;
close all;
clc;

p=[1,0,0]
x=linspace(-1,1,11)
y=polyval(p,x)

for i=1:length(x)
    plot(x(i),y(i),'s','LineWidth',5*y(i)+1,'MarkerSize',10*y(i)+10)
    hold on
end
