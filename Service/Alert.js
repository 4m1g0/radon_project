var mongoose = require('mongoose');

var Alert = {
    email: { type: String },
    level: { type: Number }
};

var schema = new mongoose.Schema(Alert);

module.exports = schema;