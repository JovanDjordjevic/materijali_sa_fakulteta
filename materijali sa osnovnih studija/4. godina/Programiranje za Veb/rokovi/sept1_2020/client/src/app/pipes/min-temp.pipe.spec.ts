import { MinTempPipe } from './min-temp.pipe';

describe('MinTempPipe', () => {
  it('create an instance', () => {
    const pipe = new MinTempPipe();
    expect(pipe).toBeTruthy();
  });
});
