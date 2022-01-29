const express = require('express');

const router = express.Router();

const controller = require('./productsController');
const authentication = require('../utils/authentication');

router.get('/', controller.getProducts);
router.get('/:productId', controller.getProductById);
router.post('/', authentication.isAuthenticated, controller.createAProduct);
router.put('/upload/:productId', authentication.isAuthenticated, controller.putProductImage);
router.delete('/:productId', authentication.isAuthenticated, controller.deleteProduct);

module.exports = router;
