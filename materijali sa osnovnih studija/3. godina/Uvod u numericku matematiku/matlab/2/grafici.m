function grafici(x,a,b,n)

funkcija;
[L,y]=Lagr1b(x,a,b,n);
xx=linspace(a,b);

plot(xx,f(xx),xx,polyval(L,xx));
legend ('Funkcija','Interp')