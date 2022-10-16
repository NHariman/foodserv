#!/usr/bin/perl
use MIME::Base64;

read (STDIN, $buffer, $ENV{'CONTENT_LENGTH'});

$upload_dir = "www/upload/"; #ensure this is writable by webserver user
$content_type = $ENV{'CONTENT_TYPE'};

$boundary_position = index($content_type, "boundary=");
$boundary = substr($content_type, $boundary_position + length("boundary="));

$content_disposition_start = index($buffer, "Content-Disposition:");
$content_disposition_end = index($buffer, "\r\n", $content_disposition_start);
$content_disposition_end = index($buffer, "\r\n", $content_disposition_end + 2);
$content_disposition_len = $content_disposition_end - $content_disposition_start;

$content_disposition = substr($buffer, $content_disposition_start, $content_disposition_len);

$filename_start = index($content_disposition, "filename=\"");
$filename_end = index($content_disposition, "\"\r\n", $filename_start);
$filename_len = $filename_end - $filename_start - length("filename=\"");

$filename = substr($content_disposition, $filename_start + length("filename=\""), $filename_len);

$contenttype_start = index($content_disposition, "Content-Type: ");

$contenttype = substr($content_disposition, $contenttype_start + length("Content-Type: "));

$body = substr($buffer, $content_disposition_end);
$body_end = index($body, $boundary);
$body = substr($body, 0, $body_end - 2);

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
<title>DEFAULT PAGE</title>
</head>
<body>";
print "<div class=\"header\"></div>";

if (index($contenttype, "text") < 0 && index($contenttype, "application/octet-stream") || (-e $upload_dir.$filename)) {
	print "<div class=\"header-text\"><h1>UPLOAD FAILED</h1>
  <p>SORRY</p>
</div>";
}
else {
	print "<div class=\"header-text\"><h1>YOU JUST UPLOADED A FILE</h1>
  <p>GOOD JOB</p>
</div>";
}

print "<div class=\"topnav\">
  <a href=\"https://thesecatsdonotexist.com/\">Use the back button to go back, because I don't know how to do links in a cgi :(. If you click here though you go to thiscatdoesnotexist.com!</a>

</div>

<div class=\"row\">
  	<div class=\"leftcolumn\"></div>
  <div class=\"middlecolumn\">
    <div class=\"card\">";

if (index($contenttype, "text") < 0 && index($contenttype, "application/octet-stream")) {
	print "Sorry, your content was not uploaded.<br>";
	print "Please only upload text files.<br>";
	print "</body></html>";
}
elsif (-e $upload_dir.$filename) {
	print "This file name already exists, please try a different file.<br>";
}
elsif (index($contenttype, "image") > -1) {
	print "this is an image. :(";
  
}
else {
	print "Your file has been uploaded to $upload_dir$filename\n<br>";
	print "Content in body:<br>";
	print "$body<br>";
}

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

if (index($contenttype, "text") < 0 && index($contenttype, "application/octet-stream") || (-e $upload_dir.$filename) || index($contenttype, "image") > -1) {
	exit ;
}
elsif (index($contenttype, "image") > -1) {
  my $upload_file = $upload_dir.$filename;
  my $decoded= MIME::Base64::decode_base64($body);
open my $fh, '>', $upload_file or die $!;
binmode $fh;
print $fh $decoded;
close $fh
}
else {
my $upload_file = $upload_dir.$filename;
open(FH, '>', $upload_file) or die $!;
print FH $body;
close(FH);
}
1;