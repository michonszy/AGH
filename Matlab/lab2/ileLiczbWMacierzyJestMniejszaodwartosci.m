clear variables;
clc;


A=randi(10,6);
display(A)

nnz(A==5) %ile jest piątek w macierzy
nnz(A) %ile jest niezerowych elementów


s=mean(mean(A)) %mean to średnia
nnz(A>s-1 & A<s+1) %ile jest elementów nie różniących się więcej niż 1 od średniej

