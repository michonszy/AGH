function varargout=argumenty(varargin)
%varargin to tablica komórkowa
%funkcje można wywałać z dowolną ilością dowolnych parametrów

% display(nargin)
% display(nargout)
% 
% display(varargin)

liczba_el=zeros(1,nargin)

for i=1:nargin
    liczba_el(i)=numel(varargin{i})
end
display(liczba_el)
[~,indx]=sort(liczba_el)


varargout=varargin(indx)