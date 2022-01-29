// ovde smo prekopirali ono od pre i malo izmenili da pokazemo kako se nasledjuje

// u JS/TS ne postoji visestrukto nasledjivanje
// to se prevazilazi koriscenjem interfejsa (vidi kasnije primer)

class Song {
    private artist:string;
    private title : string;

    constructor(artist:string, title:string){
        this.artist = artist;
        this.title = title;
    }
    public play() :void{
        console.log(`Playing ${this.title} by ${this.artist}`);
    }
}


class PlayList{
    public static readonly maxSongContent:number = 30;

    constructor(private songs:Song[] = []) {}

    public play() :void{
        if(this.songs.length == 0){
            console.log("Playlist is empty");
            return;
        }

        const song = this.songs.pop();
        song.play();
    }

    public sayHi():void{
        console.log("hi from regular playlist");
    }
}



// nasledjivanje obelezavamo sa extends
// konstruktor ove klase mora da bude kompatibilan sa konstruktorom nadklase
class RepeatingPlaylist extends PlayList{

    constructor(songs:Song[]){
        super(songs); // pozivanje kosntruktora nadklase
    }

    public playNextSong() :void{
        console.log("Playiong next song");
        super.play();
    }

    public sayHi():void{
        console.log("hi from repeating playlist");
    }
}



const songs:Song[] = [
    new Song("Arianga Grande", "7 rings"),
    new Song("Miley Cyrus", "7 things"),
    new Song("Lady Gaga", "Poker face")
];

// mozemo instancu podklase da cuvamo u promenljivoj tipa nadklase
const p:PlayList = new RepeatingPlaylist(songs);
p.sayHi();  // psotoji hijerarhijski polimorfizam, ako se u obe klase metode zovu isto, pozvace se ona 
            // cija se instanca zapravo cuva
            // u ovom primeru pisace 'hi from repeating'
            // ako bi zakomentarisali tu funkciju u RepeatingPlaylyst, pozvala bi se ona iz PlayList
