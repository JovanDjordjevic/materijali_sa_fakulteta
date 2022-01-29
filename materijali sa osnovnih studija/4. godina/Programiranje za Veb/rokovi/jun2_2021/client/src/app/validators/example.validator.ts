import { AbstractControl, ValidationErrors, ValidatorFn } from "@angular/forms";

export const ExampleValidator : ValidatorFn = (control : AbstractControl) : ValidationErrors | null => {
    const data : string = control.value.trim();

    if(data[0] === data[0].toLowerCase()){
        return {
            exampleValidationError: {
                message : "Example must start with an uppercase letter"
            }
        };
    }

    return null;
}