#!/usr/bin/perl -w

read (STDIN, $buffer, $ENV{'CONTENT_LENGTH'});

$upload_dir = "www/upload"; #ensure this is writable by webserver user
$content_type = $ENV{'CONTENT_TYPE'};

print "Content-type:text/html\r\n\r\n";


print "<html><body>uploaded to $upload_dir\n";
print "content in buffer:\n";
print "$buffer\n";
print "print content_type: $content_type\n";

print"</body></html>";

1;