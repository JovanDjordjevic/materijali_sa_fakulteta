function f=vredizvod(x)

[X,Y,Yi]=izvod();

X=X(2:end-1);
n=length(X);
prazlike=zeros(n,n-1);
for i=1:n-1
    prazlike(i,1)=(Yi(i+1)-Yi(i))/(X(i+1)-X(i));
end
for j=2:n-1
    for i=1:n-j
        prazlike(i,j)=(prazlike(i+1,j-1)-prazlike(i,j-1))/(X(i+j)-X(i));
    end
end

disp("tablica podeljenih razlika");
disp([X' Yi' prazlike]);

y=Yi(1);
p=1;
for i=1:n-1
    p=p*(x-X(i));
    y=y+p*prazlike(1,i);
end

f=y;
f

    