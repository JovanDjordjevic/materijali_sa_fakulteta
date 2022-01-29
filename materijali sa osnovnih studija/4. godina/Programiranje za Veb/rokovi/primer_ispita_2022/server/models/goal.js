const mongoose = require('mongoose');

const goalSchema = new mongoose.Schema({
    _id : mongoose.Schema.Types.ObjectId,
    naziv : mongoose.Schema.Types.String,
    opis :  mongoose.Schema.Types.String,
    vaznost : {
        type : mongoose.Schema.Types.Number,
        enum : [1, 2, 3]
    }
});

const goalModel = mongoose.model('goals', goalSchema);

module.exports = goalModel;
