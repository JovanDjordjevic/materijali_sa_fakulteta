import { AbstractControl, ValidationErrors, ValidatorFn } from "@angular/forms";

export const ProductNameValidator: ValidatorFn = (control: AbstractControl): ValidationErrors | null => {
    const nameParts: string[] = control.value.trim().split(' ')
        .filter((namePart: string) => namePart.trim().length > 0);

    if (nameParts.length === 0) {
        return {
            productName: {
                message: "Product name cannot consist of whitespaces only!"
            }
        }
    }

    if (nameParts.every((namePart: string) => namePart.match(new RegExp("^[0-9\s]+$")))) {
        return {
            productName: {
                message: "Product name cannot be only digits!"
            }
        }
    }

    return null;
}