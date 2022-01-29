const express = require('express');
const router = express.Router();

const wordsController = require('../../controllers/wordsController');

router.get('/', wordsController.getAllWords);
router.get('/:level', wordsController.getAllWordsByLevel);
router.get('/id/:id', wordsController.getWordById);             // nije eksplicitno trazeno u zadatku, trebalo mi je zbog routes na clientu
router.put('/', wordsController.updateExamplesForWord);


module.exports = router;
