function f=nula()

[X,Y,Yi]=izvod();

X=X(2:end-1);
n=length(X);

[B,I]=sort(Yi);
Yi=X(I);
X=B;

prazlike=zeros(n,n-1);
for i=1:n-1
    prazlike(i,1)=(Yi(i+1)-Yi(i))/(X(i+1)-X(i));
end
for j=2:n-1
    for i=1:n-j
        prazlike(i,j)=(prazlike(i+1,j-1)-prazlike(i,j-1))/(X(i+j)-X(i));
    end
end

disp([X' Yi' prazlike]);

s=Yi(1);
r=1;
for i=1:n-1
    r=r*(0-X(i));
    s=s+r*prazlike(1,i);
end

f=s