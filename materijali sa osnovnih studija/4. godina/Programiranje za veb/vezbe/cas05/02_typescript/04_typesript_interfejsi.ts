// slicno kao interfejsi u javi,
// ovo I ispred je samo konvencija
interface IPoint{
    x:number;
    y:number;
}   

interface IPassenger{
    name:string;
}

interface IVehicle{
    currentLocation:IPoint;
    travelTo(point:IPoint): void;
    addPassenger(passenger:IPassenger):void;
    removePassenger(passenger:IPassenger):void;
}


// ocekivali bismo da moramo da interfejs implementiramo u nekoj klasi
// ali u TS mozemo da implementiramo interfejs i kroz neki objekat
// nista ovde nismo nasledili/implementirali, bitno je samo da ovaj objekat zadovoljava uslove koje interfejs namece
// tsc u prevodu ignorise sve ove interfejse
// ako nas objekat ne zadovoljava interfejs, npr ako bi ovde falilo y, dobili bi TS gresku, ali bi se i dalje dobio neki validni JS kod
const p:IPoint = {x:10, y:5};

// interfejs mozemo da implementiramo i na standardni nacin u klasi
class Vehicle implements IVehicle{
    //...
}