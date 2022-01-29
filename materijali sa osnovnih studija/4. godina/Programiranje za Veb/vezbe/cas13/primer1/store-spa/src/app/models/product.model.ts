import { User } from "./user.model";

export enum ProductPopularity {
    VeryPopular = 'Very Popular',
    Popular = 'Popular',
    Average = 'Average',
    NotPopular = 'Not popular',
};

export class Product {
    constructor(
        public _id: string,
        public name: string,
        public description: string,
        public price: number,
        public forSale: boolean,
        public owner: User | null,
        public imgUrl: string = '../assets/default-product.jpg',
        public stars: number = 0,
        public timestamp: string,
    ) {}

    get popularity(): ProductPopularity {
        if (this.stars >= 200) {
            return ProductPopularity.VeryPopular;
        } else if (this.stars >= 100) {
            return ProductPopularity.Popular;
        } else if (this.stars >= 50) {
            return ProductPopularity.Average;
        } else {
            return ProductPopularity.NotPopular;
        }
    }
}