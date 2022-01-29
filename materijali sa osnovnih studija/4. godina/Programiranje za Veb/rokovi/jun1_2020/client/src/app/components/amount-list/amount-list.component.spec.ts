import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AmountListComponent } from './amount-list.component';

describe('AmountListComponent', () => {
  let component: AmountListComponent;
  let fixture: ComponentFixture<AmountListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AmountListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(AmountListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
