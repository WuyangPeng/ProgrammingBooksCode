if [ -f vn ]; then
	expr `cat vn` + 1 > vn
else
	echo 0 > vn
fi
HOST=`hostname`
HOST=`basename $HOST .purdue.edu`
echo "7."`cat rn`"."`cat vn`" i386 GATEWAY ("$USER"@"$HOST") "`date` > version
