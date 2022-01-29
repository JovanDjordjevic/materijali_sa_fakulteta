export class User {
    constructor(public id: string,
                public username: string, 
                public name: string, 
                public email: string, 
                public imgUrl: string) {} 

    getImageUrl(): string {
        return 'http://localhost:3000/' + this.imgUrl;
    }
}