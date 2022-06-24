
### URI syntax:
> The generic URI syntax consists of a hierarchical sequence of components referred to as the scheme, authority, path, query, and fragment.

	URI	= scheme ":" hier-part [ "?" query ] [ "#" fragment ]

		scheme      = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
		hier-part   = "//" authority path-abempty
					/ path-absolute
					/ path-rootless
					/ path-empty.  
			authority   = [ userinfo "@" ] host [ ":" port ]
				userinfo    = *( unreserved / pct-encoded / sub-delims / ":" )
				host        = IP-literal / IPv4address / reg-name
				port        = *DIGIT
		query       = *( pchar / "/" / "?" )
		fragment    = *( pchar / "/" / "?" )



The following are two example URIs and their component parts:

		foo://example.com:8042/over/there?name=ferret#nose
		\_/   \______________/\_________/ \_________/ \__/
         |           |            |            |        |
      scheme     authority       path        query   fragment
         |   _____________________|__
		/ \ /                        \
		urn:example:animal:ferret:nose

Source:
[RFC 3986 Section 3](https://datatracker.ietf.org/doc/html/rfc3986#section-3)
<br/><br/>


### URI path parsing:
>  If a URI contains an authority component, then the path component must either be empty or begin with a slash ("/") character.  
	If a URI does not contain an authority component, then the path cannot begin with two slash characters ("//").  
	In addition, a URI reference (Section 4.1) may be a relative-path reference, in which case the first path segment cannot contain a colon (":") character.  
	The ABNF requires five separate rules to disambiguate these cases, only one of which will match the path substring within a given URI reference.  


Rules:   

    path	= path-abempty    ; begins with "/" or is empty
			/ path-absolute   ; begins with "/" but not "//"
			/ path-noscheme   ; begins with a non-colon segment
			/ path-rootless   ; begins with a segment
			/ path-empty      ; zero characters.  
	
	segment       = *pchar
	pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"

Source:
[RFC 3986 Section 3.3](https://datatracker.ietf.org/doc/html/rfc3986#section-3.3)
<br/><br/>

### pchar:
>  .  

Source:
[]()
<br/><br/>

### Parsing URI with regex:
> The following line is the regular expression for breaking-down a well-formed URI reference into its components.  

		^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?
    	 12            3  4          5       6  7        8 9 .  

> The numbers in the second line [...] indicate the reference points for each subexpression (i.e., each paired parenthesis).

Source:
[RFC 3986 Appendix B](https://datatracker.ietf.org/doc/html/rfc3986#appendix-B)
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>