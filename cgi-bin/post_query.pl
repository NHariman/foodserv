#!/usr/bin/perl

read (STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
@pairs = split(/&/, $buffer);
foreach $pair (@pairs) 
{
    ($name, $value) = split(/=/, $pair);
    $value =~ tr/+/ /;
    $value =~ s/%([a-fA-F0-9] [a-fA-F0-9])/pack("C", hex($1))/eg;
    $value =~ s/~!/ ~!/g;
    $FORM{$name} = $value;
}
   
if($FORM{python}) 
{
   $python_flag ="YES";
} 
else 
{
   $python_flag ="NO";
}
   
if($FORM{java}) 
{
   $java_flag ="YES";
}
else 
{
   $java_flag ="NO";
}
   
if($FORM{kotlin})
{
   $kotlin_flag ="YES";
} 
else
{
   $kotlin_flag ="NO";
}
   
if($FORM{perl}) 
{
   $perl_flag ="YES";
} 
else 
{
   $perl_flag ="NO";
}
   
if($FORM{swift}) 
{
   $swift_flag ="YES";
} 
else
{
   $swift_flag ="NO";
}
   
$first_name= $FORM{'first_name'};
$last_name= $FORM{'last_name'};
$payment_method= $FORM{'payment'};
$first_time= $FORM{'first_time'};
$feed_back= $FORM{'feedback'};
   
print "Content-type:text/html\r\n\r\n";
print "<!DOCTYPE html>
<html>
<head>
<meta charset=\"UTF-8\">
<style>
* {
  box-sizing: border-box;
  border: 0;
  margin: 0;

}


/* padding: 10px; */
body {
  font-family: verdana;
  font-size: 0.875em;
  text-align: center;
  background: #ebeced;
  word-break: break-all;
}

/* Header/Blog Title */
.header {
  position: absolute;
  left: 0px;
  top: 0px;
  width: 100%;
  height: 14%;
    padding: 30px;
    text-align: center;
    background-color: #89cff0;
    background-image: url(\"https://bestpetsvet.com/wp-content/uploads/2019/02/cat-2146089_1280.jpg\");
    background-size: cover;
    background-repeat: no-repeat;
    filter: blur(3px);
    -webkit-filter: blur(3px);
  z-index: -1;
}

.header-text {
  background-color: rgba(0, 0, 0, 0);
  color: rgb(247, 240, 235);
  font-size: 2em;
  padding: 30px;
  text-align: center;
  z-index: 2;
}

.header h1 {
  font-size: 50px;
}

/* Footer */
.footer {
    color: #dacac6;
    padding: 20px;
    text-align: center;
    background: rgb(33, 30, 29);
    margin-top: 20px;
    left:0;
    bottom:0;
    width: 100%;
    position: relative;
}

/* Style the top navigation bar */
.topnav {
  overflow: hidden;
  background-color: rgb(33, 30, 29);
}

/* Style the topnav links */
.topnav a {
  float: left;
  display: block;
  color: #f2f2f2;
  text-align: center;
  padding: 14px 16px;
  text-decoration: none;
}

/* Change color on hover */
.topnav a:hover {
  background-color: #ddd;
  color: black;
}

.banner {
  float:left;
  width: 100%;
  -moz-animation: marquee 10s linear infinite;
  -webkit-animation: marquee 10s linear infinite;
  animation: marquee 10s linear infinite;
}

.leftcolumn{
    float: left;
  width: 10%;
  padding: 15%;
}

/* Create two unequal columns that floats next to each other */
/* Left column */
.middlecolumn {   
  float: left;
  width: 35%;
}

/* Right column */
.rightcolumn {
  float: left;
  width: 15%;
  padding-left: 20px;
}

/* Fake image */
.fakeimg {
  background-color: #aaa;
  width: 100%;
  padding: 20px;
}

/* Add a card effect for articles */
.card {
  background-color: white;
  padding: 20px;
  margin-top: 20px;
}

.card img {
  width: 85%;
}

.middlecolumn p {
  margin: 0 auto;
  text-align: justify;
  width: 75%;
  line-height: 1.65;
  margin-bottom: 30px;
}

.middlecolumn li {
  line-height: 2;
}

/* Clear floats after the columns */
.row:after {
  content: \"\";
  display: table;
  clear: both;
}

#wrapper {
    max-width: 200px; /* max-width doesn't behave correctly in legacy IE */
    margin: 0 auto;
}
#wrapper img{
    width:100%;       /* the image will now scale down as its parent gets smaller */
}

/* Responsive layout - when the screen is less than 800px wide, make the two columns stack on top of each other instead of next to each other */
\@media screen and (max-width: 800px) {
  .header-text, .banner, .middlecolumn, .rightcolumn, .leftcolumn {   
    width: 100%;
    padding: 0;
  }
}

/* Responsive layout - when the screen is less than 400px wide, make the navigation links stack on top of each other instead of next to each other */
\@media screen and (max-width: 400px) {
  .topnav a {
    float: none;
    width: 100%;
  }
}

\@media screen and (max-width: 1000px) {
  .header {
    height: 19.75%;
  }
  .topnav {
    padding: 2%;
  }
}

\@keyframes spin {
	from {
		transform:rotate(0deg); 
	}to {
		transform:rotate(360deg);
	}
}

@-moz-keyframes marquee {
  0% {
    transform: translateX(100%);
  }
  100% {
    transform: translateX(-100%);
  }
}
@-webkit-keyframes marquee {
  0% {
    transform: translateX(100%);
  }
  100% {
    transform: translateX(-100%);
  }
}
\@keyframes marquee {
  0% {
    -moz-transform: translateX(100%);
    -webkit-transform: translateX(100%);
    transform: translateX(100%)
  }
  100% {
    -moz-transform: translateX(-100%);
    -webkit-transform: translateX(-100%);
    transform: translateX(-100%);
  }
}

.spin {
	width: 5%;
	animation-name: spin;
	animation-duration: 4000ms;
	animation-iteration-count: infinite;
	animation-timing-function: linear;
}
</style>
<title>GET PAGE</title>
</head>
<body>";
print "<div class=\"header\"></div>";
print "<div class=\"header-text\"><h1>YOU DID A POST</h1>
  <p>POST IT NOTE</p>
</div>";
print "<div class=\"topnav\">
  <a href=\"https://thesecatsdonotexist.com/\">Use the back button to go back, because I don't know how to do links in a cgi :(. If you click here though you go to thiscatdoesnotexist.com!</a>

</div>

<div class=\"row\">
  	<div class=\"leftcolumn\"></div>
  <div class=\"middlecolumn\">
    <div class=\"card\">";
print "<h3>Hello $first_name $last_name</h3>";
print "<h3>Here is your Purchased Order!</h3>";
print "<h3>Python: $python_flag</h3>";
print "<h3>Java: $java_flag</h3>";
print "<h3>Kotlin: $kotlin_flag</h3>";
print "<h3>Perl: $perl_flag</h3>";
print "<h3>Swift: $swift_flag</h3>";
print "<h3>Payment Method: $payment_method</h3>";
print "<h3>First Time Customer: $first_time</h3>";
print "<h3>Feedback: $feed_back</h3><br><br>";
print "Your receipt can be found at www/upload/$first_name.txt!\n";
print "</div>
  </div>
  <div class=\"rightcolumn\">
    <div class=\"card\">
      <h2>About Me</h2>
      <img src=\"/img/beans_flip_gif.gif\" style=\"text-align: center;\">
      <p>Beans.</p>
    </div>
    <div class=\"card\">
      <h3>Popular Post</h3>
      ฅ^•ﻌ•^ฅ 💕☕<br>
      /ᐠ - ˕ -マ <br>
      (^･o･^)ﾉ<br>
    </div>
    <div class=\"card\">
      <img src=\"https://media1.giphy.com/media/W80Y9y1XwiL84/giphy.gif?cid=790b7611740fc14ab849fa4994f935b5e1ecee9486c7a1a2&rid=giphy.gif&ct=g\">
    </div>
  </div>
</div>
<div class=\"footer\">
	<p><h2>Foodserv 1.0</h2></p>
</div>
</body></html>
";
   
my $str = <<END;
$first_name $last_name,
Your order was:
Python: $python_flag
Java: $java_flag
Perl: $perl_flag
Swift: $swift_flag
Payment Method: $payment_method
First Time Customer: $first_time
Feedback: $feed_back
Thank you!
END

my $filename = "www/upload/$first_name.txt";

open(FH, '>', $filename) or die $!;

print FH $str;

close(FH);
