export class Dessert{
    public _id : string = "";

    constructor(
        public name : string,
        public description : string,
        public complexity : string,
        public nutrition : number,
        public glutenFree : boolean = false // nigde ne kaze da ne smem ovo da uradim
    ){}
}