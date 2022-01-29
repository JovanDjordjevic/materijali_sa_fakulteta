// Kreiramo direktorijum za pohranjivanje datoteka ako ne postoji.
// Takodje, postavljamo putanju kao globalnu promenljivu __uploadDir
// kako bi bila vidljiva u svim paketima ispod.
const path = require('path');
const fs = require('fs');
global.__uploadDir = path.join(__dirname, 'resources', 'uploads');
if (!fs.existsSync(__uploadDir)) {
  fs.mkdirSync(__uploadDir);
}

const express = require('express');
const mongoose = require('mongoose');

const userRoutes = require('./components/users/usersAPI');
const productRoutes = require('./components/product/productsAPI');
const ordersRoutes = require('./components/order/ordersAPI');

// Kreiranje Express.js aplikacije
const app = express();

// Konekcija na MongoDB SUBP
const mongoDBString = 'mongodb://localhost:27017/store';
const mongoDBReplicationString = 'mongodb://localhost:27017,localhost:27018,localhost:27019/store?replicaSet=rs';
mongoose
  .connect(mongoDBString, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
  })
  .then(() => {
    console.log('Successfully connected to MongoDB!');
  });

// Parsiranje tela zahteva za dva formata:
// 1) application/x-www-form-urlencoded
app.use(
  express.urlencoded({
    extended: false,
  })
);
// 2) application/json
app.use(express.json());

// Implementacija CORS zastite
app.use(function (req, res, next) {
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization');

  if (req.method === 'OPTIONS') {
    res.header('Access-Control-Allow-Methods', 'OPTIONS, GET, POST, PATCH, PUT, DELETE');

    return res.status(200).json({});
  }

  next();
});

// Definisanje osnovnih pravila za rutiranje
app.use('/api/users', userRoutes);
app.use('/api/products', productRoutes);
app.use('/api/orders', ordersRoutes);
app.use(express.static(__uploadDir));

// Obrada zahteva koji se ne poklapa sa nekom pravilom od iznad
app.use(function (req, res, next) {
  const error = new Error('Zahtev nije podrzan od servera');
  error.status = 405;

  next(error);
});

// Obrada svih gresaka u nasoj aplikaciji
app.use(function (error, req, res, next) {
  // console.error(error.stack);

  const statusCode = error.status || 500;
  res.status(statusCode).json({
    message: error.message,
    status: statusCode,
    stack: error.stack,
  });
});

// Izvozenje Express.js aplikacije radi pokretanja servera
module.exports = app;
