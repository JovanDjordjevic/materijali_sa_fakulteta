function I=trapez(a,b) 

funkcija;
n=9;
X=linspace(a,b,n);

Y=f(X);
h=X(2)-X(1);

I=(h/2)*(Y(1)+2*sum(Y(2:n-1))+Y(n));