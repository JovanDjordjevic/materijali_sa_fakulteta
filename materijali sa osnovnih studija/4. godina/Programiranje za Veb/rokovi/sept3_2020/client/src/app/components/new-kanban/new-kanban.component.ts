import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';
import { Kanban } from 'src/app/models/kanban.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-new-kanban',
  templateUrl: './new-kanban.component.html',
  styleUrls: ['./new-kanban.component.css']
})
export class NewKanbanComponent implements OnInit, OnDestroy {

  kanbanForm : FormGroup;
  sub : Subscription = new Subscription();

  constructor(private formBuilder : FormBuilder, private requestService : RequestService) {
    this.kanbanForm = this.formBuilder.group({
      title : ['', [Validators.required]],
      description : ['', [Validators.required]],
      numOfSubtasks : ['', [Validators.required, Validators.min(5)]],
    });
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onSubmitKanbanForm(){
    if(!this.kanbanForm.valid) {
      window.alert('The form is not valid');
      return;
    }

    //zahtev
    const formData = this.kanbanForm.value;
    const newKanban = new Kanban(formData.title, formData.description, formData.numOfSubtasks, 0);
    this.sub = this.requestService.addNewKanban(newKanban).subscribe((msg : string) => {
      window.alert(msg);
      this.kanbanForm.reset();
    });
  }

}
