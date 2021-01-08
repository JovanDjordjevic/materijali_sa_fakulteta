function [T,maks]=skrati(A,k)

i=1;
n=length(A);

T=zeros(n);

for j=1:n
    if sum(abs(A(i:n-j+1,j)))/(n-j+1)<=k
        T(:,j)=A(:,j);
        i=i+1;
    end
end

T=T(:,1:i-1)
maks=max(T');