# Ovo je komentar 
# Potrebna je Enterprise verzija mysql-a za rad sa xquery upitima 
# Na sledecem linku se moze skinuti alat za procesiranje xquery upita 
# Tada se ovaj skript moze pokrenuti na sledeci nacin 
# xidel person_refactored.xml --xquery < '...' 
#!/bin/bash

# Sledeci xquery upit ucitava podatke, filtrira ih i transformise ih u drugi format

xidel person_refactored.xml --output-format=xml --xquery '
for $person in //person
where data($person/@person_id) > "3"
let $person_id := data($person/@person_id)
let $fname := data($person/fname)
let $lname := data($person/lname)
return 
<individual id="{$person_id}">
  <name1>{$fname}</name1>
  <name2>{$lname}</name2>
</individual>'

# Ocekivani izlaz:
# <?xml version="1.0" encoding="UTF-8"?>
# <xml>
# <individual id="4">
#   <name1>Slar</name1>
#   <name2>Manlanth</name2>
# </individual>
# <individual id="5">
#   <name1>Stoma</name1>
#   <name2>Milu</name2>
# </individual>
# <individual id="6">
#   <name1>Nirtam</name1>
#   <name2>Sklöd</name2>
# </individual>
# <individual id="7">
#   <name1>Sungam</name1>
#   <name2>Dulbåd</name2>
# </individual>
# <individual id="8">
#   <name1>Sraref</name1>
#   <name2>Encmelt</name2>
# </individual>
# </xml>