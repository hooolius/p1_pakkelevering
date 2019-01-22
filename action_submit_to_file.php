<?php
 $path = 'data.txt';
 if (isset($_POST['addresses_input'])) {
    $fh = fopen($path,"a+");
    $string = $_POST['addresses_input'].];
    fwrite($fh,$string); // Write information to the file
    fclose($fh); // Close the file
 }
?>
