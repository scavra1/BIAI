(function () {
  var canvas = document.getElementById('tester');

  //var title = 'Execution time with different threads numbers';

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
})();
