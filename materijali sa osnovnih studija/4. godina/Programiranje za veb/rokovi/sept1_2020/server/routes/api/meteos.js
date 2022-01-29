const express = require('express');
const router = express.Router();
const meteoController = require('../../controllers/meteoController');

router.get('/', meteoController.gelAllMeteo);
router.get('/:city', meteoController.getMeteoForCity);
router.put('/', meteoController.updateTemperaturesForCity);

module.exports = router;
