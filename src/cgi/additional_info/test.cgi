#!/Users/nhariman/homebrew/bin/python3
import sys

print("Content-type:text/html\r\n\r\n")
print ("<html>")
print ("<head><title>My First CGI Program</title></head>")
print ("<body>")
print ("<p> Hello Program!! </p>")
print ("</body>")
print ("</html>")
print ('Number of arguments:', len(sys.argv), 'arguments.')
print ('Argument List:', str(sys.argv))