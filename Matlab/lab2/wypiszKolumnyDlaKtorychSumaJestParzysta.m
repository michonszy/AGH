clear variables;
clc;


A=randi(10,6);
display(A)
s=sum(A)

np=mod(s,2)

class(np)% class(wartosc) zwraca nam typ zmiennej
np=logical(np) %rzutowanie zmiennej, w tym przypadku z double na logical

A(:,np)

%jeżeli suma dzielenia z 5 wynosi 2
%np2=mod(s,5)

%class(np)% class(wartosc) zwraca nam typ zmiennej
%np2=logical(np) %rzutowanie zmiennej, w tym przypadku z double na logical

%A(:,np2==2)

%sortowanie względem klucza z pierwszej kolumny
%pobieramy indext posortowanej pierwszej kolumny i w takiej kolejności
%sortujemy kolejne kolumny
[~,indx]=sort(A(:,1)) % ~ zastępuje nieużywaną zmienną, tu chcemy tylko indexy
A=A(indx,:)