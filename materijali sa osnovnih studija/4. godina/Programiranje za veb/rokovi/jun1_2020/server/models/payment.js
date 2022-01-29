const mongoose = require('mongoose');

const paymentSchema = new mongoose.Schema({
    _id : mongoose.Schema.Types.ObjectId,
    name : mongoose.Schema.Types.String,
    surname : mongoose.Schema.Types.String,
    email : mongoose.Schema.Types.String,
    amounts : [mongoose.Schema.Types.Number]
});

const PaymentModel = mongoose.model('payments', paymentSchema);

module.exports = PaymentModel;