const mongoose = require('mongoose');
const Kanban = require('../models/kanbanModel');

const getAllUnfinished = async (req, res, next) => {
    console.log("getAllUnfinished");

    try{
        const kanbans = await Kanban.find({$expr : {$lt : ['$completedSubtasks', '$numOfSubtasks']}}).sort({numOfSubtasks : 1}).exec();
        res.status(200).json(kanbans);
    }
    catch(err) {
        next(err);
    }
}

const addNewKanban = async (req, res, next) => {
    console.log("addNewKanban");
    const {title, description, completedSubtasks, numOfSubtasks} = req.body.kanban;

    if(!title || !description || !numOfSubtasks) {
        throw new Error("Some parameters are undefined");
    }

    try{
        const kanban = await Kanban.findOne({title : title}).exec();
        if (kanban) {
            res.status(400).json("The kanban with the same title already exists!");
        }
        else {
            const newKanban = new Kanban({
                _id : new mongoose.Types.ObjectId(),
                title : title,
                description : description,
                completedSubtasks : completedSubtasks,
                numOfSubtasks : numOfSubtasks,
            });

            await newKanban.save();
            res.status(200).json("The kanban is successfully created!");
        }
    }
    catch (err) {
        next(err);
    }
}

const updateKanbanWithId = async (req, res, next) => {
    console.log("updateKanbanWithId");
    const id = req.params.id;

    if(!id) {
        throw new Error("Undefined id parameter");
    }

    try{
        const kanban = await Kanban.findById(id).exec();
        if (!kanban) {
            res.status(404).json(`The kanban with id ${id} does not exist!`);
        }
        else {
            const updatedKanban = await Kanban.findByIdAndUpdate(id, {$inc : {completedSubtasks : 1}}, {new : true}).exec();
            res.status(200).json(` A progress was made on kandan with id ${id} !`)
        }
    }
    catch(err){
        next(err);
    }
}


module.exports = {
    getAllUnfinished,
    addNewKanban,
    updateKanbanWithId
}