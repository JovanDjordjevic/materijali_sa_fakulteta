import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MeteoDetailsComponent } from './meteo-details.component';

describe('MeteoDetailsComponent', () => {
  let component: MeteoDetailsComponent;
  let fixture: ComponentFixture<MeteoDetailsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ MeteoDetailsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(MeteoDetailsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
