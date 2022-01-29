import { ProductSumPipe } from './product-sum.pipe';

describe('ProductSumPipe', () => {
  it('create an instance', () => {
    const pipe = new ProductSumPipe();
    expect(pipe).toBeTruthy();
  });
});
