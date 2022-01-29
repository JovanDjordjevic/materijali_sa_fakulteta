const express = require('express');
const router = express.Router();
const dessertController = require('../../controllers/dessertController');

router.get('/', dessertController.getAllDesserts);
router.get('/:criterion', dessertController.getDessertsWithCriterion);
router.post('/', dessertController.addNewDessert)

module.exports = router;
