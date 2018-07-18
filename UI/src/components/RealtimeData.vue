<template>
<div class="holder">
    <div>
        <b class="title">Last 7 days</b>
        <gauge :level="shortTerm"></gauge>
    </div>
    <div>
        <b class="title">Last 30 days</b>
        <gauge :level="longTerm"></gauge>
    </div>
</div>
    
</template>

<script>
import Gauge from './Gauge'
import Service from './Service'

export default {
    components: {
        Gauge,
    },
    data() {
        return {
            shortTerm: 0,
            longTerm: 0,
        }
    },
    methods:{
       fetchData(){
            var id = this.$cookie.get('sensor');
            var end = new Date();
            var start = new Date();
            start.setDate(start.getDate() - 30);
            Service.getRadonHistory(id, this.dateToString(start), this.dateToString(end), this.update);
       },
       update(data){
            var instant = 0;
            var sum = 0;
            var i = 0;
            data["values"].forEach(level => {
                if (level == 0) return;
                instant = level;
                sum += level;
                i++;
            });

            var mean = sum / i;
            this.shortTerm = instant;
            this.longTerm = Math.floor(mean);
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

<style>
.holder{
    display: flex;
}
.title{
    font-size: 1.1em;
}
</style>
