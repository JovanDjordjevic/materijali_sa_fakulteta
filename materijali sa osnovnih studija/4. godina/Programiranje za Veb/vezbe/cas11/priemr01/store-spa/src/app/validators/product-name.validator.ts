import { AbstractControl, ValidationErrors, ValidatorFn } from "@angular/forms";

// recimo da hocemo nas neki validator koji proverava da li se name sastoji samo od belina i brojeva

// validatorska funkcija mora da ima specifican oblik
// prihvata AbstractControl objekat i treba da vrati ValidationErrors objekat ili null
// tip | tip  je unija tipova, tj dodje kao neki std::variant, cesto se koristi npr za ovakve neke stvari
// gde treba da se vrati ili neki objekat ili greska
export const ProductNameValidator:ValidatorFn = (control: AbstractControl) : ValidationErrors | null => {
    // AbstractControl obejkat ima polje value gde zapravo mozemo da vidimo ono sto je prosledjeno ovoj funkciji
    const nameParts: string[] = control.value.trim().split(' ').filter( (namePart: string) => namePart.length > 0 );

    if (nameParts.length === 0) {
        // ValidationError objekat mi sami konstruisemo onako kako mi zelimo, nije nekog fiksnog oblika
        return {
            productName: {
                message: "Product name cannot consist of whitespace only!"
            }
        };
    }

    if(nameParts.every((namePart: string) => namePart.match(new RegExp("^[0-9\s]+$")))) {
        return {
            productName: {
                message: "Product name cannot be only digits!"
            }
        };
    }

    // ako je sve proslo okej treba da se vrati null
    return null;
}