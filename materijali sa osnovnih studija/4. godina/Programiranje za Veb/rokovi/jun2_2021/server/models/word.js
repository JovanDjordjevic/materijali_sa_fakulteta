const mongoose = require('mongoose');

const wordSchema = new mongoose.Schema({
    _id : {
        type : mongoose.Schema.Types.ObjectId,
        require : true,
    },
    word : {
        type : mongoose.Schema.Types.String,
        require  : true,
        maxLength : 50
    },
    meaning : {
        type : mongoose.Schema.Types.String,
        require : true,
        maxLength : 100
    },
    level : {
        type : mongoose.Schema.Types.String,
        require : true,
        enum : ['A', 'B', 'C']
    },
    examples : {
        type : [mongoose.Schema.Types.String],
        require : true,
    }
});

const WordModel = mongoose.model('words', wordSchema);

module.exports = WordModel;