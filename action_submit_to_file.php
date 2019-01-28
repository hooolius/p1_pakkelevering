<?php
if (isset($_SESSION['time'])) {
    $time_stamp = $_SESSION['time'];
} else {
    session_start();
    $time_stamp = time();
}

if ( !file_exists($dir) ) {
    mkdir ($dir, 0744);
}
$dir = "searches";

$_SESSION['time'] = $time_stamp;

$path = "searches/" . $time_stamp . "_input.txt";
if (isset($_POST['addresses_input'])) {
    $fh = fopen($path, "a+");
    $string = $_POST['addresses_input'];
    fwrite($fh, $string); // Write information to the file
    fclose($fh); // Close the file

    if(file_exists("searches/".$time_stamp."_input.txt")) {
     	$cmd = "p1_pakkelevering ".$time_stamp.".txt > searches/".$time_stamp."_output.txt";
	shell_exec($cmd);
	echo "succes?";
    } else {
        echo "Error creating file";
    }
    while (file_exists("searches/".$time_stamp."_output.txt")) {
        header("location: index.php");
    }
}

