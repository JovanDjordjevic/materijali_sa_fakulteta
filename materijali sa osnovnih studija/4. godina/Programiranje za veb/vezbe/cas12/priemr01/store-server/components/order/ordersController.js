const OrderModel = require('./orderModel');

/**
 * U ovom pristupu, za kontroler koristimo klasu koju cemo instancirati u objektu za rutiranje.
 */
class OrdersController {
  async getOrdersByUserId(userId) {
    const model = new OrderModel();
    return await model.getOrdersForUser(userId);
  }

  async getOrderById(orderId) {
    const model = new OrderModel();
    return await model.getOrderDetails(orderId);
  }

  async createOrder(userId, productIds) {
    const model = new OrderModel();
    return await model.createAnOrder(userId, productIds);
  }
}

module.exports = OrdersController;
