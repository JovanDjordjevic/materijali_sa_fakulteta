// dependency mozemo ovako da ucitamo u promenljivu
const lodash = require('lodash');
const nodemon = require('nodemon');

// console.log(lodash)
// console.log(nodemon)

// mozemo da ucitamo i nase neke module/biblioteke 
// samo za njih moramo da navodimo relativnu putanju
const constants = require('./nasi_moduli/constants')
console.log(constants.a + constants.b);

// podsecanje: mozemo da ucitamo i parcijalno
const {a} = require('./nasi_moduli/constants')
console.log(a);