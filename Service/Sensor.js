var mongoose = require('mongoose');

var Sensor = {
    _id: { type: Number },
    description: { type: String },
    mean: { type: Number },
    max: { type: Number },
    min: { type: Number },
};

var schema = new mongoose.Schema(Sensor);

module.exports = schema;