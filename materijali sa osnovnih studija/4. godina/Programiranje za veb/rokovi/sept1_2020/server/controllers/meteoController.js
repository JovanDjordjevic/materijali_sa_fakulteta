const mongoose = require('mongoose');
const Meteo = require('../models/meteoModel');

const gelAllMeteo = async (req, res, next) => {
    console.log("gelAllMeteo");

    try{
        const meteos = await Meteo.find({}).exec();
        res.status(200).json(meteos);
    }
    catch(err){
        next(err);
    }
}

const getMeteoForCity = async (req, res, next) => {
    console.log("getMeteoForCity");
    const city = req.params.city;

    if(!city) {
        throw new Error('invalid city');
    }

    try{
        const meteoForCity = await Meteo.findOne({city : city}).exec();
        if(!meteoForCity) {
            res.status(200).json(null);
        }
        else {
            res.status(200).json(meteoForCity);
        }
    }
    catch(err){
        next(err);
    }
}

const updateTemperaturesForCity = async (req, res, next) => {
    console.log("updateTemperaturesForCity");
    const city = req.body.city;
    const temps = req.body.temps;

    if(!city || temps === undefined) {
        throw new Error('city or temps invalid');
    }

    try{
        const updatedInfo = await Meteo.findOneAndUpdate({city : city}, {$set: {temperatures : temps}}, {new:true}).exec();
        res.status(200).json("Request successful");
    }
    catch(err) {
        next(err);
    }
}

module.exports = {
    gelAllMeteo,
    getMeteoForCity,
    updateTemperaturesForCity,
}