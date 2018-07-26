<template>
    <div>
        <canvas :height="customHeight" id="power-chart"></canvas>
    </div>
</template>

<script>
import Chart from 'chart.js';
import chartData from './chartTemplates/radonChartTemplate'
import Service from './Service'

export default {
    name: 'RadonHistory',
    props: [
        'customHeight',
        'id'
    ],
    data(){
        return {
            chartData: chartData,
            firstTime: true,
        }
    },
    methods: {
        createChart(chartId, chartData) {
            const ctx = document.getElementById(chartId);
            new Chart(ctx, {
            type: chartData.type,
            data: chartData.data,
            options: chartData.options,
            });
        },
        update(data){
            this.chartData.options.scales.yAxes[0].scaleLabel.labelString='Radon Level (Bq/m³)';
            this.chartData.options.scales.xAxes[0].scaleLabel.labelString='Time (hours)';
            this.chartData.data.datasets[0].label = 'Radon Level (Bq/m³)'
            this.chartData.data.datasets[0].data = data["values"];
            this.chartData.data.labels = data["dates"];

            this.createChart('power-chart', this.chartData);
            this.$emit('set_loading', false);
            this.chartData.options.animation = false; // do not animate next time
        },
        fetchHistory(){
            var id = this.$cookie.get('sensor');
            var end = new Date();
            end.setDate(end.getDate() + 1);
            var start = new Date();
            start.setDate(start.getDate() - 15);
            Service.getRadonHistory(id, this.dateToString(start), this.dateToString(end), this.update);
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
        this.fetchHistory();
    }
}
</script>
