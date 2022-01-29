import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { WordInfoWithFormComponent } from './components/word-info-with-form/word-info-with-form.component';
import { WordsByLevelComponentComponent } from './components/words-by-level-component/words-by-level-component.component';
import { WordsComponentComponent } from './components/words-component/words-component.component';

const routes: Routes = [
  {path: "", component: WordsComponentComponent},
  {path: "words/id/:wordId", component: WordInfoWithFormComponent},
  {path: "words/level/:level", component: WordsByLevelComponentComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
