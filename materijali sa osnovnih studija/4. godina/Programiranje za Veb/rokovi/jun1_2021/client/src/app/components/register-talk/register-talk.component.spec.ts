import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RegisterTalkComponent } from './register-talk.component';

describe('RegisterTalkComponent', () => {
  let component: RegisterTalkComponent;
  let fixture: ComponentFixture<RegisterTalkComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ RegisterTalkComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(RegisterTalkComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
