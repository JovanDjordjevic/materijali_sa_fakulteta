const mongoose = require('mongoose');

const dessertSchema = new mongoose.Schema({
    _id : mongoose.Schema.Types.ObjectId,
    name : {
        type : mongoose.Schema.Types.String,
        require : true,
    },
    description : {
        type : mongoose.Schema.Types.String,
        require : true,
        maxLength : 200
    },
    complexity : {
        type : mongoose.Schema.Types.String,
        require : true,
        enum : ['easy', 'medium', 'hard']
    },
    nutrition : {
        type : mongoose.Schema.Types.Number,
        require : true,
    },
    glutenFree : mongoose.Schema.Types.Boolean
});

const DessertModel = mongoose.model('desserts', dessertSchema);

module.exports = DessertModel;