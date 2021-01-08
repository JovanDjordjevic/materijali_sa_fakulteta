function L=poli(n,a)

L=zeros(n+1);

L(1,n+1)=1;
L(2,n:end)=[-1 1+a];

for j=2:n
     L(j+1,:)=( ((-1)*[L(j,2:end),0] + (2*(j-1)+a+1)*L(j,:)) -  (j-1+a)*L(j-1,:) )/(j);
     %ne radi:  L(j+1,:)=( conv(L(j,2:end),[-1, 2*(j-1)+a+1]) -  (j-1+a)*L(j-1,:) )/(j);
end

L=L(n+1,:)





