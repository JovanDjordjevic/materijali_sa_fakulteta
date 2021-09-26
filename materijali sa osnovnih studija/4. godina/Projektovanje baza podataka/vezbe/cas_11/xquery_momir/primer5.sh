# Sledeca komanda proverava da li datoteka 'person_refactored.xml',
# gde je 'person_refactored.xml' isto sto i 'person.xml' samo u lepsem formatu,
# zadovoljava strukturu koja je definisana datotekom 'primer5.xsd'
# tj. pokusava da parsira 'person_refactored.xml'
# Ocekivani izlaz: "person_refactored.xml validates"
xmllint --schema primer5.xsd person_refactored.xml --noout