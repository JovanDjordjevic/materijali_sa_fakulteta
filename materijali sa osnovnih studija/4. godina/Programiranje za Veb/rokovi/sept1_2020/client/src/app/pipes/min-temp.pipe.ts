import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'minTemp'
})
export class MinTempPipe implements PipeTransform {

  transform(value: number[], ...args: unknown[]): number {

    let min = Number.MAX_VALUE;
    for(let val of value) {
      if (val < min) {
        min = val;
      }
    }

    return min;
  }

}
