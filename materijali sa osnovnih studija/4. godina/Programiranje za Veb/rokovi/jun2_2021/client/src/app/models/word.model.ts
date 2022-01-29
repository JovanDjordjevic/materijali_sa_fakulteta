export enum Level {
    A = "A",
    B = "B",
    C = "C",
}

export class Word {
    _id : string = "";

    constructor(
        public word : string,
        public meaning : string,
        public level : Level,
        public examples : string[]
    ){}
}