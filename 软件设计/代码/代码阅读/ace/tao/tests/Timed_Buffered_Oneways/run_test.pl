eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.10 2001/08/28 13:25:54 oci Exp
# -*- perl -*-

use lib "../../../bin";
use PerlACE::Run_Test;

$iorfile = PerlACE::LocalFile ("ior");

unlink $iorfile;
$status = 0;

$SV = new PerlACE::Process ("server", "-o $iorfile");
$CL = new PerlACE::Process ("client", "-k file://$iorfile -x");

$SV->Spawn ();

if (PerlACE::waitforfile_timed ($iorfile, 5) == -1) {
    print STDERR "ERROR: cannot find file <$iorfile>\n";
    $SV->Kill (); $SV->TimedWait (1);
    exit 1;
}

$client = $CL->SpawnWaitKill (200);

if ($client != 0) {
    $time = localtime;
    print STDERR "ERROR: client returned $client at $time\n";
    $status = 1;
}

$server = $SV->WaitKill (100);

if ($server != 0) {
    $time = localtime;
    print STDERR "ERROR: server returned $server at $time\n";
    $status = 1;
}

unlink $iorfile;

exit $status;
