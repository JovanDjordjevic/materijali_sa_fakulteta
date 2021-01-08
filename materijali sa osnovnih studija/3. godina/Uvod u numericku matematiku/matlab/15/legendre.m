function L=legendre(n)

L=zeros(n+1);

L(1,n+1)=1;
L(2,n)=1;

for i=2:n
    L(i+1,:)=( (2*i-1)* [L(i,2:end) ,0]  - (i-1)*L(i-1,:))/i;
end

L=L(n+1,:);