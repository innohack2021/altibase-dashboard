var json_data;

var chart_sql = [];
var chart_cpu = [];
var chart_memory = [];

const btn_Insert_32 = document.getElementById('btn_Insert_32');
const btn_Update_32 = document.getElementById('btn_Update_32');
const btn_Select_32 = document.getElementById('btn_Select_32');
const btn_Delete_32 = document.getElementById('btn_Delete_32');
const btn_ISelect_32 = document.getElementById('btn_Insert+Select_32');
const btn_SUpdate_32 = document.getElementById('btn_Select+Update_32');
const btn_ISUpdate_32 = document.getElementById('btn_Insert+Select+Update_32');
const btn_Insert_64 = document.getElementById('btn_Insert_64');
const btn_Update_64 = document.getElementById('btn_Update_64');
const btn_Select_64 = document.getElementById('btn_Select_64');
const btn_Delete_64 = document.getElementById('btn_Delete_64');
const btn_ISelect_64 = document.getElementById('btn_Insert+Select_64');
const btn_SUpdate_64 = document.getElementById('btn_Select+Update_64');
const btn_ISUpdate_64 = document.getElementById('btn_Insert+Select+Update_64');



function draw_chart(thread, sql, chart_type) {
  let data;

  if (chart_type == 'sql') {
    data = {
      labels: ['case1', 'case2', 'case3', 'case4', 'case5'],
      datasets: [
        {
          label: 'v7.1_0.1scale',
          data: [
            json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_1'], json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_2'],
            json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_3'], json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_4'],
            json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_5']
          ],
          borderColor: '#f54e60',
          pointRadius: 5,
          pointHoverRadius: 10,
          backgroundColor: '#f54e60',
          yAxisID: 'y',
        },
        {
          label: 'v7.2_0.1scale',
          data: [
            json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_1'], json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_2'],
            json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_3'], json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_4'],
            json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_5']
          ],
          borderColor: '#3698fe',
          pointRadius: 5,
          pointHoverRadius: 10,
          backgroundColor: '#3698fe',
          yAxisID: 'y',
        },
        {
          label: 'v7.1_0.2scale',
          data: [
            json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_1'], json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_2'],
            json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_3'], json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_4'],
            json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_5']
          ],
          borderColor: '#fea700',
          pointRadius: 5,
          pointHoverRadius: 10,
          backgroundColor: '#fea700',
          yAxisID: 'y',
        },
        {
          label: 'v7.1_0.2scale',
          data: [
            json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_1'], json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_2'],
            json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_3'], json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_4'],
            json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_5']
          ],
          borderColor: '#0ca77a',
          pointRadius: 5,
          pointHoverRadius: 10,
          backgroundColor: '#0ca77a',
          yAxisID: 'y',
        }
      ]
    };
  }
  else if (chart_type == 'cpu') {
    data = {
      labels: ['case1', 'case2', 'case3', 'case4', 'case5'],
      datasets: [
        {
          label: 'v7.1_0.1scale',
          data: [
            json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_1'], json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_2'],
            json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_3'], json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_4'],
            json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_5']
          ],
          borderColor: '#f54e60',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#f54e60',
          yAxisID: 'y',
        },
        {
          label: 'v7.2_0.1scale',
          data: [
            json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_1'], json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_2'],
            json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_3'], json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_4'],
            json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_5']
          ],
          borderColor: '#3698fe',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#3698fe',
          yAxisID: 'y',
        },
        {
          label: 'v7.1_0.2scale',
          data: [
            json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_1'], json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_2'],
            json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_3'], json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_4'],
            json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_5']
          ],
          borderColor: '#fea700',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#fea700',
          yAxisID: 'y',
        },
        {
          label: 'v7.1_0.2scale',
          data: [
            json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_1'], json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_2'],
            json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_3'], json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_4'],
            json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_5']
          ],
          borderColor: '#0ca77a',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#0ca77a',
          yAxisID: 'y',
        }
      ]
    };
  }
  else if (chart_type == 'memory') {
    data = {
      labels: ['case1', 'case2', 'case3', 'case4', 'case5'],
      datasets: [
        {
          label: 'v7.1_0.1scale',
          data: [
            json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_1'], json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_2'],
            json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_3'], json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_4'],
            json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_5']
          ],
          borderColor: '#f54e60',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#f54e60',
          yAxisID: 'y',
        },
        {
          label: 'v7.2_0.1scale',
          data: [
            json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_1'], json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_2'],
            json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_3'], json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_4'],
            json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_5']
          ],
          borderColor: '#3698fe',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#3698fe',
          yAxisID: 'y',
        },
        {
          label: 'v7.1_0.2scale',
          data: [
            json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_1'], json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_2'],
            json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_3'], json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_4'],
            json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_5']
          ],
          borderColor: '#fea700',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#fea700',
          yAxisID: 'y',
        },
        {
          label: 'v7.1_0.2scale',
          data: [
            json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_1'], json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_2'],
            json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_3'], json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_4'],
            json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_5']
          ],
          borderColor: '#0ca77a',
          pointRadius: 2,
          pointHoverRadius: 5,
          backgroundColor: '#0ca77a',
          yAxisID: 'y',
        }
      ]
    };
  }

  const config = {
    type: 'line',
    data: data,
    options: {
      responsive: true,
      interaction: {
        mode: 'index',
        intersect: false,
      },
      stacked: false,
      plugins: {
        title: {
          display: true,
          text: chart_type.toUpperCase(),
          font: {
            size: 20,
          },
          color: 'white'

        },
        subtitle: {
          display: true,
          text: sql,
          color: 'white',
        },  
        legend: {
          labels: {
            font: {
              size: 13,
            },
            color: 'white'
          }
        }
      },
      scales: {
        x: {
          title: {
            display: false,
            text: 'case',
            color: '#f00',
            font: {
              family: 'Comic Sans MS',
              size: 15,
              weight: 'bold',
              lineHeight: 1.2,
            },
          },
          ticks: {
            font: {
              size: 15,
            },
            color: 'white'
          },
          grid: {
            color: "#464660",
          }
        },
        y: {
          title: {
            display: false,
            text: 'tps',
            color: '#f00',
            font: {
              family: 'Comic Sans MS',
              size: 15,
              weight: 'bold',
              lineHeight: 1.2,
            },
          },
          type: 'linear',
          display: true,
          position: 'left',
          ticks: {
            // stepSize: true,
            font: {
              size: 15,
            },
            color: 'white',
            callback: function (value, index, values) {
              if (chart_type != 'sql')
                value = value.toFixed(1)
              return value + (chart_type == 'sql' ? ' tps' : '%');
            }
          },
          grid: {
            color: "#464660",
            lineWidth: 0.5,
          },
        }
      }
    },
  };
  return (config);
}

function draw_chart_avr(thread) {
  const v71_sql = json_data['scale0.1']['ver71'][thread];
  const v72_sql = json_data['scale0.1']['ver72'][thread];
  const labels = ['Insert', 'Select', 'Update', 'Delete', 'IS', 'SU', 'ISU'];
  const data = {
    labels: labels,
    datasets: [{
      label: 'v7.1_scale0.1',
      data: [
        json_data['scale0.1']['ver71'][thread]['Insert']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver71'][thread]['Update']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver71'][thread]['Select']['TEST_RESULT_AVG'], 
        json_data['scale0.1']['ver71'][thread]['Delete']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver71'][thread]['Insert+Select']['TEST_RESULT_AVG'], 
        json_data['scale0.1']['ver71'][thread]['Select+Update']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver71'][thread]['Insert+Select+Update']['TEST_RESULT_AVG']
      ],
      backgroundColor: [
        '#f54e60'
      ],
      borderColor: [
        '#f54e60'
      ],
      borderWidth: 1
    },
    {
      label: 'v7.2_0.1scale',
      data: [
        json_data['scale0.1']['ver72'][thread]['Insert']['TEST_RESULT_AVG'], 
        json_data['scale0.1']['ver72'][thread]['Update']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver72'][thread]['Select']['TEST_RESULT_AVG'], 
        json_data['scale0.1']['ver72'][thread]['Delete']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver72'][thread]['Insert+Select']['TEST_RESULT_AVG'], 
        json_data['scale0.1']['ver72'][thread]['Select+Update']['TEST_RESULT_AVG'],
        json_data['scale0.1']['ver72'][thread]['Insert+Select+Update']['TEST_RESULT_AVG']
      ],
      backgroundColor: [
        '#3698fe'
      ],
      borderColor: [
        '#3698fe'
      ],
      borderWidth: 1
    },
    {
      label: 'v7.1_0.2scale',
      data: [
        json_data['scale0.2']['ver71'][thread]['Insert']['TEST_RESULT_AVG'], 
        json_data['scale0.2']['ver71'][thread]['Update']['TEST_RESULT_AVG'],
        json_data['scale0.2']['ver71'][thread]['Select']['TEST_RESULT_AVG'], 
        json_data['scale0.2']['ver71'][thread]['Delete']['TEST_RESULT_AVG'],
        json_data['scale0.2']['ver71'][thread]['Insert+Select']['TEST_RESULT_AVG'], 
        json_data['scale0.2']['ver71'][thread]['Select+Update']['TEST_RESULT_AVG'],
        json_data['scale0.2']['ver71'][thread]['Insert+Select+Update']['TEST_RESULT_AVG']
      ],
      backgroundColor: [
        '#fea700'
      ],
      borderColor: [
        '#fea700'
      ],
      borderWidth: 1
    },
    {
      label: 'v7.2_0.2scale',
      data: [
        json_data['scale0.2']['ver72'][thread]['Insert']['TEST_RESULT_AVG'], 
        json_data['scale0.2']['ver72'][thread]['Update']['TEST_RESULT_AVG'],
        json_data['scale0.2']['ver72'][thread]['Select']['TEST_RESULT_AVG'], 
        json_data['scale0.2']['ver72'][thread]['Delete']['TEST_RESULT_AVG'],
        json_data['scale0.2']['ver72'][thread]['Insert+Select']['TEST_RESULT_AVG'], 
        json_data['scale0.2']['ver72'][thread]['Select+Update']['TEST_RESULT_AVG'],
        json_data['scale0.2']['ver72'][thread]['Insert+Select+Update']['TEST_RESULT_AVG']
      ],
      backgroundColor: [
        '#0ca77a'
      ],
      borderColor: [
        '#0ca77a'
      ],
      borderWidth: 1
    }
    ]
  };
  const config = {
    type: 'bar',
    data: data,
    options: {
      plugins: {
        title: {
          display: true,
          text: thread + ' average',
          color: 'white',
          font: {
            family: 'Comic Sans MS',
            size: 25,
            weight: 'bold',
            lineHeight: 1.2,
          },
        },
        legend: {
          labels: {
            font: {
              size: 15,
            },
            color: 'white'
          }
        }
        
      },
      scales: {
        x: {
          ticks: {
            font: {
              size: 15,
            },
            color: 'white',
          },
          grid: {
            color: "#464660",
            lineWidth: 0.5,
          }
        },
        y: {
          beginAtZero: false,
          ticks: {
            callback: function (value, index, values) {
              return value + ' tps';
            },
            font: {
              size: 15,
            },
            color: 'white',
          },
          grid: {
            color: "#464660",
            lineWidth: 0.5,
          }
        }
      }
    },
  };
  return (config);
}

/*OS INFO*/
function get_env_info()
{
  document.getElementById('ver71_os_32').innerHTML = json_data['scale0.1']['ver71']['info']['OS'];
  document.getElementById('ver71_version_32').innerHTML = json_data['scale0.1']['ver71']['info']['ALTIBASE_VERSION'];
  document.getElementById('ver72_os_32').innerHTML = json_data['scale0.1']['ver72']['info']['OS'];
  document.getElementById('ver72_version_32').innerHTML = json_data['scale0.1']['ver72']['info']['ALTIBASE_VERSION'];
  document.getElementById('ver71_os_64').innerHTML = json_data['scale0.1']['ver71']['info']['OS'];
  document.getElementById('ver71_version_64').innerHTML = json_data['scale0.1']['ver71']['info']['ALTIBASE_VERSION'];
  document.getElementById('ver72_os_64').innerHTML = json_data['scale0.1']['ver72']['info']['OS'];
  document.getElementById('ver72_version_64').innerHTML = json_data['scale0.1']['ver72']['info']['ALTIBASE_VERSION'];
}

/* 제이슨 파싱 */
function readTextFile(url, callback) {
  var rawFile = new XMLHttpRequest();
  rawFile.overrideMimeType("application/json");

  rawFile.open("GET", url , true);
  rawFile.onreadystatechange = function () {
    if (rawFile.readyState === 4 && rawFile.status == "200") {
      callback(rawFile.responseText);
    }
  }
  rawFile.send(null);
}

/* 실행 */
new Promise(() => {
  readTextFile("multi_scale_data.json", function (text) {
    console.log(text);
    json_data = JSON.parse(text);
    get_env_info();
    chart_sql[0] = new Chart(document.getElementById('chart_sql_32'), draw_chart('thread32', 'Insert', 'sql'));
    chart_cpu[0] = new Chart(document.getElementById('chart_cpu_32'), draw_chart('thread32', 'Insert', 'cpu'));
    chart_memory[0] = new Chart(document.getElementById('chart_memory_32'), draw_chart('thread32', 'Insert', 'memory'));
    new Chart(document.getElementById('chart_avr_32'), draw_chart_avr('thread32'));

    chart_sql[1] = new Chart(document.getElementById('chart_sql_64'), draw_chart('thread64', 'Insert', 'sql'));
    chart_cpu[1] = new Chart(document.getElementById('chart_cpu_64'), draw_chart('thread64', 'Insert', 'cpu'));
    chart_memory[1] = new Chart(document.getElementById('chart_memory_64'), draw_chart('thread64', 'Insert', 'memory'));
    new Chart(document.getElementById('chart_avr_64'), draw_chart_avr('thread64'));

  });
}).then(arg => {
  json_data = arg;
});


/* 버튼이벤트 */

function btn(thread, sql) {
  if (thread == 'thread32')
    chart_no = 0;
  else if (thread == 'thread64')
    chart_no = 1;
  chart_sql[chart_no].options.plugins.subtitle.text = sql;
  chart_sql[chart_no].config.data.datasets[0].data = [
    json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_1'],
    json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_2'],
    json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_3'],
    json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_4'],
    json_data['scale0.1']['ver71'][thread][sql]['TEST_RESULT_5']
  ];
  chart_sql[chart_no].config.data.datasets[1].data =
    [
      json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_1'],
      json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_2'],
      json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_3'],
      json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_4'],
      json_data['scale0.1']['ver72'][thread][sql]['TEST_RESULT_5']
    ];
    chart_sql[chart_no].config.data.datasets[2].data =
    [
      json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_1'],
      json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_2'],
      json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_3'],
      json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_4'],
      json_data['scale0.2']['ver71'][thread][sql]['TEST_RESULT_5']
    ];
    chart_sql[chart_no].config.data.datasets[3].data =
    [
      json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_1'],
      json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_2'],
      json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_3'],
      json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_4'],
      json_data['scale0.2']['ver72'][thread][sql]['TEST_RESULT_5']
    ];
  chart_sql[chart_no].update();

  chart_cpu[chart_no].options.plugins.subtitle.text = sql;
  chart_cpu[chart_no].config.data.datasets[0].data = [
    json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_1'],
    json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_2'],
    json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_3'],
    json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_4'],
    json_data['scale0.1']['ver71'][thread][sql]['CPU_USAGE_5']
  ];
  chart_cpu[chart_no].config.data.datasets[1].data =
    [
      json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_1'],
      json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_2'],
      json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_3'],
      json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_4'],
      json_data['scale0.1']['ver72'][thread][sql]['CPU_USAGE_5']
    ];
    chart_cpu[chart_no].config.data.datasets[2].data =
    [
      json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_1'],
      json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_2'],
      json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_3'],
      json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_4'],
      json_data['scale0.2']['ver71'][thread][sql]['CPU_USAGE_5']
    ];
    chart_cpu[chart_no].config.data.datasets[3].data =
    [
      json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_1'],
      json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_2'],
      json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_3'],
      json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_4'],
      json_data['scale0.2']['ver72'][thread][sql]['CPU_USAGE_5']
    ];
  chart_cpu[chart_no].update();

  chart_memory[chart_no].options.plugins.subtitle.text = sql;

  chart_memory[chart_no].config.data.datasets[0].data = [
    json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_1'],
    json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_2'],
    json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_3'],
    json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_4'],
    json_data['scale0.1']['ver71'][thread][sql]['MEMORY_USAGE_5']
  ];
  chart_memory[chart_no].config.data.datasets[1].data =
    [
      json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_1'],
      json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_2'],
      json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_3'],
      json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_4'],
      json_data['scale0.1']['ver72'][thread][sql]['MEMORY_USAGE_5']
    ];
    chart_memory[chart_no].config.data.datasets[2].data =
    [
      json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_1'],
      json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_2'],
      json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_3'],
      json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_4'],
      json_data['scale0.2']['ver71'][thread][sql]['MEMORY_USAGE_5']
    ];
    chart_memory[chart_no].config.data.datasets[3].data =
    [
      json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_1'],
      json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_2'],
      json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_3'],
      json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_4'],
      json_data['scale0.2']['ver72'][thread][sql]['MEMORY_USAGE_5']
    ];
  chart_memory[chart_no].update();
}



btn_Insert_32.onclick = function () {
  btn('thread32', 'Insert');
};

btn_Update_32.onclick = function () {
  btn('thread32', 'Update');
};

btn_Select_32.onclick = function () {
  btn('thread32', 'Select');
};

btn_Delete_32.onclick = function () {
  btn('thread32', 'Delete');
};

btn_ISelect_32.onclick = function () {
  btn('thread32', 'Insert+Select');
};

btn_SUpdate_32.onclick = function () {
  btn('thread32', 'Select+Update');
};

btn_ISUpdate_32.onclick = function () {
  btn('thread32', 'Insert+Select+Update');
};

btn_Insert_64.onclick = function () {
  btn('thread64', 'Insert');
};

btn_Update_64.onclick = function () {
  btn('thread64', 'Update');
};

btn_Select_64.onclick = function () {
  btn('thread64', 'Select');
};

btn_Delete_64.onclick = function () {
  btn('thread64', 'Delete');
};

btn_ISelect_64.onclick = function () {
  btn('thread64', 'Insert+Select');
};

btn_SUpdate_64.onclick = function () {
  btn('thread64', 'Select+Update');
};

btn_ISUpdate_64.onclick = function () {
  btn('thread64', 'Insert+Select+Update');
};


