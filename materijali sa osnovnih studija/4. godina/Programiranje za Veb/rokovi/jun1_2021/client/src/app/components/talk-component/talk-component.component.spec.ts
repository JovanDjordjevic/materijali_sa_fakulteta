import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TalkComponentComponent } from './talk-component.component';

describe('TalkComponentComponent', () => {
  let component: TalkComponentComponent;
  let fixture: ComponentFixture<TalkComponentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TalkComponentComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TalkComponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
