<?php
$explorer = file_get_contents('https://explorer.onixcoin.com/api/getpeerinfo');

$info = file_get_contents('https://explorer.onixcoin.com/api/getinfo');

$connections = json_decode($info,TRUE)["connections"];

$array = json_decode($explorer,TRUE);

for ($x=0; $x<$connections; $x++) {

echo "addnode=".$array[$x]["addr"]."\n";
}

?>