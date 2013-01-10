#!/usr/bin/perl -w

use strict;

# A script which automates the process of
# 1) copying the various mass files from the svn repository
#    into a single directory
# 2) giving them distinct names
# 3) running ROOT to rebin them

my @selections = ("elecloose_1_pt41", "elecloose_2_pt41",
		  "elecloose_pt41", "electron_pt36",
		  "electron_pt41", "electron_pt46",
		  
		  "muloose_1_pt33", "muloose_2_pt33",
		  "muloose_pt33", "muon_pt26",
		  "muon_pt33");

my %defaultPt = ("electron" => 41, "muon" => 33);

my $basedir = "/afs/cern.ch/user/p/plujan/tdr2/papers/EXO-11-101/trunk/WinterFigs/selection";

# loop over different selections
foreach my $selection (@selections) {
    
    # find the pt
    $selection =~ /pt(\d+)/;
    my $pt = $1;

    # the label used in the name of the text files
    # doesn't contain the pt, so scrap that
    my $txtfilelabel = $selection;
    $txtfilelabel =~ s/_pt\d+//;

    foreach my $type ("data", "backgroundMC") {
	
	# get the infile
	my $infile = "masses_${type}_${txtfilelabel}.txt";

	# rename the outfile if this isn't the "standard" pt, to
	# avoid collisions
	my $outfile = $infile;
	if ($defaultPt{$txtfilelabel} &&
	    $defaultPt{$txtfilelabel} != $pt) {
	    $outfile =~ s/$txtfilelabel/$txtfilelabel$pt/;
	}

	system("cp $basedir/$selection/limits/$infile $outfile");

	my $rootfile = $outfile;
	$rootfile =~ s/.txt/_rebin.root/;

	# fun with quoting
	system("root -b -q txt_to_root.C\\(\\\"$outfile\\\",\\\"$rootfile\\\"\\)");

	# repeat for the nonprompt file. this only needs to be done for
	# the basic level
	if ($selection eq "electron_pt41" || $selection eq "muon_pt33") {
	    my $isGZipped = 0;
	    my $infilePrompt = "masses_${type}_${txtfilelabel}_noLifetimeCuts.txt";
	    if (!-e "$basedir/$selection/limits/$infilePrompt") {
		$infilePrompt .= ".gz";
		$isGZipped = 1;
	    }
	    
	    my $outfilePrompt = $infilePrompt;
	    if ($defaultPt{$txtfilelabel} &&
		$defaultPt{$txtfilelabel} != $pt) {
		$outfilePrompt =~ s/$txtfilelabel/$txtfilelabel$pt/;
	    }
	    
	    system("cp $basedir/$selection/limits/$infilePrompt $outfilePrompt");
	    if ($isGZipped == 1) {
		system("gunzip -f $outfilePrompt");
		$outfilePrompt =~ s/.gz//;
	    }
	    my $rootfilePrompt = $outfilePrompt;
	    $rootfilePrompt =~ s/.txt/_rebin.root/;
	    
	    # fun with quoting
	    system("root -b -q txt_to_root.C\\(\\\"$outfilePrompt\\\",\\\"$rootfilePrompt\\\"\\)");
	    
	}
    } # data/bkg loop
}

# Also copy in the efficiency files.

foreach my $selection ("electron_pt41", "muon_pt33") {
    system("cp $basedir/$selection/limits/eff*.txt .");
}
