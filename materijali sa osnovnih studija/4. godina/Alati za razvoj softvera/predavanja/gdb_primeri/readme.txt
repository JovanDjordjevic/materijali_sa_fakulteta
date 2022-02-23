hocemo da u pajtonu implementiramo novu komandu za gdb koja ce da uradi continue ili run kada stignemo do breakpointa (?)
cesta praksa je da se ovakve dodatne komande cuvaju u nekom folderu npr
	.gdb/my_py_scripts/ime...

da bi korsitili nasu komandu, pokrenemo gdb u terminalu, i onda treba da ucitamo komandu ovako:
	source ~/.gdb/my_py_scripts/cont_or_run.py

Ova source komanda je komanda koja cita fajl na datoj putanji i pravi komandu od toga (?) Moze da se pise u pajtonu a moze i u 
nekom drugom script jeziku (?)

I sada mozemo da korsitimo komandu iz gdba, tako sto samo pozovemo:
	cont_or_run

Lep use case za custom komande je da pravimo neki formater/pretty printer za neke nase c++ klase ako nam trebaju (jer ih gdb ispisuje na neki svoj nacin koji nam mozda ne odgovara)