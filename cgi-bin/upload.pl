#!/usr/bin/perl -w
  use CGI;

  $upload_dir = "www/upload"; #ensure this is writable by webserver user

  $query = new CGI;

  if (!$query){
    print "could not find \$query";
    exit;
    }

  $filename = $query->param("uploaded_file");
  $filename =~ s/.*[\/\\](.*)/$1/;
  $upload_filehandle = $query->upload("uploaded_file");

  if (!$filename) {
    print "could not fufill: \$query->param(\"uploaded_file\")";
print $query->header ( );
  print <<END_HTML;
  <HTML>
  <HEAD>
  <TITLE>SORRY!</TITLE>
  </HEAD>
  <BODY>
  <P>Couldn't upload!</P>
  </BODY>
  </HTML>
END_HTML
    return;
  }

  open UPLOADFILE, ">$upload_dir/$filename";

  while ( <$upload_filehandle> )
  {
    print UPLOADFILE;
  }

  close UPLOADFILE;

  print $query->header ( );
  print <<END_HTML;
  <HTML>
  <HEAD>
  <TITLE>Thanks!</TITLE>
  </HEAD>
  <BODY>
  <P>Thanks for uploading your photo!</P>
  <P>Your photo:</P>
  <img src="www/upload/$filename" border="0">
  </BODY>
  </HTML>
END_HTML