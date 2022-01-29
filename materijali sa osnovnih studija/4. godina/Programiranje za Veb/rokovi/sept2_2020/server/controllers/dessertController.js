const mongoose = require('mongoose');
const DessertModel = require('../models/dessertModel');

const getAllDesserts = async (req, res, next) => {
    console.log("getAllDesserts");

    try{
        const desserts = await DessertModel.find({}).exec();
        res.status(200).json(desserts);
    }
    catch(err) {
        next(err);
    }
}

const getDessertsWithCriterion = async (req, res, next) => {
    console.log("getDessertsWithCriterion");
    const criterion = req.params.criterion;

    if(!criterion) {
        throw new Error('undefined criterion')
    }

    if(criterion !== 'lowcalorie' && criterion != 'glutenfree') {
        // ne zele da se ovde izbaci greska (?)
        res.status(200).json(null)
    }

    try{
        let desserts = [];
        switch(criterion){
            case 'lowcalorie':
                desserts = await DessertModel.find({nutrition : {$lte : 400}}).exec();
                break;
            case 'glutenfree':
                desserts = await DessertModel.find({glutenFree : true}).exec();
                break;
            default:
                break;
        }
        res.status(200).json(desserts);
    }
    catch(err) {
        next(err);
    }
}

const addNewDessert = async (req, res, next) => {
    console.log("addNewDessert");
    const {name, description, complexity, nutrition, glutenFree} = req.body.dessert;

    if(!name || !description || !complexity || !nutrition) {
        //ne zele gresku ovde?
        res.status(200).json(null)
    }

    let gluten = false;
    if (glutenFree === undefined) {
        gluten = false; // nigde ne kaze da ovo ne smem da uradim
    }
    else {
        gluten = glutenFree;
    }

    try{
        const newDessert = new DessertModel({
            _id : new mongoose.Types.ObjectId(),
            name : name,
            description : description,
            complexity : complexity,
            nutrition : nutrition,
            glutenFree : gluten
        });

        await newDessert.save();
        res.status(200).json(newDessert);
    }
    catch(err){
        next(err);
    }
}

module.exports = {
    getAllDesserts,
    getDessertsWithCriterion,
    addNewDessert
}