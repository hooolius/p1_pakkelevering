<!DOCTYPE html>
<html>
  <head>
    <link rel="stylesheet" href="styles.css">

    <title>P1 Pakkelevering - Web Frontend</title>

    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <link rel="shortcut icon" type="image/x-icon" href="docs/images/favicon.ico" />

   <!--
leaflet css og js lib
-->
  <link rel="stylesheet" href="leaflet/leaflet.css" />
<script src="leaflet/leaflet.js"></script>


  </head>  <?php
  if (isset($_SESSION['time'])) {
      //Do nothing
      echo $_SESSION['time'];
  } else {
      session_start();
  }
  ?>
  <body>

    <div class="map_and_input">
      <center>
        <div id="mapid" style="width: 900px; height: 600px;float:left;"></div>
        <div id="input" style="float:right;">
          <form action="action_submit_to_file.php" method="post" id="usrform">
            <br>
            <textarea rows="30" cols="70" name="addresses_input" form="usrform">Enter addresses</textarea>
            <div class="controls">
              <button>Submit</button>
            </div>
          </form>
        </div>
      </center>
    </div>
    <script>

      var mymap = L.map('mapid').setView([57.0429, 9.9261], 12);

      L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', {
  maxZoom: 18,
  attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' +
  '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
  'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
  id: 'mapbox.streets'
}).addTo(mymap);
      L.marker([57.050674661396556,9.922714233398438]).addTo(mymap).bindPopup("this is popping");

    </script>



  </body>
</html>
