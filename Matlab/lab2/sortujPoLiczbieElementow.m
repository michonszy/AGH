% function [a,b]=sortujPoLiczbieElementow(a,b)

% if numel(a)>numel(b)
%     c=a
%     a=b
%     b=c
% end
function [a,b]=sortujPoLiczbieElementow(a,b)

%sprawdzenie ile argumentów jest przekazywanych
% display(nargin) %liczba elementów wejściowych
% display(nargout) %liczba elementów wyjściowych

if numel(a)>numel(b)
    c=a
    a=b
    b=c
end
