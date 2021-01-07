%ovaj zadatak mi ne radi

% (ime, prezime, tip, boja)

clan(X, [X|_]) :- !.
clan(X, [G|R]) :- G \==X,  clan(X, R).

drugarice(X) :- X = [(_,_,_,_), (_,_,_,_), (_,_,_,_), (_,_,_,_)],
                        clan((milica,_,_,_), X),
                        clan((anja,_,_,_), X),
                        clan((kaca,_,_,_), X),
                        clan((jelena,_,_,_), X),
                        clan((_,ranisavljevic,_,_), X),
                        clan((_,andonov,_,_), X),
                        clan((_,cugurovic,_,_), X),
                        clan((_,bogdanovic,_,_), X),
                        clan((_,_,cizme,_), X),
                        clan((_,_,sandale,_), X),
                        clan((_,_,cipele,_), X),
                        clan((_,_,patike,_), X),
                        clan((_,_,_,zelena), X),
                        clan((_,_,_,braon), X),
                        clan((_,_,_,pink), X),
                        clan((_,_,_,crne), X),
                        clan( (_, ranisavljevic, _, zelena), X),
                        clan( (_, _, cizme, braon), X),
                        clan( (milica, _, sandale, _), X),
                        clan((kaca, andonov, _, _), X),
                        \+( clan((_, cugurovic, cizme, braon), X  )),
                        \+( clan((milica, ranisavljevic, sandale, _),X) ),
                        \+( clan((milica, _, sandale, crne), X)),
                        \+( clan((kaca, andonov, cizme, _), X)),
                        \+( clan( (_, _, cipele, pink), X)),
                        \+( clan((anja, bogdanovic,_ ,_), X)),
                        \+( clan( (jelena, _,patike, _), X)).
                        
