function [X,Y,Yi]=izvod()

tablica;

n=length(X);
Yi=zeros(1,n-2);
j=1;
for i=2:n-1
    Yi(j)=(Y(i+1)-Y(i-1))/(X(i+1)-X(i-1));
    j=j+1;
end   

X
Y
Yi