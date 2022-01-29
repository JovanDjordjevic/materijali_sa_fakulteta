import { Component, ElementRef, EventEmitter, OnInit, Output, ViewChild } from '@angular/core'; // ElementRef, EventEmitter, Output, ViewChild
import { Product } from 'src/app/models/product.model';

// ne zaboravimo ovu liniju da bi nam radio jquery izraz u ngOnInit
declare const $: any;

@Component({
  selector: 'app-create-product',
  templateUrl: './create-product.component.html',
  styleUrls: ['./create-product.component.css']
})
export class CreateProductComponent implements OnInit {

  // u htmlu smo za input postavili referencne promenljive. Ovde treba nekako da ih dohvatimo. Njihov tip mora da bude ElementRef
  // takodje moramo da dodamo i ovaj dekorater ViewChild, argumenti su mu ime_ref_promenljive (bas onako stoje u html bez #) i objekat 
  // sa nmekim podesavanjima, nije nam to mnogo bitno sad, recimo samo da treba ovako sa static:true
  // u nekom od metoda ispod cemo dohvatiti vrednosti ovih elemenata
  @ViewChild('inputName', {static:true}) inputName: ElementRef  = {} as ElementRef;     // NOTE: nije na vezbama objasnjeno zasto mora ovo = {} as ElementRef (??) 
  // isto i za ostale
  @ViewChild('inputPrice', {static:true}) inputPrice: ElementRef  = {} as ElementRef;
  @ViewChild('inputDescription', {static:true}) inputDescription: ElementRef  = {} as ElementRef;
  @ViewChild('inputForSale', {static:true}) inputForSale: ElementRef  = {} as ElementRef;

  // promenljiva koja ce da salje podatak 'napolje' tj ka parentu, mora da bude bas tipa EventEmmiter<top_koji_se_salje>
  // mora i da ima dekorator 
  @Output() productCreated: EventEmitter<Product> = new EventEmitter<Product>();

  constructor() { }

  ngOnInit(): void {
    // kada smo napravili ovu kompoenntu, videli smo da checkbox ne radi, pa izguglamo zasto i nadjemo ovaj jquery kod
    $('.ui.checkbox').checkbox();
  }

  addNewProduct(){
    // da bi dohvatili podatak iz ElementRef promenljive, moramo da dohvatimo i underlying element, to radimo sa nativeElement
    // pominjali smo na proslom casu, ovo mora da se prvo castuje u HTMLInputElement zato sto native element moze biti bilo sta, tj nesto sto uopste ne mora
    // da ima svojstvo value 
    const name: string = (this.inputName.nativeElement as HTMLInputElement).value;
    const price: number = Number.parseFloat((this.inputPrice.nativeElement as HTMLInputElement).value); // ovaj vraca broj pa mora da se parsira u string
    const description: string = (this.inputDescription.nativeElement as HTMLInputElement).value;
    const forSale: boolean = (this.inputForSale.nativeElement as HTMLInputElement).checked;   // ovaj ima checked jer je u pitanju checkbox

    // neka kratka validacija
    if (name === '' || Number.isNaN(price) || description==='') {
      window.alert("Some required fields are missing");
      return;
    }

    // kreiramo novi proizvod koji ce se ubaciti u "bazu"
    const newProduct: Product = new Product(name, description, price, forSale, 'assets/default-product.png', 'Pera Peric', 90);

    // da bismo poslali ovaj podatak u parent, koristimo vezivanje dogadjaja
    // moramo u detetu specificno da naglasimo da se emituje dogadjaj, to radimo iz one EventEmitter promenljive koju smo napravili
    // u zagradi je ono sto saljemo
    this.productCreated.emit(newProduct);
  }
}
