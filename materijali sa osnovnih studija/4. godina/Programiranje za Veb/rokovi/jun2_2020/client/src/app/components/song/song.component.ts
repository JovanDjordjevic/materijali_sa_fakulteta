import { Component, Input, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Song } from 'src/app/models/song.model';
import { RequestServiceService } from 'src/app/services/request-service.service';

@Component({
  selector: 'app-song',
  templateUrl: './song.component.html',
  styleUrls: ['./song.component.css']
})
export class SongComponent implements OnInit, OnDestroy {

  @Input() song : Song;
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestServiceService) {
    this.song = new Song("", "", 0);
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onClickBtn(){
    this.sub = this.requestService.incrementCountForSong(this.song._id).subscribe((song : Song) => {
      this.song = song;
    });
  }
}
