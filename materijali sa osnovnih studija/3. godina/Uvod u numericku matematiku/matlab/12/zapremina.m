function z=zapremina(a,b,tol)

h=(b-a)/2;
I1=simps(a,b,h);
h=h/2;
I2=simps(a,b,h);
while(runge(I1,I2)>tol)
      I1=I2;
      h=h/2;
      I2=simps(a,b,h);
end

z=I2;


function I=simps(a,b,h);
n=(b-1)/h+1;
X=linspace(a,b,n);
funkcija;
Y=f(X).^2*pi;   %!!!!!!!!!  ()^2  *pi
I=(h/3)*(Y(1)+4*sum(Y(2:2:end-1))+2*sum(Y(3:2:end-1))+Y(end));
