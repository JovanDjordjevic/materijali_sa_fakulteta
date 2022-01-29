// U ovoj datoteci definisemo model koji ce imati nasi proizvodi
const mongoose = require('mongoose');
const mongoosePaginate = require('mongoose-paginate-v2');

const productSchema = new mongoose.Schema({
  _id: mongoose.Schema.Types.ObjectId,
  name: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  price: {
    type: mongoose.Schema.Types.Number,
    required: true,
  },
  description: {
    type: mongoose.Schema.Types.String,
    required: true,
  },
  forSale: {
    type: mongoose.Schema.Types.Boolean,
    required: true,
  },
  state: {
    type: mongoose.Schema.Types.String,
    required: true,
    enum: ['New', 'Barely Used', 'Moderately Used'],
  },
  imgUrls: {
    type: [mongoose.Schema.Types.String],
    required: true,
    default: [],
  },
  owner: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User',
    required: true,
  },
  stars: {
    type: mongoose.Schema.Types.Number,
    required: true,
    default: 0,
  },
  timestamp: {
    type: mongoose.Schema.Types.Date,
    required: true,
  },
});

// Omogucujemo stranicenje (eng. pagination) za nasu shemu
productSchema.plugin(mongoosePaginate);

// Pravimo model za datu shemu
const Product = mongoose.model('Product', productSchema);

// Definisemo funkcije koje cemo izvesti kontroleru.

/**
 * Pronalazi sve proizvode u bazi, pri cemu se vrsi njihova paginacija na osnovu eventualnih parametara.
 * Metod ih vraca sortirane po datumu kreiranja.
 * @param {number} page Broj stranice u paginaciji. Podrazumevano je 1.
 * @param {number} limit Broj proizvoda po stranici. Podrazumevano je 10.
 * @returns {Promise<mongoose.PaginateResult>} Paginacija proizvoda.
 */
async function paginateThroughProducts(page = 1, limit = 10) {
  return await Product.paginate({}, { page, limit, populate: 'owner', sort: 'timestamp', projection: '-timestamp' });
}

/**
 * Pronalazi proizvod iz baze na osnovu zadatog identifikatora.
 * @param {string} productId 
 * @returns {Promise<mongoose.Document>} Pronadjen proizvod ili `null` ukoliko nije pronadjen.
 */
async function getProductById(productId) {
  return await Product.findById(productId).populate('owner').exec();
}

/**
 * Pravi novi proizvod i cuva ga u bazu podataka.
 * @param {string} name Naziv.
 * @param {number} price Cena.
 * @param {string} description Opis.
 * @param {boolean} forSale Da li je za prodaju ili ne.
 * @param {string} state Koriscenost.
 * @param {string} owner Prodavac.
 * @returns {Promise<mongoose.Document>} Kreirani proizvod.
 */
async function createProduct(name, price, description, forSale, state, owner) {
  const product = new Product();
  product._id = new mongoose.Types.ObjectId();
  product.name = name;
  product.price = price;
  product.description = description;
  product.forSale = forSale;
  product.state = state;
  if (owner) {
    product.owner = owner;
  }
  product.timestamp = new Date();
  return await product.save();
}

/**
 * Dodaje putanju do nove slike u niz slika za dati proizvod.
 * @param {string} productId Identifikator proizvoda.
 * @param {string} imgUrl Putanja do slike koju klijent koristi za preuzimanje sa servera (od korene putanje servera).
 */
async function addImageToProduct(productId, imgUrl) {
  const product = await Product.findById(productId).exec();
  product.imgUrls.push(imgUrl);
  await product.save();
}

/**
 * Brise informacije o proizvodu sa datim identifikatorom.
 * @param {string} productId Identifikator proizvoda
 */
async function deleteProductById(productId) {
  await Product.deleteOne({ _id: productId }).exec();
}

// Skup funkcija koji se izvozi treba da bude minimalan, tj. da odrzava jedino interfejs nad nasim podacima.
// Kontroler koji koristi model ne sme da zna da li se koristi MongoDB, MySQL ili nesto trece.
// Njemu treba da budu dostupne samo informacije o argumentima funkcija i njihovim povratnim vrednostima.
module.exports = {
  paginateThroughProducts,
  createProduct,
  addImageToProduct,
  getProductById,
  deleteProductById,
};
