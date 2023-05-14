clear variables;
close all;
clc;

n=10000;

%1/[1,5,9]' apostrof na końcu wykonuje dzielenie przez macierz pionową
%1./[1,5,9] kropka sprawia że traktuje macierz jako tablice i dzieli każdy
%element

Pi=4*(sum(1./(1:4:n))-sum(1./(3:4:n)));
disp(Pi)

Pi2=(6*sum(1./(1:n).^2))^0.5;
disp(Pi2)

%format long
%Pi2 = 3.141497163947211
%format short
%Pi2 = 3.1415