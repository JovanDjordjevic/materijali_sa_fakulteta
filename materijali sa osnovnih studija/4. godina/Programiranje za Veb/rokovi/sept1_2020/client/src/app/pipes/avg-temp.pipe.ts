import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'avgTemp'
})
export class AvgTempPipe implements PipeTransform {

  transform(value: number[]): number {

    let avg : number = 0;
    for(let val of value) {
      avg += val;
    }
    
    avg /= (value.length)
    avg = parseFloat(avg.toFixed(2));

    return avg;
  }

}
