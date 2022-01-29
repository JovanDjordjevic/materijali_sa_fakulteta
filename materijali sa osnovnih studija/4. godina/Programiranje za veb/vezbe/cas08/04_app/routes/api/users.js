const express = require('express');

const userController = require('../../controllers/users');

const router = express.Router();

// NOTE: na prolsim vezbama su ovde stajale cele putanje tipa:   /api/users/....
// ali ovde smo taj zajednicki prefiks izdvojili u app.js. To je pokazano na proslim vezbama ali u tom primeru nisam izmenio
router.get('/', userController.getAllUsers);  

router.get('/:username', userController.getUserByUsername);

router.post('/', userController.addNewUser);

router.put('/', userController.changeUserPassword);

router.delete('/', userController.deleteUser);



module.exports = router;