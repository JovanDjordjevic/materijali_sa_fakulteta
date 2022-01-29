import { Product } from "./product.model";

// ovaj interfejs pravimo tako moze da sadrzi podatke u obliku u kom ih dobija http zahtev
// posalji postman zahtev na   .../api/products da vidis
export interface ProductPagiantion {
    docs : Product[],   // sam niz proizvoda
    totalDocs : number,  // i neki pomocni parametri koje server vraca ...
    limit : number,
    totalPages : number,
    page : number, 
    pagingCounter : number,
    hasPrevPage : boolean, 
    hasNextPage : boolean,
    prevPage : number | null,
    nextPage : number | null
}