function t=trapez(a,b,n)

funkcija;

X=linspace(a,b,n);
Y=f(X);
h=X(2)-X(1);

t=(h/2)*( Y(1) + 2*sum(Y(2:n-1)) + Y(n) );