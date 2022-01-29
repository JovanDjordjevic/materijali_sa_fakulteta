const express = require('express');
const router = express.Router();
const paymentController = require('../../controllers/paymentController');

// greska u tekstu zadatka, ne mogu oba get zahteva da idu na /api/payments/{parametar}
router.get('/email/:email', paymentController.getPaymentByEmail);
router.get('/id/:id', paymentController.getPaymentById);          
router.patch('/', paymentController.addAmount);

module.exports = router;
