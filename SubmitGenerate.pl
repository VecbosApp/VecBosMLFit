#!/usr/bin/perl

#
# SubmitGenerate.pl
# N. Danielson June 19, 2003
# E. Di Marco Oct 10, 2008
#

use Getopt::Long;


my ($jetbin, $nexp, $njobs, $queue, $logdir, $prefix, $interactive, $command, $release);

# Defaults...

$jetbin=1;
$nexp=1;
$njobs=50;
$queue='cmsshort';
$command='src/GenerateWjets.cc';
$interactive=0;
$directory="toys";
$prefix="";

if ($#ARGV < 1) {
    print <<ENDOFTEXT;
usage: SubmitGenerate.pl [OPTIONS]

 -b, --jetbin=INTEGER
       Jet bin multiplicity to run.  Default=$jetbin

 -n, --nexp=INTEGER
       Number of experiments to run.  Default=$nexp
 
 -j, --jobs=INTEGER
       Number of jobs to submit.  Each job will run [#exp]/[#jobs] experiments
       (rounded down to the nearest integer).  Default=$njobs

 -q, --queue=STRING
       Queue to submit to.  Default=$queue

 -l, --log=STRING
       Name of directory to put the log files in.  Default=<Same as directory specified by -d flag>

 -p, --prefix=STRING
       Prefix to apply to the results and log file names to distinguish wjets/zjets toys  Default is null. 

 -i, --interactive
       Run interactively, not in batch.

 -x, --exe=STRING
       Name of command to use.  Default=$command

 -r, --release=STRING
       CMSSW release where set the ROOT environment.

example: ./SubmitGenerate.pl -r ~/releases/vecbos/CMSSW_2_1_17 -n 10000 -j 10 -q cmsshort -p z -b 3 -x src/GenerateZjets.cc

ENDOFTEXT

   exit 0;
}

GetOptions(
	   "jetbin|b=i"    => \$jetbin,
	   "nexp|n=i"      => \$nexp,
	   "jobs|j=i"      => \$njobs,
	   "queue|q=s"     => \$queue,
	   "log|l=s"       => \$logdir,
	   "prefix|p=s"    => \$prefix,
	   "interactive|i" => \$interactive,
	   "exe|x=s"       => \$command,
	   "release|r=s"   => \$release
	   );

# If CMSSW release is not set, exit
if (! defined $release) { 
    print "release is ot set. Set with -r option. Exiting.\n";
    exit 0;
}

# If no log directory was specified, use toys/log
if (! defined $logdir) {$logdir="$directory/log"};

# Does $logdir exist?
if (! -d "$logdir") {
    print STDERR "$logdir doesn't exist.  Do you want to create it? (y/n)\n";
    my $ans = <STDIN>;
    chomp($ans);
    if( ($ans =~ /yes/i) || ($ans eq "y") ) {
	print STDERR "Creating directory $logdir\n";
	`mkdir -p $logdir`;
    } else {
	print STDERR "Exiting because directory $logdir doesn't exist\n";
	exit 0;
    }
}

# If no log directory was specified, use toys/output
if (! defined $outputdir) {$outputdir="$directory/output"};

# Does $outputdir exist?
if (! -d "$outputdir") {
    print STDERR "$outputdir doesn't exist.  Do you want to create it? (y/n)\n";
    my $ans = <STDIN>;
    chomp($ans);
    if( ($ans =~ /yes/i) || ($ans eq "y") ) {
	print STDERR "Creating directory $outputdir\n";
	`mkdir -p $outputdir`;
    } else {
	print STDERR "Exiting because directory $outputdir doesn't exist\n";
	exit 0;
    }
}
    
# Does $scriptdir exist?
$scriptdir = "$directory/scripts";
if (! -d "$scriptdir") {
    print STDERR "$scriptdir doesn't exist.  Do you want to create it? (y/n)\n";
    my $ans = <STDIN>;
    chomp($ans);
    if( ($ans =~ /yes/i) || ($ans eq "y") ) {
        print STDERR "Creating directory $scriptdir\n";
        `mkdir -p $scriptdir`;
    } else {
        print STDERR "Exiting because directory $scriptdir doesn't exist\n";
        exit 0;
    }
}

my $nExpPerJob=int($nexp/$njobs);
my $ntotal=$nExpPerJob*$njobs;

print <<ENDOUT;
Will run $njobs jobs with $nExpPerJob experiments per job for a total of: $ntotal experiments.
Command:                    $command    
Directory to use:           $directory  
Directory for log files:    $logdir     
Directory for output files: $outputdir
Queue:                      $queue 
Release:                    $release
ENDOUT
    ;    
my $results=`ls -1 $outputdir/results-jet$jetbin-[0-9]*.dat 2> /dev/null`;

# Submit the jobs...
for (my $i = 1; $i <= $njobs; $i++){

    print "Running job $i out of $njobs\n";
    my $logfile = "$logdir/results-$prefix$jetbin\jet-$i.log";
    my $iscript = "$scriptdir/script-$prefix$jetbin\jet-$i.csh";
    my $outfile = "$outputdir/results-$prefix$jetbin\jet-$i.dat"; 
    my $iseed = int(rand(65536));
    open(SCRIPTFILE,">$iscript");
    print SCRIPTFILE "\#\!/bin/tcsh\n\n";
    print SCRIPTFILE "cd $release\n";
    print SCRIPTFILE "cmsenv\n";
    print SCRIPTFILE "cd -\n";
    print SCRIPTFILE "root -b src/RooLogon.C <<EOF\n";
    print SCRIPTFILE ".L $command\n";
    print SCRIPTFILE "SetSeed($iseed)\n";
    print SCRIPTFILE "SetNjets($jetbin)\n";
    print SCRIPTFILE "Generate($nExpPerJob,$iseed,\"$outfile\")\n";
    print SCRIPTFILE ".q\n";
    print SCRIPTFILE "EOF\n";
    system("chmod 777 $iscript");
    if ($interactive==1) {
	system("source $iscript");
    } else {
	system("bsub -q $queue -o $logfile -J $prefix$jetbin\jet-$i < $iscript");
    }
}

print "Done.\n";
