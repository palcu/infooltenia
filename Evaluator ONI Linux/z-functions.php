<?
require "z-config.php";

function ConfirmMySQLServer()
{
  global $host;
  global $user;
  global $password;
  global $serverURL;
  global $check_offline;
  echo "-- Configurare --------------------------------\n";
  echo sprintf("|%45s|\n","MySQL server: ".$host);
  echo sprintf("|%45s|\n","MySQL user: ".$user);
  echo sprintf("|%45s|\n","MySQL password: ".$password);
  //echo sprintf("|%45s|\n","Server URL: ".$serverURL);
  if($check_offline)
  	echo sprintf("|%45s|\n","Verific output_only: TRUE");
  else
  	echo sprintf("|%45s|\n","Verific output_only: FALSE");
  echo "-----------------------------------------------\n";
  echo "PHP Settings:\n";
  echo "Memory limit: ".ini_get("memory_limit")." Recomended value: 256M\n";
  echo "-----------------------------------------------\n";
  echo "Este corect ?(Y/n) ";
  $raspuns=ReadYesNo("Y");
  if($raspuns=="N")
  {
    die ("\nCorectati valorile in z-config.php\n\n");
  }
}

function ConfirmSourceStatus()
//nume prost, lipsa de inspiratie
{
  echo "Vreti sa evaluati toate sursele ?\n";
  echo "  Y - toate sursele\n";
  echo "  N - doar sursele inca neevaluate\n";
  echo "Deci, (y/N) ";
  $raspuns=ReadYesNo("N");
  if($raspuns=="Y")
  {
    $q="update sources set status='pending'";  $r=mysql_query($q);  
  }
  else
  {    //debug
       // de sters !!!!!!!
    $q="update sources set status='pending' where status='executing'";    $r=mysql_query($q);
    $q="update test_jobs set status='pending' where status='executing'";    $r=mysql_query($q);
  }
}

function ReadYesNo($r="Y")
{
  do
  {
    
    $raspuns=strtoupper(trim(fgets(STDIN)));
	 if(empty($raspuns))
		 $raspuns=$r;
    if($raspuns!="Y" && $raspuns!="N")
      echo "Va rog raspundeti Y(es) sau N(o)! ";
  }while($raspuns!="Y" && $raspuns!="N");
  return $raspuns;
}

function problemaActualizata($problemId){
	$q="select actualizat from problems where id={$problemId}";
	$r=mysql_query($q);
	if(!$r)
		die("Eroare ala verificarea starii problemei - functia problemaActualizata");
	$l = mysql_fetch_array($r);
	return $l['actualizat']==0;
}

function SetProblem( $problemId)
{
  /*
   * 
   *  descarca problema curenta, daca este cazul
   *  
   * 
   * */
  global $serverURL;
  global $task_type;
  $q="select * from problems where id=".$problemId;
  $r=mysql_query($q);
  $l=mysql_fetch_array($r);
  $dirname="prob/".$l['title'];
  $task_type = $l['problemType'];
  if(!file_exists($dirname) || problemaActualizata($problemId))
  {
          //downloadez archiva cu teste
          if ( file_exists($dirname) ){
			echo "\nSterge testele existente\n";
			$cmd="rm -r {$dirname} 2> /dev/null";
			exec($cmd);
		  }
          echo "Descarc arhiva cu teste \n";
          $qv="select verificator from problems where id=".$problemId;
          $rv= @ mysql_query($qv);
  		  $verificator = @ mysql_result ($rv, 0 , "verificator");
  		  echo "Gata verificator\n";
  		  $fv=fopen("prob/verif.zip","wb");
  		  fwrite($fv,$verificator);
  		  fclose($fv);
  		  echo "Scris fisier\n";  
          //$cmd="wget ".$serverURL."dwn-eval-cli.php?id=".$problemId." -O prob/verif.zip 2> /dev/null";
          //exec($cmd);
          //dezarhivez
          $cmd="unzip prob/verif.zip  -d ./prob";
          exec($cmd);
          echo "Dezarhivat\n";
          exec("chmod -R 755 prob/".$l['title']."/");
          //sterg arhiva
          unlink("prob/verif.zip");
          //setez problema ca descarcata
          if (! mysql_query("update problems set actualizat=1 where id = {$problemId}"))
			die("Nu pot seta problema ca descarcata  - functia SetProblem");
  }
  else
  {
          //directorul exista
          //echo "Arhiva de teste exista\n";
  }      
  return $l['title'];
}

function FinalizeSource($sourceId , $score, $compilerMessage)
{
  $q="update sources set status='complete', score=".$score.", compilerMessage='".addslashes($compilerMessage)."' where id=".$sourceId;
  mysql_query($q) or print mysql_error();
}

function FileContent($file_name,$size=0)
{
  $f = fopen($file_name,"r");
  if($size == 0)
    $size= filesize($file_name);
  $content = fread($f,$size);
  fclose($f);
  return $content;
}

function FormatCompilerMessage($message)
{
  $s="<h2>Compiler message</h2><pre style=\"white-space:normal;padding:5px;background:#ccc;\">".nl2br($message)."</pre>";
  return $s;
}

function FormatTableRow($message, $test_number)
{
  $rez=strtok($message," \t");
  $time=strtok(" \t");
  $memory=strtok(" \t");
  $score=strtok(" \t");
  $mm="";
  $cuvant=strtok(" \t");
  while($cuvant !== false)
  {
    $mm .= " ".$cuvant;
    $cuvant=strtok(" \t");
  }
  $result=array('rez' => $rez , 'time' => $time , 'memory' => $memory , 'message'=>$mm, 'score'=>$score);
  return $result;
  //return "<tr> <td align=\"center\">".$test_number."</td> <td align=\"center\">".$time."</td> <td align=\"center\">".$memory." KB</td> <td>".$mm."</td> <td align=\"center\">".$score."</td> </tr>";
}

function RunitResult($message)
{
  $result=array();
  $result['rez']=strtok($message," \t");
  $result['time']=strtok(" \t");
  $result['memory']=strtok(" \t");
  $result['score']=strtok(" \t");
  $mm="";
  $cuvant=strtok(" \t");
  while($cuvant !== false)
  {
    $mm .= " ".$cuvant;
    $cuvant=strtok(" \t");
  }
  $result['message']=$mm;
  return $result;
}

?>
