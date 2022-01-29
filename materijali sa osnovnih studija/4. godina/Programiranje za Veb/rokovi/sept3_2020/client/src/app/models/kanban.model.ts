export class Kanban{
    public _id : string = "";

    constructor(
        public title : string,
        public description : string,
        public numOfSubtasks : number,
        public completedSubtasks : number = 0,
    ){}
};