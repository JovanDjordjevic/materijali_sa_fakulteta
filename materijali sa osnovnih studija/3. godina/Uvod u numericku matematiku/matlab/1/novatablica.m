tablica;

X1=zeros(1,length(X)*2-1);
Y1=zeros(1,length(Y)*2-1);

j=1
for i=1:2:length(X)*2-1 
    X1(i)=X(j);
    Y1(i)=Y(j);    
    j=j+1;
end    

j=1
for i=2:2:length(X)*2-1
    X1(i)=(X(j)+X(j+1))/2;
    Y1(i)=(Y(j)+Y(j))/2;
    j=j+1;
end    

X1
Y1