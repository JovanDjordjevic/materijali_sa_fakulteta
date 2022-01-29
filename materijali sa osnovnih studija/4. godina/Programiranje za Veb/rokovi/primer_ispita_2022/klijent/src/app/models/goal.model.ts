import { Step } from "./step.model";

export enum Importance{
    VeryImportant = 1,
    MildlyImportant = 2,
    LessImportant = 3,
}

export class Goal{
    
    public _id : string = "";

    constructor(
        public naziv : string,
        public opis : string,
        public vaznost : Importance,
        public koraci : Step[]
    ){}
};