clear variables;
clc;

A=randi(10,4);
display(A)
s=sum(A)
[ss,indx]=sort(s) %zwraca posortowaną macierz i pozycje elementów przed sortowaniem

%sortowanie aby kolumny się sortowały (kolejność kolumn, najpierw
%największa, mniejsza itd)
B = A(:,indx)
sum(B)

%C ma być losową kolejnością
C=A(:,randperm(4)) %randi losuje liczby i mogą się zdażyć takie same wartośći
% randperm losuje unikatowe wartości (jako że nie może być dwóch takich samych indeksów kolumn)

D=A(randperm(4),randperm(4)) %randperm = permutacja zbioru

A(1:10) %10 pierwszy elementów macierzy A

E=reshape(A(randperm(numel(A))),4,4) %reshape z jednoliniowego wyniku (wektor poziomy) tworzy macierz
%numel pobiera ilość elementów w macierzy

m=min(min(A)) %pierwszy min zwraca najmniejszy wier, drugi min najmniejszą wartość w nim 
% finalnie pokazuje najmniejszą wartość w macierzy

[m,i]=min(A) %wartość minimalna, i index wcześniej
[m,j]=min(m) %najmniejsza wartość w całej macierzy i jej indeks
i=i(j)
disp([i,j])

%to działa wolniej niż to wyżej ale znajduje wszystkie wartości minimalne
%nie tylko pierwszą
m=min(min(A))
[i,j]=find(A==m)

