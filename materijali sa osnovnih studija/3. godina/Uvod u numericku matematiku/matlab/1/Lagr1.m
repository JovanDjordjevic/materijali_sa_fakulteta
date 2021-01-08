function V=Lagr1(x)

novatablica;

V=0;

for i=1:length(X1)
    p=1;
    for j=1:length(X1)
       if i~=j
           p=p*((x-X1(j))/(X1(i)-X1(j)));
       end
    end   
    V=V+p*Y1(i);
end   

