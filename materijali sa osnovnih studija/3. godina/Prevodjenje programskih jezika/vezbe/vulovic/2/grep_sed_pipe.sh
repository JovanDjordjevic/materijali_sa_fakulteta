#ZADATAK:
#Iz html datoteka nastava.html i nastava1.html izdvojiti i podatke o studentima koji su upisani
#od 2000 godine do danas i broj indeksa im je u intervalu [1,350] bez vodecih nula.
# Za svakog studenta na osnovu indeksa kreirati alas nalog. Pretpostaviti da su svi sa I smera.
#Izdvojiti ime, prezime i alas nalog (odvojen sa karakterom ',' od ostalih podataka).
#Spisak urediti rastuce po imenu i numerisati i upisati u datoteku spisak.txt

#Ovaj skript pokrenuti iz konzole naredbom: 
# sh grep_sed_pipe.sh

egrep '<td>\s*[A-Z][a-z]+\s+[A-Z][a-z]+\s*</td>\s*<td>\s*([1-9][0-9]?|[12][0-9][0-9]|3[0-4][0-9]|350)/20(0[0-9]|1[0-7])\s*</td>' nastava*.html -h \
|  sed -r 's~\s*<td>([ A-Za-z]+)</td>\s*<td>\s*([0-9]{1,3})/([0-9]{4})\s*</td>\s*~\1 \2 \3~' \
|  sed -r 's/([0-9]{3}) [0-9]{2}([0-9]{2})/, mi\2\1/'   \
|  sed -r 's/([0-9]{2}) [0-9]{2}([0-9]{2})/, mi\20\1/'  \
|  sed -r 's/([0-9]) [0-9]{2}([0-9]{2})/, mi\200\1/' \
|  sed -r 's/([A-Za-z]+)\s+([A-Za-z]+)\s+/\2 \1/'  \
| \
sort \
| egrep -n ',' \
| sed -r 's/:/. /' \
> spisak.txt

#poziv u 9. redu moze i sa egrep -n '.*'
