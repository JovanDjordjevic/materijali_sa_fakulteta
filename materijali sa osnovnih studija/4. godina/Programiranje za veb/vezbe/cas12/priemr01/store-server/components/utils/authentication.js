const express = require('express');
const User = require('../users/userModel');
const jwt = require('./jwt');

/**
 * Funkcija srednjeg sloja koja proverava da li je moguce prijaviti korisnika sa datim korisnickim imenom i lozinkom.
 * @param {express.Request} req 
 * @param {express.Response} res 
 * @param {express.NextFunction} next 
 */
module.exports.canAuthenticate = async (req, res, next) => {
  const username = req.body.username;
  const password = req.body.password;

  try {
    // Validiramo podatke
    if (!username || !password) {
      const error = new Error('Please provide both username and password');
      error.status = 400;
      throw error;
    }

    const user = await User.getUserByUsername(username);
    if (!user) {
      const error = new Error(`User with username ${username} does not exist!`);
      error.status = 404;
      throw error;
    }

    if (!(await user.isValidPassword(password))) {
      const error = new Error(`Wrong password for username ${username}!`);
      error.status = 401;
      throw error;
    }

    // Ako je sve u redu, onda cemo na nivou req objekta sacuvati neophodne podatke o autorizaciji,
    // na primer, identifikator i username korisnika iz baze podataka
    req.userId = user._id;
    req.username = user.username;

    // Pozivamo narednu funkciju srednjeg sloja
    next();
  } catch (err) {
    next(err);
  }
};

/**
 * Funkcija srednjeg sloja koja proverava da li je JWT token koji je klijent poslao validan.
 * @param {express.Request} req 
 * @param {express.Response} res 
 * @param {express.NextFunction} next 
 */
module.exports.isAuthenticated = async (req, res, next) => {
  try {
    // Ocekujemo da klijent uz svoj zahtev prosledi HTTP zaglavlje oblika:
    // "Authorization": "Bearer <JWT>"
    const authHeader = req.header("Authorization");
    if (!authHeader) {
      const error = new Error('You need to pass Authorization header with your request!');
      error.status = 403;
      throw error;
    }

    const token = authHeader.split(' ')[1];
    const decodedToken = jwt.verifyJWT(token);
    if (!decodedToken) {
      const error = new Error('Not Authenticated!');
      error.status = 401;
      throw error;
    }

    // Citamo podatke iz dekodiranog tokena i cuvamo na nivou req objekta,
    // kako bi naredna funkcija srednjeg sloja mogla da iskoristi taj podatak.
    req.userId = decodedToken.id;
    req.username = decodedToken.username;

    // Pozivamo narednu funkciju srednjeg sloja
    next();
  } catch (err) {
    next(err);
  }
};
