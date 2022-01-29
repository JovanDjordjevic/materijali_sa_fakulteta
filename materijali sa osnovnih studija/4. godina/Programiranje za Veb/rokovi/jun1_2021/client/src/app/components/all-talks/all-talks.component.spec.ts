import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AllTalksComponent } from './all-talks.component';

describe('AllTalksComponent', () => {
  let component: AllTalksComponent;
  let fixture: ComponentFixture<AllTalksComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AllTalksComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(AllTalksComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
