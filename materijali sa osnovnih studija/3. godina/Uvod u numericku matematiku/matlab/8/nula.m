function f=nula()

[X,~,Y2i]=drugiizvod();

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

q0=0;
q1=(-Y2i(1)-q0*(q0-1)*krazlike(1,2)/2 -q0*(q0-1)*(q0-2)*krazlike(1,3)/6 )/(krazlike(1,1));

while ( abs(q1-q0)>1e-4)
    q0=q1;
    q1=(-Y2i(1)-q0*(q0-1)*krazlike(1,2)/2 -q0*(q0-1)*(q0-2)*krazlike(1,3)/6 )/(krazlike(1,1));
end

f=X(1)+q1*(X(2)-X(1))