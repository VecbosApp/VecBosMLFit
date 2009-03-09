#!/usr/bin/perl

#
# SubmitGenerate.pl
# N. Danielson June 19, 2003
# E. Di Marco Oct 10, 2008
#

use Getopt::Long;


my ($jetbin, $jetflavour, $nexp, $njobs, $queue, $logdir, $prefix, $interactive, $command, $release, $disklocation);

# Defaults...

$jetbin=1;
$jetflavour="calojet";
$nexp=1;
$njobs=50;
$queue='cmsshort';
$command='src/GenerateWjets.cc';
$interactive=0;
$directory="toys/";
$prefix="";

if ($#ARGV < 1) {
    print <<ENDOFTEXT;
usage: SubmitGenerate.pl [OPTIONS]

 -b, --jetbin=INTEGER
       Jet bin multiplicity to run.  Default=$jetbin

 -f, --jetflavour=STRING
       Flavour of the jet (calojet or trackjet).  Default=$jetflavour

 -n, --nexp=INTEGER
       Number of experiments to run.  Default=$nexp
 
 -j, --jobs=INTEGER
       Number of jobs to submit.  Each job will run \#exp/\#jobs experiments
       (rounded down to the nearest integer).  Default=$njobs

 -q, --queue=STRING
       Queue to submit to.  Default=$queue

 -l, --log=STRING
       Name of directory to put the log files in.  Default=<Same as directory specified by -d flag>

 -d, --disklocation=STRING
       Name of directory to put the dat files in. Default=toys

 -p, --prefix=STRING
       Prefix to apply to the results and log file names to distinguish wjets/zjets toys  Default is null. 

 -i, --interactive
       Run interactively, not in batch.

 -x, --exe=STRING
       Name of command to use.  Default=$command

 -r, --release=STRING
       CMSSW release where set the ROOT environment.

example: ./SubmitGenerate.pl -r ~/releases/vecbos/CMSSW_2_1_17 -n 10000 -j 10 -q cmsshort -p Z -b 3 -f calojet -x src/GenerateZjets.cc -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wcalojets

ENDOFTEXT

   exit 0;
}

GetOptions(
	   "jetbin|b=i"    => \$jetbin,
           "jetflavour|f=s"=> \$jetflavour,
	   "nexp|n=i"      => \$nexp,
	   "jobs|j=i"      => \$njobs,
	   "queue|q=s"     => \$queue,
	   "log|l=s"       => \$logdir,
           "disklocation|d=s" => \$disklocation,
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

$outputdir=".";

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
my $results=`ls -1 $outputdir/results-$prefix$jetbin$jetflavour-[0-9]*.dat 2> /dev/null`;

$currDir=`pwd`;
chomp $currDir;

# Submit the jobs...
for (my $i = 1; $i <= $njobs; $i++){

    print "Running job $i out of $njobs\n";
    my $logfile = "$logdir/results-$prefix$jetbin$jetflavour-$i.log";
    my $iscript = "$scriptdir/script-$prefix$jetbin$jetflavour-$i.csh";
    my $outfile = "$outputdir/results-$prefix$jetbin$jetflavour-$i.dat"; 
    my $iseed = int(rand(65536)+$i);
    open(SCRIPTFILE,">$iscript");
    print SCRIPTFILE "\#\!/bin/tcsh\n\n";
    print SCRIPTFILE "cd $release\n";
    print SCRIPTFILE "eval `scramv1 ru -csh`\n";
    print SCRIPTFILE "cp -r $currDir/toyconfig \$WORKDIR\n";
    print SCRIPTFILE "cp -r $currDir/src \$WORKDIR\n";
    print SCRIPTFILE "cd \$WORKDIR\n";
    print SCRIPTFILE "mkdir toys\n";
    print SCRIPTFILE "root -b src/RooLogon.C <<EOF\n";
    print SCRIPTFILE ".L $command\n";
    print SCRIPTFILE "SetNjets($jetbin)\n";
    print SCRIPTFILE "SetJetFlavour(\"$jetflavour\")\n";
    print SCRIPTFILE "Generate($nExpPerJob,$iseed,\"$outfile\")\n";
    print SCRIPTFILE ".q\n";
    print SCRIPTFILE "EOF\n";
    print SCRIPTFILE "scp results-*dat -o BatchMode=yes -o StrictHostKeyChecking=no $disklocation\n";
    print SCRIPTFILE "scp toys/*root $currDir/$directory\n";
    system("chmod 777 $iscript");
    if ($interactive==1) {
	system("source $iscript");
    } else {
	system("bsub -q $queue -o $logfile -J $prefix$jetbin\jet-$i < $iscript");
    }
}

print "Done.\n";
