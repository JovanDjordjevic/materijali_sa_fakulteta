# Store-server

- Node.js projekat koji implementira server sa narednim API-jem:

| Metod | Ruta | Kratak opis | 
| ---   | ---  | ---         |
| POST | /api/users/register | Registracija novog korisnika |
| POST | /api/users/login | Prijavljivanje postojećeg korisnika |
| PATCH | /api/users/ | Promena informacija o postojećem korisniku |
| GET | /api/products | Dohvatanje informacija o proizvodima |
| GET | /api/products/{productId} | Dohvatanje detaljnih informacija o proizvodu |
| POST | /api/products | Kreiranje novog proizvoda |
| PUT | /api/products/upload/{productId} | Pohranjivanje slike za proizvod |
| DELETE | /api/products/{productId} | Brisanje jednog proizvoda |
| GET | /api/orders | Dohvatanje narudžbina za korisnika |
| GET | /api/orders/{id} | Dohvatanje detaljnih informacija o jednoj narudžbini za korisnika |
| POST | /api/orders | Kreiranje nove narudžbine za korisnika |

## User API

- Implementirana je autorizacija i autentikacija korišćenjem JWT tokena.
    - Pogledati datoteku `components/utils/authentication.js`
    - JWT se prosleđuje kroz `Authorization` zaglavlje HTTP zahteva, korišćenjem Bearer sheme.
- Implementirano je šifrovanje lozinke korišćenjem `bcrypt` paketa.
    - Pogledati model `components/users/userModel.js`

## Product API

- Osetljive putanje su zaštićene autentikacijom i autorizacijom
    - Pogledati ruter `components/products/productsAPI.js`
    - Pogledati kontroler `components/products/productsController.js`
- Implementirano je pohranjivanje slika za proizvode korišćenjem paketa `multer`
    - Pogledati kontroler `components/products/productsController.js`
    - Pogledati kontroler `components/upload/uploadController.js`
- Implementirana je paginacija proizvoda korišćenjem Mongoose sistema dodataka (eng. plugin) i dodatka `mongoose-paginate-v2`.
    - Pogledati model `components/products/productModel.js`

## Order API

- Ceo API je organizovan korišćenjem OOP u JavaScript jeziku. Ovo je urađeno na ovaj način čisto radi demonstracije. Ne očekuje se korišćenje ovog pristupa na ispitu :)
    - Primetimo da klase koje ulaze u sastav obrade zahteva (`OrdersRouter`, `OrdersController`, itd.) ne čuvaju nikakvo stanje zahteva, već se za svaki zahtev instanciraju novi objekti ovih klasa. Obično je ovakav pristup koji se koristi u praksi, kako ne bi dolazilo do "mešanja" različitih zahteva. Trebalo bi napomenuti da, umesto da svaka klasa instancira objekte drugih klasa, bolja praksa bi bilo korišćenje ubrizgavanja zavisnosti kroz konstruktore ovih klasa. Ipak, radi jednostavnosti koda, odabrali smo da ne implementiramo i ovaj mehanizam.