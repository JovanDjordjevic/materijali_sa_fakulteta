xidel Biografije/*.xml --output-format=xml --xquery \
'
(: 5. Ko je sve od profesora rođen u Beogradu? :)

for $bio in //html for $seg in $bio/body/p/font/seg 
where fn:contains(fn:lower-case($seg/string()), "beograd") and
 (fn:contains(fn:lower-case($seg/string()), "rođen je") or fn:contains(fn:lower-case($seg/string()), "rođena je") or fn:contains(fn:lower-case($seg/string()), "je rođena")or fn:contains(fn:lower-case($seg/string()), "je rođen")) 
return fn:concat("Osoba sa imenom ",$bio/head/title/name, " rođena je u ", $seg/loc/string(), ".")
'