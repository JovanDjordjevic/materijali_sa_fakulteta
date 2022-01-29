const mongoose = require('mongoose');
const EventModel = require('../models/eventModel');

const getAllEventsInMonth = async (req, res, next) => {
    console.log('getAllEventsInMonth');
    const month = parseInt(req.params.month) + 1;

    if(!month || month < 1 || month > 12) {
        throw new Error("Invalid month parameter");
    }

    try{
        let events = await EventModel.find({}, {todo : 0}).exec();
        
        // unga bunga
        events = events.filter((event) => {
            [yyyy, mm, dd] = event.date.toISOString().slice(0, 10).split('-');
            //console.log(parseInt(yyyy), parseInt(mm), parseInt(dd))
            return parseInt(mm) == month && parseInt(dd) >= 1 && parseInt(dd) <= 31;
        });

        res.status(200).json(events);
    }
    catch(err) {
        next(err);
    }
}

const getEventById = async (req, res, next) => {
    console.log('getEventById')
    const id = req.params.id;

    if(!id) {
        throw new Error('Id invalid');
    }

    try{
        const event = await EventModel.findById(id).exec();
        res.status(200).json(event);
    }
    catch(err) {
        next(err);
    }
}

const addTodoStep = async (req, res, next) => {
    console.log('addTodoStep')
    const id = req.body.id;
    const step = req.body.step;

    if(!id || !step) {
        throw new Error("id or step invalid");
    }

    try{
        const event = await EventModel.findByIdAndUpdate(id, {$push: {todo : step}}, {new: true}).exec();
        res.status(200).json(event);
    }
    catch(err) {
        next(err);
    }
}

module.exports = {
    getAllEventsInMonth,
    getEventById,
    addTodoStep
};