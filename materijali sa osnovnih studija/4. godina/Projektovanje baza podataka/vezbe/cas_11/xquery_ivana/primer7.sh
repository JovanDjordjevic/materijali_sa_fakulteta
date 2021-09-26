xidel Biografije/*.xml --output-format=xml --xquery \
'
(: 7. Imena koja se pojavljuju u biografijama :)

for $bioname in //name
return $bioname/string()
'