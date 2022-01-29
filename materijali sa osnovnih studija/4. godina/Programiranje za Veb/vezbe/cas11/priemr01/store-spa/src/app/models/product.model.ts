export enum ProductPopularity{
    VeryPopular = 'Very popular',
    Popular = 'Popular',
    Average = 'Average',
    NotPopular = 'Not popular',   
}

export class Product {
    constructor(
        public name: string, 
        public description: string, 
        public price: number,
        public forSale: boolean,
        public imgUrl: string,
        public owner: string,
        public stars: number = 0, 
    ){}

    get popularity() : ProductPopularity {
        if(this.stars >= 9) {
            return ProductPopularity.VeryPopular;
        } else if(this.stars >= 7) {
            return ProductPopularity.Popular;
        } else if(this.stars >= 5) {
            return ProductPopularity.Average;
        } else {
            return ProductPopularity.NotPopular;
        }
    }
}