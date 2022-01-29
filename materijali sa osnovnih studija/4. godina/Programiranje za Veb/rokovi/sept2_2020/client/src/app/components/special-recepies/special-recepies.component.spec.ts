import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SpecialRecepiesComponent } from './special-recepies.component';

describe('SpecialRecepiesComponent', () => {
  let component: SpecialRecepiesComponent;
  let fixture: ComponentFixture<SpecialRecepiesComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ SpecialRecepiesComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(SpecialRecepiesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
