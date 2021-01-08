function [X,Y]=tabeliraj(a,b,n)

funkcija;
X=linspace(a,b,n);

Y=zeros(1,n);
for i=1:n
    Y(i)=f(X(i));
end




