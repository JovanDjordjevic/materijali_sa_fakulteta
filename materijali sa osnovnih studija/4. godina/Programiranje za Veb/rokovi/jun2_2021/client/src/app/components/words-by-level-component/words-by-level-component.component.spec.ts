import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WordsByLevelComponentComponent } from './words-by-level-component.component';

describe('WordsByLevelComponentComponent', () => {
  let component: WordsByLevelComponentComponent;
  let fixture: ComponentFixture<WordsByLevelComponentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WordsByLevelComponentComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WordsByLevelComponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
