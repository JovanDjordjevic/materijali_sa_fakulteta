import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ToDoComponentComponent } from './to-do-component.component';

describe('ToDoComponentComponent', () => {
  let component: ToDoComponentComponent;
  let fixture: ComponentFixture<ToDoComponentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ToDoComponentComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ToDoComponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
