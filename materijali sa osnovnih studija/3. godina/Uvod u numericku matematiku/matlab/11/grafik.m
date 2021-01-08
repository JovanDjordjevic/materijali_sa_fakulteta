function grafik(a,b)

tol=10.^[-1:-1:-6];
brs=zeros(1,6);
brt=zeros(1,6);

for i=1:6
    [I,brs(i)]=integrals(a,b,tol(i));
    [I,brt(i)]=integralt(a,b,tol(i));
end


plot(tol,brs,'b',tol,brt,'r');
legend('Simpson','Trapez');
xlabel('tol');
ylabel('br iter');
