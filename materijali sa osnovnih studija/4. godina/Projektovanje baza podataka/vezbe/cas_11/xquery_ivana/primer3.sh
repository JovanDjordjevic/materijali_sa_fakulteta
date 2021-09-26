
xidel Biografije/*.xml --output-format=xml --xquery \
'
(: 3. Koje znacajnije radove je objavio prof Bakša? :)

for $bio in /html for $seg in $bio/body/p/font/a/i 
where fn:contains($bio/head/title/name/string(), "Bakša")
return $seg/string()
'