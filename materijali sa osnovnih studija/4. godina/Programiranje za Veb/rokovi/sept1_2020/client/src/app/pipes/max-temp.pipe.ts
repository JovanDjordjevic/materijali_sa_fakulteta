import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'maxTemp'
})
export class MaxTempPipe implements PipeTransform {

  transform(value: number[]): number {
    let max : number = Number.MIN_VALUE;

    for(let val of value) {
      if (val > max) {
        max = val;
      }
    }

    return max;
  }

}
