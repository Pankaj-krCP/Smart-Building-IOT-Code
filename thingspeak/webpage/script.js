document.getElementById("light-on").addEventListener("click", function () {
  var ts_api_key = document.getElementById("ts-api-key").value;
  var url =
    "http://api.thingspeak.com/update?api_key=" + ts_api_key + "&field2=1";
  $.getJSON(url, function (data) {
    console.log(data);
  });
});

document.getElementById("light-off").addEventListener("click", function () {
  var ts_api_key = document.getElementById("ts-api-key").value;
  var url =
    "http://api.thingspeak.com/update?api_key=" + ts_api_key + "&field2=0";
  $.getJSON(url, function (data) {
    console.log(data);
  });
});

setInterval(function () {
  // Call a function repetatively with 1 Second interval
  getThingSpeakLightState();
}, 1000);

function getThingSpeakLightState() {
  var ts_channel_id = document.getElementById("ts-channel-id").value;
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      if (myObj.field2 == 1) {
        document.getElementById("LIGHTState").innerHTML = "ON";
        document.getElementById("LightImage").src = "./images/ledon.png";
      } else {
        document.getElementById("LIGHTState").innerHTML = "OFF";
        document.getElementById("LightImage").src = "./images/ledoff.png";
      }
    }
  };
  xhttp.open(
    "GET",
    "https://api.thingspeak.com/channels/" +
      ts_channel_id +
      "/fields/2/last.json",
    true
  );
  xhttp.send();
}
