import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Goal, Importance } from 'src/app/models/goal.model';
import { Step } from 'src/app/models/step.model';
import { GoalService } from 'src/app/services/goal.service';

@Component({
  selector: 'app-goal-form',
  templateUrl: './goal-form.component.html',
  styleUrls: ['./goal-form.component.css']
})
export class GoalFormComponent implements OnInit {

  goalForm : FormGroup;

  ImportanceEnum = Importance;

  // mrzi me da radim ispis gresaka

  constructor(private formBuilder : FormBuilder, private goalService : GoalService) {
    this.goalForm = this.formBuilder.group({
      name : ['', [Validators.required, Validators.maxLength(50)]],
      description : ['', [Validators.required, Validators.minLength(10), Validators.maxLength(100)]],
      importance : ['', [Validators.required]],
      step1 : ['', []],
      step2 : ['', []],
      step3 : ['', []],
      step4 : ['', []],
      step5 : ['', []],
    });
  }

  ngOnInit(): void {
  }

  onSubmitGoalForm() {
    if(!this.goalForm.valid) {
      window.alert('Some fileds have invalid values');
      return;
    }

    const formData = this.goalForm.value;

    let steps : Step[] = [];
    if (formData.step1 != '') {
      steps.push(new Step(1, formData.step1));
    }

    if (formData.step2 != '') {
      steps.push(new Step(2, formData.step2));
    }

    if (formData.step3 != '') {
      steps.push(new Step(3, formData.step3));
    }

    if (formData.step4 != '') {
      steps.push(new Step(4, formData.step1));
    }

    if (formData.step5 != '') {
      steps.push(new Step(5, formData.step5));
    }

    const newGoal = new Goal(formData.name, formData.description, formData.importance, steps);

    // zahtev
    this.goalService.addNewGoal(newGoal).subscribe((goal : Goal) => {
      console.log("added new:", goal);
    });
  }

}
