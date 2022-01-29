const express = require('express');
const router = express.Router();
const songController = require('../../controllers/songController');

router.get('/:sortBy', songController.sortBy);
router.patch('/', songController.incrementCountForSong);
router.put('/', songController.addNewSong);

module.exports = router;
