(function () {
  var canvas = document.getElementById('tester');

  if(typeof networkErrors === 'undefined') {
    document.getElementById('tester').innerHTML = "<strong>No data has been found!</strong>";
  } else {
    var xdata1 = new Array(networkErrors.length).fill(0).map((item, index) => index);
    var xdata2 = new Array(networkCorrectness.length).fill(0).map((item, index) => index);

    var trace1 = {
       name: "Mean square error"
      ,x: xdata1
      ,y: networkErrors
      ,mode: "lines"
      ,type: 'scatter'
    };
    var trace2 = {
       name: "Classification correctness"
      ,x: xdata2
      ,y: networkCorrectness
      ,mode: "lines"
      ,type: 'scatter'
    };

    var layout = {
      xaxis: {
          title: "Iterations"
          //,range: [ 0, 1 ]
      },
      yaxis: {
          title: "Error"
          ,range: [0, 1]
      }
      ,title: "n = 1.0, m = 1.0"
    };
    var data = [
       trace1
      ,trace2
    ];
    Plotly.plot(canvas, data, layout);
  }
})();
