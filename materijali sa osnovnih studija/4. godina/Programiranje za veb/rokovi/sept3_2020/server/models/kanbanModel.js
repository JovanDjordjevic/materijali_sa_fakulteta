const mongoose = require('mongoose');

const kanbanSchema = mongoose.Schema({
    _id : {
        type : mongoose.Schema.Types.ObjectId,
        require : true
    },
    title : {
        type : mongoose.Schema.Types.String,
        require : true
    },
    description : {
        type : mongoose.Schema.Types.String,
        require : true
    },
    numOfSubtasks : {
        type : mongoose.Schema.Types.Number,
        require : true
    },
    // NOTE: u tekstu zadataka naziva ovo completedTasks, a u json podacima se zove completedSubtasks
    completedSubtasks : {
        type : mongoose.Schema.Types.Number,
        require : true,
        default : 0
    },
});

const kanbanModel = mongoose.model('Kanban', kanbanSchema);

module.exports = kanbanModel;