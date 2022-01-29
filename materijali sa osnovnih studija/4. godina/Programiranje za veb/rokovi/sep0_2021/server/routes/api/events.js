const express = require('express');
const router = express.Router();

const eventController = require('../../controllers/eventController');

router.get('/month/:month', eventController.getAllEventsInMonth);
router.get('/:id', eventController.getEventById);
router.put('/', eventController.addTodoStep);

module.exports = router;
