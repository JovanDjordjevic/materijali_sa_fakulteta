function t=tablicaCheck()

tablica;

t1=1;
t2=1;  %rastuci 
t3=1;  %opadajuc

for i=2:length(X)
   if X(i)<=X(i-1)
       t1=0;
       t=0
       disp("x nije rastuci")
       break;
   end    
end  

for i=2:length(Y)
    if Y(i)<Y(i-1)
        t2=0;
    end
    if Y(i)>Y(i-1)
        t3=0;
    end
end

if t2==0 && t3==0
        disp("y nije monoton")
        t=0
end

if (t1 && t2) || (t1 && t3)
   t=1      
end
