//Happening da se nebi zvao Event
export class Happening {
    public _id : string = "";

    constructor(
        public title : string,
        public date : Date,
        public duration : number,
        public todo : string[]
    ){}
}