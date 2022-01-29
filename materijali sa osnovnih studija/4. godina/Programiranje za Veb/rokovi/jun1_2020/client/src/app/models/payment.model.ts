export class Payment{
    public _id : string = '';

    constructor(
        public name : string,
        public surname : string,
        public email : string,
        public amounts : number[],
    ){}
}