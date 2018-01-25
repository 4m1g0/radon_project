var express = require('express');
var status = require('http-status');
var bodyparser = require('body-parser');

module.exports = function(wagner) {
  var api = express.Router();

  api.use(bodyparser.json());

  api.post('/history', wagner.invoke(function (RadonLog) {
      return function (req, res) {
          ///console.log(req.body);
          var log = new RadonLog(req.body);
          log.save(function (error, log) {
              if (error) {
                  return res.status(status.BAD_REQUEST).json({error: error.toString()});
              }

              return res.status(status.OK).json({log_id: log._id});
          });
      };
  }));


  api.get('/history', wagner.invoke(function (RadonLog) {
      return function(req, res){
          console.log(req.params);
          RadonLog.find({sensorId: req.query.sensorId, date : { $lt : "2018-01-25" ,
                  $gt : "2018-01-01"}}, function(error, logs){
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

  return api;
};