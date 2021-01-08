function y=izvod(x)

tablica;

n=length(X);
krazlike=zeros(n,4)
for i=1:n-1
    krazlike(i,1)=Y(i+1)-Y(i);
end
for j=2:4
    for i=1:n-j
        krazlike(i,j)=krazlike(i+1,j-1)-krazlike(i,j-1);
    end
end
disp([X' Y' krazlike]);

h=(X(2)-X(1));
q=(x-X(1))/h;

y=(1/h)*( krazlike(1,1)+(2*q-1)*krazlike(1,2)/2 + (3*q*q-6*q+2)*krazlike(1,3)/6 + (4*q*q*q-18*q*q+22*q-6)*krazlike(1,4)/24);

y