import { MaxTempPipe } from './max-temp.pipe';

describe('MaxTempPipe', () => {
  it('create an instance', () => {
    const pipe = new MaxTempPipe();
    expect(pipe).toBeTruthy();
  });
});
