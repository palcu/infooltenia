#!/usr/bin/php 
<?
	declare(ticks = 1);
	pcntl_signal(SIGINT, "signalHandler");
	function signalHandler($semnal){
		global $surse_evaluate, $teste_evaluate;
		print "\n\n\nDeci te-ai plictisit.... Cateva statistici:\n\t{$surse_evaluate} surse evaluate\n\t{$teste_evaluate} teste evaluate.\nBye bye!!\n\n\n";
		die();
	}
	
	
  if(posix_getuid()!=0)
  {
  		echo "\n\nScriptul trebui rulat cu drepturi de root, sau cu sudo...\n\n ";
		die();
  }
   exec("./clean-up.sh 2>/dev/null");
  require "z-config.php";
  require "z-functions.php";
  
  ConfirmMySQLServer();
  
  mysql_connect($host, $user, $password) or die ("Nu ma pot conecta la serverul MySQL\n");
  mysql_select_db($db) or die("Nu pot deschide baza de date\n");
  
  //ce evaluez (toate sursele, sau doar cele ramase in executing si pending)
  ConfirmSourceStatus();
  
  //Sterge testele existente
  
  
  echo "\nSterge testele existente\n";
  $cmd="rm -r prob/* 2> /dev/null";
  exec($cmd);
  
  
  $task_type='normal';
  $surse_evaluate = 0;
  $teste_evaluate = 0;
  while(1)
  {
  	//$cmd="rm -r prob/* 2> /dev/null";
    //exec($cmd);
    $noJob=TRUE;
    echo "\n".date("Y.m.d h:i:s")."\n";
    //caut sursa in asteptare
    $q="select * from `sources` where `status` like 'pending' and problemId not in (SELECT id FROM problems WHERE problemType LIKE 'offline') order by `uploadTime` limit 1 for update";
    if($check_offline)
    	$q="select * from `sources` where (`status` like 'pending')  order by `uploadTime` limit 1 for update";
    $r=mysql_query($q);
    if(mysql_num_rows($r)==0)
    {
      //daca nu am
      echo "No source pending\n";
      
    }
    else
    {
      $noJob=FALSE;
      //daca am sursa, o extrag
      $l=mysql_fetch_array($r);
      //setez executing pe sursa
      echo "Source ID : ". $l['id']." \n";
      $sourceId=$l['id'];
      
      mysql_query("DELETE FROM tests_result WHERE sourceId=$sourceId");
      
      $qq="update sources set status='executing' where id=".$l['id'];
      $rr=mysql_query($qq);
      
      //determin datele concurentului
      $q2="select * from useri where id=".$l['userId'];
      $r2=mysql_query($q2);
      if(mysql_num_rows($r2)>0)
      {
        //rezolv chestiunile legate de problema
        $linie_user=mysql_fetch_array($r2);
        echo "User ID   :".$linie_user['user']."\n";
        $problemTitle = SetProblem($l['problemId']);
        echo "Problem ID: ".$problemTitle."\n";
        //scriu sursa
        if(! file_exists("stud/evaluator"))
          mkdir("stud/evaluator");
          
        $cmd="rm stud/evaluator/* -r";
        exec($cmd, $output, $return_value);
        
        $sourceName="stud/evaluator/".$l['fileName'];
        $f=fopen($sourceName,"w");
        fwrite($f , $l['source']);
        fclose($f);
        if($task_type=='normal' || $task_type=='interact')
      	{
        	//compilez
        	echo "Compilez ....";
        
        	if($l['fileExtension']!='pas')
          		$cmd="cd stud/evaluator; ".sprintf($compile[$l['fileExtension']], $l['fileName'])." 2> ../../log/compiler";
        	else
          		$cmd="cd stud/evaluator; ".sprintf($compile[$l['fileExtension']], $l['fileName'])." > ../../log/compiler";
        	$return_value = 1;
        	exec($cmd,$output,$return_value);
        	echo "DONE\n";
        	if($return_value>0)
        	{
          		echo "Compile error\n";
          		$total=-1;
          		$rezultat_executie="";
        	}
        	else
        	{
          		echo "Running test :\n";
          		$stud_tmp_dir="stud/evaluator/".$problemTitle.".tmp";
          		if(!file_exists($stud_tmp_dir))
		            mkdir($stud_tmp_dir);
          		if(!rename("stud/evaluator/the.exe", $stud_tmp_dir."/the.exe"))
          		{
	            	echo "Cannot move exe file !!!!\n\n";
            		sleep(5);
          		}          
          		$test_number = explode("\n", FileContent("prob/".$problemTitle."/tests.txt"));
	          
          		$total = 0;
          		foreach($test_number as $test_line)
	            	if(trim($test_line)!="")
            		{
              		$test_line = explode(" ",trim($test_line));
              		$test=$test_line[0];
              		echo $test." ";
              		$cmd = "./eval.sh -- ".$problemTitle." evaluator ".$test." ";
              		exec($cmd);
              		if(file_exists("work/test.res"))
              		{
                		$fc = FileContent("work/test.res",500);
                		//echo $fc,"\n";
                		$rezultat_executie = FormatTableRow($fc, $test); //vector
	                	$v = explode(" ",$fc);
   	             	$total += $rezultat_executie['score'];// $v[3];
              		}
              		else
                		$rezultat_executie = FormatTableRow("badeval 0.0 0 0 Evaluation error", $test);
              		$qaddTest=sprintf("INSERT INTO tests_result VALUES (NULL, %d, %d, %f, %f, '%s', %d )",$sourceId, $test, $rezultat_executie['time'],$rezultat_executie['memory'], $rezultat_executie['message'],$rezultat_executie['score']);
              		mysql_query($qaddTest);
            		}
          		echo "\nDone: ".$total." puncte\n";
          
        	}
        
        	$rezultat_compilare = FileContent("log/compiler",10000);
        
        	FinalizeSource($l['id'], $total ,  $rezultat_compilare);
        	}
			else
			if($task_type=='offline')
			{
			//problema offline
				
				$cmd="unzip $sourceName -d ./stud/evaluator";
				exec($cmd , $output, $return_value);
				if($return_value)
				{
					die ("Nu pot dezarhiva fisierele pt output only\n");
				}
				$test_number = explode("\n", FileContent("prob/".$problemTitle."/tests.txt"));
				$total = 0;
				foreach ($test_number as $test_line)
					if(trim($test_line) != "")
					{
						
						$test_line = explode(" " , trim($test_line));
						$test= $test_line[0];
						$score= $test_line[1];
						print "$test ";
						$out_file = "stud/evaluator/$problemTitle-out/$test-$problemTitle.out";
						
						if(file_exists($out_file))
						{
							
							
							$cmd = "cp ./stud/evaluator/$problemTitle-out/$test-$problemTitle.out work-offline/$problemTitle.out -v";
							exec($cmd,$output,$return_value);
							
							if(file_exists("prob/$problemTitle/$test-$problemTitle.ok"))
							{
								$cmd = "cp prob/$problemTitle/$test-$problemTitle.ok work-offline/$problemTitle.ok -v";
								exec($cmd,$output,$return_value);
								
							}
							if(file_exists("prob/$problemTitle/$test-$problemTitle.in"))
							{
								$cmd = "cp prob/$problemTitle/$test-$problemTitle.in work-offline/$problemTitle.in -v";
								exec($cmd,$output,$return_value);
								
								
								if(!file_exists("prob/$problemTitle/verif"))
								{
									$message = "badtask\t0.0\t0\t0\tMissing verifier";
									
								}
								else
								{
									$cmd = "cp prob/$problemTitle/verif work-offline/";
									exec($cmd,$output,$return_value);
									
									if(!file_exists("prob/$problemTitle/params.sh"))
									{
										$message = "badtask\t0.0\t0\t0\tMissing params.sh";
									}
									else
									{
										$cmd = "cp prob/$problemTitle/params.sh work-offline/";
										exec($cmd,$output,$return_value);
										$cmd = "cd work-offline/; ./verif $problemTitle.in $problemTitle.out $problemTitle.ok $score";
										
										$ss = exec($cmd,$output,$return_value);
										$message = "vok\t0\t\0\t$ss";
										
									}
								}
							}
							else
							{
								$message = "badtask\t0.0\t0\t0\tMissing input file $test-$problemTitle.out";
							}
						}
						else
						{
							$message = "missout\t0.0\t0\t0\tMissing output file $test-$problemTitle.out";
						}
						$rezultat_executie = FormatTableRow($message, $test);
              			$qaddTest=sprintf("INSERT INTO tests_result VALUES (NULL, %d, %d, %f, %f, '%s', %d )",$sourceId, $test, $rezultat_executie['time'],$rezultat_executie['memory'], $rezultat_executie['message'],$rezultat_executie['score']);
              			$total += $rezultat_executie['score'];
              			mysql_query($qaddTest);
					}
				echo "\nDONE: $total puncte\n";
				FinalizeSource($l['id'], $total ,  "Offline task. No compilation.");
				exec("rm work-offline/*");
			}
			else
			{
				//problema interactiva. De facut
			}
       // exec("./clean-up.sh 2>/dev/null");
        //exec("rm stud/evaluator/* -r 2> /dev/null");
      $surse_evaluate++;
      }
      else
      {
        //nu exista userul. sursa orfana
        echo "Userul care a trimis sursa nu mai exista. O sterg\n\n";
        $q1="delete from sources where id=".$l['id'];
        $r1 = mysql_query($q1);
        
      }
	}
    //caut test in asteptare
    $q="select * from `test_jobs` where `status`='pending' order by `uploadTime` limit 1 for update";
    $r = mysql_query($q);
    if(mysql_num_rows($r)==0)
    {
      print "No tests pending\n";
    }
    else
    {
      echo "Running test job. id=".$l['id']."\n";
      $l=mysql_fetch_array($r);
      $q="update `test_jobs` set `status`='executing' where id=".$l['id'];
      mysql_query($q);
      
      //citesc datele problemei
      $qproblem = "select `inFile`, `outFile`,`memoryLimit`,`stackLimit`,`timeLimit` from problems where id=".$l['problemId'];
      $rproblem = mysql_query($qproblem);
      $lproblem= mysql_fetch_array($rproblem);
      
      //descarc sursa
      $qsursa = "select `source`,`fileName`,`fileExtension` from sources where id=".$l['sourceId'];
      $rsursa = mysql_query($qsursa);
      $lsursa = mysql_fetch_array($rsursa);
      
      //scriu fisierul de intrare
      echo "Writing input file...";
      $f = fopen ("work-test/".$lproblem['inFile'], "w");
      fwrite($f , $l['input']);
      fclose($f);
      echo  "  DONE\n";
      
      //scriu fisierul sursa
      echo "Writing source file ... ";
      $f = fopen("work-test/".$lsursa['fileName'],"w");
      fwrite($f, $lsursa['source']);
      fclose($f);
      echo " DONE\n";
      
      
      echo "Compiling source ....";
      if($l['fileExtension']!='pas')
          $cmd="cd work-test; ".sprintf($compile[$lsursa['fileExtension']], $lsursa['fileName'])." 2> ../log/compiler";
      else
          $cmd="cd work-test; ".sprintf($compile[$lsursa['fileExtension']], $lsursa['fileName'])." > ../log/compiler";
      $return_value = 1;
      exec($cmd,$output,$return_value);
      echo "DONE\n";
      $status=array();
      $output="";
      if($return_value>0 || !file_exists("work-test/the.exe"))
      {
        echo "Compile error\n";
        $status['time']=0.0;
        $status['message']="Compile error";
        $output=FormatCompilerMessage(FileContent("log/compiler",10000));
      }
      else
      {
        echo "Running test ... \n";
        $cmd = 'cd work-test; ../env/linux/runit the.exe nobody '.$lproblem['timeLimit'].' '.$lproblem['memoryLimit'].' '.$lproblem['stackLimit'].' /dev/null "" 0 > runstat.tmp';
        //print $cmd."\n";
        exec($cmd);
        if(!file_exists("work-test/runstat.tmp"))
        {
          $status['time']=0.0;
          $status['message']="Evaluation error";
        }
        else
        {
          $status=RunitResult(file_get_contents("work-test/runstat.tmp"));
          //print_r($status);print "\n";
          if($status['rez']=="runok")
          {
            if(file_exists("work-test/".$lproblem['outFile']))
            {
              $output=file_get_contents("work-test/".$lproblem['outFile']);
              $status['message']="Run OK. Output not verified!";
            }
            else
              $status['message']="Run OK . No output file!";
          }
          else
          {
            
          }
	  echo $status['message']."\n";
        }
      }
      
      //scriu rezultatele
      $q="update `test_jobs` set `output`='".addslashes($output)."', `status`='complete', `eval_status`='".$status['message']."', `time`=".$status['time']." where id=".$l['id']."";
      $r=mysql_query($q);
      $noJob=false;     
      exec("rm work-test/* -rf");
      $teste_evaluate++;
    }
    if($noJob)
    {
      sleep(1);
    }
	}
?>
