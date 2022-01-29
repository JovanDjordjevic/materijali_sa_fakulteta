import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { NewSongComponent } from './components/new-song/new-song.component';
import { PlaylistComponent } from './components/playlist/playlist.component';

const routes: Routes = [
  {path: "", component: PlaylistComponent},
  {path: "scrobble", component: NewSongComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
