const mongoose = require('mongoose');
const WordModel = require('../models/word');

const getAllWords = async (req, res, next) => {
    console.log("getAllWords");
    try {
        const allWords = await WordModel.find({}).exec();
        //console.log(allWords);
        res.status(200).json(allWords);
    }
    catch(err) {
        next(err);
    }
}

const getAllWordsByLevel = async (req, res, next) => {
    console.log("getAllWordsByLevel");
    const level = req.params.level;

    try{
        if(!level || (level !== 'A' && level !== 'B' && level !== 'C')){
            // ne zele da se ovde ispali greska (?)
            res.status(404).json(null);
        }
        else {
            const wordsByLevel = await WordModel.find({level : level}).exec();
            //console.log(wordsByLevel);
            res.status(200).json(wordsByLevel);
        }
    }
    catch (err) {
        next(err);
    }
}

const getWordById = async (req, res, next) => {
    console.log("getWordById");
    const id = req.params.id;

    try{
        if(!id){
            throw new Error("Invalid id");
        }
        else {
            const word = await WordModel.findOne({_id : id}).exec();
            res.status(200).json(word);
        }
    }
    catch (err) {
        next(err);
    }
}

const updateExamplesForWord = async (req, res, next) => {
    console.log("updateExamplesForWord");
    const {id, example} = req.body;

    try{
        if(!id || !example) {
            // ni vode ne zele da se izbaci greska (?)
            res.status(404).json(null);
        }
        else {
            const updatedWord = await WordModel.findByIdAndUpdate(id, {$push : {examples : example}}, {new :  true}).exec();
            //console.log(updatedWord);
            res.status(200).json(updatedWord);
        }
    }
    catch (err) {
        next(err);
    }
}

module.exports = {
    getAllWords,
    getAllWordsByLevel,
    getWordById,
    updateExamplesForWord
}