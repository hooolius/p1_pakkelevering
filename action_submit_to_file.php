<?php
if (isset($_SESSION['time'])) {
    $time_stamp = $_SESSION['time'];
} else {
    session_start();
    $time_stamp = time();
}


$_SESSION['time'] = $time_stamp;
$path = "searches/" . $time_stamp . "_input.txt";
if (isset($_POST['addresses_input'])) {
    $fh = fopen($path, "a+");
    $string = $_POST['addresses_input'];
    fwrite($fh, $string); // Write information to the file
    fclose($fh); // Close the file

    if (file_exists("p1_pakkelevering.exe") OR file_exists("p1_pakkelevering.out")) {
        exec("p1_pakkelevering.out" . $time_stamp . "txt >>" . $time_stamp . "_output.txt");
    } else {
        echo "<br> No executable found.";
    }

    while (file_exists("searches/".$time_stamp."_output.txt")) {
        header("location: index.php");
    }
}

