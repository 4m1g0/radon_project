
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
    addAlert(alert){
        var headers = new Headers();
        headers.append("Content-Type", "application/json");


        var config = {
            method: 'POST',
            body: JSON.stringify(alert),
            headers: headers
        };

        fetch("http://radon.4m1g0.com:3000/radon/api/v1/alerts/", config)
          // eslint-disable-next-line
          .then(res => console.log(res));
    },
    delAlert(email){
        var config = {
            method: 'DELETE',
        };

        fetch("http://radon.4m1g0.com:3000/radon/api/v1/alerts/" + btoa(email), config)
          // eslint-disable-next-line
          .then(res => console.log(res));
    },
    getAlerts(callback){
        fetch("http://radon.4m1g0.com:3000/radon/api/v1/alerts/")
            .then(response => response.json())
            .then((data) => {
                // eslint-disable-next-line
                console.log(data);
                callback(data["alerts"]);
            });
    },
  }

  export default Service;