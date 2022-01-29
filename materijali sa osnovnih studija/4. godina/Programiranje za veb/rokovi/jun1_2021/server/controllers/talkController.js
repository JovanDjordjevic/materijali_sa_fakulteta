const mongoose = require('mongoose');
const TalkModel = require('../models/talk');

const getAllTalks = async (req, res, next) => {
    //console.log('getAllTalks')

    try {
        const allTalks = await TalkModel.find({}).exec();
        //console.log(allTalks);
        res.status(200).json(allTalks);
    }
    catch (err) {
        next(err);
    }
}

const getAllTalksInArea = async (req, res, next) => {
    //console.log('getAllTalksInArea')
    const area = req.params.area;
    //console.log(area)

    if(!area) {
        throw new Error('Missing parameter');
    }

    try{
        let talks = [];
        switch (area){
            case 'Angular':
                talks = await TalkModel.find({area: 'Angular'}).exec();
                res.status(200).json(talks);
                break;
            case 'Node':
                talks = await TalkModel.find({area: 'Node.js'}).exec();
                res.status(200).json(talks);
                break;
            case 'JS':
                talks = await TalkModel.find({area: 'JavaScript practices and tools'}).exec();
                res.status(200).json(talks);
                break;
            default: // ne postoji 
                res.status(404).json(null);
                break;
        }
    }
    catch(err) {
        next(err);
    }
}

const addNewTalk = async (req, res, next) => {
    //console.log('addNewTalk')
    const {title, speaker, area, duration} = req.body.talk;

    if(!title || !speaker || !area || duration === undefined) {
        // ne zele da izbacim error ovde (?)
        res.status(404).json(null);
    }

    try{
        const newTalk = new TalkModel({
            _id : new mongoose.Types.ObjectId(),
            title : title,
            speaker : speaker,
            area : area,
            duration : duration
        });

        const addedTalk = await newTalk.save();
        //console.log(addedTalk)
        res.status(200).json(addedTalk);
    }
    catch(err){
        next(err);
    }
}


module.exports = {
    getAllTalks,
    getAllTalksInArea,
    addNewTalk,
}