const mongoose = require('mongoose');

const orderSchema = new mongoose.Schema({
  _id: mongoose.Schema.Types.ObjectId,
  products: {
    type: [mongoose.Schema.Types.ObjectId],
    required: true,
    ref: 'Product',
  },
  user: {
    type: mongoose.Schema.Types.ObjectId,
    required: true,
    ref: 'User',
  },
  orderTimestamp: {
    type: mongoose.Schema.Types.Date,
    required: true,
  },
});

const OrderMongoose = mongoose.model('Order', orderSchema);

/**
 * U ovom pristupu, za model koristimo klasu koju cemo instancirati u kontroleru.
 */
class Order {
  async getOrdersForUser(userId) {
    return await OrderMongoose.find().where('user').equals(userId).exec();
  }

  async getOrderDetails(orderId) {
    return await OrderMongoose.findById(orderId).populate('products').populate('user').exec();
  }

  async createAnOrder(userId, productIds) {
    const newOrder = new OrderMongoose({
      _id: new mongoose.Types.ObjectId(),
      user: userId,
      products: productIds,
      orderTimestamp: new Date(),
    });
    await newOrder.save();
    return newOrder;
  }
}

module.exports = Order;
