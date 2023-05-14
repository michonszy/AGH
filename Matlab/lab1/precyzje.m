clear variables;
close all;
clc;

%kierunek dzielenia z matlabie jest rozróżniany tzn 1/2 == 2\1
A0=[2,6;2,6];
b0=[8;8];
A=A0;
b=b0;
e=0.1;

for i=1:20
    display(i);
    A(2,2)=A0(2,2)+e;
    b(2)=b0(2)+e;
    display(rcond(A));
    x=A\b;
    %display(x)
    e=e/10;
end


