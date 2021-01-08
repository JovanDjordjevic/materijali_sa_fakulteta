function t=tablicaCheck()

tablica

rastojanje=X(2)-X(1);
for i=3:length(X)
    if (X(i)-X(i-1))~=rastojanje
        disp("nije ekvidistantna")
        t=0
    end
end
for i=2:length(X)
    if X(i)<=X(i-1)
        disp("niej strogo rastuca")
        t=0
    end
end

t=1