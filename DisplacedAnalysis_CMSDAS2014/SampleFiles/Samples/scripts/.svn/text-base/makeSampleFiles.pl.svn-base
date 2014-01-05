#!/usr/bin/perl -w

# This takes the entire contents of the PATtuple directory and makes
# a bunch of sample files, one for each found in the directory.

my $directory = "/pnfs/cms/WAX/11/store/user/plujan/PATtuples";
my $sampledir = "/uscms_data/d3/plujan/CMSSW_5_3_3/src/SampleFiles/Samples/python";
my $template = "signal_template_8TeV_cff.txt";

my @files = glob("$directory/*8TeV*.root");

# Hash of all the files found. The key is the name of the sample
# and the data an array of the files belonging to that sample.

my %samples;

foreach my $file (@files) {
    if ($file =~ /PATtuple_(.*)_(\d+).root/) {
	my $sampleName = $1;
	my $number = $2;

	if ($samples{$sampleName}) {
	    push (@{ $samples{$sampleName}}, $file);
	} else {
	    my @temp = ($file);
	    $samples{$sampleName} = \@temp;
	}
    } else {
	warn "Error: couldn't understand file name $file!\n";
    }
}

foreach my $sample (keys %samples) {
    my @files = sort(@ {$samples{$sample}});

    my $numevents = 10000*(scalar(@files));

    my $infile = $sampledir."/".$template;
    open INFILE, $infile or die "Couldn't open $infile: $!\n";

    my $outfile = "$sampledir/signal_${sample}_cff.py";
    open OUTFILE, ">$outfile" or die "Couldn't open $outfile: $!\n";

    while (my $line = <INFILE>) {
	if ($line =~ NEVENTS) { $line =~ s/NEVENTS/$numevents/; }

	if ($line =~ FILELIST) {
	    foreach my $file (@files) { print OUTFILE "    \"dcache:$file\",\n"; }
	} else {
	    print OUTFILE $line;
	}
    }
    close INFILE;
    close OUTFILE;
}

