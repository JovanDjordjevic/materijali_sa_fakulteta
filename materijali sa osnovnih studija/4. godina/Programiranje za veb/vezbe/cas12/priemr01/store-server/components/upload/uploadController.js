const util = require('util');
const multer = require('multer');
const maxSize = 10 * 1024 * 1024;

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    cb(null, __uploadDir);
  },
  filename: (req, file, cb) => {
    const newFilename = Date.now().toString() + '_' + file.originalname;
    cb(null, newFilename);
  },
});

const uploadFile = multer({
  storage: storage,
  limits: { fileSize: maxSize },
}).single('file');

module.exports.uploadFile = util.promisify(uploadFile);
