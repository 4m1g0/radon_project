<template>
    <div class="scroll" v-bind:style="{ height: customHeight*1.9 + 'px' }">
    <table>
        <thead>
          <tr>
              <th>Date</th>
              <th>Mean</th>
              <th>Min</th>
              <th>Max</th>
          </tr>
        </thead>

        <tbody>
          <tr v-for="(data, index) in tableData" :key="index">
            <td>{{data.date}}</td>
            <td>{{data.mean}}</td>
            <td>{{data.min}}</td>
            <td>{{data.max}}</td>
          </tr>
        </tbody>
      </table>
    </div>
</template>

<script>
import Service from './Service'

export default {
    name: 'DailyStats',
    props: [
      'customHeight'
    ],
    data(){
        return {
            tableData: [{date:"2018-07-02",mean:"98", min:"90", max:"107"}],
        }
    },
    methods:{
       fetchData(){
            var id = this.$cookie.get('sensor');
            var end = new Date();
            end.setDate(end.getDate() + 1);
            var start = new Date();
            start.setDate(start.getDate() - 30);
            Service.getRadonHistory(id, this.dateToString(start), this.dateToString(end), this.update);
       },
       update(data){
            var splited = {};
            for (var i=0; i<data["values"].length; i++) {
                var date = data["dates"][i].substr(0,10)
                splited[date] = splited[date] || []; // initialize list
                splited[date].push(data["values"][i]);
            }

            var tableData = [];
            for (var day in splited) {
                var j = 0;
                var sum = 0;
                var min = 9999;
                var max = 0;
                splited[day].forEach(value => {
                    if (value == 0) return;
                    j++;
                    sum += value;
                    if (value < min) min = value;
                    if (value > max) max = value;
                });
                var mean = Math.floor(sum / j);
                if (sum == 0) {
                    mean = 0;
                    min = 0;
                    max = 0;
                }

                tableData.push({date: day, mean:mean,min:min, max:max});
            } 

            this.tableData = tableData.reverse();

            this.$emit('set_loading', false);
        },
        dateToString(date){
            var dd = date.getDate();
            var mm = date.getMonth()+1; //January is 0!
            var yyyy = date.getFullYear();
            if(dd<10){ dd='0'+dd;} 
            if(mm<10){mm='0'+mm;} 
            date = yyyy + '-' + mm + '-' + dd;
            return date;
        }
    },
    mounted() {
        //this.timer = setInterval(this.fetchHistory, 1000*10);
        this.fetchData();
    }
}
</script>

<style scoped>
.scroll{
  overflow-y: scroll; /*vertical scroll*/
}
</style>

