function y=vredfunk(x)

tablica;
t=tablicaCheck();
if t==0
    error("nisu ispunjeni uslovi")
end

n=length(X);
prazlike=zeros(n,n-1);

for i=1:n-1
    prazlike(i,1)=(Y(i+1)-Y(i))/(X(i+1)-X(i));
end

for j=2:n-1
    for i=1:n-j
        prazlike(i,j)=(prazlike(i+1,j-1)-prazlike(i,j-1))/(X(i+j)-X(i));
    end
end    

%disp([X' Y' prazlike])

y=Y(1);
p=1;
for i=1:n-1
    p=p*(x-X(i));
    y=y+p*prazlike(1,i);
end
y

%koeficijenti njutnovog:
pol=Y(1);
p=1;
for i=1:n-1
   p=conv(p,[1,-X(i)]);
   pol=[0,pol] + p*prazlike(1,i);
end    
pol
