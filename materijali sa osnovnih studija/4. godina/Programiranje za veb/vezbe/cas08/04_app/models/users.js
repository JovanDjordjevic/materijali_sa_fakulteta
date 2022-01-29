// ideja je da u ovom folderu budu sheme za kolekcije (?)
const mongoose = require('mongoose');

// iskoristicemo istu shemu iz proslog primera
const usersSchema = new mongoose.Schema({
    _id: mongoose.Schema.Types.ObjectId,
    username: {   
        type: String, 
        required: true,
    },
    email: {
        type: String, 
        required: true,
    },
    status: {
        type: String,
        default: 'active',
    },
    password: {
        type: String,
        required: true,
    },
    age: Number,   
    progSkills: [String],   
});

const userModel = mongoose.model('users', usersSchema);

// potrebno je da sada ovu shemu exportujemo jer cemo nad njom pozivati odgovarajuce funkcije
// iz upita (ovde vise necemo implementirati neke stvari rucno vec cemo korsititi ugradjene mogucnosti baze)
module.exports = userModel;