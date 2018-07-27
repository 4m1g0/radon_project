export const chartData = {
    type: 'line',
    data: {
      labels: [],
      datasets: [
        {
          label: '',
          data: [],
          backgroundColor: [
            'rgba(71, 183,132,.5)', // Green
          ],
          borderColor: [
            '#47b784',
          ],
          borderWidth: 3
        }
      ]
    },
    options: {
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