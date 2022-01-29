const express = require('express');
const router = express.Router();
const kanbansController = require('../../controllers/kanbansController');

router.get('', kanbansController.getAllUnfinished);
router.post('', kanbansController.addNewKanban);
router.patch('/:id', kanbansController.updateKanbanWithId);

module.exports = router;
