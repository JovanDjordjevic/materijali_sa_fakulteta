const mongoose = require('mongoose');

const songSchema = new mongoose.Schema({
    _id : mongoose.Schema.Types.ObjectId,
    artist : {
        type : mongoose.Schema.Types.String,
        require : true
    },
    title : {
        type : mongoose.Schema.Types.String,
        require : true
    },
    count : {
        type : mongoose.Schema.Types.Number,
        require : true,
        default : 1
    }
});

const SongModel = mongoose.model('songs', songSchema);

module.exports = SongModel;