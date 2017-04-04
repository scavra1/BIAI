(function () {
  var canvas = document.getElementById('tester');

  if(typeof networkErrors === 'undefined') {
    document.getElementById('tester').innerHTML = "<strong>No data has been found!</strong>";
  } else {
    var xdata = new Array(networkErrors.length).fill(0).map((item, index) => index);

    var trace1 = {
       name: "Assembly"
      ,x: xdata
      ,y: networkErrors
      ,mode: "lines"
      ,type: 'scatter'
    };

    var layout = {
      xaxis: {
          title: "Iterations"
          //,range: [ 0.75, 5.25 ]
      },
      yaxis: {
          title: "Error"
          //,range: [0, 1]
      }
      //,title: title
    };
    var data = [trace1];
    Plotly.plot(canvas, data, layout);
  }
})();
