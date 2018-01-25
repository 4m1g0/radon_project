var mongoose = require('mongoose');

var radonLogSchema = {
    date: { type: Date, required: true },
    sensorId: { type: Number, ref: 'Sensor', required: true },
    value: { type: Number, required: true }
};

var schema = new mongoose.Schema(radonLogSchema);

schema.index({sensorId: 1, date: 1});

module.exports = schema;