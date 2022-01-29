const mongoose = require('mongoose');

const TalkSchema = new mongoose.Schema({
    _id : {
        type: mongoose.Schema.Types.ObjectId,
        required : true    
    },
    title : {
        type: mongoose.Schema.Types.String,
        required : true,
        maxLength : 100 
    },
    speaker : {
        type: mongoose.Schema.Types.String,
        required : true,
        maxLength : 50    
    },
    area : {
        type : mongoose.Schema.Types.String,
        required : true ,
        enum : ['Angular', 'Node.js', 'JavaScript practices and tools']
    },
    duration : {
        type: mongoose.Schema.Types.Number,
        required : true,
        min : 0,
        max : 3 
    },
});

const TalkModel = mongoose.model('talks', TalkSchema)

module.exports = TalkModel;