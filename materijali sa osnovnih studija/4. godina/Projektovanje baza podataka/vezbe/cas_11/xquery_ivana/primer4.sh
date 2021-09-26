xidel Biografije/*.xml --output-format=xml --xquery \
'
(: 4. Biografije kojih profesora su prisutne u kolekciji? :)

for $bioname in //html/head/title/name return $bioname/string()
'