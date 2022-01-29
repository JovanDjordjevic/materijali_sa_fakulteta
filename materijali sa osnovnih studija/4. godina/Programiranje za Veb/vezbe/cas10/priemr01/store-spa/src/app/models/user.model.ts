export class User {
    public name: string;
    public email: string;
    public imgUrl: string;

    constructor(name: string, email: string, imgUrl: string) {
        this.name = name;
        this.email = email;
        this.imgUrl = imgUrl;
    }
}