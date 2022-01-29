export class Meteo {
    public _id : string = "";

    constructor(
        public city : string,
        public country : string,
        public temperatures : number[]
    ){}
}