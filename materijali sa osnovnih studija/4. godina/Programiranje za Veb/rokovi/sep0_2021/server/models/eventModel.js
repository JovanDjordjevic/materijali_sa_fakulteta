const mongoose = require('mongoose');

const eventSchema = new mongoose.Schema({
    _id : {
        type : mongoose.Schema.Types.ObjectId,
        require : true
    },
    title : {
        type : mongoose.Schema.Types.String,
        require : true
    },
    date : {
        type : mongoose.Schema.Types.Date,
        require : true
    },
    duration : {
        type : mongoose.Schema.Types.Number,
        require : true
    },
    todo : {
        type : [mongoose.Schema.Types.String],
        require : true
    }
});

const EventModel = mongoose.model('events', eventSchema);

module.exports = EventModel;