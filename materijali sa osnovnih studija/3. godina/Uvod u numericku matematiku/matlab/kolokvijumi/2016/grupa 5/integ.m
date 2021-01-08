function [s,t]=integ(q)

p=@(x) (1-x).^2.*(1+x).^3;

f=@(x) x.*p(x).*polyval( conv(q,q) ,x);

s=integral(f,-1,1);
round(s,3)
