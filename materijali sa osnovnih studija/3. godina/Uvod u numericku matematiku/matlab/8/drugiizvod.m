function [X,Y,Y2i]=drugiizvod()

tablica;

n=length(X);
h=X(3)-X(2);
Y2i=zeros(1,n-2);
j=1;
for i=2:n-1
    Y2i(j)=(Y(i-1)-2*Y(i)+Y(i+1))/(h*h);
    j=j+1;
end

X
Y
Y2i