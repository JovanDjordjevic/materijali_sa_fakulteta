const User = require('./userModel');
const { uploadFile } = require('../upload/uploadController');

module.exports.registerUser = async (req, res, next) => {
  const username = req.body.username;
  const password = req.body.password;
  const email = req.body.email;
  const name = req.body.name;

  try {
    if (!username || !password || !email || !name) {
      const error = new Error('Please provide all data for a new user');
      error.status = 400;
      throw error;
    }

    const jwt = await User.registerNewUser(username, password, email, name);
    return res.status(201).json({
      token: jwt,
    });
  } catch (err) {
    next(err);
  }
};

module.exports.loginUser = async (req, res, next) => {
  const username = req.username;

  try {
    const jwt = await User.getUserJWTByUsername(username);
    return res.status(201).json({
      token: jwt,
    });
  } catch (err) {
    next(err);
  }
};

module.exports.changeUserInfoData = async (req, res, next) => {
  const username = req.username;
  const name = req.body.name;
  const email = req.body.email;

  try {
    if (!email || !name) {
      const error = new Error('New data cannot be empty');
      error.status = 400;
      throw error;
    }

    const jwt = await User.updateUserData(username, name, email);
    return res.status(201).json({
      token: jwt,
    });
  } catch (err) {
    next(err);
  }
};

module.exports.changeUserProfileImage = async (req, res, next) => {
  const userId = req.userId;
  const username = req.username;

  try {
    await uploadFile(req, res);
    console.log(req.file);

    if (req.file == undefined) {
      const error = new Error('Please upload a file!');
      error.status = 400;
      throw error;
    }

    const imgUrl = req.file.filename;
    await User.changeUserProfileImage(userId, imgUrl);

    const jwt = await User.getUserJWTByUsername(username);
    return res.status(200).json({
      token: jwt,
    });
  } catch (err) {
    next(err);
  }
};
