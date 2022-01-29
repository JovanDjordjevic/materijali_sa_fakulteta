const Product = require('./productModel');
const { uploadFile } = require('../upload/uploadController');

module.exports.getProducts = async function (req, res, next) {
  const page = req.query.page;
  const limit = req.query.limit;

  try {
    const products = await Product.paginateThroughProducts(page, limit);
    res.status(200).json(products);
  } catch (err) {
    next(err);
  }
};

module.exports.getProductById = async function (req, res, next) {
  const productId = req.params.productId;

  try {
    const product = await Product.getProductById(productId);
    if (product === null) {
      const error = new Error(`Product with id ${productId} is not found`);
      error.status = 404;
      throw error;
    }
    res.status(200).json(product);
  } catch (err) {
    next(err);
  }
};

module.exports.createAProduct = async function (req, res, next) {
  // Iz autentikacije
  const owner = req.userId;
  // Iz tela zahteva
  const name = req.body.name;
  const price = Number.parseFloat(req.body.price);
  const description = req.body.description;
  const forSale = Boolean(req.body.forSale);
  const state = req.body.state;

  try {
    // Jednostavna validacija implementirana radi ilustracije.
    // Ovo moze ici dosta slozenije.
    if (name === '' || Number.isNaN(price) || description === '' || state === '') {
      const error = new Error('Product validation has failed');
      error.status = 400;
      throw error;
    }

    const product = await Product.createProduct(name, price, description, forSale, state, owner);
    res.status(201).json(product);
  } catch (err) {
    next(err);
  }
};

module.exports.putProductImage = async function (req, res, next) {
  const productId = req.params.productId;

  try {
    await uploadFile(req, res);
    console.log(req.file);

    if (req.file == undefined) {
      const error = new Error('Please upload a file!');
      error.status = 400;
      throw error;
    }

    const imgUrl = req.file.filename;
    await Product.addImageToProduct(productId, imgUrl);

    res.status(200).send({
      message: 'Uploaded the file successfully: ' + req.file.originalname,
    });
  } catch (err) {
    next(err);
  }
};

module.exports.deleteProduct = async function (req, res, next) {
  const ownerId = req.userId;
  const productId = req.params.productId;

  try {
    const product = await Product.getProductById(productId);
    if (!product) {
      const error = new Error('Product not found!');
      error.status = 404;
      throw error;
    }

    if (product.owner.toString() !== ownerId) {
      const error = new Error('You are not authorized to remove this product!');
      error.status = 403;
      throw error;
    }

    await Product.deleteProductById(productId, ownerId);
    res.status(200).json({ message: `Successfully removed the product ${product.name}!` });
  } catch (err) {
    next(err);
  }
};
