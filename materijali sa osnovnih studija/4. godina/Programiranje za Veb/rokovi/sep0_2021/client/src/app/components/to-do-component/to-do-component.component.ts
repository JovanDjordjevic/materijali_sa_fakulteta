import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Happening } from 'src/app/models/happening.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-to-do-component',
  templateUrl: './to-do-component.component.html',
  styleUrls: ['./to-do-component.component.css']
})
export class ToDoComponentComponent implements OnInit {

  @Input() id : string = "";
  todoItemForm : FormGroup;
  @Output() updatedTodos : EventEmitter<string[]>= new EventEmitter();

  constructor(private formBuilder : FormBuilder, private requestService : RequestService) { 
    this.todoItemForm = this.formBuilder.group({
      step : ['Do stuff', [Validators.required, Validators.minLength(10)]]
    });
  }

  ngOnInit(): void {
  }

  onTodoItemFormSubmit(){
    if(!this.todoItemForm.valid) {
      window.alert("The form is invalid");
      return;
    }

    const formData = this.todoItemForm.value;
    this.requestService.addTodoForEvent(this.id, formData.step).subscribe((happening : Happening) => {
      this.todoItemForm.reset();
      this.updatedTodos.emit(happening.todo);
    });
  }

}
