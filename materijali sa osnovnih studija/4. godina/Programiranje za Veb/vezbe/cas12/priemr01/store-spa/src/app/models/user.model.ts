export class User {
    public id :string;  // dodali ovaj cas
    public username: string;   
    public name: string;
    public email: string;
    public imgUrl: string;

    constructor(id :string, username: string, name: string, email: string, imgUrl: string) {
        this.id = id;
        this.username = username;  
        this.name = name;
        this.email = email;
        this.imgUrl = imgUrl;
    }

    public getImageUrl() : string {
        return "http://localhost:3000/" + this.imgUrl;
    }
}

