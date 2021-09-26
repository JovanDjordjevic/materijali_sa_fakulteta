# komentari u xqueryju su (: ... :)

xidel Biografije/*.xml --output-format=xml --xquery \
'
(:Za biografiju profesora Bakše…:)
for $bio in /html[fn:contains(head/title/name/string(), "Bakša")] 

(: izdvoji sve recenice :)
for $seg in $bio/body/p/font/seg 

(: u kojima se javlja re “rođen”.:)
where fn:contains(fn:lower-case($seg/string()), "rođen")
 
return fn:concat("Osoba sa imenom ",$bio/head/title/name, " rođena je u ", $seg/loc/string(), ".") 
'