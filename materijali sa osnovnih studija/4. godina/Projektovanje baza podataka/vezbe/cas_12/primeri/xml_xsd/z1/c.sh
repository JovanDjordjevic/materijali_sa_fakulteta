# za pokretanje xquery upita koristimo ovaj xidel alat, ima za linux, mene
# mrzi da podesavam za windows a i nebitno je jer se ispit radi na papiru


xidel b.xml --output-format=xml --xquery \
'//Avion[@PIBproizvodjac=@PIBvlasnik]'