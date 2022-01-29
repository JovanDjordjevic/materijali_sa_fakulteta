const GoalModel = require('../models/goal');
const StepModel = require('../models/step');
const moongoose = require('mongoose');

const getAllGoals = async (req, res, next) => {
    //console.log('getAllGoals');
    try{
        const allGoals = await GoalModel.find({}).exec();
        
        let allGoalsClientModel = [];

        for(goal of allGoals) {
            const steps = await StepModel.find({cilj : goal._id}).exec();
            const goalClientModel = {
                _id : goal._id,
                naziv : goal.naziv,
                opis : goal.opis,
                vaznost : goal.vaznost,
                koraci : steps
            }
            
            allGoalsClientModel.push(goalClientModel);
        }

        //console.log(allGoalsClientModel);
        res.status(200).json(allGoalsClientModel);
    }catch(err){
        next(err);
    }
};

const getGoalById = async (req, res, next) => {
    console.log('getGoalById');
    //console.log(req)
    const id = req.params.id;
    //console.log("id", id);

    if(!id){
        const message = "Korisnik nije prosledio id";
        res.status(400).json(message);
    }
    else {
        try {
            const goal = await GoalModel.findById(id).exec();
            const steps = await StepModel.find({cilj : goal._id}).exec();

            const goalClientModel = {
                _id : goal._id,
                naziv : goal.naziv,
                opis : goal.opis,
                vaznost : goal.vaznost,
                koraci : steps
            }

            //console.log(goal);
            res.status(200).json(goalClientModel);
        }
        catch (err){
            next(err);
        }
    }
};

const addNewGoal = async (req, res, next) => {
    console.log('addNewGoal');
    //console.log(req.body.goal)
    const {naziv, opis, vaznost, koraci} = req.body.goal;

    if(!naziv || !opis || !vaznost){
        const message = "Korisnik nije prosledio validne podatke";
        res.status(400).json(message);
    }
    else {
        try {
            const goalId = new moongoose.Types.ObjectId();

            const newGoal = new GoalModel({
                _id : goalId,
                naziv : naziv,
                opis : opis,
                vaznost : vaznost
            });
 
            addedSteps = [];

            for(korak of koraci){
                const newStep = new StepModel({
                    _id : new moongoose.Types.ObjectId(),
                    cilj : goalId,
                    redniBroj : korak.redniBroj,
                    opis : korak.opis,
                });

                const step = await newStep.save();

                addedSteps.push(step);
            }

            const addedGoal = await newGoal.save();

            const clientGoal = {
                _id : addedGoal._id,
                naziv : addedGoal.naziv,
                opis : addedGoal.opis,
                vaznost : addedGoal.vaznost,
                koraci : addedSteps
            }
            //console.log(clientGoal)
            res.status(200).json(clientGoal);
        }
        catch (err){
            next(err);
        }
    }
};


module.exports = {
    getAllGoals,
    getGoalById, 
    addNewGoal
}