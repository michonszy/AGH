clear variables;
clc;

s=ile(rand(2,3),[1,2,3])
display(s)

a=rand(2,3,4)
b=[1,2,3]
s1=ile(a,b)
display(s1)

[a,b]=sortujPoLiczbieElementow(a,b)



argumenty(rand(2),'AGH',[1,2,3]) %varargin = 1×3 cell array : {2×2 double}    {'AGH'}    {[1 2 3]}
%a = argumenty(1,2,3)

[a,b,c]=argumenty(1,[1,2,3,4,5],[1,2])