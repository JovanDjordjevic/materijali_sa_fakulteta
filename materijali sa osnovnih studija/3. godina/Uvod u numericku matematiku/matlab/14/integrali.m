function integrali(f)


disp(integral(@(x) f(x),-1,1) )

disp( integral(@(x) f(x).*sin(x),-1,1) )

L=legendre_poly(5);

disp( integral(@(x)f(x).* polyval(L(6,:),x ),-1,1) ) 

disp( integral(@(x) polyval(L(6,:),x).*polyval(L(4,:),x), -1, 1) )