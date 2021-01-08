function y=vred2izvod(x)

[X,Y,Y2i]=drugiizvod();

X=X(2:end-1);
n=length(X);
krazlike=zeros(n,n-1);
for i=1:n-1
    krazlike(i,1)=Y2i(i+1)-Y2i(i);
end
for j=2:n-1
    for i=1:n-j
        krazlike(i,j)=krazlike(i+1,j-1)-krazlike(i,j-1);
    end
end
disp("konacne razlike");
disp([X' Y2i' krazlike]);

q=(x-X(1))/(X(2)-X(1));
y=Y2i(1);
Q=q;               %moze i od Q=1 pa onda dole Q=Q*(q-i) ali pre y=...
for i=1:n-1
    y=y+Q*krazlike(1,i)/factorial(i);
    Q=Q*(q-i);
end

y