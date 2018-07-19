
export const Service = {
    dateToString: function(date){
        var dd = date.getDate();
        var mm = date.getMonth()+1; //January is 0!
        var yyyy = date.getFullYear();
        var hh = date.getHours();
        var MM = date.getMinutes();
        if(dd<10){ dd='0'+dd;} 
        if(mm<10){mm='0'+mm;} 
        if(MM<10){MM='0'+MM;} 
        date = yyyy + '-' + mm + '-' + dd + ' ' + hh + ':' + MM;
        return date;
    },
    getRadonHistory: function(id, start, end, callback){
        /* EXAMPLE
            id: 3
            start: 2018-06-09
            end: 2018-6-10
        */
        var url = "http://radon.4m1g0.com:3000/radon/api/v1/history?sensorId=" + id + "&start=" + start + "&end=" + end;
        fetch(url)
            .then(response => response.json())
            .then((data) => {
                data = data["logs"];
                // eslint-disable-next-line
                console.log(data);
                var lastDate = new Date(start);
                lastDate.setHours(0);
                var values = {dates:[],values:[]};
                var i = 0;
                while (i < data.length){
                    var diff = (new Date(data[i]["date"]) - lastDate) / 36e5;
                    if (diff > 1){ // is not the next value (there is a gap)
                        values["dates"].push(this.dateToString(lastDate));
                        values["values"].push(0);
                        lastDate.setHours(lastDate.getHours() + 1);
                    } else {
                        values["dates"].push(this.dateToString(new Date(data[i]["date"])));
                        var level = data[i]["value"];
                        if (level > 8000 || level < 0)
                            level = 0;
                        values["values"].push(level);
                        lastDate = new Date(data[i]["date"]);
                        i++;
                    }
                }

                while((new Date(end) - new Date(lastDate)) / 36e5 > 1) {
                    // missing values at the end
                    values["dates"].push(this.dateToString(lastDate));
                    values["values"].push(0);
                    lastDate.setHours(lastDate.getHours() + 1);
                }
                
                callback(values);
            });
    },
    getPriceHistory: function(callback) {
        var today = new Date();
        var dd = today.getDate();
        var mm = today.getMonth()+1; //January is 0!
        var yyyy = today.getFullYear();
        if(dd<10){ dd='0'+dd;} 
        if(mm<10){mm='0'+mm;} 
        var date = dd + '-' + mm + '-' + yyyy;
        
        fetch("http://tfm.4m1g0.com:1880/prices/?date=" + date)
            .then(response => response.json())
            .then((data) => {
                // eslint-disable-next-line
                console.log(data.slice(4,28));
                data.forEach((element, i, data) => {
                    data[i] = element / 1000000;
                });
                
                callback(data);
            });
    },
    getPowerHistory(callback){
        fetch("http://tfm.4m1g0.com:1880/powerHistory")
                .then(response => response.json())
                .then((data) => {
                    // eslint-disable-next-line
                    console.log(data);
                    data.forEach((element, i, data) => {
                        data[i] = element; // in case we need to transform the values
                    });
                    callback(data);
                });
    },
    getStatus(callback){
        fetch("http://tfm.4m1g0.com:1880/status")
            .then(response => response.json())
            .then((data) => {
                // eslint-disable-next-line
                console.log(data);
                callback(data);
            });
    },
    getTimers(callback){
        fetch("http://tfm.4m1g0.com:1880/timers")
            .then(response => response.json())
            .then((data) => {
            for(var i=0; i<data.length; i++){
                var arrayNumbers = data[i].Days.split("");
                var arrayBool = []
                for (var j=0;j<arrayNumbers.length;j++){
                if (arrayNumbers[j] == '1'){
                    arrayBool.push(true);
                } else {
                    arrayBool.push(false);
                }
                }
                data[i].Days = arrayBool;
            }
            // eslint-disable-next-line
            console.log(JSON.stringify(data));

            callback(data);
            
        });
    },
    setStatus(state){
        var config = {
            method: 'PUT',
            body: ''
          };

        if (state)
            config.body = '{"power":"OFF"}';
        else
            config.body = '{"power":"ON"}';

        fetch("http://tfm.4m1g0.com:1880/status", config)
            // eslint-disable-next-line
            .then(res => console.log(res));
    },
    saveTimer(timer, i){
        var config = {
            method: 'PUT',
            body: ''
          };

        config.body = JSON.stringify(timer);
        // eslint-disable-next-line
        console.log(config.body);

        var id = parseInt(i)+ 1;
        fetch("http://tfm.4m1g0.com:1880/timer/" + id, config)
          // eslint-disable-next-line
          .then(res => console.log(res));
    }
  }

  export default Service;