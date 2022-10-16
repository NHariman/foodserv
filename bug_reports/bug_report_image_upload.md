# IMAGE POSTING BUG REPORT, EXAMPLES
Use ctrl+f to find BUG REPORT COMMENT to find the comments and differences.


BUG REPORT COMMENT: ///////////////////////////////////////////////////////////////////////////////////SUCCESS/FAILURE
// comment will be here. the top indicates if this bug report comment has to do with a succesful run or failed run. //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# Regular POST request via cgi for a form, SUCCESS
```
************* START CLIENT REQUEST *************
GET /post_cgi.html HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/upload.html
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
GET /css/basic_css.css HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/css,*/*;q=0.1
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/post_cgi.html
Sec-Fetch-Dest: style
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
GET /img/beans_flip_gif.gif HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: image/avif,image/webp,*/*
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/post_cgi.html
Sec-Fetch-Dest: image
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
POST /cgi-bin/post_query.pl HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Content-Type: application/x-www-form-urlencoded
Content-Length: 75
Origin: http://localhost
Connection: keep-alive
Referer: http://localhost/post_cgi.html
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1
Sec-GPC: 1

first_name=d&last_name=d&kotlin=yes&payment=Paypal&first_time=No&feedback=d
************* END CLIENT REQUEST *************

BUG REPORT COMMENT: ////////////////////////////////////////////////////////////SUCCESS
// I have the DEBUG flag on, in here the CGI code is called and then executes the cgi//
///////////////////////////////////////////////////////////////////////////////////////
path: /Users/nhariman/codam/webserv/cgi-bin/post_query.pl
CGI: cgi_pass extension: .pl
execute with path: /usr/bin/perl
executable_path: /usr/bin/perl
true
validate extension
_path in Validate Extension: /Users/nhariman/codam/webserv/cgi-bin/post_query.pl
file_name in HasExtension: /Users/nhariman/codam/webserv/cgi-bin/post_query.pl
extension in HasExtension: .pl
hasextension has been validated
In GetQuery: first_name=d&last_name=d&kotlin=yes&payment=Paypal&first_time=No&feedback=d
/usr/bin/perl
/Users/nhariman/codam/webserv/cgi-bin/post_query.pl
CONTENT_LENGTH=75
CONTENT_TYPE=application/x-www-form-urlencoded
DOCUMENT_ROOT=www/html
PATH_INFO=/Users/nhariman/codam/webserv/cgi-bin/post_query.pl
REMOTE_HOST=localhost
REQUEST_METHOD=POST
SCRIPT_FILENAME=/Users/nhariman/codam/webserv/cgi-bin/post_query.pl
SCRIPT_NAME=/Users/nhariman/codam/webserv/cgi-bin/post_query.pl
SERVER_NAME=localhost
SERVER_PORT=
SERVER_PROTOCOL=HTTP/1.1
SERVER_SOFTWARE=foodserv
_valid_file true


BUG REPORT COMMENT: /////////////////////////////////////////////SUCCESS
// after execution, the _content is printed post cgi script execution //
////////////////////////////////////////////////////////////////////////
content: Content-type:text/html

<html><head><title>GeeksForGeeks - Post Method</title></head><body><h3>Hello d d</h3><h3>Here is your Purchased Order!</h3><h3>Python: NO</h3><h3>Java: NO</h3><h3>Kotlin: YES</h3><h3>Perl: NO</h3><h3>Swift: NO</h3><h3>Payment Method: Paypal</h3><h3>First Time Customer: No</h3><h3>Feedback: d</h3></body></html>Your receipt can be found at www/upload/d.txt!
```

# Using upload.html with a .cpp file, SUCCESS

```
************* START CLIENT REQUEST *************
GET /upload.html HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/post_cgi.html
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
GET /css/basic_css.css HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/css,*/*;q=0.1
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/upload.html
Sec-Fetch-Dest: style
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
GET /img/beans_flip_gif.gif HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: image/avif,image/webp,*/*
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/upload.html
Sec-Fetch-Dest: image
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
POST /cgi-bin/upload.pl HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Content-Type: multipart/form-data; boundary=---------------------------118506401310246102853553464584
Content-Length: 1539
Origin: http://localhost
Connection: keep-alive
Referer: http://localhost/upload.html
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1
Sec-GPC: 1

-----------------------------118506401310246102853553464584
Content-Disposition: form-data; name="uploaded_file"; filename="Zombie.cpp"
Content-Type: application/octet-stream

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 13:56:59 by nhariman      #+#    #+#                 */
/*   Updated: 2021/12/09 17:21:32 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{}

Zombie::~Zombie()
{
	std::cout << this->_name << " has been slain.\n";
}

void		Zombie::announce(void)
{
	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ...\n";
}
void		Zombie::setName(std::string name)
{
	this->_name = name;
}

-----------------------------118506401310246102853553464584
Content-Disposition: form-data; name="submit"

Uploadfile
-----------------------------118506401310246102853553464584--

************* END CLIENT REQUEST *************

BUG REPORT COMMENT: ////////////////////SUCCESS
// here the cgi code is called and processed //
///////////////////////////////////////////////
path: /Users/nhariman/codam/webserv/cgi-bin/upload.pl
CGI: cgi_pass extension: .pl
execute with path: /usr/bin/perl
executable_path: /usr/bin/perl
true
validate extension
_path in Validate Extension: /Users/nhariman/codam/webserv/cgi-bin/upload.pl
file_name in HasExtension: /Users/nhariman/codam/webserv/cgi-bin/upload.pl
extension in HasExtension: .pl
hasextension has been validated
In GetQuery: // what's in the query string -----------------------------118506401310246102853553464584
Content-Disposition: form-data; name="uploaded_file"; filename="Zombie.cpp"
Content-Type: application/octet-stream

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 13:56:59 by nhariman      #+#    #+#                 */
/*   Updated: 2021/12/09 17:21:32 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{}

Zombie::~Zombie()
{
	std::cout << this->_name << " has been slain.\n";
}

void		Zombie::announce(void)
{
	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ...\n";
}
void		Zombie::setName(std::string name)
{
	this->_name = name;
}

-----------------------------118506401310246102853553464584
Content-Disposition: form-data; name="submit"

Uploadfile
-----------------------------118506401310246102853553464584--

/usr/bin/perl
/Users/nhariman/codam/webserv/cgi-bin/upload.pl
CONTENT_LENGTH=1539
CONTENT_TYPE=multipart/form-data; boundary=---------------------------118506401310246102853553464584
DOCUMENT_ROOT=www/html
PATH_INFO=/Users/nhariman/codam/webserv/cgi-bin/upload.pl
REMOTE_HOST=localhost
REQUEST_METHOD=POST
SCRIPT_FILENAME=/Users/nhariman/codam/webserv/cgi-bin/upload.pl
SCRIPT_NAME=/Users/nhariman/codam/webserv/cgi-bin/upload.pl
SERVER_NAME=localhost
SERVER_PORT=
SERVER_PROTOCOL=HTTP/1.1
SERVER_SOFTWARE=foodserv
_valid_file true


BUG REPORT COMMENT: ///////////////////////////////SUCCESS
// here it also responds properly and returns correctly.//
//////////////////////////////////////////////////////////
content: Content-type:text/html

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
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
    background-image: url("https://bestpetsvet.com/wp-content/uploads/2019/02/cat-2146089_1280.jpg");
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
  content: "";
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
@media screen and (max-width: 800px) {
  .header-text, .banner, .middlecolumn, .rightcolumn, .leftcolumn {   
    width: 100%;
    padding: 0;
  }
}

/* Responsive layout - when the screen is less than 400px wide, make the navigation links stack on top of each other instead of next to each other */
@media screen and (max-width: 400px) {
  .topnav a {
    float: none;
    width: 100%;
  }
}

@media screen and (max-width: 1000px) {
  .header {
    height: 19.75%;
  }
  .topnav {
    padding: 2%;
  }
}

@keyframes spin {
	from {
		transform:rotate(0deg); 
	}to {
		transform:rotate(360deg);
	}
}

moz-keyframes marquee {
  0% {
    transform: translateX(100%);
  }
  100% {
    transform: translateX(-100%);
  }
}
webkit-keyframes marquee {
  0% {
    transform: translateX(100%);
  }
  100% {
    transform: translateX(-100%);
  }
}
@keyframes marquee {
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
<body><div class="header"></div><div class="header-text"><h1>YOU JUST UPLOADED A FILE</h1>
  <p>GOOD JOB</p>
</div><div class="topnav">
  <a href="https://thesecatsdonotexist.com/">Use the back button to go back, because I don't know how to do links in a cgi :(. If you click here though you go to thiscatdoesnotexist.com!</a>

</div>

<div class="row">
  	<div class="leftcolumn"></div>
  <div class="middlecolumn">
    <div class="card">Your file has been uploaded to www/upload/Zombie.cpp
<br>Content in body:<br>

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 13:56:59 by nhariman      #+#    #+#                 */
/*   Updated: 2021/12/09 17:21:32 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{}

Zombie::~Zombie()
{
	std::cout << this->_name << " has been slain.\n";
}

void		Zombie::announce(void)
{
	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ...\n";
}
void		Zombie::setName(std::string name)
{
	this->_name = name;
}

<br></div>
  </div>
  <div class="rightcolumn">
    <div class="card">
      <h2>About Me</h2>
      <img src="/img/beans_flip_gif.gif" style="text-align: center;">
      <p>Beans.</p>
    </div>
    <div class="card">
      <h3>Popular Post</h3>
      ฅ^•ﻌ•^ฅ 💕☕<br>
      /ᐠ - ˕ -マ <br>
      (^･o･^)ﾉ<br>
    </div>
    <div class="card">
      <img src="https://media1.giphy.com/media/W80Y9y1XwiL84/giphy.gif?cid=790b7611740fc14ab849fa4994f935b5e1ecee9486c7a1a2&rid=giphy.gif&ct=g">
    </div>
  </div>
</div>
<div class="footer">
	<p><h2>Foodserv 1.0</h2></p>
</div>
</body></html>


************* START CLIENT REQUEST *************
GET /img/beans_flip_gif.gif HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: image/avif,image/webp,*/*
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/cgi-bin/upload.pl
Sec-Fetch-Dest: image
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Sec-GPC: 1


************* END CLIENT REQUEST *************
```
# BAD REQUEST, ATTEMPT TO UPLOAD AN IMAGE WITH UPLOAD.HTML, DOES NOT REACH CGI CODE
```

************* START CLIENT REQUEST *************
GET /favicon.ico HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: image/avif,image/webp,*/*
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Referer: http://localhost/upload.html
Sec-Fetch-Dest: image
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Sec-GPC: 1


************* END CLIENT REQUEST *************


************* START CLIENT REQUEST *************
POST /cgi-bin/upload.pl HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:105.0) Gecko/20100101 Firefox/105.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-CA,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Content-Type: multipart/form-data; boundary=---------------------------89322681528612771194264535139
Content-Length: 90779
Origin: http://localhost
Connection: keep-alive
Referer: http://localhost/upload.html
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1
Sec-GPC: 1

-----------------------------89322681528612771194264535139
Content-Disposition: form-data; name="uploaded_file"; filename="088.jpg"
Content-Type: image/jpeg

����%89:HIJWXYZghijwxyz�����������������������������������������������������������	
��)*789:FGHIJUVWXYZdefghijstuvwxyz��������������������������������������������������������������������������������f�R�i��
�Ke��e��p�΂� �B�Qu�����N1�����4Ｎy�	�Lun3��I6��4m�SSZ��2'H�;j�SX�J�������r�	��gڦ:���1��Hi�l)����ju[<��O��E��y���:mNFE�Ē�m�6�~mU�K��2S��y(�SU�7{����O��;�⸟Q��5Y�Z���m�h��e�p`����l��;
Fh�;��욚���5��j��� +���d�r(Q�^ �DtOG3�ZL+_�A�E����y�)&��擶T~�5��ۧ���e@5���R�ְƢ�7����̫�Q�����~�,sU0��3	�J��>}ބ�jjjkT�@:\��N�'+�ܸ@�Aiք�BkT�kG	K�y�
������uJ�S�X�Y���u����S�ʦ�ڈ�󤫡��+ۭ��I�w#.��}^��툎�@袰�D� ���~H;�zN�k�I������=X�[h):�k�/�.�:-�SZ�%BkGR�{�&���XJ�v�<\]&d�E�����_T���T��jkT�"U���8=?ָ�{�r�/ʭ���5!��I2-J)Nc��t�ԸX/#��Ɣ�L�$�Z��>G������8=R���668#�n��V[^a�zg��.?�/������5�BP�&�uZg�9�/���pY�;vp6�T�CFE�f�	��֭~Si����g��6���|^�����x�??���>S��rm�Hi�RL�Ky�_D��~9\������IR�����r��=�M�ѷ�jP��<L�&GDe�����"i�V�FE5"Պ��4&��
XRv	���>?�ǟ�u�zV�N�yst3�+Q�>~�g�'�|�7�b�S�T�
Z�*[����ʨ5;�;@�cM<R����q��_F��@
3r�ЅU���,�iѩ�}���]���{_��T�� jkABTd�z�x��L^&D
&f���^�j�zuMMjULp�ڜg
��+�0��:�/Vz�c�w>��|������*g�=:����/��#e��4+ȫe`A*�X��z	�:��8����.�"k��Ն�J�o�k���H�}j�oZ����|�,��j6y�
����wt���ב��Y}�Q�|ʹlk j(_E�M"��B��-&�5��aLތW����|Ǹj8�fЩaV����²�F�\��7@��I#M�~g��=chMaW7I��"f�U�j��(Z3Z�H����rV�kT�֥WQ�V�ǈ�g�\W�IU!����x�퟇�����L��|ܮ�H�r��N��B������
���g1�4����$�%�W�ٽEl�$�Ի��B���������<n٬`�b+�3��
�\0jA*������%�t�>��N�8�LܮZ!:4}�6͎�SD}��[�F�ABњբ�5*��³^�֩��]�_b8_d�C��ۈ�Ck��[������cɃ��`z[?�^��1��G�Cw�\;h=���||�y��+MaMI+Un���;>�M��rQT��U{>�cf�=��;N=�I�����؄��=��g%C��pw3a�S�\�O:��S��������������<UwT{��P^�����
C`f���*����V�7&*�
��s�z�j��J��׾݄-̒A�lBMv�x��J�b�ԅ�Yx�����]ZZ�
	X����D�ﭾ\HemS5�:�^ye��}A�H6�s��"��5s�;+N#�͞��xoGؼ����[��氹�a�^�'��}*��������RVk�2\�h�3gk,��/3׭��F���S�����@.��@:�.b��]�.�W(��^�{��~}n�
WI�\��Z�S�d�S�B�g��R֣��?
��Ey�۽�-G-�^M�{�ޱ�}[�#;O7��>�����yRJ��ف�dY+}}�/��}�� J5�4����p�Y��U}���Z��;�J�_S�>����`Mj	B�iڛPH	)B561����wG��O��{̓G~{�����������=^ڡ������蚐;_.s�5��Q�z,�j�Þ�n���
kWs����w�[s�w^3�ސ��g��y�_D�����܃��D@�fHi���@~�r_s���'���+S5��"��Z]`���t�
�Z�T��{��d��j�A�H ��VjťV��S@53��}ך
Ӷ��������t<�����>W3��w͋�Q���.�$��,�1�ybc��-Ut\�kj�ǚ�^�����i�C��A&�}P�j���������O������)�	����HW��+�>CO���@
���b"����$��j�\Oe�������z�9�5�8E �E��V5jW����_��>���H�[m���ac�vtu��W��{͈���4�ς�N�E�8m���m��h�X�=6f���2)����)U1Ԭ���>��������yi5�4�H�@�E$��`X��bUNglq'�p1TXV�.��d�
�WY�ݶ�n�I��fԚ�aE.#4޹�387
�ޗ	����'��iz77|�r��}��њ��Z�����|����1�*���4�&��
��:�k��jjk"��55�h����.�[�:�ԞV�U�%$�RN�y6x���nK��(�����GTԊbEZ�|�N����E��mZ���g_��~'OK��Z�@hu�kQh�ةt"LȷVdEg����Xs�]���|�;�}_H�w�g��������4�;t�S�mm�>�w]���FDf�M(	�6���k�5^�Z)�DUL��
P�F2����}��/҉�Z#"�-���P[�����&@�u��k�?���4b�j��G'�	��&�,*����[�;�Ӵ��R7�bU&�_�Ms΍�z
������e��z�?;v~����]N�E���ss�+��p��,��Ѯ��2�N�7�0P�L�
U[,���T�`bdp�	�E�:IR����t3��7��H�=�j�§���|oV���.<���19o�˜�o�K,F
�5�h�(t�=����s�6�����6{\�l� ��G\ö��E�L�nCRH��X�V*��x��O���|���v\|\�WR�`�P�ٳ�=]&�ա5�P��9���w2���(�L2�.uF���m
E50�ԡM9���>o���K�>/v���D^�z_�ɏ�|�;��-��?շ��q�%6�Δ��K��XzFa�d�SZ���p2:��r8�`.W�&�l��N�.�ɰ��G\��׷T֥
jE0��\���}���}{��l6x�B�W������#��6�O�A�d8�K�˕��Q����|��C��:O/��4���MG5�Xݝ?? �C�L���ۧ�Ǘ���z�g�N��t�;�* �&
��4!�����Sp��g��ྦྷ�T��g���e�

�!�%�\e��g
��N�)�T��֭XW�y��z�f��(z�	m	�
a��u?5�G�l.N���ǋE�_��}�����	��ʳgz��!P}%6=�^��w�L5(Pi�׷�r�I":���&*a�	�j�А16Ya�o�HRe
jjkV��8)u�2��L�o3>�փ�U@�t�^�u?+�i���=>����;S�;��>��>B�|�/���	P��ի��˟>��'��#��3}$RmJ�KQ��1�W7e�>L�5ڧ]��c%�fU"��zG�zE��b0P�`�hEk���ȉѲK�kV�֭S	�0Ը�Ek�W�jt�,�����K� :
�Rth�m,s�ѡ��%�|���֏���K�T�{�+��>s��~=�
����8�L�և�Q����O��u�87ҥ����45���Z6YeeΗܨ��K�3H�ڕJQA���U�գ��P0��f� U('�z�ge�n�7!�
�P�o,z;���&�Ս5��Z͘,V]Ô�����UӼ�o��n�;��9���n�W��v4��Ra瞷b�-�\���Ȧ�3~u�/o�B}������t���ן�~[�~����8�O`�	�t�\��i�z�tk Ȥڈ���$�(q�s�ҥQ�V�.��>w�x��,u�V�BM�0lC2	�y���f��8���.�������<���q1 �U�;�u���/S{��T/93�|�UV�'C��L���}���E�rg��Yy_��	���~�����~�P ϲ�!�_x�ƃ���{�+�s�|��o���/���91���?E��9(�۔���8y�D�}-���k"�-EC�:��V��nuj�N�ôs����H���k�f�&�@!��)���_������iV65�A����*�c���y�r��?gZ���b��Fn�*^g���뾛���~z���������s��{<B��n������֢�~g�y�T�"X��ڵW�%�q��n�pn܆��UjM�=�k�}P&�4"E�+w}�~3�Gݐ��N�5��Գv�~<�v���\`�\����v�v<�~�'A�.S�ӹ�q� �N��:5*<�u\<�}���(���1ӣV��|��t�󾯢���?JF���Y�tN�F?A�<���+O��[cZa�܀X��:I��T����
@Uj�H�7���GUcke˖��ǑրQQM`ڔeTᇭ���F�+У�;��u�x
�R6�A=����~��c���'۱@t��kvk�eI��Y�KO���i�zzʃFkR�t6�BPyqR�ݫ
���������{�2A�JҴ�s�}7=���n�9kTԋR�jkT�E�jkT���nU��qtZy,�>���EEj���h��MM.��Or�ʧ������E�;x�o�U�чQ	���C�~�;��~��5S���
�$A��ty��AM����󨞫�6�����D֥CT�� ���������qwt~7�u����T��)R[:�����6���T*U�r�K��PU�@.YP�*�Z�X
7�tzo|����E%@E&�Xڵ2�R���Z����6Ǎ�+��ٷ��ux��:L�S	���Έ�K����.��f�ڦ�X&a�	x��=,t�XU��!JM�8�S��׾���г?#�_W1�ɐ
!�4BO
R$u�?c���
�4֭Z1QSZ:�/3f�B&��RLF)1(Ud��q�wo�g��IS+H2�>�
W�yT~�Ϗnm	���kT�֥T�T֌�jE�1�jP��N��� �MM.�i�T��(��҄CH�S�t�ו{���`y~�9Ǹ���$H�C��]*�SB5o�p�SՈ��bq���/��Xi�֭	IX��MZe���.�}[����wJ�S*dJ�*���}_�W�"X:�SR�*kR�i5�1�j�hLdDZ��]�ޖ�4������H�R�Ԋ\
)t�E�=�&�~n�����
�sk&H�@����@�i��r��MPi�#T�B�'!�m�𦊪U���\2V~ŷ����r#b�9J�a��5g��o0��j�Y�"�*��i:�WA��Mn�n�Q牌B)U�z��E�ij(����*�
�I�4�T�qԺkH�	�&�C"B,z2�=����-�����T�@�Z��h�] L����~s����5f���\	'���*�\r������̯ר�	�T��,4��g���	UE��'��a����yr����0�匷!�=�E���O�sשS_B�ҍ5�BcJ5�	�<4Rh0@8Ů������9���y�]c$B��Q1&�b�}�q���'I�������8�9N��1�9����ك�p�{W������$H	U�q��}Uyނ�:���K=���o��϶�3��܁�UWI�Zho���Qv��R�I5�0��fZ�3��C�9�ګ����T�j���s�>�l�g�Te���iT�SA�	%E"�H��î���\]|OY+"M"�D0�!�+�FS�W���#��{�3��Q+6�����]^�9��,�4,�X]g�>���g��k�z�jA�>R�P��_���N{E�5�v�k�j���_d-�����ͧ:�@�
>��Hd^r)r~�0������m����g}Yi�E�B���:Ѓ0Y4��T:%"�iPt�s�qPy~�kTRi5��oJq�CD�����!����sW룓���7K�Z󒂰kw������E��.�z,�B���0�R�F]*�Z��0i�^���4:L	Jp�cV����Q��D�Rif(�ٌ{�1���x���������5��
���2 ����=_���V��X����u�M@9�w
2���<ʂB�����TSg�
���W�=�d
>�j䴽"��6unỨ�ZE<[����WL �ɂ��ԪU&��i�E����=.�QFjkV�I�D3A.�E��
�Z��Q%ګv3V�m�YC:]��6�j�&v�ʳ�gi��v��*�-�sŘX�Z)q�J���	`SH��
F��I��e���N�="��V�Z�jիV�Z�jիV�Z�jիV�Z�jիV�Z�����ɮ���̯M�K�|ǥS
z�0iF��&*��j&�1�D�%.�d	�
����CV��MT�%LKK2�>�}~I�� LC������-�=����(��V�Z�D��Z�jիV�Z�jիV�Z�jթ��Z�����ɖ����W[��~���.)���I������Ux�E�9�J���(0LKJ��F!1]MWT��H��mR�>��o�Ȧ��*��me�Yf��=�u�vr���CT���AL*��)�[��y�w��Wi\u�y^}G�j�k��z��k��������+�����WQ\��GӋ-Q��J�-������F�����ML:!
��aNΛ�tcU4�%.������*�TIQL� ��iF�)�>�ʬ�Es��G�n��g�k��;�~���kg���EX<�Z�
tuAN���*�U]t�טWYQ]PW9]=�j+Ϋ�)5���uG\�\�ꚣ�ʵ&�^w���u�n���2��3��z���;*��`�1it�ɻ~oG�ہ�FtZqjjiT�]I�ū�/�/�g�U�^����`�5�S���YՕq���+]^W�W�Um?��{\%\�[H�:�H�^i^�T�c\59����﫝�J�6�Ss�+5Z���-E͵^�4��^��Р��!Q\�{��܇�����NI(��Lf���K��l
��Q ��EV��9'�ӣLl}C}��Aj�m� Ӫ�g���4�8w�c�W��냦5{Tt:����껺�
�
���I^�M����+�k�i5�5��צTW]�y�t5U]�p>�<�RVl��̔G�q�w_�M�Y
�h&* �Jr�9}�d��G��ʢa��UM*�HaZ�U�$�#�����]:2i�I*���S*sD�\��7֕��~��/<r1Rt�Y��nmZUY�y�2_#��y�
��O�y�
V�Z�jիV�Z�jիV�Z�jիV�Z�jիV�Z�y���9ٝf¿El�R1�á����zU4
6!�"
���4GNh0qQH�I�6�L�4���L�w���\��篕�'���"iT���8,�~�Ek8w�Y�me�Zb��=�ݷ�԰ujիV�Z�jիV�Z�jիV�Z�jիV�Z�jիW���s}y�l+�+Osɦ�;_�o�� ޙTY�N(ts��N���R�"M(��޵8���Uơ�(�J
$J��G�M�&UB�F)+��ws�~�W�t��@5�Ͱ���I���SJ�M4�MMM{��W�˗���<����ͩ�,ʢ��W�M�Q�Uy�np{P:]��|���l�2d#S$��4ް�)�BeQ���D�R)%j���d֤�4��8�p���U��P��Yg�$1��P���_1���jjEm���ɤM��i�R�4T��TV�J��a��w���d��;x���9ɵc.�-W�����4����?/�ߣ;�g}��=͝f^![��XŖ�U"��A�d�hcD �XRl-��*#� �0X7`�@�@�E��1�3p��y�4�m�4��$&4Q��h���ƚ�d�	���T�M"U(����$�6��T�%	P�ժ)&�Cg�<�I��
&:@h,�D�U-w='�����}Mhpjf�8c�(��Ս��+T��U&�Q��.���L*ގs��uP��A��>�ż8<�g��cL�u�XfL����o˳��p�B�Bp�f�'��4�Y-E`Z*Ԋc5�V���(�(��6A0j=L���kǴE��j���F��M�$*�� I+��XZ���(SReV֬i��[7���5��BUM�?�x����ᛮwZjP�kTFiѝHm��]NҾ�U����T�����R��B�!���2�y�q�)z�]�d$6��RmZ�Bhl�X�M	��:�����2u1��*R���w1}M*�����ʌҍ5�R�&Q
��V��SZ��P�T�U.�l%�B�j~@���=>>��`�M$`[1�����<�F":�:A�r�7CWluh�\��x�G3�����yi�"�x�QQ�j�_�n�#e��{�E�&�j���yA��k3Ѕ�@���s���}jyz�ódқ�;�ى��0eL�&Ԩ�.��iԚjjE�jM�**E�F��B����aEѯC�/��r�{Sаdָ�^�����pb�<AȜg��YÝGA��i����
\P��X�=o�����֩����E��b��*�]'��q2B��_̆�eSM��mb�,�f�,ܭ��)�O���{h����k��y7
)U���ʄ��*�6�F��ik���IiJ�ż�ݥ|�_*FA�&�qR�d��{�ӷ]^';d֪�`���q:s��/;m�[}%����r��{n����{p�TT{[�	�$�<�-M6���0�o^Q!��3rY�B�O��<wxzaV�7k�o���;Y���)%��e�a�.�$4̩mɯk{Yfp�Ɔ!��h��Ak�)3ma����/+{��wE(!B�k�yjI�7���j]$�Fv�j������]{�d��[R���'�[/�@%��e4�)�� �aC3��f�B���%�$!QH���D�I`����	��S�,��QB�NE�/�mwq!�w*�$����4���e�Q�GFC�.4����eH���6F�I���&a"
� G�/+{�)6�W
�U|ؐ�t�nVY�C���7
��`PIwV�X�a<g����d�J1��X��6�P\�s)�O݊5�%��)2�܌4��C�I���\*��W"�D��H�D��w�5����]��Uz�/�0	;6�-!!��,�cia�
:���K�X�q�i[���6򉢾�_3nB�o�{vWc�qub�6j�[�aq���i����!�8"rH�®ڮ$,�J�m��ik:�\w0�Iw
���4;�r��J��i2�,m C��6���u#2�{+�����*���~����)¶�%�'j�a)N+*4%yW�[�9'�
��y���R.i��K���X��JV��9w��K�^�D.U)�lRT�_-H����+��\-�BbW߈�^���DȻ�0�~���G:߷���m�K�Ne9�
,���*[�;}�J1���BEܱK�JTZm�-6����CU�v�K�k����Z*�]g��2>��f;lו���/#�����P�V�
�V�-1G*v���#���P�1Ti�*4eK�8���?}�дvڒ�r��ڧ�m��`
e"��j�w��W�����̬��[Z���'X�\�-�	C\aAv�;���\�n�5��Z������L[Dv��_F��-w+�F�z*>�����ꟿ����O`9��eO/kR�Sɕ5)����hm�Bb��;+�"��TǙ�Eܹ��u��׸)��u2�+��~���!9�sl�P��
���K/������
+nV7otM&��o@Q"V�&�����;���#�4S:�����w+������((�@.�)Q����G��u\I$�W/p�Q��EʙƬw3A�����d�Yg����t}*t��l����Q�JW�_���{��"#̩�����skb���\�m�T+��7���6��x�[q��	o����R.�V�+J�����k�I������u;C����*���6r�D���!���>�KN�v�`;�V=Oq�\2�n�S��ug�Ս��:+h����%ĉE$���&\*��r�����-�V%�՞�A`��Z}�M��u^WOk�A�K���9Ӷ'��j����C5�<�}���zO���:��E��l{�#;�@����
�w���e����ζvI(���Kkecp�AI�q�C�AH�U!/�#*'�{�~����LG!h�y;+��o ��g�Q�
����)�l���WWVK��=�G����(Q���դ��W�++=�y�M̷܇"��42E$3gh�{���		@��E�J�]�}R'	�3��)IK�U����Y��+�o,r"D�є��on
į���qp�� TĜSf�G�wZ�L�)�u�v~� ����*Hfh��ڪ�p��y�`�D3wZ�d-SJ�h���ܗ^İ�KG�:Ix���H���2oUH{[\�n'�I��Z�_��m��^�V�%�����B�}ڮ�oVu��O[��8�V����F�˂�,���
�8��ҥ%�d�~�v�p�d�jt#[)�X�,GD��r% �!��n�f�Ve����/�vLR-��v�~�l���5\̦I?wk]m���װa����q�d�[4�E4*t��Eʵ�e��5=�v�Y�`�D�H�VL[�z�k���9۰y��B�e�������PA	D!K�0�|����/1�R��u�����_����+M!�W6ȎYS�ϼ�Ev�9̢�d��^L�	�)�T2Y��f�ݷ9��۹s�H#��k�����o��JX���U1j�����_:�/ޢq���dL�/5����S<�ťtqܼ�d~��=�݋����'܆5K$�TrX٢X�v�&�a}�H�轥�+�ص2����%jTabx���"��	�L�]Gη{m�E4B�qZBЛd���b�����r��ƙ�3Mmu4��{�g.�|��SI?�JTX�R�^�-Ţ_��U/�-���6o�����ٚR�'�v��Ă�.�z�x&U�y
�`��%��#H�E�W������2���a�p�&�Hږoe"��4���r.mcý�������`�X-%Ƨe	X�� ��	�n*���k~���o���Q\'����p�-WW
g_�O�Y%*,A)b�F-�|�t�����,ߡ��;[�I-��"c$����S
qM�yQ}�Td�`����w$sB✇�N�D�,$��,O�_ދ��8���l��s=m/�8C�E�v���t*	���+i
�1��M���@GqԺ�
A����B����N58�򣾗fY�O�F�1H��I�M�ŧo,X���%�h����{�����NY�bʔ~�*�]�?I��C����d�|�bG!��(j�s&��*G=�0;{�g*B�w�iEZ���ME�� �n2�����^���	a�3�,�&��=����cKgbiw��}�?ů�G#p�A�v!Ȗj��ZVЧ�+k[���v���Y�R�`Ŝ!�l�­R��0��f�Fg��~�
�]�����#�j���m�%�p~���݇�{��r\�[��Pk�ѩ.D5Ơ��K��4L�r�}��R��˳K��/ޒ�ڙ���,�G�ۯ���jî߇hb�e��R�o~F7��v��;|n�3
�����pe��Z2KRZR�aj	+Q�}	RϹ�9#\e�aPv��q�6}HP�M0L��+�ӷ\�6ɘ��vȝ�Q�3ە���p�{t���{��v�&x|@��v�=`�ȰS�/k_aI��)Z̋���ο�.i��kL���3DA�\��F�+�".m�IB��=��dr��e,ZLX�����Z��A��]�S��Z��I%?�[��3�#�5Ʀ�����4�m(��佱 [�]�>��E˿�E�y(�y-���XM����{�#_���E�$h8�ss�뭾��e�dcN)�G-3�G	��aIa�!��wrU۪�1��������� ����5�q��+�_u��X����R�F*�?��c�T�ĥ�d.��h��d+o�M�-A��b��J�5#Rӊ���=�w�"��4�Bt1�W �b�D�b�G�Fk���tJh��d����J���̴����H �ۼ�[�?K���W�����t�V�!*3~�;*$���!TH�X&�eW�u<���n���쿽s��ݞ�	\u{:�%�w�Q�Iu*Tn�,�!d��<�~�IeՖ{	Iۯ�̆��2�S��DmP^��I���f�_6M��k|�n�kcS�9TSsl��
���/;k�����C̊׮({m��!��.����P��ZI˹{�x���S
��Rc��!���x
�3,�)����^�2��i*&{��Kͦ�P�^�U��-�s: �j+V�|E9Q�JJ��l�)n���� �u�����
~����F�(���7{�0����%կܱV77��罌��=�<��6)�:��I��u Q7I���Ҋ�m@�ܕ"{A}q�)5�\�-JZ�%JI3��G�
�\��v�Bf���0I. �RR�d�X샧ܷ�P�bb�����KP�����E��x=��}͹5����nВ�Kk,q�c���d�[N������K;b$I��"��3�5��8Gv��ߎe���/��hw�}�/��5���5�y/5�?rur��x�U��G4W�}D6�x�R�����*��eث���\�(JJ��X6ِ��p����ʅ����'up�����H�Ҭ;�����K���FJ@��.?�BV���2:��r>D���~�;�I�����G�K~�_�?rK�$?t������*�<-C�,v�3EGZ�XS���e::wK�����q˹swwv����궸���ĉ�{������������\<T�r>T�[�������S�q��B���-���l6�7iϒ�ʍ����O ��T������_�?{~���J~���2?x���|�_6G�[�N�����ReǊ	j�u�~�,��te����!M��;佶��o���o��~�#��_�J��f_6�KL�)ۤ����T�ӫ̼B�O��q��E&A��`�׹�'15g��
%�\��M����\�X��Ճ��*���3̵��x��x��wI��$��a�4�G)*4/��:@��x�^/�x��NR��y�X�0�#������{+�_�b���B��ӭ��&��g�����������ׅ��q��z�KtP[�%RŻ:�*�T�R-H��B�Pt.��S�@���cr¨�FE�g-��S��K���x!���;]�\��{v�	�-�Y
&{�ױ4����4��,�����\j��ͳ�F7#�Q�^ò}��B����A���h���\A���h�%7q��"���V���#Ɲ�U]��(���[I�Pj���3�=��c'.��1a2~�����v��&�����2w����ڴ���y�Kٕ�;�6�ߠ��Yf]��Y�K�ہkqlaPC���qG�Ť�d�>�]!��Э�N�:fEb���i,�=�n�����f����5���J�(��c/6��>U��'�]ݦ����Q#�w%%��-ղ'E�1��2��]�<ɂZ�
L��2��JRk/��t̑��j���E$Ř�l��TT_-�kW���r��TH��a�M���]�XE/JRH�Gd{d{�0%2�,	H�Ԇ@a�������P�����E!{���>������]��Yv�䤛�}(IZ䵸�T�]n)���s*}�Ne��.��9���,c	a,�U�*Lt<St���q���ӧ-��I�x���XI1r���AS���[DI��F�!X�$4GY1wߺ)d2ȧe�n;�����eJ�Ir(5���}]j�8��]�Xd̑=��U�Ⱥ�r�=��j��;�_x{u��F�B��2�	qG���@	a/��-	�H��)���W-�,@*!T�N8�X���J(�$Ӓ_$�K�D�dn(�B�������%�-A�{'��%����!ɃU/ �Izv�j9R����Xt
5FP������e=�o&;S�T���q:A$������i�[�M��-V/�EGgp�i;M��[���B��S��-Q��/�Y�Eඨ�O!m(X�Jb	SļT�Jx�B�V覤(����xP\�Ȧm�q@��Kw6�)j��j��r�H*��ە�ȅR)Q�.D� K8��Sо�-?���kH/*�������:�ZmV��S?s�����g~�;�i�-�|�Za�E#DKp�AKF�~���n��pPjjh��p���BG*SW*Z�څ�<�LvX����a�e�qN9#�v�S�ya���nx�Rۉ�#�:�U"�4��`K�b����2j�M�O���Ҡ{x���15�A�Ĵ�YC�_���q�v�T{Ս�}�����õ�Ko�\��6����g�����_����n��)ض�m��<��v�K��K{ȷXE�{>�{��o�ŭ����HR�]�7�KsGu����ܬSw�K�m^�5�����&ڤlQO��6��H���;;���/d�W2��������{;{������i����v7�xo���Jv����F��5��T��6�q��X��
���4j��̚4��vi����LA�\>���8Z�����ʉNDQ��ʞD	"�G4k%�o�h8�ԗj�.T�Y�V���s�<������*��� %;��ܮF�業%2���w+�TY����PJ]^�U���2���=�q�"�h��ХF������ ��WV8;9p]���-����]��ŷ�_{v��_��TcB�g}ܬ�,wk_ƴH����v���|}ψ����/�ﻎ�cx�3�Z]�]�'�y%��I7���ch��hTw�"���H6�m�ͭ��kD���������VO��[_Z][��{wmg�lm#��$��z��v����aD�On��%+F�msgue���	��,y6�]����R��'�;u����κ3Rx:��Շ��H.wk��Wp#�������SqZH;Gƭ:���K�g����&��f�ZB�c�u����QiI�>��kJV�`���N_������EF�F�۟�ܮF���@�Vj#Z���	��6��7+����S��BzUb�%M��2�.�U����48ˉD8��F�c��n������&KZ�mˌD�H�T��4���]�3�bcp����_=-W(�D���p��r���A������H/��nP�F��楪����!���AbT�e��{C7�����8ܡb�/a/�"{��+Yr�#��
��di�N(i��P���C=�p}���ں�J�Um"o,J��,��H
��J��hcPR(SwnA�
������_��	���%���a�F��o��:��`��?p0��U�N�-a�:K�_H��OҬ��KO���2���h�Ljā�k&hSS<fd:Pv�:G�?�����|����2j<C%G��ã��$��"Ň�D��V���R�Prݨ�)SB�T�V�b�y��o7������>c�k���C�Nھ���^o7����el��mKk[T�r.�jj-GT�Q�ERҚX�E���A,��F���`�=K���^��cf���V;�n�Z�D�G�N��ӱK)S�A�]�$.	y��K��!+�F�
\��qCjɪP�5IRec'��o������2U��|��|��|��|��|��/�_<�x|���|��Q?�dPZ���H։Z��]Z�*�<�'��Y#"�JmԄ(�4HcZ�gFKSW���>k�c�>k�c�>c�>c�>c�3#�����ٺS7e���2�L�����=���:�H���H�:�lrEZ�K�W�
L��\�,R�%�^��ѧG
�.�p8.���0Y�)=ɫG��4)��
\p��
Ԕ3*)Y5rP��U}ʺ����c�>c�y[���~��[|�J�M�E�n9�7������^���nԥʔȕTIH�2�0J��LC7�H*Z��r��kFM{G����s�5��Oj��{o55pS?̏�_�;���q�ڰ�o��=H�OS/D�RvȣF�Dw[Lϗ8�9�	3�d78��:J"B���xϧ~`(��`�˪˓𣧜���A�2��i(Ča�r�tzIpG�3��S�@'���s̵"�RFc�k�������YaH>̨�9��^�;$2�� <��<>�\���C�������i��0�a<�W��i�O�^C>�eɆx�g�KџU�����!�C�|͇E�>y@Ɲ^-���2�"p�����F �/S�{t|$v�V�푏��>܂H���OS�g�'4˶RF������L�=����FE�]�S!G����:V�B>Y�����Y�~X�>��<Q�����=\�d�����0~h�Dع	�G����c��G�˩��~A=FB���!��r}=�����:Hp�����K˃��c���M�.�Ӗ;��9m.�|=P�=G�F��8!�浜wF��{����\�Ïۀ���:
:�^2�E��&q��{�˫����'ّFb�k�0�H
*��'X�6��e7œ�����YYde1��/�/�ǗwL����\�?r?����T�V�%�O��O���c����Il�Z�?�$'���=G���/��Lz3�\�8�,8�j>�Qqq�Џ�^,��`d��'2������ٓZ@��[��vǆb�=`��� ޙc�.ye�!���7ƞ�&�Q�4��[����4/�)Zr�����OSG�>o4��L�GEV81�Ѫ�q�p�_L�'����=t�qb�^���YDa�>�?�ɺ����-9Ǎ0t�oL���$pǜO^>���yh�Pm�cȧ�
����N�'��'�t�*H4�χg�\5�C�<8�n�b��2��tye�@=J:\C�����e���'�t	���s�#c,f'�4���gn�<��n�E��8-�p��;h#��qbli��OK�|9��>�� xz�?D��AӬ��Ѿ�ߜz�ؾ�C���I��@��6�X��E�>�i4�Ã�O��C�Ʒ����КS��#4��H9�,1�2����$wD���=���n=�ƇΑ��B���^����q�<7��c-)ˊ�s�0��i��}��7�~`s�K!l��d�T�Adl���E����L}��l��4K�)�r��NL@%E���,�O��i1�7��jD}��>��9z~�Qz^��d�>�4�`��@���_��e�|S�:N>�&�, qE�;�XW�q���$lޙ���?k�;K��BB��a=�Hʼ1��oY�����俣v�Iהi���xvE��v��M5�>2�' }��/�'|�K��a��K��#�OS�?�'���h�K�ɏA�yc�|�G���m�j:�^X�G��z8?��O��+LU����yr�|zs�h~�qű6/��t#o�����C��2������$_������fQ}�h���(�ۏ���^59�=S����3O���6y�(�#��ǥ�D�N;Q;F�� ~P\9���}L�s��/�"�B�Y���~?��,�}0�;"�윶����N?P��ğ:e�a���^~��8�o���[E�6-˘�A�Q�'$o%8�A�S�m1��֦�	Oo�[	m��r�D��e9�_pݹ1n�4Cr,c�S,bO����:f������2�͔����@��|���=��9�Y�����"���@z44���ø�C���|7��z���_֑'_y~هd��g��>��nO��%�۝�3L���~-3ʅ8'�����H��p?�����7�Z�ؿ�Zu��,jN#qr�x�È���a����#��W����݇���P|�N��٘���Q��ԣ������(J7N��HK;zl[��ߖVv�&A�6��x����}C���.�Lc�2�'�5��N���xd7
pOth�h�X�Lt��Jb%�͏o1a-�����`?�g
��Ěc#	m���_^F�)n7��X%=V!ꞿ~@z��>����/.Ls��v��?�:\hÌz;G�ݒ;�C�K�>�#oG�Է�8hF��0}�ޓ�I�j��"��]e���Ii�~���2��~RQ��� ��Qa���Ի��I�ߧ��w'p���8N�m,���(�n�O�������J�]�$����e���#�)벟���xv��_���(��GK`�=�N̑�����}����c�=6ń6�b?�I�&02��%�hY,���꽸�rOq��d,S�0�l�o�BN<�!͖Ƒ�]��9���.Xn�����򣰱�$i�!���[�RQ'���,��=,?N�m�X�\��~I����I0�%俥��_яR��0c��>��������bH�Bi���u�ezc�w�gc�C	�wE�����L�E"�x�'I���Ҵ���#B�w]��4������n��������e���Tt�7�H�VȈ�����Q-�}��6/I���<xc-�����'d�v�N|c�OY�z����[#�/��K�\�G�yb~�S-��$ӽ��| �/(�o�yr�t�{�����#�
L\Hz3�=��pb�-���?ä��;�n�)7��}N�A��|�L�L�����Q |i�T����|6��=F1��8����g�_{�>��>������H��t��1@z;@c.���W�~J'�z1��B^]� ք^��%��d���t�fSrc����,����ɤy8[�`�X�g�e��t!��9۟(�_�ɿHH�tˠf�4t���!�qc��"�&!�8ǀ�r
��C��:Q�_���D|v�W���c�xI���m2��ƕ��"�H�7�10�z��F��C��D�l^��i�[���m��6�e��
,E�t#NI��z��E͗�1�ƹ�L���
��0%�����C�8	Ƌ|:F��ǀE��2W��4��>BpD������CY��xN�ι���Ov>̘�r,�oS�ޚW����s�����7�1���R��2���]���(^�������r��ϗ`s岟�O�%����.�:q�J6<��@g=���>;����e�a��X~O�B�.���0v�
�k�L���&��R�:�@pB�b�0�ݒ{C9�%�s�e0������z������cS��T�E�P����ye���(�}n����7�n������}����_���_���o�1�Fx�����֏��Ԓ|=1���D��-�[//ܛːȽvy�>��_`�o��_c���}���_j/�ۋ���hh5�c� W�f��xx|��>��FOQdn�W��`��՟�_���W���+�g?�o����'��_g�O�W�y��r�ao��3�_�������������}�>�?&x��ÄDŌ��؃�;���;#C�������.K?��s�6~�i��,O�_T��ѯ��o0�ҧ���e����Ŷ;�m����6a��\��˸�������i�������f�w
/Q����
p}l���n��Y
ؿ����U�i�0����޷\�>rV�9�J���iֵ������Ɠ
�ɺ��O�k�`��V)��[/��'�z��L1�xA�2�2E���v�Z�1�`/���1Ckm�ޝgQ���˴3��+A�ִ!�vSMk]��X���x=��yp�l�a������8���N9m���,���xz��Ӟe�K���s���~z֡�Xƃ�⡼��m܉9��Q�����▴��i��i��v�����:�N��駺?Zq�q(�k�;d�[���q���'e/r��ٕ[	mz���a��o���\8�ʛ�����L�E�6S�V\�Қi��i����kJ�����˓�'!E�q����r��Q-���H�h9�qq���i������������ZSM1C�l�n��ͽF]�hdt��@i��i��i��kJ�0p�0�|h`�E���C����J"��N�s���I��k���v�]�֚i��i��v�K��K����%�$v@���͜a�A�v'�؟��Y��W��U��Q��}�����w��wG�MN/��|����oofcD� ��>\D�Ӏ���o�1�~�B�/C"p���"��<��,�������X�����N �f�W�������,�bh�����#a�&�, �LYxa�t�y�>�:c�s�ČM�e|�=N-܏ۺ�;%�Mq���a�AG�"^{�3��YH��q�8�3Ȟ\�o��sb�#L��#+	����e�^�o��R���~Q����g�C��]d@�5h��#�/=������G�lyq��A��}H��Ã��FNN�'Ó�y�T7�v�e�Ic�'��o8�G��;�~H�c�m�_��m��m�[m��N@����Zu���I�� p���~�8p��ܰ"�&<�-�vJ�Sc*c+Кm�=[�9l�[w;�'pm�٦�x�>ՠ&2�,��=4�[�0�X�u���uخ;ǣ	�.XN�����e&�������˸�˽�p;ü;�m�s�@o��?�%�HO��G��ym��}��fHrն�n���T���m��m'��m��m��Ӈ��i�;���}��ϼz/�܏��쟄e���D�o�;�YO+���l�I��r�7�~�L$����8���X��i�lO�M�m��Am���m��m��m��m��m��ӇhLq����!���=]ه����c6;KGл�ݗ�zl�v���bRo��R0dm���(4t�Ag;b\�im��m�l�)}������n��t�sm��z[m�}��cLg^X�w$��c���a���O�,E>PHcl���4���-��[Cm����m%�-��m[m��z[m��Y3�����=?���𡟆H�B|���Ν?�d�O�F�:�������?C�f��%�O�@}f�Yu_��,�*/Pj8o�9�qqp$�C�^�ԩ�ѭ1Ktm���j'��ƹ<1��L"Q��a�rq.��o������"�˔}���_tm�-�Q�Q&�v�:O,!��/�����ۦ���1������#$%�ǍH�Ii�	�5rK������2C�/Q����^��oK/F|J��MGJ%�	�t��0�45<�״�'#��"�e�ݣ��`����q~�h�O:��m��k����ϗ?���〙r{D�Ï�ˌ�K��&8�-���]@��LjV���~	��<9ro�M�aO�2����� ����&/s�
W�K�7��_����_T�]LC����<'��)xO�L|H��K����.ֵ��e�~X�������Bft_��!������7y۵�j�9v<jN�xc���[zWt�GwK�����
��c#a�:����&KV)������E�Q3�˩�V_&b�����:��8`l}
�9��F�m���6yFT�$�.u���Y���OQԁ���/�,���A��K�)ː�����9vu��:nn(����!�L�L��	�_���}���??�� �l��)�i��O����́�<�,����7ȓ���ܝD���ևA"�"�E��HEǐO�K��ɓi�72�c��rl���D�#��i�L&$�b��3	��vH�,`��s0��:�r�;��S��S�{$��z�����b?�u���:�Y�[�6۹����z/���}	xD��9�jP噿��xr��|��.ߢt��rt7oI-�"���ry�je���@�����?5�:���5�i�G�-1KtAr�Y������e��sz[m���m��B^�����]�#pa-����#�;J
}�G0!*�(�o�OQ#�oO<c�9�k�-�	K�.1bO�NS����"�O����g�#B�y�J"�i�C����H6�7�����zۧ��.�C�[��m[m����OF~�wK�K�q��Ο/���'� Lr��?H�2x/���rD�<����G6;:�Q�S�$,ve������x����	�i�iˌH=W�ٷ7G��/E�91J>t[A��oKm�K��38�c�K�f6JÒ;�a�+�$�
}��1�!��}��r�)�GZ�����cBhYe�Du2�a�LXz�sN,&|�1�/O�p��?˳��5�,�����f,8�����K�4�*e�"0.sx�8�% ����2<i������pDx��1�<�B��!��x�:�Szs�=D6ˇ��I���S�M�$�����-�8�e;bOn��#鬸��ؽ��(��.�x�8�?^�t���x�?f��so��=FѰw�m����&��}�qw)�S��m�Mi��ni�"�i��4c���aT|=/�s��?�.��cZ`c�c�m�F�?�L�3ҟR��(�����O���w~LM���=�zX���_�鿈����.a��oK/G����jCO�rg��M=Fa�w��.�N{G���]�je���/M�o���0��C^���I����O�k��է���c?�t������X��b�`k�124����L���脼9:y�^��������/���l�h1���6 �)�&�~?s��:��I�348=�#	l���J'�2ߍ�z��,�ˇ�l����;E3��I�<i!a�⾖�ȋ�����~����}��a�5%��m|� �OQ�晑�����'����'���OS��>�?�s�^��)A鸛��q��?�u�#9O��eB�R�r
6�;�o���M��t�.���S��q���z�Æ�����!�3�~��z��3z��Pst�˧1��)ŚQ&&,w��r�����J@>\��C�i��'<3��9	ጌM�m˻���������0�J�������wM��Q!�������#���)S��)뺡����-6'y}��'I�{0���k����C�
8��E�<9�1/�"���zcR���=�Ó�Q����3��|8��}�n�����w����w|>��N����w��ԝ���a��8�Lq>�u���݄�F]��2_%뺃�ю�v�`�o��[�^��N1P��O�?�����fl?�?�.�#�Ӧ>�xblh��������D�4揫� �ޓ�8�2�������e3QC�~����i��
}h���y<޲��%��D
���ْT�y�~S���=Ze�^����gÃ�A��@i�����ug�0�'�\�63�e��.<b��x�%�A�"FV��a"��j`.���1��p���C��/�0����Z�������KƓ������	�g����=_z�z�'����螨�N)JQ��A�q�47���	m/E*�������8�2䑜��k1�,2�1��8��Yzά�4<3K�a�?�>���Q2��Yt��˽�$wSſv9&{�[r�}<Lxq�q��.C��|��Y�"�h\_�g]���B��N|������x�!�H��6�~;���˃�����i�y:uc����r?��N�x:t���m�Ji�r�!rz��y��ҙF��Ï�G���H�XKaЋx�!�S�OQ�=4��z�?��Y�(�0��ÉV��n�vtѹ_g�gY�zB[�nIS�f�_�{q�%�|$�zt]?�=�Ã��[q��s��
4�ҩ����!xkN�tv��Hx�j��}�!�Y|����ɒy
���5�K�u��puX����'�H��S�}�#q҆��.@ xI���2F<9�Mŏ�.\9O�i�|�̓#�Ei�aٗ����#N�_�z��C�0�2�<�,��(۱��DXa9$ .��]���4���	��:��x�>�ø\{K�v��a�9��\_'��0ώ����,�ֹ�B�q�t��������I����[f�n�/⃌��̓#�:혰�<vf�ِ���&���or^��i�%��:_n;����-���h�r8�QN���'�q���� �RvG��2񬮸a+�����0_���;�I����-���Ql�Jȸ!�����
8�����?����a?�u�~�nZ\��s�'�3�0�TF�Қӡ��o>����A��e�^����}vIx�22��|s�Rmˇ�).,[γ��	?%�K��a�����	�p�x(��'4I�#�fn8,���<�x�2��=0c��s��7��Թ�NI_%�2{�7zz5ۏ�=�ÀD��m�a���p>�}����_u�_p��w��'t���5'l��_�}���9z1�)����|��Ϡ��A�??Gi�?iq|��8��Y�~�Ň���pw�|]�}Ⱦ�Y��t3��ɹ�,�=��-V���ޏ��aϒ��9��	}��}���l>�v`vhv��M}	�L�c��'�F_�t=G����Gt�?���ˋ�z^�9�<�w;�-��~��jN�;$��O��O�l>�}�����)��4擞c��R�#9z�t�>;��}�8qn,!_�K��H��ٺ^�x����f,�����;M���	}Ipo��m��,����Y���q�i�����9�m�q��(mm��m��m��m��/_��4f`l=>Ov)'��/Q��;��nO��a��fߐ�=�|y-V��h='J0B�\p���Q&G�ۓ0�z��ޟ�Ǩ���bB�)�Yg�w|����r~���.��m��l�<wc ~���̭�Q
��?������?@���g�]�~�>�H�a���%,e��a�
�Xm�-��b1���s�9M4�_��?�����e�*�Q�)�qʥ��f��g��/Nxe����1�ᑩim���w�a�xmܙ$�!�w���Қi�o�d�@��P�U �s���2�$m�M����0?s?�S�ǔU&QU�!�-��ѧO�/�Pp�܄~�����|�T6q��-�������a�m�-�YD��^�S�Ul2�\��r���*a�s����?�k��S���O�a�І�ǆ�'1�K�s<��m�=]��Z9LHc=�2nm�,�I�&�޷�������1��[��Le�2��8ۮx�n	z6��.aqq��
���psF��Ƙ�F��y٦�wS���g����L[~�۹���m��fl6�\3���e.qs.Qw&TpyAo�3�%8������2}~�{s0��2��b����q0)�a��sB�8�l�f%����Ie*I��Asd�h�ŏyw"N�̱��a:e>bxIA}��wސ�;�J�l��n((=��'O�?�?X�Վ{&$��[@i�k�E�P�}������Ӛ?�r��NX�i�0�}�""���AD�L�a�ü6�m�N�[m��Q�?6S��y"�f����n��	-�����e����!��wL�|�I��
~L����ѷ�`1�c�d��������s�sÌ��CA9��'���8�9?����>��C�#R~o��x��y!ͣ&��~������������`��0�M�v���7�qxg�\�������(O�z�����V�0�y����}�_�a!�4Y�8����
rs�ZJD���?݊9~��䧫�!�S	;��_��216He���R�A�ŗ��?O�����G��N#��@K���L9̆Q�a1/C�������F��P��b���\��q�.֚v�k���M;Zi��v�]���v��M4ӵ��.�k���}�>̟d�A�!	�-�NR��zo��#����w������i��i��i��i���4�v�Zi��v�(�!����#�D�'�O��2a�����FL�ZtӾ>���"[Ha���e��~�N1����$$$$0�i�CN֝�֝��k���v�ih��4ӵ��v�]��j"��(�@@BxM6��41�qJ�E��9��Zz|{y?C���Q'6*�hC�)�e�����F��m!!!�=���3xi�k���v�]��k���v�]��c���n�av�ih�)�B��.\4����q�/������n,��o�K�r~����1s�0�xBXd�\��RHiņ��8����ZӖ��M2ǹ�M"6�S���;\��.L\Xq�iiڞ9)�S#n?�.�S}Ќ�@�k���i��kZg�JEya�ora�Y���r	��_���m��H�sa�]�S����Yo�;P�2ǹ1��v�]��-9�Ë�;S..b�e�p��������i��ÈHYr��/�����:�j��>���N��}�G�Gz%$���~n��=4z������	�_�h���Ԓ�����%��T�JQ��i���>cZ�J�7O�jG��Q�L�cTeӶ_�;jh��������o���=ү�J�t�D��R���T4I��h_�4��?sAW���?��Z��������u����F�|�Z~����R@�u���H�Iu�-^���C�
m^�Pԏ]Z��6~:�UR��c�}J'���_�����R�zԾ	�~OD�G���� ��(}�̈́I�)�h&���5Q�"�w
C T-룪����ӧ��5��h^�x��b_0(�����KF�<YI�Z�W���F�|{(z)�Q��.��wD��Q/�k�>Ǡ%�Q.�5��#�:{?'���8�Tx4�Ji���
O�Z���!ťl��+R=Gd���_�cVRx�)5a��j���z����W������=j_�J��_��?��8�G��~z�d>��t��=^��_.����u�cD��(�Z5��A����Y@���A�h�w�$�f�7�'����^���D���C�!��gW���?h��t�<������K����K����yHt�`!?i�}	�<{b��z{��UP
��r=C�>?GG��:��J��S��T���E����J���j�W*)���E��������¿�.�ʼ&=�jFCP���I/�R�}KQtz��T���?��Կ����0���I>�U5�T|Hr[/�Q�k�����\h��)�eZ��~����7@4z>��
!��	g��^���)�Ғ_H���L��k�A�h����?�����Oǿ�]��G`;�=�c��i?6�u��x�yP3�'�P�4~�u�q�@5�)��r!:����&0���]�֤
�*��|�$�~/�W�Jd���I쿎�(q�OǾ��Z�
��*���o����v�������ى\F�Ŀ=>א�Tꟴ:!%*y�k�h%h��"�;�~d��;F;�'���R_Ҩ��NI?7�����'�4a8��O��>��+��X^��e8�O6R�q�j���wB��?k��<(rG��?%jI�5a){�SOO��/�Zު���P���|��E~?t�թ>����������:�S�����=���������=�+������C�~���Ԟ����^��#�E_Bq>�R������O]XW��e'PC�ڌ�Z&"�����;���~,+�=��d��R��T���
�|�;)���/����tIu�?:U�Q�������|�L���)Pf5�C�.8��ʠ2x�R�$2T*5��v\G͔�6��}������Yz����~��]h̊	�g��_���z{#�jH2���y>L�uբ�# C)<��+�-ILih�3{#��u�5?��
R7D��н#C�E}�����Ή'�~�f5q�z�=T^������_����At�k�A䓐�
c���)��2u��֞L�s��nn^Ǔ)��j��0,�M�&�^���2����B����e}�:��B���$�`� �Xz��������Pz!OH���]��4�z�_���������>��C�/D�|K����AK����H��og���������aC��eZ�C�z>`�ŋ�p<]cU\R��R*G�œ�C�Ui�HIE�@+J�>E!��>�V|��/D���}���j>/D$> |��B�Q?o�J�J�E?����j������CL����A��џ�^G�|^?����j@�T*?�L`��G�j��G�H}R~�H_���H�J�zP?i��y~��m+�u+T�Et
qV��������쟓��%�)|���|�ȣ�F���#����N�yV�A�F��v#̟��=Y	 �.�Q�����Ŧtp%��,JhR}�\AÊZjHt���tW�V�Ia��.]h?���z�މ.Y>���1�=#z$? ���'�п4��>����$(
|DԼ�R�	}CpO���j�T�O��㇑j�+�MZ��(�ʏ$��Z�}Z����YI�;TB��?��ꔏ��޳�T�������<Ge��W�
�Uai5�C_#���}����O4读��#W���}�U$>���O��Jh�+=C�����O�j��~�^+=�G��A>���O$���^d�1%��KLg���<��d�6P�Q�Ń�:��nT�������V��3�*�-?���5� H�t���t�%'��h�5�_Q���_�_�SO0����D�������~�|O�
�V��
є�/�OFR@�?֒�iW�j	�0��Ŕ��	���kG���'�.�D3S���J���B�4��;���?�u��_����~�^�q�ʪv��+�O�eG�,kG��5e)����C�~G�V8�8VH������?�4�R=�?.�Y�eP�>����R��G���.����� ЇʗI?���\�H1(#ե~|�c���*�V�����~.��J}��B�"��i�h�	�%ࡊ�c�K\E���rk�:�Q��'O���#ӼRz+�?�+������j��%���\*<K�h*��N4ʡ�N���?�?��]R�$z:'Rx��W�=YQ�X�sJpS������A#��`��ק�7��N���C��>ʵ��B��_�j��O�YOƌ�G�ީQYW���
y$��hP�����ё�iG�kP�h�����i�A�q�>�)S��8ҏ_dj^\=�����=�q��@����d����i��'�^�̑����}���B��W�?huS��t�݇����GE����K:z:)i�-@kW�����4�5J��C�*/]�����O�e���_��_�m/�����?l��/�~��������$W���x|tj����?���?ݫ��S��~��?���_������>/2t���~��~�����/�/�/�|�1�#F?ԁ(��W�5���8~����̵!�����eC�Г�����O�����߭����m�_����O��������ZrQ!�B�]I,$0��{�8�o�X'����PΟ{kGQO�_�а8�ƙ
pN#��2/��k����/�2���g���O��	�P�*���S����4:���­	�Kw����j�+�z�~֍C��#����#��oo�:vׇ����壋�Q?'��X�_�h���W����?a?��G��v_����O
�;k��?������͔ԏ�o���{PZ�*4<*dH�:4?�Zi�K�0���U����号��O�R��s�
o�<���S��(�,*���:�i��U>ot=�>o������R,�����G͘��O#��W��C��R�I��/_e]%�_�.>)��4��Ł��jcQ�_̗Tǣ댁�֟CV���3ˌ�u��7�
5 �O}^�F�ǋ�T����)�|C�`�]1���A�|;���h%#�j�<���G�Ej��hj�Pw�t��y���~�~t����~�<�ޯ�����Rq֟�C�^�ү>�^MQ�45i9W��O�K�~�A��\x���P�+�#���lT*�{U��zy}�=^G����Q���d��oj�~N��)Ҥ?Q�z�YW�'�'��G�#���j���~o���~_�'�}��N��z��{�#��
2�hXJx�T��%���A�c�5���x�F%z�I�{��]�F�N����������?;Sõ�v�#���~�~n����<H�!���z��S����}����KTJH5�h�"E�V<�)�P���xӨ0� ��\���������25q�>,�4�	�������/N�1����p��}�wO����I��Ƿ������]Q���O�CB�~}��U@�<K�I����â�Q�ډ^���O��Q�/VC�Ŀ����?��������W����:b_�_�_������.�+�~¿NZ���~D��z�_��U�=���~ʿ��+�~ʿ���*����t���W��c_�/�_�%����y�/�Zo�)RJH��Oϰ��=^�z�ۃ��ߟܣ!��1_�?����Q�+���/�?Ώ���_�_����j�_�_����~���?'�:����UDд��~�檝�����7weq(��SN�{˴�)L<�D%ģk
�"rZ��.ʶ��@b��_��2f/F�\ęEu�f+h㶽�_�y���/�ѩO*�-%��c�	Z�T8-So�]VF�yW��a1"��H��3la+��*���3$�DUG�vv�{$F?_�����
�u�H��v����J��0�A
rśD���<SN.KLp�C�PJ��-V7×}�?l~�e*��jq�t��^kP�����&�,��Hf���ku`O��=��~�~�~��t	������a^�C�S��0:����J�4��jъ
t��'��v
_1�/u�H�� �~�u
�:%!a�z����xE��Y�.?�\���J��Q�-֯�F��A�$u'�<� 
�.��=?���T��~��c�T*�����_S_'�Z��Z��#���Q���
��.J��R���I?R��W���;��s���PF��W��}���Ic<R]��T�A_V��ڿ�����^.��?���9�T��8�2\G�)s�?����<�G�P�����e�y�;$��4����K>�W�K�ia_Q�|��c�^�͉���M|�D1����cɟ۷X��A�̦2��*?e]���r
���˿��^���*v�ZyW1L�"��9?'��ێb�����	�*�w����#�#6L2?�a)���X��kO'�?����T9Rn#���&G5E ��u�z��>������O�S(<Ŀ�z)�t{+�L/�Z~M-?6^>���f�*�*
����e�<��)%uo��Ai<:R�M��Lq�����(䈑��?"��9d<U���ϸMu�[�L�zO����!�m�ȉ�.��70)q���e�7���iU���wQ*��JUS8�	"$��O�v�N�]%t����B����y�_�?��O�����O4Ji���m�2�b_�;k��L D���?m+^�|����?�W�z��Ph���������YR5����!@�D0�x��0AQ��ب�;�%�*>����;�����_�-=���ʤ�B%P\jU
x�=�Z���~�|^��S���T�!�*PxT�j�0�M+B����]�O�r���P�_ñ��}��~w����v���%_"���R�)tRII��O�x��������Ľ���/>]��ު���ױ�22���f�TL&���t�����iz�(��T�C�W��h���+��'����I�?eo�~ʟ�'�������~ؗ�ؓ�~���)�+��n
~��?eO�[�_���eo�[�$����r��~��H�������=;+�ެ1N��p�K��)�#�W�7OFP}�����=�~/_��uJ��>_��=��ʕqI��A���>������������i���%�%�?r0�
����_> ���P�:�%
�ua^a�d�?����Ŧ$�e��ʏ��?�	I����c�Ŧ�z�P�R��d�?���S����O7�x'�u��u��T�����.��C�(]7�a����Q}"�h���u�Q�eG�/���=
5x�֯�C�z'S�z�}��Y�j�����t5�'����(�W���8���Pd�#Jv�x�$�����~/��4檟64!�Q�i/٧��*ў�YQ=#��Vh*�Y��<�I/��	N���.��kG�}]]R����&��8����P����i��ڿ�s�q������{���a]t쟗�_����-_.��4���>}��_�MI->��;�_ɟ�u|��>o��_��'�Ȝ2?�b̐�
��i&�.��'�5�e���+�����}������� ��>�2���_���->
��ӕ�3��8SCx	����Q�!U9�q���C����Lgh�~?2�4|���u�\7L�>=����c�J�W��|�ɸQ~7z��|�Ş�4�AQ:*)O��57A�|�Q���Z�OŅ���\�%F��P����>�93�<�e=:��9
4(�%���p$�i�%�IG�����,1ы�3/���j�x�|���?�����_�//
3,���4V�.���B�@A_�m��c�FQ}��^��h���/�4ߦʠ<���zE����F8~���蠽�S����ϴ���
t�m����9���@��n!���G��,�~e��b�e��}�*�px+����I~b�$�a!��JDv拾�W����(&'�M'�#ݐ]1��e��������A�$����Gu`G`d�@9A�����O�?��(�Z�^G��X��*y`x�t�9� uHM1<���|_G��6��?�q�����~��"I�ŀ݋�Dfp~2�>��I�������ca&kS
r�Y����f��~*��+>^,٦�?�.%'�P����qK�W��l�f��5P���T�V_��g��h�xHE,̧����Ď_���Rf~���!_݀�̶S��+�m��#�W�f����?�}�������?U~?�=y����6���Ջ~tt����3��qS/����O�Wdj���Q9�tT?���?�eN�~O��E��^�� �����f͟�J�tu�D��@�M�����������Q���wJ�e�����%��S�?� A��K�sӿ�·�{��o�����V\O�%|��S��Sy��ᗕ�l��2(Y��4���
�b�v�\��0��?��#�{��QDNK��}k����������]�?D��1Jwi?�Pɩ�Y%0{qbA(��~
0�m�yLs^�QR&iʟ��@b�<P�����E�zh�7�
8��O- 隡�A��FeK3\Nl�� ��YjR��L'A������	_���ЂO~�������9�
7�#����۔��\�'��ڢc�v7I���������=֗m4�@���k��������#���7ޛ!�8z�:�l+�3��b�����F�lP��lϒC���vv†��kU���a5��ܪ*�X<�xk�����s���V�\��^u���h�Da��Q��g�l����B\�h2��+<��������U��L�ƣ�Yj��6J2T	��~�M*�����"���]Gk6�������+��48���a�T�EB~��Y�6
|
�{�����k\����*	C걇|�V�����G�FTWa��A��ꕅ������p&#�)�kf���:���J��<����7���a�����
����������G���z]��歨���5��d\��r�l>?�[llx��`�*���]
����/���.h��������{��a�躟V/�%��@XԆPv\9
A!=�鶷�F�~Q�lL��	�
ߙ��a�J�����G���Q��z<^�	�R#9%�DJ&���X:S~h��S�-�аi�xj5Y��?���PaN�8/g^o!�R���%���&Ch�]��Q����S����J�f*��W��<9o���
���x?�{<Ԥ^E(�Ơ��e���V�z��Prxߛ+�%˯�����&���|������a�Fי\_��G��R��>��觪�X��!��Jӟ�g@H����7����)i��]<�5��S��N���(5��xi�SֹS�D��Th�P�J�T��?�H1)  ����°m�aI�o��A�����'�����K)�>�N)�zR?�cj���h�n�+���%,ú���e���Z�������0+5�J���Ȱ�+�������0X��t'|f��8b��f
t���E�����²���9*��� J����Y�X٘q�~8���jɷ`���S�eh���]~)�v�_���xJ��=�'��%��*�@�)��Q@�_��ǟ�bp_��?�O�樒We���g�����OV��/���_�S���	I��� �i�?�/�X����=VVYn�r�Yz��u�H�C��շ�=�>����I��<_?)*A���V,:~ePh�<Ǫb���͞�w���DB�t��{����n~h�,t��H�F�e�ˌ�M���Ei��^�����*��rK럺�I��ϰ��X����d�Fz+�E3���
>�|��c���l�L'��ڽ�+�B�O�0�y��W�/-qϓ�)S8�����We���'��TP���ŌCs���
��#����Ɲ;�y��w*>�%�҂� �������?��������
�#��ݫ6����x}W��J��M��ￜ���������yf���Hj�� 0�
9��xq�%n��p�g�w��UV�<���Tr$�`��ɕ�E�.�q4؁^Ǐm���1q�A���42n�G�7{���끢b�G���lB����c���q}���`g�߮�X�����vp�V��}��[������~�3��'+�Kϊ���HwS{4VGF<=����!��{�~k���/CI���E�����\x�����] L��D���T_YQ����7U��>��P����`}�V&*�j�M6��Ic��a�^������4�OM�c���t��*�F
�8��,E��j���;�7���s^W�q���wk�݃�fD^��P���q�0׆�~�Z.�e��W�L?�G��u�~t���������,R�#��V(0�/D'�f��|�����Y�Ֆ?��{�`�Vh�x��9Y�E��s�V�&���������ᙧ�L$��8'��Ǳ�V8��]��@�(��)P:9=��<��������j,��5G�U�|�&(,���͛�I�g���X���J6S�n���Ӧ��/���sf��R�3@i�\^�	�����7J�<ށ�x��:Y{�����xQ`F���~��~�p�
�D�p�f��X>Z��M�_��h�����$*sO���S��O
�ͧi-����͏��X!Ag
�JE�"RP���1G��+�]�l�^�OX��n@êo��`��I�Ґ3�9�Ρ��v��.�5���L��?���87��~a���[[_.��+m��Ű�a�S���^3�F�%�7�d�t��-�.��K=��<�~�f�Kkh�m�n�d奬���u�`��?����~Ks����IRG��-�S�(b���ۉ�)�#�e�$0>� ɶ[�7�l�X�(����^�����m�5Ed�aL�O����n��ڮ�^��`3��O6�dZ�Md��I@ץ衐]@���ۛm߻ـ3��!f���@	WK�
�7Uǳ��������D��EIٚ���u��0m/`��i�^�X��/�����1�5lN-:��?����t�f�?��f����>U���r�I���\��D&L���I$����5�,�<-.K��I&����TVj�N��K�t��x���%�%�]�H������]Ѵd�,�I��~�<R�$����brLV���.Kd0 rU���[rg���aW&��`�Ix�o�*q*eY������>ۡ�cu�� ���\0Q,��"Iɡn�0�f3rp�<X�&T'��`[ĂU�=�m����I��p��D��gR `� N�2�:nCK�E��K-m@��A�GЂ?�B��<H��W�7���T\lw�*�C������a�� ������$r	`�I5�($�[��'�e $A$�H �H �I$����A �L�&����Q��Ŗ[4�M��C�����ف�osIă��g�A����h�$�E�
E��lt��F�L�z�#�`���&#��Uq�8��	m��V�u%ԟ0ۂX�63�c��#�]~�P�n��gt�n����`�tqվm�}���CgmO���\S�݄��ϩ�i���_3���CF�l�O韟72��.<o��r3�wle��2��|=_>i?y�n�y�d���/���i�y�n@�O��K�a�@���Olݾ2��c��w��m���<��Ջ��y���i���'�U���{��N'�]��|�����\�<?(���d\O����}4���+�w<_��myp��~_�W����~��
�fO����"<}QN�Ż��]��Or�O��c�{�f�N?�m����2frc������e�nin"[�c��'���-x9>N���[;��+�O�\%'�����+83���<7}x[Aֳ?A��K,���O�f���x#�M�����
	�t��WZ�v�Ol��t�e���#����'��$a#��Go����u*gv\�ԔW͡,A��s��7�:�!~����_�����}`#����I3��a��Ng��z?����p�'���c�[᠝�$à�-�S��{���Gic���Evn/���^�/�n��8����1��|Xy&[��e��p.;��Nb�,P���%6e����r2�.S�h]4�M��=0t�:Qp7!O@�y��������Cm��,ς�Ř�f�-E�3�8ww3�6x&;cs?�^Z� �П4����M���%w����?<����4��ƙs��x�VF��d 6O��e����ݚ�O�<�.�@Fv�ߤ���Q�KW��>�L����-��/�\�\�����2]%DN��Z@�\��̓�~W�_�ӂm���<��8�	c��m���gQ��6���z��cH��>`���'g��e��bM��r���[Gw[�Y,�`׫���|X�v�wu�;�a���-��3Hi��o����>�ݽ���r�>�m���y�~:/�����)q�7�y@%�z��1���N��L��V\��!=�V�~�s��	�BJQ���2>̛Ɵ�����K�-��m��������~0{l���-��ʹC�9��&���#���X�"�6X_�xT�G��:Ys�����d8�:�̆@k$��l���2����f�����B���&�Bg���K�-ӿ�ѿ�~%~nv��gò3���\c[V9i��'��g�����ǜ����O�?_x�?�)H�{��;��'�#��%��~T�^����/ɵ�}B���4;���
�ƣ����V�7����æ~������Y�n���[��|�$q��;��`dJӣ���OB���GԺ��<}f�e������������������C�4Y��W��}"�Ć��,�>�l/��%�[0]��3���)�ՠ�.�1��e}_�a�a��$�~g�]�2�'�'�]��Λ�BS���.�.�,�O���{�dî6�q��xqm!��۶��t��4BC��/��73��[q���xϛo���l�ׁ����Y3�Sh����(Ğ����J�@"����t~�Ȼ?�hA�&d?[��P�X�ݥ�g�X�]2�!������I��m�����F�Ă��	V�>��K��6�Q��o���~���n�ݓ���|̅����U�ɰ�����,��n�$#���J���/�n����ߎ�_(.��O�Ȃ	�;���=��O�3��܋pq������j1�7�lj�g�����D`���?^�=GN{���ӎn���T�d`]Lkm�P�	����z����#��n?
�B�&_2��o飻��R{�g{�ԟ[�m�m�>��û�{���|���/����O�Ϫ޷I:a`uo����=?�}��z�As�1d#|��}|���$4u�E�R:���>���]�*���T��5�Lf��u���b�$HZ{�䋓��q�����.Gц�K�s�,�$��C��_��z~��U��|�;`�.�S;e[�.>��7ir�����0���z�x�ۑe����	H���ϴ8�h�qm��;�%܉���t�@�Wh��{��r�T��s�;�6����ǟv,4��?<8��Y@'��:��3�%�8%K�6w6���>t3e��������>�������ӑ������?���o�ۦ1�	,.C��ĺ�?��fv+b3��Z7%&g��R.'R�P/����ǚ���l\>`��Ջl���Զp�����}����=���_4)�"#u��X3bOSm�<[���vI�W-��u�\�۫~%�Yw����e�?6pGt�D�<����q�e�G��"a���}K�q�Y���u�����[]e�C�O���%<qj}F�^l����=���e��?Ѿ����#�N~�]	d���~g.�;d,�m�n�:]?_I�#��~\B��-��q1����ƴ~�=Y?��KT'�{�m��1��ǖ����#2���ֿ6w�d�R>"�?�d�e��?������m_-���_q��o���אƭ.k��Y�7��_	�O	�����\f�H�>�V��R�`����ʾ���}��M�j�[�S� ���0�mɧ�3����<3aU+�͟���nG3Ŷ\.�\Yb̲��x7FZ���7���vl�>�V����\4$�~n�g6m����q'̐i���8�<\1�a~�~<�b������6¾X�����9|��᫯��$�,}G��|N^&3�$�͒����vz��,Ȁ�\9�u����9z$|FYr����1�)$�K�:�92||m�g�!�ß�������ў)����Lz�w.Tx��P,��q�,}�Q�����ac�c�c�c�`7fZ��Z�Z�Z�k�k�j�v�˷nU�����'�Oҟ�}��,�G� �$���G>�_�~
�??��d��>��'����W���G��U�ѹ�c��?��LsA�
����p�;-4��9���y:����}��F?�xY�(���q��A�ǅ�%b#�������
��,���l�g��r� z��HMya&]K���N��H��n$�d���wQْ�@̱m�ض�m��m��m��lX�bŋ-��<fA�O�'�����]��N�'��{������?��|�q?�t�đ�xYe�z��Kp���������wi�P��d�\����DDV�{��p᾿�>����
������-�_��+W�m��S���V�w�>'G��^�{��?�"�v�|�>G�e���v'Χ����>=�~|D��ǝ.���>��_��|;���i⚗HA��K=K�~���p{�x��]�#��~.�_�e��O:e���-=��~m�/�����}	�7L��?�k˛�	�>-$4md��$8/�VD���7"�<�~�G@�/��6�<:�?�'�>��}_�o��k�>�>~f��՛�h�g�.��~�V#l~�E���H��;���~O:��'�	l;
'M���L?���J�{�cŗͶ��1�����~�
#�Ę�7>t�
'
rHI�S�|�y?RZ~~ˈ��.�2�	�x��w�fx��X��9d�w�Ǎ�*od�>&͉�z���l�|aߋ�ȵ�'0#���������v�ş�bJz�?��$h������?%�Z�(�>,���3�.<9�)����J�W��a��v��X������]M�����M�pK��`�-���`I".�����g��.K�W����/���]�����g�ߍ>���p6����y�fS��Z�]"9�q���A����!������a[ǹc�a�d,�4��S��?�?�/�	y`�y�?�,�b9#���7YC��N[`�؇V�������r7���o���������Ӿ���x�A��`�O���_�C�ßw����v���9�'����;�h.h� �����o��YdDxn۫�q��sb�_�o�Ĺ'��~��`�n��=$�W��<��4˂����}����"�� ľ?�n^61k����g����y���k1!ظ��Z��Cei��S�׽;w~{g��Y�Ip�B�i@���1�
0��?��~X�PY>&����i/����?	��œZ�~��q��ylb< ���3V�.\.S�<�X�]ϙg��[�n����ۃ7/؆��},�q�>�7�h+��܈�
�'�l���ѧ���7���_K����������?2c�"d�@Y�s��D���i,��Y���>W0������5�;ʸ���Y�:���q�f!�����%�ß��'����ϸ?ߨ|�m�=�w�y�S�!]a�������}����}�
�~�$��$����y�l?�]|@�."�H���Z�$���m|���>-	�̲˶<nh?��D!�#��H�mǣO��$qi�$|D�W�<��O��A�o�"i͂�_�w�?��-���Y�Y���r��A�Č�Ό�a�vYcşO�������M�Y�o��w�7�}/����7&La�/��
�Q��,���̪�k<�Ͳ����.����Z�~��i���?Oq�^#Ƭ&
�ߙ�Y�Y�3����q����!���`]�oLm.L~�'�"p�<A��u6�>�¾|k|�L�k�,���6	����{�~f��L}�����f>}G�Z���}N���n/���گ>/���}���KE�@|q���{���G��K���g���<~�����S-�������I�s�0�r�� �}��
��#ori#�9V���bIu	���sr�L��%�G�P�����K�'��q�1�1 �Xt]y��u�_5VYe��a�R��pԲ߉��>��n
��~�-�� &x�wd�a���_�#�ս a��?���>$�Kc[P���l����ݿ�WV��><�ġ��öG�m�E�-{���>c؞\��3�x{K�n^����r��zwk�n��\�|�B�s�8��	�O��8Y��|[�>��o��$�?���{�z�I�.������m��H��̗��E��l[��`�� ~-�.G��?d�*.��y�?���a9\�G6�Z8�i�=��FwsS�&�0�s���yӶlt�6TqheWwG���R����������I$��Ը?�a��>o�b����B�`?0v?���dZb����\���������6�8���a���������#c}!U�}�u�����$>)�O��.�K8�]q7d�S���a�S���I��>��y��6�;��d��-�����"+1�m]|@k|?{3�<�6�@a�����8����o��]Y��.pc^Hm��lݠ�����z}u�r$��r�IWa}��,�=���.�[��\��!�0���i�>�Dq�B
Y������eY5^&�></��G�"�����������5�t��%��1������qi���"��~tq-�d["8���?��i� ?�u����ſ>��9'�<B���V�f=��=g�s�u��{>y�E�i���a��M�"��X͑���bt�~��s����Ỉp]��зq.c��q�b+��1��v��{y���̇��Xs��a�*G�$X�q��,��3������~�0)�<'�'�v����m���+���W{���q��P5�Ṽ���O��hs�L��e���_2?�<I�p��Y�Y������~�����G s��h���;�����珵�^|����@<�C���������%��<9Ϲ�<�q��lJ�#��d緿�L��
��zy��r�Ǿ��c]l��{�����}�k�g����|���<1�n1k�$�n~)��3�����>���u�ֈ��]��[��ۛ,��}Xm��Ƨ���LI$�����K������<��J�H��������ř�O��V�{�̋0���垤�����<�����{����o������������GѶ<���6�=�^wg�)�.���FY$��=^����iu����	�9��C�qO��p��c�c\Q��{~��Z��t�=?�'nF?g�7ǫ}L�#��i�~�s���u�������'��LǙ"��k*(*�忟��p,0�0�f���w�>nl���ܤ�Bq2�.�:��{9�-����<9����;l�K�S��[�Y=�K�\�Il���3�H�(���q[����ˇN�1�}g�F�K��:��9��|e��
Ucs�M�Շn�}WK�l:�|�|L�����}��jm�|��|[�w��U�6��Cax����s��w�^���Θ�'#��?2��~1ݧ�?��e��!?{�莿͒Y$�}���F�ǝ����<��<���A���X���ߧ������g��џ���'_��Y3�ܻ��,OO���O���@��b ?I�՟�8�1P]�ĺ�#��K2��XL�Gv��e�"�Hs|
͘s<n����X�[ �G0|��X������E�}��#����� ���\�[w%����Zl�ۭ�ܾ����?{���d#FD���/P���f�v[t�p�r�������ԑ��������{��c�g�
�rG�]0��ꟽ�G�_O���?����/��"����ӯ���<b|<X��f͛|����|�e����.r��z==��,^�����t���=��Q̀FGK:'�ev�S���Rv�����^�n����	>�s%��ǻ۔�M�>�`��ι�y�9�gv���W�{~Vs��{����Oj]��!9���]�?^z����<��Ǚd6x�: h�P.ם��ź�e�t�y<��ۖ���mAw�,9ܹ�%Yv�Z�jݻv�۵jݫ^Z�nܲݻv�yj��/�n��<�.x-6sۓ�}�9����u��pc��""q�a�s�����'/=��k�e��C��C�j>�~�l_���X�b7�	��Q}V>�<
xy�ֽ`x� =X<����#���.meFe�8�ߪ�^��Ə$:ߖWfB�{?��~��R��J>�@~��=1���5�"��1��_3�C�'Ϗ��o���?d'L|k�!��eÞ1H�a�up�?3�e�n�&����x�i��iJR�י���	�~�A�m��$1���͟��v������8S�yp1�=LJ�vǫE�K���̶��R~e|\�已ρL����oE��_=|��=������7�@��;�O�t+��y�G�Ȑ��#��G���3�J�xG�{�S���0�����M���A%���
	�"G̊G��7��]=i� R�>�u����(����ӕn>er K��
y�f��`�=�7G��sL�s���g5�L޴~�C�|��s1��]�9H�l�/��̦�_�4ad�%A��n����Y��?j�~N�:�rnyR�O'҃�����"�>�AG�/&*4F|Ԯ�pvQ����ݏXj��yᯑ������2�|!a����>�lp
���}6Oa�?��X�*�?e���A�-��G�����h��b�h�׹�M�p_�Y>�@~J���O�U^I8>?�q��uI���o���l��F��*��-(=�o+��iF��=X�ׇ��u�`�G������!�s����+*Q>Y�]Y�f
/t�B�"ͣU܀�R�Ydv��豢zH���f?�迚��%�,���>����)�z���SPM�>�������@�v�r�M1�����gϢ�}�C��S0�Jq/7��VuN���!Oʿ�,�"��OY���0tl������$sv�٧+鿰T!�6S��q�C�\��1�E�5)���?M� �O�R��I��)'����
#���vO�S���Y@�٥	8�G�? �� }���"#:x��)���9�~&�;���ك��Pd�/�Z�D������3��V|��營׊��J@Ӯ,�d���+��z~h����"fc��Gk������.!>�hأ��.͖���xP?-vI���c�|���*��?���5y���Y��r����z��Q��Q9f��񻟣��1���2oOc����$�%�i{�_�X�
�;��2]8?ݝ���*�C���B;�Q !����U���h������i	2���M3�>�W�e�Ծ���������x�џ�X����y~�����)4��Ϗ�ٲ�;)/��;�����C������e�vqK� 嘪���
�7Si�@�B�d�Bl-�x��:��WU8a��ݙ��	ϊw��%^�
��y�@W	�
�?�1���KyP��&�?|R:���*z��bEl�5qA� >�R1	��D=�	b^�J�}������9Y�Ұ���b�>������h�?�lڥ����7�?��<�3����)��g0��'�ry�Z	��c�ОW5�@������H�ek'l�L؉�~*�,�>����' �P<e��F٨x�]����4d�����("x�q�\�a��Ł�5���	O��$�c�`�*3�i��C>;?���q�����>�A)����|Ϙ<�G����>�������c���?�.�0��?����vw\sf�>���y6��Q�;Q]��yl�!��,R���|�R)I<S��<���~�lT(���"���ۛ�
+W�*�>(ѼaI��~����y�CX2z��PU�P�����c^��9!@�a���J>�`��j��������=�~iρ[͝��b������{�#�xl����f���v�f���	���M`��5���#��T����]1z��������㎗�RA�X����\]9S=�~��5��������ŖǪWo*)?�4�""H�Ԥ_(�:�ہd)g���f�:���.$�8�|����JBC�y���<:�O�Ч�TbA���x
�����`G���z�N�|
��̲�eZ�A��jy�wuݓ�z(�߆�������@�r.㶕M���w/�"��S\ܒyD�SɄ%�#��b+����Ŝ�<?�+!=���`����:O��e����|QN(ś�Bp����i�ǧ�Y������'	'�����?t�ѣ�s1]R�BF`s�t��_d�u/�������i�����iI�J���tX�c��>O��V�:"�0�
��(�(����I��/,�e�V������hb������hp;���%��>_�
JMc��1NN\��
����žjc��G�溆0/�fý�����r���R�|�Ҷ�{�8	�2<T[+��>������\���d.�8���1�<�]�?uG�L�u?֠���f�¼���I]/o��*oؖ�q�7��2|�*�ҢЈ�,8��>[�v�()^�/	�.��W��K��^�>�E��*�������幞����|��E$�����F���\O�Q�*p>�W�O���r
�w�Q0�
�K�<Oє���<�J!��s�\@�ԞK%@h��)L O�~H�O�l(k`z�hq�a���_�'�W�-qG�(��[�r�|f�����s熙����\���+�)Nj?���7�W�r�d﵎ǟ[{5W���H��v���@�����\]Y����v}?��9�ό���:t\F����Ϫ�y��B��H�yF;j���$��o�$��)d��h��"�"�$�B��iް?gt�M?'U���6�����ٞ��Y��Uh�a}d����|6q�|I�B����P�u�B��1���q�M�6���َo��%L6�v�P����J���y?m!`���_���W����M�����9���/��p=��~���j��?ʕ����?9�a��
��6hO�W�9Y��D���?�O���aQ�����d�ҍ8��gg�-K������`4��7`�r����U8�h� ����lB9�+`�N����՗�h�'<S�o(�_����YR|��zD�<"Ϡ����ě���ʣ����xW��m%��&��y�~��fW��������S��iBft�xӋ$���4_����O��NK��e����������e�~�U'�U�U~Zf?�#��K��RQ|'���#��Yy�y����0�n�X|��Y"Ϋ�}Ք��Y���a�a�?�&e��U�X'52��7n\(5�D�K��@n���G�.G�Y��Ͽ��Սib�D'�SDW�T�&��y�0r�1�'�P�0�Y����aO����������1�z|y;��s�Q�u��p��S?�svܮT"�n������$2��`=�dWs4AC����Q��s���.N����<ՔP����F�J$O%���~�R$��O�A������˻�<���1�N�)T�������� |�R��9��suz�b,r���*�ƕ�y��c��3��<����z�����|��6D¾�������P��B^Q��%Ƿ�T��AeÏ��Z�FQȚL��Ρ�!?VZ̝�@~W�U�����DJ�(U}�V��,�x�)�^k�m_���&�!"y(���$��T>�jqxW(���{N8�Tݍ@L��*
3�ί�0.���ڸ�A������Aw$��ZE¨��|�J:��x}Ty����5����n2>�D�H�Ф�Bd�=?4=���������P�N���ۊ�E���rʉ�H#`N��drխ�'i<��	�7�QZw�ڱcuc�{���������q��$�xLiP��^��O@���㛂�?'/�h؜Bz������(�0��y&��+��\�6<�?eL�F�{n���১:$���1J��H�����^���I��\]���Œ��k/Ջ��<�?�0�ɍ'�]����V�I"<�y~vT���ʾh�K4|ӛ��!�;����ϲ���?���'��L��&���H�fER������Pd�C���@�ﱠIՉO�n�N,r��������Yi\�������<?���Q�h��W�ג�A�
�6BEO+TQ�u>�l,A
�����eQ�>A�O�Y�L���Q�E>?�����$�|�mH!�G�Ot�d��j�?�����{����MNH|�W��9~"��f=���6'�>>"�<LU�yO�S��Iz�
_�/��W�c/���f��YN�g��fh���<�g�sZk��X:��eYS�<����XX��Bc���Z�c@�2�k���3�{�������J�nxn�R
^���S⹂+R"(q���GJ��a����I�"�����peVV�2�VOU���_�X������?�i�4|ѣg��4h�D�^��
8/���d�y���S���jݝ��f�A����mܱ�ȩ�|���)�CyH~*nJ�(vzh�qQ2�~�+�&���A&!�����0������-���"|,Ƿ�N���<'e�~�K�a�����)<�?���BG���>h���5G�;Xx����S��r�#�SH�����7>9�DAV*����.�^'��4E����V���4���t<^~?9��$������:T��-rt��Ǝ���p|��0��^Ni�7ݒ��^O�RႢb �5�i��S8k����1~)&X�Q�M8�^j���o����6�j�J��q)��0q�����X7ӟ�.&�"]����b)����w^T�],���l�`�I����&���z���� sQq����y�
��檃����|&�����}^�������U8~�/
|/XZ��d���#*3��T�A��?����Ƕ�R|'��dD�N�}�g��8ִàzO�����P�ܲ�LC�y0��q|
?�Ga�S���,'1�cs8���TK=�J��^*�զV�0�S��6���
�Js�����D<������8>��V�f,�F>+5g��2��P%�1��<��?�Պ3d;�y���i����l>�*C�X��+�猦��k�׃�'�
U�?�]dV_LR�}����+����}S$QW�������k�\�A�l��������q���?�g"��)b�]����P
���z���u�?��W�P/�C��>�\��&hEe[�	D�+��a�t�����Q��IX�'4L��E1�
������GH��l~5K$�:�YK$U��3i��6
re�b|�'t�t��P���	�9z�	�՟rQ���꒲�DK-L���I���� �9�ؽvO��0`1�/D��nDix
J& ���
S�h��B��Vf���>?%�`̏������H�C! x��G�j�I���[H��a��>��G��
L��xl�"e�{?����`�HD�[���ZbG��+	ŔԎW���L�9hK��~k���z+e�=���
�h�V"�ǻ8����Hd�<SvǕ�6�=�cO����T�^S�>�؋��f�屄�'�/�X
=��Ь1f{BO�n���s31�*�K���V@������tdge��� �R�?���L��������1�N+��b뿕e�T`�|˙�?�GeYxJ̣�=�rp�,�$�E(z� |���%��-��������8i�>F��h�'�n�����9_|E�%[)�;۠c�� Så�Nި��WeC(bR�����K��M�Ǥ��)%h�i���:��R}�c����~���a���d48Zx��D8�X?7����|���|4"t<E����1b*����x|���)3��b�>"�jCS�^ KH������m	cx���/
ҌNG���,!���U�3�,j��[�G(�058"CW���E�!'�7谗0�}2T>�ќ�z&>���4����}��~؟�����U�<�G���r
&p8��}AEW,�i��<x.��f(�|�Gj��q��y�O��Q�q���q�>:����T!�Vn����7�,�5<Pd`��h�"��4�R�'
Rd�,� ���P����<`x�颬�Yd���F�
~���M��+���c(I٠(G�`����Ιz,XQ��O`��Xc�lO��U>�x�>�n��h}]�x)�6G�	��<�#�=��N��@�q����Y0��Op�p|���=�v�,YuZ�ꦼ~��>(�(ۤ��PNXck5��~�!e<��?�����gF9NϲK9�K��0�G�q��̳�j��!��1{P��Hx]��χ�O��a��d51��+@��l��,&N��\`����4x��W�
DBo���Δ���*@|ՠC�$'����A�A%G�Lp8�1(G��.����:�vj�����[$6�����z�f@'A?�O{y�ھ�\����*�Rx�
�)=sX���d�ey�I�T�O-�x�y�f�H!>�vI ��4n�1o����T
�"D�x��o���������x������*�@9��������ln����ͱ�ʃd�tNe���LZxo�&�븉I^�{w�~Tf?���h�?���⦊@?�X,7�x�"�'�k̓��*&�5�|#�fa�6\��{��?�%�t����Ґq��V�8Gu�k��	�����:�?µ���T�C죏hAQ��J�V���께�����<�P�
=A�7��s�$��	��o�Q��⇿�X��|��<�o���>�����&���K���e�#MV$&<�W�����H�q�����QGxGo�}-"VP�Y��'͏R�	�^���2��R��|X����כ%�qM(�)����(5K����q4'��O�l����u������z�|H��؉�y�0��?�~uT���?�0>���7%O���^�ΑN�`bϺ�~j4�H6n
�ĖNC�o�+9=ti#rS��,�DݜRS,\Ԃ�rF�}ԝ9���e�vǾ�2|����68#Jm'P�sA♆�`�kEރ�pZg�'
zMI%yQ��Ž���[:�B�V@��������b�c�O��FDhY{
C����a�C�������P:ƫK�X�3��V� ��6:�X�A<&p\�72��K�"� !�F�A�PS
�α�!.Qzu3��$;����ϔWj[�#����Ȑf#��Zŀ���3C!�"H<2�ψ0n�kU��	r#�yx}�[�$ 솢���%<�*���	&�(�
�{�
��z���GF�c�U��eܝM?�1��7
y���鴝�i%��
 P�b�Ț�>�~<�H��cs0Q8��@���1��@�ǂ��Z�G����YNj�����"X��υax���iFo|�%�G}�!�ܨ�<�4,3�	��8!	�`�̘�8O�z�,|�j�h����'A�1=�aa��=���ZB������eLr��;$49��>h����=٘��U����_d?F8wM���\��rx�?��#8}]��AY4v�e��	d͒!+�1g��o�8q������l^���;"|�@E��"�@���o?7��B�K��S���x�y}'F3�����������~��$����R=?t��v������	/�#L!+H��
�!���-����͋L ��� �U�R��8��4A򲨞h�cɍ�@�,����Y�
��~�&��������8�$�D`OvI7S|���;w�s"	l����%>Ǭ�����?v�g�:���I�fK���`�Б�Ģ���3�0�:�1/��z���J5s( B�����]ơ���@
H~�����Ax�����%ǔ��Ɗ��!���Xk�b�W&`���AJަ~3�]U1�a.��C�/iz��������F� �^�,���Pc��D"6�]���e�h0e��LX�k�I]j�O	^rm�9O&�!Ѵ�>y2�B#�>"���p'��59�8��(D��������Y6)�/�X��P��g�m6a�Ԇ�s�iF�zYJ�k��bA���q�C첆
Z���h#��l4R���y��W�N��9�藉xD'���)\�?��Tp�4��~8�<������: G݊z̨M9[��;d9&ו9j�R�p
���, G��;��%0<�SsV!I�5��g�+��h��l���a�N���B�Vw�JBV�w��b���{�SR댑�����$��$?��&>���v�.St����X,^q>��6�5�o}޲��l���E����\�U���o9��lB�#.���Ŝ$������믚g5��V%W�6'9�%K4$|��1&,2$�='��5�{�U����6{'C�ƅ��������lb�)p\
���#�w�m����FL���Ny�d��4���ɪ��uJU~$���{��@�4t��8~k\�e���߇�AM�;`g��ti?��>��)��%!p�}6p"�wdC���A	����6O�f@��������V�Zp#�e����[�EI�,x����_6O�?���������QS������'��oe��G��
�����>��X��Xd���*|��¾ʱ�=�SX*��q��O�>m_����A
���/;i�I�g��";Ś>e���U�m��8$?u�@	_&t���X&3�M'��UK��'QL��b�M�+&�\��C�#g���Y�W��_��E6o�C�Q�Eŀ�`:�i��!1�O�RBN/<)�"�S$^�#��M�F���>*�]U�(^��>�*#�az׊zb�`��gtP �Ovz�D���TB6%$�U;��.h����A,�Ő���L��o7C���h�N���z/r��._Og?U6��h�S!����Tq�����4�f�
C�����07����F�V��ҹHG��m�G�6%��D��0W9�jisOv�=����Gt�z���@�'��˞���k�9A�>l�?��ʳ�?6^��K��</��j��#���a���O���+�*4/0��B9���lR��[�u*�D�eĿE�6�nC��\<�����C0:�y�#�R؍b�2��gq���c�#�ǻ�
O2X^U���@Y��"y���}Y��2f<�>����l0�x�@�ʒ�����_B�)��2�y��*K&S=YW(�伾��c��hx����5�k/���
�I��h���"U�Ht5'�{��U9GڻrT0�ѫ���Դ�4C�2�z6c�嘈��F��^[3�(�_���Ε4��,�~D��Q\�����l�8e���rN�U��Q�^���Ϊ�<>i	�66.�k!a��Q
�)M�qJK�K�a\o4l혰N,'�H�
�db̺�zuD����V#�j��a���;�O�_�Q�a��^@<8�z)�*�T�ǒ΂,#XZD��rL�Xx�&��4��]�&tH����"NGu�G"Dx���W����	i~.0������35���Q�G�<|МT4N�`��}�����{�����~JH%Ї���R$}����F����W`��or}�)�*B5�e���仚PkJ�iݳ�	�h�l��ϊG�0
~���-�4� |�ZIMA�z�'�x�<=x�J�PPC9����l�	�~2���3�<��Wp��ǜ�W��%�5��t���vZD���Vc��ً���v��Ѡ�̠4g������8Gv"����^��J�}WA49r�@Lot�E���\�2��L�	U:|���>����^cJ��0�����9%�����S���X~�p+&�J���'��9��Ulm�!�?�,#�,T����#�ϱߊ{􃯜�d�K�|��������D�	��
e��X��ēPB\~_�v�Hpt�>@�")��&3���+����H��_��@����c+��G���?�s|���{V�/����
-----------------------------89322681528612771194264535139
Content-Disposition: form-data; name="submit"

Uploadfile
-----------------------------89322681528612771194264535139--

************* END CLIENT REQUEST *************

BUG REPORT COMMENT: //////////////////FAILURE
// here, the cgi is not called nor reached //
/////////////////////////////////////////////
```