export enum Area {
    Angular = "Angular",
    Node = "Node.js",
    JS = "JavaScript practices and tools"
}

export class Talk{
    public id : string = "";

    constructor(
        public title : string,
        public speaker : string,
        public area : Area,
        public duration : number
    ){}
}