const express = require('express');
const { urlencoded, json } = require('body-parser');
const mongoose = require('mongoose');

const app = express();

const databaseString = 'mongodb://localhost:27017/pveb_jun2_2021';
mongoose.connect(databaseString, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

mongoose.connection.once('open', function () {
  console.log('Uspesno povezivanje!');
});

mongoose.connection.on('error', (error) => {
  console.log('Greska: ', error);
});

app.use(json());
app.use(urlencoded({ extended: false }));

app.use(function (req, res, next) {
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Headers', 'Content-Type');

  if (req.method === 'OPTIONS') {
    res.header(
      'Access-Control-Allow-Methods',
      'OPTIONS, GET, POST, PUT, PATCH, DELETE'
    );

    return res.status(200).json({});
  }

  next();
});

/* ----- deo o rutama - pocetak --- */
const wordsRoutes = require('./routes/api/words');
app.use('/api/words', wordsRoutes);
/* ----- deo o rutama - kraj ---- */

app.use(function (req, res, next) {
  const error = new Error('Zahtev nije podrzan!');
  error.status = 405;

  next(error);
});

app.use(function (error, req, res, next) {
  const statusCode = error.status || 500;
  res.status(statusCode).json({
    error: {
      message: error.message,
      status: statusCode,
      stack: error.stack,
    },
  });
});

module.exports = app;
