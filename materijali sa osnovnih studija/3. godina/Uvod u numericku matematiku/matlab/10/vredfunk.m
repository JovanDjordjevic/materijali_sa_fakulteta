function [X,Y]=vredfunk(k,p)

X=2:k ;              %isto kao X=linspace(2,k,k-1);
Y=zeros(1,k-1);
for i=1:k-1
    if p==1
        Y(i)=simps(1,X(i));
    elseif p==2
        Y(i)=trapez(1,X(i));
    end
end

X
Y