const mongoose = require('mongoose');
const SongModel = require('../models/song');

const sortBy = async (req, res, next) => {
    console.log("sortBy");
    const sortParam = (req.params.sortBy).toLowerCase();

    if(!sortParam || (sortParam !== 'artist' && sortParam !== 'title' && sortParam !== 'count')) {
        throw new Error("wrong sorting parameter");
    }

    try{
        let songs = []
        switch (sortParam) {
            case 'artist':
                songs = await SongModel.find({}).sort({artist : 1}).exec();
                break;
            case 'title':
                songs = await SongModel.find({}).sort({title : 1}).exec();
                break;
            case 'count':
                //
                songs = await SongModel.find({}).sort({count : 1}).exec();
                break;
            default:
                break;
        }
        
        res.status(200).json(songs);
    }
    catch(err) {
        next(err);
    }
}

const incrementCountForSong = async (req, res, next) => {
    console.log("incrementCountForSong");
    const id = req.body.id;

    if(!id) {
        throw new Error('invalid id');
    }

    try{
        const song = await SongModel.findByIdAndUpdate(id, {$inc: {count : 1}}, {new : true}).exec();
        res.status(200).json(song);
    }
    catch(err){
        next(err);
    }
}

const addNewSong = async (req, res, next) => {
    console.log("addNewSong");
    const title = req.body.title;
    const artist = req.body.artist;

    if(!title || !artist) {
        throw new Error("title or artist invalid");
    }

    try{
        const song = await SongModel.findOne({title : title, artist : artist}).exec();
        if(song) {
            res.status(309).json("The song already exists! Try again!”");
        }
        else {
            const newSong = new SongModel({
                _id : new mongoose.Types.ObjectId(),
                artist : artist,
                title : title,
                count : 1
            });

            const savedSong = await newSong.save();
            res.status(201).json("The song has successfully been scrobbled!");
        }
    }
    catch(err){
        next(err);
    }
}

module.exports = {
    sortBy,
    incrementCountForSong,
    addNewSong
}