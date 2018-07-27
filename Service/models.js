var mongoose = require('mongoose');
var _ = require('underscore');

module.exports = function(wagner) {
    mongoose.connect('mongodb://localhost:27017/radon');

    wagner.factory('db', function() {
        return mongoose;
    });

    var RadonLog = mongoose.model('RadonLog', require('./RadonLog'), 'radonLogs');
    var Sensor = mongoose.model('Sensor', require('./Sensor'), 'sensors');
    var Alert = mongoose.model('Alert', require('./Alert'), 'alerts');

    var models = {
        RadonLog: RadonLog,
        Sensor: Sensor,
        Alert: Alert
    };

    // To ensure DRY-ness, register factories in a loop
    _.each(models, function(value, key) {
        wagner.factory(key, function() {
            return value;
        });
    });

    return models;
};