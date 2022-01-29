const express = require('express');
const goalController = require('../../controllers/goal');

const router = express.Router();

router.get('/', goalController.getAllGoals);
router.get('/:id', goalController.getGoalById);
router.post('/', goalController.addNewGoal); 

module.exports = router;
