xidel VlastitaImena/vlastitaImena.xml --output-format=xml --xquery \
'
(: 6. Imena koja se pojavljuju u dokumentu VlastitaImena.xml :)

for $ime in //root/languages/language/prolexemes/prolexeme/@name/string()
return $ime
'