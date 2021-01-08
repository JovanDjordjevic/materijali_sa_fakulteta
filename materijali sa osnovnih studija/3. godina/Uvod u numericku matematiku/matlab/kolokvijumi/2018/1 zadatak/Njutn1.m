function y=Njutn1(x,tol)

podaci;

Y=f(X);
n=length(X);
krazlike=zeros(n,n-1);
for i=1:n-1
    krazlike(i,1)=Y(i+1)-Y(i);
end
for j=2:n-1
    for i=1:n-j
        krazlike(i,j)=krazlike(i+1,j-1)-krazlike(i,j-1);
    end
end

disp([X' Y' krazlike]);

j=1;
while j<=n-1
    if 2^j*tol>max(abs(krazlike(:,j)))
        break;
    end
    j=j+1;
end

j=j-1;

q=(x-X(1))/(X(2)-X(1));
y=Y(1);
Q=q;
for i=1:j
    y=y+Q*krazlike(1,i)/factorial(i);
    Q=Q*(q-i);
end

y