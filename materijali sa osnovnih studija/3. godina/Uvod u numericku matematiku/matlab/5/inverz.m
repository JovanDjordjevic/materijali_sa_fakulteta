function x=inverz(c)

[X,Y]=tablica();
disp([X',Y']);

[X1,I]=sort(Y);  %X1=Y(I)

Y1=X(I);

disp([X1',Y1']);

n=length(X1);

y=0;
for i=1:n
    p=1;
    for j=1:n
        if j~=i
            p=p*(c-X1(j))/(X1(i)-X1(j));
        end    
    end
    y=y+p*Y1(i);
end

x=y