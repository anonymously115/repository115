<!DOCTYPE html>
<html lang="ja">
	<head>
		<meta charset="utf-8">
		<title>FizzBuzz</title>
	</head>
	<body>
<?php
			$m=array_key_exists("num",$_POST)?$_POST["num"]:100;
			$n=array_key_exists("num",$_POST)?$_POST["num"]:0;
			$a=array_key_exists("fizz",$_POST)?$_POST["fizz"]:3;
			$b=array_key_exists("buzz",$_POST)?$_POST["buzz"]:5;
?>
		<form method="post">
			<label for="num">n=</label>
			<?php echo '<input type="number" id="num" name="num" min="0" max="100" value="'.$m.'"><br>'."\n" ?>
			<label for="fizz">a=</label>
			<?php echo '<input type="number" id="fizz" name="fizz" min="1" max="10" value="'.$a.'"><br>'."\n" ?>
			<label for="buzz">b=</label>
			<?php echo '<input type="number" id="buzz" name="buzz" min="1" max="10" value="'.$b.'"><br>'."\n" ?>
			<input type="submit" value="FizzBuzz">
		</form>
<?php
			for($i=1;$i<=$n;$i++){
				echo "\t\t";
				if($i%$a==0 && $i%$b==0){
					echo 'FizzBuzz';
				}elseif($i%$a==0){
					echo 'Fizz';
				}elseif($i%$b==0){
					echo 'Buzz';
				}else{
					echo $i;
				}
				echo '<br>'."\n";
			}
?>
	</body>
</html>
