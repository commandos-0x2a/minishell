 []	| echo test|cat -e	# pipe with arg in same token
 []	| echo test| cat -e	# pipe with arg in same token
 []	| echo test |cat -e # pipe with arg in same token
 []	| echo "\"		  " # Don't handle backslash read the subject
 [] | << limiter cat > out # here doc write '> ' on stdout(redirection) not on (stdout)tty
 [] | << 123 cat -e << 321 Makefile | cat -e # argv is ["cat", "-e", "Makefile"] << 321 is here doc
 