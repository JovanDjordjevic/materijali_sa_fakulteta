import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NewKanbanComponent } from './new-kanban.component';

describe('NewKanbanComponent', () => {
  let component: NewKanbanComponent;
  let fixture: ComponentFixture<NewKanbanComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ NewKanbanComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(NewKanbanComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
