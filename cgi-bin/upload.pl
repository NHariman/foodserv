#!/usr/bin/perl -w

read (STDIN, $buffer, $ENV{'CONTENT_LENGTH'});

$upload_dir = "www/upload"; #ensure this is writable by webserver user


print "Content-type:text/html\r\n\r\n";


print "<html><body>uploaded to $upload_dir";
print "content in buffer:";
print "$buffer";

print"</body></html>";

1;