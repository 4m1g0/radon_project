var mongodb = require('mongodb');

var uri = 'mongodb://localhost:27017';

mongodb.MongoClient.connect(uri, function(error, client) {
    var db = client.db('radon');

    if (error) {
        console.log(error);
        process.exit(1);
    }

    db.collection('history').insertOne({x: 1}, function(error, result){
        if (error){
            console.log(error);
            process.exit(1);
        }

        db.collection('history').find().toArray(function (error, docs) {
            if (error) {
                console.log(error);
                process.exit(1);
            }

            console.log('Found docs: ');
            docs.forEach(function (doc) {
                console.log(JSON.stringify(doc));
            });

            process.exit(0);
        });
    });
});