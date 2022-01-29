import { Component, EventEmitter, OnInit, Output } from '@angular/core';
import { FormBuilder, FormGroup, ValidationErrors, Validators } from '@angular/forms';
import { Product } from 'src/app/models/product.model';
import { ProductNameValidator } from 'src/app/validators/product-name.validator';
import { ProductState } from '../../models/product-state';

declare const $: any;

@Component({
  selector: 'app-create-product',
  templateUrl: './create-product.component.html',
  styleUrls: ['./create-product.component.css']
})
export class CreateProductComponent implements OnInit {

  createProductForm: FormGroup;

  ProductStateEnum = ProductState;

  @Output() productCreated: EventEmitter<Product> = new EventEmitter<Product>();

  constructor(private formBuilder: FormBuilder) { 
    this.createProductForm = this.formBuilder.group({
      name: ['', [Validators.required, Validators.minLength(10), ProductNameValidator]],
      price: [0, [Validators.required, Validators.min(10)]],
      description: ['', [Validators.required, Validators.maxLength(200)]],
      forSale: [false, [Validators.required]],
      state: [null, [Validators.required]],
    });
  }

  ngOnInit(): void {
    $('.ui.checkbox').checkbox();
    $('.ui.radio.checkbox').checkbox();
  }

  onCreateProductFormSubmit() {
    if (this.createProductForm.invalid) {
      window.alert('Some the fields do not have valid values!');
      return;
    }

    const data = this.createProductForm.value;

    const newProduct = new Product('', data.name, data.description, data.price, data.forSale, null, '', 200, '');
    this.productCreated.emit(newProduct);

    this.createProductForm.reset({ name: '', price: 0, description: '', forSale: false, state: null });
  }

  nameHasErrors(): boolean {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('name')?.errors;

    return errors !== null;
  }

  priceHasErrors(): boolean {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('price')?.errors;

    return errors !== null;
  }

  descriptionHasErrors(): boolean {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('description')?.errors;

    return errors !== null;
  }

  forSaleHasErrors(): boolean {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('forSale')?.errors;

    return errors !== null;
  }

  stateHasErrors(): boolean {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('state')?.errors;

    return errors !== null;
  }

  nameErrors(): string[] {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('name')?.errors;

    // Svaki put kada definisemo nesto kao uniju vise tipova, kada zelimo da nastavimo da ga koristimo
    // kao da je samo jedan od tih tipova, moramo SUZITI odlucivanje tipova za TS. Ako otkomentarisete
    // sledecu liniju i hover-ujete iznad 'errors'...
    // console.log(errors);
    // ...videcete da je tip promenljive 'errors' ova unija kao iznad. Medjutim, posle if-a ispod, 
    // ako hover-ujete iznad promenljive 'errors', videcete da je njen tip samo ValidationErrors.
    // Ovim if-om smo proverili da li je 'errors' null ili undefined. Kada kazemo == null, to obuhvata
    // i null i undefined, a ako hocemo da proveravamo sa ===, onda ce uslov biti:
    // errors === null || errors === undefined.
    // TS zna da 'errors' nakon if-a sigurno nece biti null i undefined, jer smo proverili, pa ga u 
    // nastavku mozemo koristiti kao da je njegov tip samo ValidationErrors.

    if (errors == null) {
      return [];
    }

    // console.log(errors);

    const errorMsgs: string[] = [];

    // Od Typescript 4.2 (ako pogledate u package.json fajlu videcete da mi koristimo 4.4), podrazumevano je flag
    // --noPropertyAccessFromIndexSignature podesen na true. Vise o tome zasto i kako ovaj flag funkcionise, 
    // mozete pogledati na ovom linku:
    // https://devblogs.microsoft.com/typescript/announcing-typescript-4-2/#no-property-access-index-signature
    // Ukratko, on zabranjuje pristup preko tacka notacije, za ona polja koja mozda nisu definisana u objektu
    // (tacnije, izbacuje RuntimeError, a inace bi to polje jednostavno bilo undefined). Ovo je nesto sto se 
    // podesava na nivou tipa, sto mozete videti ako pogledate kako je implementiran tip ValidationErrors.
    // Posto kod nas polja kojima pristupamo u 'errors' objektu dolaze iz razlicitih validacija, struktura tog
    // objekta nece uvek biti ista, pa zbog toga neka polja nekada nece biti definisana. 
    
    // Ovo nije nesto cime smo se bavili na casu, tako da cemo mi ovaj flag podesiti na false u tsconfig.json fajlu.
    // Kod ispod prikazuje kako bismo implementirali dohvatanje tih polja u slucaju kada je on ukljucen, a ispod
    // je implementacija bez ukljucenog flega, koju cemo mi koristiti.

    // if (errors['required']) {
    //   errorMsgs.push('Product must have a name.');
    // }

    // if (errors['minlength']) {
    //   errorMsgs.push(`Product name is ${errors['minlength'].actualLength} characters long, when it should be at least ${errors['minlength'].requiredLength} characters.`);
    // }

    // if(errors['productName']) {
    //   errorMsgs.push(errors['productName'].message);
    // }

    if (errors.required) {
      errorMsgs.push('Product must have a name.');
    }

    if (errors.minlength) {
      errorMsgs.push(`Product name is ${errors.minlength.actualLength} characters long, when it should be at least ${errors.minlength.requiredLength} characters.`);
    }

    if(errors.productName) {
      errorMsgs.push(errors.productName.message);
    }

    return errorMsgs;
  }

  priceErrors(): string[] {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('price')?.errors;

    if (errors == null) {
      return [];
    }

    let errorMsgs: string[] = [];

    if (errors.min) {
      errorMsgs.push(`Price should be at least ${errors.min.min} dollars!`);
    }

    return errorMsgs;
  }

  descriptionErrors(): string[] {
    const errors: ValidationErrors | null | undefined = this.createProductForm.get('description')?.errors;

    if (errors == null) {
      return [];
    }

    let errorMsgs: string[] = [];

    if (errors.required) {
      errorMsgs.push('Description can\'t be empty!');
    }

    if (errors.maxlength) {
      errorMsgs.push('Description can\'t be longer than 200 characters!');
    }

    return errorMsgs;
  }

}
