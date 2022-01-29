const express = require('express');

const router = express.Router();

const controller = require('./userController');
const authentication = require('../utils/authentication');

router.post('/register', controller.registerUser);
router.post('/login', authentication.canAuthenticate, controller.loginUser);
router.patch('/', authentication.isAuthenticated, controller.changeUserInfoData);
router.patch('/profile-image', authentication.isAuthenticated, controller.changeUserProfileImage);

module.exports = router;
