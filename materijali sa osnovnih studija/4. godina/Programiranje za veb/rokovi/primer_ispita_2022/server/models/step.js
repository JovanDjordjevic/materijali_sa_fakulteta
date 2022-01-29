const mongoose = require('mongoose');

const stepSchema = new mongoose.Schema({
    _id : mongoose.Schema.Types.ObjectId,
    cilj : {
        type : mongoose.Schema.Types.ObjectId,
        ref : 'goals'
    },
    redniBroj : mongoose.Schema.Types.Number,
    opis : mongoose.Schema.Types.String
});

const stepModel = mongoose.model('steps', stepSchema);

module.exports = stepModel;