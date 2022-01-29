import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WordInfoWithFormComponent } from './word-info-with-form.component';

describe('WordInfoWithFormComponent', () => {
  let component: WordInfoWithFormComponent;
  let fixture: ComponentFixture<WordInfoWithFormComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WordInfoWithFormComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WordInfoWithFormComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
