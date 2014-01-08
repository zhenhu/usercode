#!/usr/bin/perl -w

# This script parses the new-format efficiency files from Emyr
# and produces three parts of output:
#  * arrays of efficiencies vs. mass suitable for pasting
#    into makeEfficiencyFits.C or suchlike
#  * arrays of efficiencies vs. lifetime suitable for pasting
#    into a script to fit vs. lifetime
#  * values of efficiency factor suitable for pasting into
#    runLifetimeJobs.pl
#  * arrays of efficiencies vs. lifetime suitable for pasting
#    into Ian's kristiansData.py.
#  * latex table for Results section of AN-NOTE
#
# "efficiency factor" is simply the combination of the two efficiencies
# and BR: effFactor = 2*epsilon_1*BR*(1-BR) + 2*epsilon_2*BR^2

use strict;

# set $usePileupUncertainty 0 to disable pileup entirely.
# For the new efficiency files, pileup uncertainty is always assumed to be relative
my $usePileupUncertainty = 1;

my $indir = "/afs/cern.ch/work/p/plujan/public/DisplacedFermions/AnalysisMacros/DileptonMacros/EfficiencyFiles";

my %channels = ("e1" => "2eTrack_one",
		"e2" => "2eTrack_two",
		"mu1" => "2muTrack_one",
		"mu2" => "2muTrack_two");


my %ctaufacts;  # store the various ctau factors we've seen so far

# ctau factors to produce outputs for
my @ctaufactsOut = ("0.033", "0.050", "0.100", "0.333", "0.500", "1.000", "2.000", "3.000", "10.000", "20.000", "30.000");

my $br = 0.01;

if ($usePileupUncertainty == 0) { print "=== WARNING: PILEUP UNCERTAINTY IS OFF ===\n"; }

# No need for separating masses from used masses any more; if you don't want a mass
# to appear in the output, just delete it from here

#my %masses = (120 => ["20", "50"],
#	      200 => ["20", "50"],
#	      400 => ["20", "50", "150"],
#	      1000 => ["20", "50", "150", "350"]);

# note: since not all samples are available yet, we have
# a reduced set for testing porpoises
# (no porpoises were harmed in the course of these tests)

my %masses = (125 => ["50"],
	      200 => ["20", "50"],
	      400 => ["20", "50", "150"],
	      1000 => ["20", "50", "150", "350"]);

# Nominal lifetimes in cm
my %nominal_lifetimes = ("1000_350" => 35,
		         "1000_150" => 10,
		         "1000_50" => 4,
		         "1000_20" => 1.5,
		         "400_150" => 40,
		         "400_50" => 8,
		         "400_20" => 4,
		         "200_50" => 20,
		         "200_20" => 7,
			 "125_50" => 50,
			 "125_20" => 13,
		         "120_50" => 50,
		         "120_20" => 13);

# Systematic for NLO (included only for 125 for the time being)
# This is expressed as a relative uncertainty
my %nlo_systematic = ("125_020" => .037394,
		      "125_050" => .116845);

# Relative systematic due to tracking plus anything else that is not derived from the .txt files.
my $trackingsys_rel = 0.11;

# These hashes store all the data.
# For the efficiency and errors, the hash keys (are in order): channel, ctau factor,
# hmass, xmass.

my %eff;      # efficiency
my %efferr;   # error on efficiency
my %relerr;   # relative error on efficiency

# Obtain the efficiency for each channel.

foreach my $channel (sort keys %channels) {
    my $filetag = $channels{$channel};

    # The looping is much simpler than with the old-format Kristian files. Just loop
    # over the different H and X masses and then read in the corresponding file. Yay!

    foreach my $hmass (keys %masses) {
	my @xmasses = @{ $masses{$hmass}};
	foreach my $xmass (@xmasses) {
	    
	    my $infile = "$indir/efficiencies_HTo2LongLivedTo4F_${hmass}_${xmass}_${filetag}.txt";
	    open INFILE, $infile or die "Couldn't open $infile: $!\n";
    
	    while (my $line = <INFILE>) {
		chomp $line;
		next if ($line =~ /Efficiency/); # skip header lines!
		
		my ($pdg, $ctau, $reweightFactor, $eff, $staterr, $statrelerr, $puplus, $puminus) = split(" ", $line);

		$ctau = $ctau + 0; # coerce to int
		# Could also just calculate this as $ctau/$nominal_ctau. I'm not sure which way is
		# more preferable, really. This avoids nasty unit conversion, however.
		my $ctauFactor;
		if ($pdg == 6001113) { $ctauFactor = 0.1*$reweightFactor; }
		elsif ($pdg == 6002113) { $ctauFactor = $reweightFactor; }
		elsif ($pdg == 6003113) { $ctauFactor = 10*$reweightFactor; }
		else { warn "Alert: unknown PDG id $pdg\n"; }

		# Actually, on second thought, let's make sure this answer makes sense by checking it
		# against the other value.
		my $expected_ctau = $nominal_lifetimes{"${hmass}_${xmass}"} * $ctauFactor * 10;  # 10 to convert cm -> mm
		if ($expected_ctau ne $ctau) {  # not sure why string comparison is needed here, but apparently it is
		    warn "Warning: got unexpected ctau factor; expected $expected_ctau, got $ctau\n";
		}

		# mark this ctau factor as seen
		$ctaufacts{$ctauFactor} = 1;
		
		# I've changed the measurement of quality here from the reweighting factor to the
		# relative error. Could also use the old way if preferred.
		
		# If this entry doesn't exist, or we've found one with a better relative error, store it;
		# otherwise, move along
		if (!$eff{$channel}{$ctauFactor}{$hmass}{$xmass} || $statrelerr < $relerr{$channel}{$ctauFactor}{$hmass}{$xmass}) {
		    $eff{$channel}{$ctauFactor}{$hmass}{$xmass} = $eff;

		    my $puErrPlus = $puplus - $eff;
		    my $puErrMinus = $eff - $puminus;

		    # Compute the total uncertainty.
		    my $poserr2 = $staterr*$staterr + $puErrPlus*$puErrPlus;
		    my $negerr2 = $staterr*$staterr + $puErrMinus*$puErrMinus;

		    my $toterr = (sqrt($poserr2) + sqrt($negerr2))/2;

		    $efferr{$channel}{$ctauFactor}{$hmass}{$xmass} = $toterr;

		    # use only the stat relative error for the measurement of quality -- pileup systematic
		    # should be the same anyway
		    $relerr{$channel}{$ctauFactor}{$hmass}{$xmass} = $statrelerr;
		}

	    }
	    close INFILE;

	} # X mass loop
    } # H mass loop

} # loop over channels

# Next produce the variables for the fits vs. lifetime.

my $nlifetimes = scalar(keys %ctaufacts);

print "// Results by lifetime\n\n";

print "const int nhmass = ", scalar(keys %masses), ";\n";
my $maxnxmass = 0;
my @nxmasses;
foreach my $hmass (sort {$b <=> $a} keys %masses) {
    my $thisnxmass = scalar(@{$masses{$hmass}});
    if ($thisnxmass > $maxnxmass) {$maxnxmass = $thisnxmass;}
    push @nxmasses, $thisnxmass;
}
print "const int nxmass[nhmass] = {", join(", ", @nxmasses), "};\n";
print "const int maxnxmass = $maxnxmass;\n";

print "const int hmass[nhmass] = {", join(", ", sort {$b <=> $a} keys %masses), "};\n";
print "const int xmass[nhmass][maxnxmass] = {";
foreach my $hmass (sort {$b <=> $a} keys %masses) {
    my @xmasses = sort {$b <=> $a} @{$masses{$hmass}};
    if (scalar(@xmasses) < $maxnxmass) {
	@xmasses = (@xmasses, (-1) x ($maxnxmass - scalar(@xmasses)));
    }
    print "{", join(", ", @xmasses), "},\n";
}
print "};\n";
print "const int nlifetimes = $nlifetimes;\n";

# We do basically the same loop twice -- one for the lifetimes
# and then again within the lepton type loop for the efficiencies.

my @lifetimes_out;

my $hindex = 0;
foreach my $hmass (sort {$b <=> $a} keys %masses) {
    my @xmasses = @{$masses{$hmass}};
    my $xindex = 0;
    foreach my $xmass (sort {$b <=> $a} @xmasses) {
	
	my $pat = "${hmass}_${xmass}";
	next if (!$nominal_lifetimes{$pat});
	
	my @lifetimes;
	foreach my $ctau (keys %ctaufacts) {
	    push @lifetimes, ($ctau * $nominal_lifetimes{$pat});
	} # lifetime loop
	
	# store for printing
	
	$lifetimes_out[$hindex][$xindex] = "{".join(", ", @lifetimes)."}, // $hmass/$xmass\n";
	
	$xindex++;
    } # xmass loop
    
    $hindex++;
} # hmass loop

my $spacer = "{". join(", ", (-1)x$nlifetimes)."},\n";
print "float lifetimes[nhmass][maxnxmass][nlifetimes] = {";
for (my $i=0; $i<=$#lifetimes_out; $i++) {
    my @lifetimes_h = @{$lifetimes_out[$i]};
    if (@lifetimes_h < $maxnxmass) {
	push @lifetimes_h, ($spacer) x ($maxnxmass-@lifetimes_h);
    }
    print "{", @lifetimes_h, "},\n";
}
print "};\n";

foreach my $channel (sort keys %channels) {
    my @lifetimes_out;
    my @effvals_out;
    my @efferrs_out;

    my $hindex = 0;
    foreach my $hmass (sort {$b <=> $a} keys %masses) {
	my @xmasses = @{$masses{$hmass}};
	my $xindex = 0;
	foreach my $xmass (sort {$b <=> $a} @xmasses) {
	    
	    my $pat = "${hmass}_${xmass}";
	    next if (!$nominal_lifetimes{$pat});
	    
	    my @effvals;
	    my @efferrs;
	    foreach my $ctau (keys %ctaufacts) {
		push @effvals, (sprintf "%.6f", $eff{$channel}{$ctau}{$hmass}{$xmass});
		push @efferrs, (sprintf "%.6f", $efferr{$channel}{$ctau}{$hmass}{$xmass});
		
	    } # lifetime loop

	    # store for printing

	    $effvals_out[$hindex][$xindex] =  "{".join(", ", @effvals)."}, // $hmass/$xmass\n";
	    $efferrs_out[$hindex][$xindex] = "{".join(", ", @efferrs)."}, // $hmass/$xmass\n";

	    $xindex++;
	} # xmass loop

	$hindex++;
    } # hmass loop

    print "float effvals_${channel}[nhmass][maxnxmass][nlifetimes] = {";
    for (my $i=0; $i<=$#effvals_out; $i++) {
	my @effvals_h = @{$effvals_out[$i]};
	if (@effvals_h < $maxnxmass) {
	    push @effvals_h, ($spacer) x ($maxnxmass-@effvals_h);
	}
	print "{", @effvals_h, "},\n";
    }
    print "};\n";
    print "float efferrs_${channel}[nhmass][maxnxmass][nlifetimes] = {";
    for (my $i=0; $i<=$#efferrs_out; $i++) {
	my @efferrs_h = @{$efferrs_out[$i]};
	if (@efferrs_h < $maxnxmass) {
	    push @efferrs_h, ($spacer) x ($maxnxmass-@efferrs_h);
	}
	print "{", @efferrs_h, "},\n";
    }
    print "};\n";

} # lepton type/number loop

# One final loop!
# This is to calculate the effective efficiencies for the known samples.
    
print "\n// Effective efficiency values\n\n";

foreach my $channel ("e", "mu") {
    print "$channel:\n";
    foreach my $hmass (sort keys %masses) {
	my @xmasses = @{$masses{$hmass}};
	foreach my $xmass (sort @xmasses) {
	    
	    my $pat = "${hmass}_${xmass}";
	    next if (!$nominal_lifetimes{$pat});

	    foreach my $ctau (keys %ctaufacts) {
		my $eff1 = $eff{$channel."1"}{$ctau}{$hmass}{$xmass};
		my $eff2 = $eff{$channel."2"}{$ctau}{$hmass}{$xmass};
		my $efferr1 = $efferr{$channel."1"}{$ctau}{$hmass}{$xmass};
		my $efferr2 = $efferr{$channel."2"}{$ctau}{$hmass}{$xmass};

		my $efffactor = 2*$eff1*$br*(1-$br) + 2*$eff2*$br*$br;
		my $effterm1 = 2*$efferr1*$br*(1-$br);
		my $effterm2 = 2*$efferr2*$br*$br;
		my $efferr = sqrt($effterm1*$effterm1 + $effterm2*$effterm2);

		my $trackerr = $trackingsys_rel*$efffactor;

		my $nloerr = 0;
		if ($nlo_systematic{$pat}) {
		    $nloerr = $nlo_systematic{$pat}*$efffactor;
		}

		my $toterr = sqrt($efferr*$efferr + $trackerr*$trackerr + $nloerr*$nloerr);
		
		# print "percent error = ", sprintf("%.2f", ($toterr/$efffactor)), "\n";
		my $lt = $ctau * $nominal_lifetimes{$pat};


		print "\"$pat"."_$lt\" => \[$efffactor, $toterr\],\n";
	    } # lifetime loop

	} # x mass loop
    } # h mass loop
} # e/mu loop

# Repeat for "Jeremy file"
# Note that the print is currently commented out because this isn't
# really useful any more, but it's retained just in case we need it
# in the future.

foreach my $channel ("e", "mu") {
    foreach my $hmass (keys %masses) {
	my @xmasses = @{$masses{$hmass}};
	foreach my $xmass (@xmasses) {
	    
	    my $pat = "${hmass}_${xmass}";
	    next if (!$nominal_lifetimes{$pat});

	    foreach my $ctau (keys %ctaufacts) {
		my $eff1 = $eff{$channel."1"}{$ctau}{$hmass}{$xmass};
		my $eff2 = $eff{$channel."2"}{$ctau}{$hmass}{$xmass};

		my $efffactor = 2*$eff1*$br*(1-$br) + 2*$eff2*$br*$br;
		my $lt = sprintf("%.1f", $ctau * $nominal_lifetimes{$pat});

		my $modset = $channel;
		$modset = "el" if ($channel eq "e");

		my $modxmass = $xmass;
		$modxmass =~ s/^0//;

		# print $modset . "_MH${hmass}_MX${modxmass}_ct$lt => $efffactor\n";
	    } # lifetime loop
	} # x mass loop
    } # h mass loop
} # e/mu loop

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# Produce variables for Ian's fits vs. lifetime.

print "\n// Results by lifetime for Ian\n\n";
	
foreach my $hmass (keys %masses) {
    my @xmasses = @{$masses{$hmass}};
    foreach my $xmass (@xmasses) {
	    
	my $pat = "${hmass}_${xmass}";
	next if (!$nominal_lifetimes{$pat});

	my @lifetimes;
	foreach my $ctau (keys %ctaufacts) {
	    push @lifetimes, ($ctau * $nominal_lifetimes{$pat});
		
	} # lifetime loop

	print "\n";
        print "s = SignalSampleInfo(${hmass}, ${xmass}, ${nominal_lifetimes{$pat}})\n";

        foreach my $channel ("e1", "mu1" ) {

	    my @effvals;
	    my @errvals;
	    my @relerrs;
	    foreach my $ctau (keys %ctaufacts) {
		push @effvals, $eff{$channel}{$ctau}{$hmass}{$xmass};
		# Inflate uncertainty to include 20% tracking systematic
		my $trackerr = $trackingsys_rel * $eff{$channel}{$ctau}{$hmass}{$xmass};
		my $toterr = sqrt($efferr{$channel}{$ctau}{$hmass}{$xmass} * $efferr{$channel}{$ctau}{$hmass}{$xmass} + $trackerr * $trackerr);
		push @errvals, $toterr;
		if ($eff{$channel}{$ctau}{$hmass}{$xmass} == 0) {
		    push @relerrs, 9999;
		} else {
		    push @relerrs,  ( $toterr / $eff{$channel}{$ctau}{$hmass}{$xmass} );
		}
		
	    } # lifetime loop

	    if ($channel eq "e1") {
                # Electron:
		print "s.setE(\n";
		print "[";
		my $first = 1;
		foreach (@effvals) {
		  if (${first} eq 1) {
		      $first = 0;
		  } else {
		      print ", ";
		  }
		  printf "%.6f", $_;
		}
		print "],\n";
		print "[";
		$first = 1;
		foreach (@relerrs) {
		  if (${first} eq 1) {
		      $first = 0;
		  } else {
		      print ", ";
		  }
		  printf "%.6f", $_;
		}
		print "])\n";
	    } else {
                # Muon: 
		print "s.setM(\n";
		print "[";
		my $first = 1;
		foreach (@effvals) {
		  if (${first} eq 1) {
		      $first = 0;
		  } else {
		      print ", ";
		  }
		  printf "%.6f", $_;
		}
		print "],\n";
		print "[";
		$first = 1;
		foreach (@relerrs) {
		  if (${first} eq 1) {
		      $first = 0;
		  } else {
		      print ", ";
		  }
		  printf "%.6f", $_;
		}
		print "])\n";
            } 

	} # lepton loop
	print "samples.append(s)\n"
    } # xmass loop
} # hmass loop

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


# Produce Latex table of efficiencies for AN-NOTE

print "\n// Latex table of efficiencies for AN-NOTE\n\n";
	
foreach my $hmass (sort {$b <=> $a} keys %masses) {

    my @xmasses = @{$masses{$hmass}};
    foreach my $xmass (sort {$b <=> $a} @xmasses) {
	    
	my $pat = "${hmass}_${xmass}";
	next if (!$nominal_lifetimes{$pat});

	print "\\hline \n";

	# lifetime loop
	my $count = 0;
        my $first = 1;
	foreach my $ctau (keys %ctaufacts) {
	    $count = ${count} + 1;
	    # Only put some lifetimes into table, so not too long.
	    if (${count} eq 3 or ${count} eq 6 or ${count} eq 9) {
		if (${first} eq 1) {
		    $first = 0;
		    my $xmass = ${xmass} + 0; # Remove leading zeros
		    printf " %6i      &  %6i     &   ", ${hmass} , ${xmass} ;
		} else { 
		    print "             &             &   ";
		}

		my $life = $ctau * $nominal_lifetimes{$pat};

		my $n = 3 - int(log(${life})/log(10.));
		for (my $i = 0; $i < $n; $i++) {print "~"}
		printf '%.1f', ${life};
		
		# lepton loop
		foreach my $channel ("e1", "e2", "mu1", "mu2") {
		    if ($eff{$channel}{$ctau}{$hmass}{$xmass} > 0.1) {
			printf '   & %.2f~', $eff{$channel}{$ctau}{$hmass}{$xmass};
		    } else {
			printf '   & %.3f', $eff{$channel}{$ctau}{$hmass}{$xmass};
		    }
#		    print " \pm $efferr{$channel}{$ctau}{$hmass}{$xmass}";

		} 
		print "  \\\\ \n"
	    }

	} 
    } 
}
