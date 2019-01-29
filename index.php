<head>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css"
          integrity="sha384-GJzZqFGwb1QTTN6wy59ffF1BuGJpLSa9DkKMp0DgiMDm4iYMj70gZWKYbI706tWS" crossorigin="anonymous">
    ---
    layout: examples
    title: Starter Template
    extra_css: "starter-template.css"
    ---
    <title>P1 Pakkelevering</title>
    <script src="jquery.js"></script>
</head>
<?php
if ($_SESSION['time'] != 0) {
    echo "This is true";
} else {
    session_start();
    $_SESSION['time'] = time();
}
?>

<nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
    <a class="navbar-brand" href="index.php">P1_Pakkelevering</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault"
            aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarsExampleDefault">
        <ul class="navbar-nav mr-auto">
            <li class="nav-item active">
                <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
            </li>
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="dropdown01" data-toggle="dropdown" aria-haspopup="true"
                   aria-expanded="false">Dropdown</a>
                <div class="dropdown-menu" aria-labelledby="dropdown01">
                    <a class="dropdown-item" href="#">Placeholder</a>
                    <a class="dropdown-item" href="#">Placeholder</a>
                    <a class="dropdown-item" href="#">Placeholder</a>
                </div>
            </li>
        </ul>
    </div>
</nav>


<main role="main" class="container">
    <div class=" spacer">
        <br>
        <br>
        <br>
        <br>

    </div>
    <div class="starter-template">
        <link rel="stylesheet" href="leaflet/leaflet.css"/>
        <script src="leaflet/leaflet.js"></script>
        <div class="map_and_input">
            <div id="mapid" style="width: 45%; height: 600px;float:left;"></div>
            <div id="result" style="display: none;float:right; width: 45%; height: 600px;">
                <p id="result_length"></p>
                <p id="result_trip"></p>
            </div>
            <div id="input" style="float:right; width: 45%; height: 600px;">
                <p>Enter addresses on form: </p>
                <form id="usrform">
                    <textarea rows="23" cols="70" name="addresses_input" placeholder="Enter addresses"></textarea>
                    <input type="submit" value="Submit" id="submit" name="Submit">
                </form>

            </div>
        </div>


        <script>
            var request;
            var length =0;
            var mymap = L.map('mapid').setView([57.0429, 9.9261], 12);

            L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoiaG9vbGl1cyIsImEiOiJjanJnNTdkNTIxa3RhNDNtbGR1Ync2dHloIn0.9y2imHxvRfjNoiPPBrNCKg', {
                maxZoom: 18,
                attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' +
                    '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
                    'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
                id: 'mapbox.streets'
            }).addTo(mymap);

            $('#usrform').submit(function (event) {
                event.preventDefault();
                var post_data = $('#usrform').serialize();
                request = $.ajax({
                    url: "action_submit_to_file.php",
                    type: "post",
                    data: post_data
                });
                var url = "<?php echo('searches/' . $_SESSION['time'] . '_output.js')?>";
                // Callback handler that will be called on success
                request.done(function (response, textStatus, jqXHR) {
                    $.ajax({
                        url: url,
                        dataType: "script"
                    });
                    alert("Done");
                });

            });


        </script>


    </div>

</main><!-- /.container -->
