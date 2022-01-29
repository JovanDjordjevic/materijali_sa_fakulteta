export class User {
    public username: string;    // dodali ovaj cas
    public name: string;
    public email: string;
    public imgUrl: string;

    constructor(username: string, name: string, email: string, imgUrl: string) {
        this.username = username;  
        this.name = name;
        this.email = email;
        this.imgUrl = imgUrl;
    }
}