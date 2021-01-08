function C=cebisev_poly(n)

C=zeros(n+1);
C(1,n+1)=1;
C(2,n)=1;

for i=2:n
    C(i+1,:)=2*[C(i,2:end),0]-C(i-1,:);
end

boje='cmykrgb';
X=linspace(-1,1);

plot(X,polyval(C(1,:),X),boje(1));
hold on
for i=2:n+1
    plot(X, polyval(C(i,:),X ),boje(mod(i,7)+1) );
end
hold off