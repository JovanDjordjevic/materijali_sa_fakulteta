function integral(n,m,tol)

P=polinom(n,m)

f=@(x) polyval(P,x).*exp(x);

a=-1;
b=1;

h=(b-a)/2;
X=a:h:b;
Y=f(X);

S1=(Y(1) + Y(end) +4*sum(Y(2:2:end-1)) + 2*sum(Y(3:2:end-1)))*h/3;

h=h/2;
X=a:h:b;
Y=f(X);
S2=(Y(1) + Y(end) +4*sum(Y(2:2:end-1)) + 2*sum(Y(3:2:end-1)))*h/3;

briter=2;

while(abs(S1-S2)/15 >tol && briter<100 )
    S1=S2;
    h=h/2;
    X=a:h:b;
    Y=f(X);
    S2=(Y(1) + Y(end) +4*sum(Y(2:2:end-1)) + 2*sum(Y(3:2:end-1)))*h/3;
    briter=briter+1;
end

I=S2


