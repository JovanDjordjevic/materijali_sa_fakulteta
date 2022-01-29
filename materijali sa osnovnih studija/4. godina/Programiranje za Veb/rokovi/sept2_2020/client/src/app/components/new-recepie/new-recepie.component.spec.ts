import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NewRecepieComponent } from './new-recepie.component';

describe('NewRecepieComponent', () => {
  let component: NewRecepieComponent;
  let fixture: ComponentFixture<NewRecepieComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ NewRecepieComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(NewRecepieComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
