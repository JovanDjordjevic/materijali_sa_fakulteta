const mongoose = require('mongoose');
const PaymentModel = require('../models/payment');

const getPaymentByEmail = async (req, res, next) => {
    console.log('getPaymentByEmail');
    const email = req.params.email;

    if(!email) {
        throw new Error('invalid email');
    }

    try{
        const payments = await PaymentModel.find({email : email}).exec();
        if (payments.length == 0) {
            res.status(200).json(null);
        }
        else {
            res.status(200).json(payments[0]);
        }
    }
    catch(err) {
        next(err);
    }
}

const getPaymentById = async (req, res, next) => {
    console.log('getPaymentById');
    const id = req.params.id;

    if(!id) {
        throw new Error('invalid id');
    }

    try{
        const payment = await PaymentModel.findById(id, {name : 0, surname : 0, email : 0}).exec();
        if(!payment) {
            res.status(404).json();
        }
        else {
            res.status(200).json(payment);
        }
    }
    catch(err){
        next(err);
    }
}

const addAmount = async (req, res, next) => {
    console.log('addAmount');
    //nigde ne kaze da ne mogu da prosledim i id
    const id = req.body.id
    const amount = req.body.amount;

    if(amount === undefined) {
        throw new Error("Invalid amount");
    }

    try{
        const payment = await PaymentModel.findByIdAndUpdate(id, {$push : {amounts : amount}}, {new : true}).exec();
        res.status(200).json(payment);
    }
    catch(err) {
        next(err);
    }
}


module.exports = {
    getPaymentByEmail,
    getPaymentById,
    addAmount
};