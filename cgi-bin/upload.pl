#!/usr/bin/perl

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
if (index($contenttype, "text") < 0 && index($contenttype, "application/octet-stream")) {
	print "Sorry, your content was not uploaded.<br>";
	print "Please only upload text files.<br>";
	print "</body></html>";
	exit;
}
else {
	print "<html><body>";
	print "Your file has been uploaded to $upload_dir$filename\n<br>";
	print "Content in body:<br>";
	print "$body<br>"
}
print "</body></html>";
	
my $upload_file = $upload_dir.$filename;
open(FH, '>', $upload_file) or die $!;
print FH $body;
close(FH);

1;