import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WordsComponentComponent } from './words-component.component';

describe('WordsComponentComponent', () => {
  let component: WordsComponentComponent;
  let fixture: ComponentFixture<WordsComponentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WordsComponentComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WordsComponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
