import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Song } from 'src/app/models/song.model';
import { RequestServiceService } from 'src/app/services/request-service.service';

@Component({
  selector: 'app-playlist',
  templateUrl: './playlist.component.html',
  styleUrls: ['./playlist.component.css']
})
export class PlaylistComponent implements OnInit, OnDestroy {

  songs : Song[] = [];
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestServiceService) { }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onSortSelected(){
    const selectElem = document.getElementById('sortFilter');
    const sortParam = (selectElem as HTMLSelectElement).value;
    if (sortParam !== "none"){
      this.sub = this.requestService.sortBy(sortParam).subscribe((songs : Song[]) => {
        console.log(songs)
        this.songs = songs;
      });
    }
  }
}
