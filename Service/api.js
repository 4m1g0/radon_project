var express = require('express');
var status = require('http-status');
var bodyparser = require('body-parser');

module.exports = function(wagner) {
    var api = express.Router();

    api.use(bodyparser.json());

    api.post('/history', wagner.invoke(function (RadonLog) {
        return function (req, res) {
	    console.log(req.body);
            var log = new RadonLog(req.body);
            log.save(function (error, log) {
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }
                
                if (log.value < 0){
                    return res.status(status.RESET_CONTENT).json({log_id: log._id});
                }

                return res.status(status.CREATED).json({log_id: log._id});
            });
        };
    }));

    api.get('/history', wagner.invoke(function (RadonLog) {
        return function(req, res){
            RadonLog.find({sensorId: req.query.sensorId, date : { $lt : req.query.end,
                    $gt : req.query.start}}, function(error, logs){
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }

                if (!logs) {
                    return res.status(status.NOT_FOUND).json({error:'Not found'});
                }

                res.json({logs:logs});
            });
        };
    }));

    api.get('/sensor/:id', wagner.invoke(function (Sensor) {
        return function(req, res){
            Sensor.findOne({_id: req.params.id}, function(error, sensor){
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }

                if (!sensor) {
                    return res.status(status.NOT_FOUND).json({error:'Not found'});
                }

                res.json(sensor);
            });
        };
    }));

    api.get('/sensor', wagner.invoke(function (Sensor) {
        return function(req, res){
            Sensor.find({}, function(error, sensors){
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }

                if (!sensors.length) {
                    return res.status(status.NOT_FOUND).json({error:'Not found'});
                }

                res.json({sensors:sensors});
            }).limit(100);
        };
    }));

    api.delete('/history', wagner.invoke(function (RadonLog) {
        return function(req, res){
            RadonLog.remove({sensorId: req.query.sensorId, date : { $lt : req.query.end,
                    $gt : req.query.start}}, function(error, logs){
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }

                if (!logs) {
                    return res.status(status.NOT_FOUND).json({error:'Not found'});
                }

                res.json({logs:logs});
            });
        };
    }));

    api.delete('/alerts/:email', wagner.invoke(function (Alert) {
        return function(req, res){
            Alert.remove({email: atob(req.params.id)}, function(error, alerts){
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }

                if (!logs) {
                    return res.status(status.NOT_FOUND).json({error:'Not found'});
                }

                res.json({alerts:alerts});
            });
        };
    }));

    api.post('/alerts/', wagner.invoke(function (Alert) {
        return function (req, res) {
            console.log(req.body);
            var alert = new Alert(req.body);
            alert.save(function (error, alert) {
                if (error) {
                    return res.status(status.BAD_REQUEST).json({error: error.toString()});
                }

                return res.status(status.CREATED).json({alert: alert});
            });
        };
    }));

  return api;
};
