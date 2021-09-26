xidel Biografije/*.xml --trace-stack --output-format=xml --xquery \
'
(: 2. U kojoj recenici se spominje rođenje prof Bakše? :)

(:Za biografiju profesora Bakše…:)
for $bio in /html[fn:contains(head/title/name/string(), "Bakša")] 

(:…izdvoji sve recenice…:)
for $seg in $bio/body/p/font/seg 

(:…u kojima se javlja rec “rođen”.:)
where fn:contains(fn:lower-case($seg/string()), "rođen")

(:I vrati kao rezultat tu recenicu:)
return $seg/string()
'