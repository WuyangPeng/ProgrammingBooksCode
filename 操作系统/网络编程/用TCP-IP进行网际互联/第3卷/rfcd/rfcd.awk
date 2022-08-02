BEGIN		{ RFCPATH = "/usr/local/rfc" ; body = 0 ; count = 0 }
/From:/		{ retaddr = substr($0, 6); next }
/Subject:/	{ rfcnum = substr($0, 9); next }
END	{ cmd =  RFCPATH " " rfcnum;
	  cmd = cmd " | /usr/ucb/mail -s 'RFC Query ("rfcnum")' '"retaddr"'"
	  print cmd
	}
