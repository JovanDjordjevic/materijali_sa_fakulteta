const express = require('express');
const router = express.Router();

const talkController = require('../../controllers/talkController');

router.get('/', talkController.getAllTalks);
router.get('/:area', talkController.getAllTalksInArea);
router.post('/', talkController.addNewTalk);

module.exports = router;
