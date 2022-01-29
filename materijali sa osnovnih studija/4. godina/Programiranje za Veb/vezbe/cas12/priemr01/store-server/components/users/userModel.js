const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const jwtUtil = require('../utils/jwt');

const SALT_ROUNDS = 10;

const userSchema = new mongoose.Schema({
  username: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  hash: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  salt: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  email: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  name: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  imgUrl: {
    type: mongoose.Schema.Types.String,
    required: true,
    default: 'default-user.png',
  },
});

userSchema.methods.setPassword = async function (password) {
  this.salt = await bcrypt.genSalt(SALT_ROUNDS);
  this.hash = await bcrypt.hash(password, this.salt);;
};

userSchema.methods.isValidPassword = async function (password) {
  return await bcrypt.compare(password, this.hash);
};

const User = mongoose.model('User', userSchema);

/**
 * Dohvata jedan dokument-korisnika iz baze.
 * @param {string} username Korisnicko ime.
 * @returns {Promise<mongoose.Document>} Dokument koji predstavlja korisnika za dato korisnicko ime.
 */
async function getUserByUsername(username) {
  const user = await User.findOne({ username }).exec();
  return user;
}

/**
 * Kreira JSON Web Token sa podacima o korisniku.
 * @param {string} username Korisnicko ime.
 * @returns {Promise<string>} JWT sa podacima o korisniku sa datim korisnickim imenom.
 */
async function getUserJWTByUsername(username) {
  const user = await getUserByUsername(username);
  if (!user) {
    throw new Error(`User with username ${username} does not exist!`);
  }
  return jwtUtil.generateJWT({
    id: user.id,
    username: user.username,
    email: user.email,
    name: user.name,
    imgUrl: user.imgUrl,
  });
}

/**
 * Pamti novog korisnika u bazi podataka.
 * @param {string} username Korisnicko ime.
 * @param {string} password Lozinka.
 * @param {string} email Adresa elektronske poste.
 * @param {string} name Ime i prezime.
 * @returns {Promise<string>} JWT sa podacima o novom korisniku.
 */
async function registerNewUser(username, password, email, name) {
  const user = new User();
  user.username = username;
  await user.setPassword(password);
  user.email = email;
  user.name = name;

  await user.save();
  return getUserJWTByUsername(username);
}

/**
 * Azurira osnovne podatke o korisniku.
 * @param {string} username Korisnicko ime.
 * @param {string} name Novo ime i prezime.
 * @param {string} email Nova adresa elektronske poste.
 * @returns {Promise<string>} JWT sa azuriranim podacima o korisniku.
 */
async function updateUserData(username, name, email) {
  const user = await getUserByUsername(username);
  user.name = name;
  user.email = email;
  await user.save();
  return getUserJWTByUsername(username);
}

/**
 * Azurira korisnikovu profilnu sliku.
 * @param {string} userId Identifikator korisnika.
 * @param {string} imgUrl Putanja slike na serveru.
 */
async function changeUserProfileImage(userId, imgUrl) {
  const user = await User.findById(userId);
  user.imgUrl = imgUrl;
  await user.save();
}

module.exports = {
  getUserByUsername,
  getUserJWTByUsername,
  registerNewUser,
  updateUserData,
  changeUserProfileImage,
};
