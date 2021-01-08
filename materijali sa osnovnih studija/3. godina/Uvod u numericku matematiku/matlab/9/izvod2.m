function y=izvod2(x)

X=linspace(2,4,10);
Y=exp(X);

n=length(X);
krazlike=zeros(n,n-1);
for i=1:n-1
    krazlike(i,1)=Y(i+1)-Y(i);
end
for j=2:n-1
    for i=1:n-j
        krazlike(i,j)=krazlike(i+1,j-1)-krazlike(i,j-1);
    end
end
disp([X' Y' krazlike]);

h=(X(2)-X(1));
q=(x-X(1))/h;

y=( krazlike(1,2)+(q-1)*krazlike(1,3)+(12*q*q-36*q+22)*krazlike(1,4)/24 ) / (h*h);

y