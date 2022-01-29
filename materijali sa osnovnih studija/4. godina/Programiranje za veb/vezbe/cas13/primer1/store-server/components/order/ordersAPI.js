const express = require('express');

const router = express.Router();

const OrdersRouter = require('./ordersRouter');
const authentication = require('../utils/authentication');

router.get('/', authentication.isAuthenticated, async (req, res, next) => {
  const router = new OrdersRouter();
  await router.get(req, res, next);
});

router.get('/:id', authentication.isAuthenticated, async (req, res, next) => {
  const router = new OrdersRouter();
  await router.getById(req, res, next);
});

router.post('/', authentication.isAuthenticated, async (req, res, next) => {
  const router = new OrdersRouter();
  await router.post(req, res, next);
});

module.exports = router;
