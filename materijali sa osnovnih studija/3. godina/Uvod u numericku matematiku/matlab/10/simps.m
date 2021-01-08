function I=simps(a,b)

funkcija;
n=9;
X=linspace(a,b,n);
Y=f(X);

h=X(2)-X(1);

I=(h/3)*( Y(1) + 4*sum(Y(2:2:end-1)) + 2*sum(Y(3:2:end-1)) + Y(n) );