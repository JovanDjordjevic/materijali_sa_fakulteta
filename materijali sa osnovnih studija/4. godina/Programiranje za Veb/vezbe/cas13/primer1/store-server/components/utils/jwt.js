const jwt = require('jsonwebtoken');
const MY_SECRET = 'SECRET_THAT_NO_ONE_SHOULD_KNOW';

module.exports.generateJWT = (data) => {
  return jwt.sign(data, MY_SECRET, { expiresIn: '7d' });
};

module.exports.verifyJWT = (token) => {
  return jwt.verify(token, MY_SECRET);
};
