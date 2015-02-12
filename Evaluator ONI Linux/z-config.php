<?
   
  $host = "192.168.1.250";
  $user = "evaluser";
  $password = "tech~3kVraid";
  $db = "eval";
  //$host = "192.168.0.1";
  //$user = "evaluser";
  //$password = "parola12";
  //$db = "eval";
  $check_offline=TRUE;
  
  $serverURL="http://eval.hangman.ro/"; // nu uita slash la final
  
  
  $compile = array('pas' => "fpc -O2 -Xs -othe.exe %s",
                      'c'=>"gcc -lm -Wall -O2 -static -o the.exe %s",
                    'cpp'=>"g++ -lm -Wall -O2 -static -o the.exe %s");
  $compiler_name = array( 'pas' => "fpc",
                         'c'=>"gcc",
                         'cpp'=>"g++");
?>
