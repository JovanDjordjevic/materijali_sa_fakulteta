%    Ko laže taj krade.
%    Ko krade i uhvaćen je u krađi, taj ide u zatvor.
%    Al Kapone laže.
%    Al Kapone je uhvaćen u krađi.
%    Laki Lućiano laže.

% pisemo program koji ce da nam kaze da li al kapone i u zatvor i da li laki ide u zatvor
% kada ucitamo u terminal nas fajl, odgovore na ta pitanja dobijamo tako sto kucamo
% zatvor(alKapone)   i  zatvor(lakiLuciano)  i ispisace se yes/no 

laze(alKapone).
uhvacen(alKapone).
laze(lakiLuciano).

krade(X) :- laze(X).
zatvor(X) :- krade(X), uhvacen(X).