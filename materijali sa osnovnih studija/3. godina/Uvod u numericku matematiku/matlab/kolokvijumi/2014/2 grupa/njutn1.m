function koef=njutn1()

tablica

n=length(X);
krazlike=zeros(n,n-1);
for i=1:n-1
    krazlike(i,1)=F(i+1)-F(i);
end
for j=2:n-1
    for i=1:n-j
        krazlike(i,j)=krazlike(i+1,j-1)-krazlike(i,j-1);
    end
end
disp( [X' F' krazlike]);

koef=F(1);
Q=[1 0];

for i=1:n-1
    koef=[0 koef]+Q*krazlike(1,i)/factorial(i);
    Q=conv(Q,[1,-i]);
end

koef