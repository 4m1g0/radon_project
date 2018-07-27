<template>
    <div>
        <canvas :height="customHeight" id="price-chart"></canvas>
    </div>
</template>

<script>
import Chart from 'chart.js';
import chartData from './chartTemplates/priceChartTemplate'
import Service from './Service'

export default {
    name: 'PriceHistory',
    props: [
        'customHeight'
    ],
    data(){
        return {
            chartData: chartData,
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
            this.chartData.options.scales.yAxes[0].scaleLabel.labelString='Cost (€/KWh)';
            this.chartData.options.scales.xAxes[0].scaleLabel.labelString='Time (hours)';
            this.chartData.data.datasets[0].label = 'Cost (€/KWh)'
            this.chartData.data.datasets[0].data = data.slice(4,28);
            for (var i=4;i<data.length;i++){
               var n = i-4;
                this.chartData.data.labels.push(n>9?n:'0'+n);
            }
            this.createChart('price-chart', this.chartData);
            this.$emit('set_loading', false);
        }
    },
    mounted() {
        Service.getPriceHistory(this.update);
    }
}
</script>
