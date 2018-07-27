var express = require('express');
var wagner = require('wagner-core');

require('./models')(wagner);

var app = express();

// Add headers
app.use(function (req, res, next) {

    // Website you wish to allow to connect
    res.setHeader('Access-Control-Allow-Origin', '*');//'http://radon.4m1g0.com:8080');

    // Request methods you wish to allow
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    // Request headers you wish to allow
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

    // Pass to next layer of middleware
    next();
});

app.use('/radon/api/v1', require('./api')(wagner));

app.listen(3000);
console.log('Listening on port 3000!');
