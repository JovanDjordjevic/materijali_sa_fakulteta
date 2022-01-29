// imamo kljucnu rec abstract
// ovakva klasa mora imati konstruktor (?) i bvarem jedan abstraktni metod
abstract class Vehicle{
    constructor(){}

    // abstraktna funkcija mora da se navede sa kljucnom reci abstract (eventualno pre nje moze neki access modifier )
    public abstract driveToPoint();
}


class Car extends Vehicle{
    driveToPoint(){
        // ovde mora da se implementira...
    }
}