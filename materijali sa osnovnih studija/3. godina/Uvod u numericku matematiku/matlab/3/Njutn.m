function N=Njutn(x)

tablica;

if tablicaCheck()==1
    if polozaj(x)==1
        nj=1;
    elseif polozaj(x)==2
        nj=2;
    else
        disp(" u sredini");
    end
else
    disp("nije ekvidistantna ");
end



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

disp([X' Y' krazlike])

if nj==1
    q=(x-X(1))/(X(2)-X(1));
    y=Y(1);
    Q=q;
    for i=1:n-1
        y=y+krazlike(1,i)*q/factorial(i);
        q=q*(Q-i);
    end
N=y    
    
else  %nj=2
    q=(x-X(n))/(X(2)-X(1));
    y=Y(n);
    Q=q;
    for i=1:n-1
        y=y+krazlike(n-i,i)*q/factorial(i)
        q=q*(Q+i);
    end
    
N=y    
    
end    
        