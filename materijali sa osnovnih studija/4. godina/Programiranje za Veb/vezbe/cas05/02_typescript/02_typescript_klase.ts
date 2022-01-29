// NOTE: kada prevodimo ovo sa sa   tsc ime.ts      dobijamo gresku da accessori (geteri i seteri koje korsitimo)
// postoje tek od ECMAScript 5. Prevodicemo ovo sa:
//      tsc --target ES5 ime.ts


// u klasama podrazumevana vidljivost je public
// i ovo se prevodi u neku samopozivajucu funkciju i rade se neke madjije sa prototipovima itd...
class Song {
    private artist:string;
    private title : string;

    // konstruktyor se navodi ovako kljucnom recju, ne zove se kao sama klasa
    // takodje nema povratni tip
    constructor(artist:string, title:string){
        this.artist = artist;
        this.title = title;
    }

    // kada imamo ovako trivijalan konstruktor, imamo precicu za njegovo pisanje
    //         constructor(private artist:string, privatetitle:string) {}
    // u ovoj jednoj liniji se i deklarisu promenljive (pa ne moramo to iznad da radimo kao sto smo sad)
    // i dodeli im se odmah vrednost koja se prosledi na toj poziciji argumenta

    public play(){
        console.log(`Playing ${this.title} by ${this.artist}`);
    }
}


class PlayList{
    // mozemo za neko public polje da navedemo da je readonly i onda moze da mu se pritupi van klase
    // ali ne moze da se menja, to dodje kao da je private pa da imamo getter
    public songs:Song[] = [];
    public static readonly maxSongContent:number = 30;

    // mozemo da pravimo ovakav konstruktor iako vec imamo neka polja klase
    // koja su rucno deklarisana
    constructor(public name:string) {}

    addSong(song:Song){
        if(this.songs.length >= PlayList.maxSongContent){
            throw new Error("Playlist is full");
        }

        this.songs.push(song);
    }

    // ovako se pravi geter, ima kljucnu rec get ispred
    // NOTE: iako je ovo funkcija, geter se poziva kao polje klase, tj bez ()
    public get getSongs() :Song[]{
        return this.songs;
    }

    // slicno za seter
    public set allSongs(p:PlayList){
        this.songs = [];
        for(const song of p.getSongs){
            this.addSong(song);
        }
    } 
}


// nasu klasu takodje navodimo kao tip
const song:Song = new Song("Lady Gaga", "Poker face");
song.play(); 

// pristupanje privatnom polju klase je greska u TS ali ovo ce se naravno prevesti
// u JS kod i moci ce da se pokrene
//      console.log(song.artist);

const p:PlayList = new PlayList("Neka plejlista");

try{
    p.addSong(song);
    p.addSong(new Song("Arianga Grande", "7 rings"));
    p.addSong(new Song("Miley Cyrus", "7 things"));  // na pocetku je ovo izbacivalo gresku jer je limit bio 2
} catch (err){
    console.log(err.message);
}

// dohvatanje sa geterom. Geter i i seteri se pozivaju bez ()
// ali ce se sama funkcija pozvati u pozadini
p.getSongs;

const p2:PlayList = new PlayList("nesto nesto");
// seter se poziva isto bez ()
p2.allSongs = p;
