function y=vredfunk(x)

[X,Y]=tablica();

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
nn=0;
for i=1:n-1
    l=krazlike(:,i);
    if  length( l( find( abs(l)>1e-2 ) )  )>0
        nn=nn+1;
    else
        break;
    end
end

krazlike=krazlike(:,1:nn);
krazlike

q=(x-X(n))/(X(2)-X(1));
y=Y(n);
Q=q;
for i=1:nn
    y=y+Q*krazlike(n-i,i)/factorial(i);
    Q=Q*(q+i);
end
y
