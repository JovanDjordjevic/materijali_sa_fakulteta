function x=nula(a,b,n)

[c,d]=promenaZnaka(a,b,n);

funkcija;

[X1,Y1]=tablica(c,d,n);

kr=zeros(n,3);
for i=1:n-1
    kr(1,i)=Y1(i+1)-Y1(i);
end
for j=2:3
    for i=1:n-j
        kr(i,j)=kr(i+1,j-1)-kr(i,j-1);
    end    
end
disp([X1' Y1' kr]);

q0=0;
q1=(-Y1(n)-q0*(q0+1)*kr(n-2,2)/2 - q0*(q0+1)*(q0+2)*kr(n-3,3)/6)/kr(n-1,1);
Q=[q0,q1];

while(abs(q0-q1)>=1e-4)
    q0=q1;
    q1=(-Y1(n)-q0*(q0+1)*kr(n-2,2)/2 - q0*(q0+1)*(q0+2)*kr(n-3,3)/6)/kr(n-1,1);
    Q=[Q q1];
end

x=X1(end)+Q(end)*(X1(2)-X1(1));
disp(x);