<?php
if (isset($_SESSION['time'])) {
    $time_stamp = $_SESSION['time'];
} else {
    session_start();
    $time_stamp = time();
}

$dir = "searches";
if ( !file_exists($dir) ) {
    mkdir ($dir, 0744);
}

$_SESSION['time'] = $time_stamp;

$path = "searches/" . $time_stamp . "_input.txt";
if (isset($_POST['addresses_input'])) {
    $fh = fopen($path, "a+");
    $string = $_POST['addresses_input'];
    fwrite($fh, $string); // Write information to the file
    fclose($fh); // Close the file

    if(file_exists("searches/".$time_stamp."_input.txt")) {
     	$cmd = "p1_pakkelevering searches/".$time_stamp."_input.txt > searches/".$time_stamp."_output.js";
	shell_exec($cmd);
    } else {
        echo "Error creating file";
    }
    while (file_exists("searches/".$time_stamp."_output.txt")) {
        header("location: index.php");
    }
}

