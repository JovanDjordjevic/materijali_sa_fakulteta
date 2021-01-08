function [I,briter]=integralt(a,b,tol)

funkcija;

n=3;
I1=trapez(a,b,n);
n=2*n-1;
I2=trapez(a,b,n);
briter=2;

while(abs(I1-I2)/3<tol)
    I1=I2;
    n=2*n-1;
    I2=trapez(a,b,n);
    briter=briter+1;
end

I=I2;
