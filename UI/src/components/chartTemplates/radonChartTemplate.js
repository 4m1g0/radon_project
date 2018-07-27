export const chartData = {
    type: 'line',
    data: {
      labels: [],
      datasets: [
        {
          label: '',
          data: [],
          backgroundColor: [
            'rgba(71, 132,183,.5)', // Blue
          ],
          borderColor: [
            '#4784b7',
          ],
          borderWidth: 3
        }
      ]
    },
    options: {
      elements: { point: { radius: 0 } },
      responsive: true,
      lineTension: 1,
      scales: {
        yAxes: [{
          ticks: {
            beginAtZero: true,
            padding: 25,
          },
          scaleLabel: {
            display: true,
            labelString: ''
          }
        }],
        xAxes: [{
          ticks:{ 
            autoSkip:true, 
          },
          scaleLabel: {
            display: true,
            labelString: ''
          },
          gridLines: {
            drawOnChartArea: false
          }
        }],
      }
    }
  }

  export default chartData;