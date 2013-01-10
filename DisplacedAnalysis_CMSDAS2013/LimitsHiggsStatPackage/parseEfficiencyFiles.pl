#!/usr/bin/perl -w

# This script parses the efficiency files from Kristian
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

# Pileup uncertainties are only provided for nominal ctau.
# If this is zero, then the same pileup uncertainty will be used for all ctau.
# If this is one, then the same RELATIVE pileup uncertainty will be used for all ctau.

my $usePileupUncertainty = 1;   # set to 0 to disable pileup uncertainty entirely
my $useRelativePileupUncertainty = 1;
my $indir = "WinterSelection";

my %channels = ("e1" => "dielectron1",
		"e2" => "dielectron2",
		"mu1" => "dimuon1",
		"mu2" => "dimuon2");

# ctau factors in the files
my @ctaufactsIn = ("0.033", "0.050", "0.100", "0.200", "0.300", "0.333", "0.500", "1.000", "2.000", "3.000", "3.333", "5.000", "10.000", "20.000", "30.000");

# ctau factors to produce outputs for
my @ctaufactsOut = ("0.033", "0.050", "0.100", "0.333", "0.500", "1.000", "2.000", "3.000", "10.000", "20.000", "30.000");

my $br = 0.01;

if ($usePileupUncertainty == 0) { print "=== WARNING: SHOULD INCLUDE PILEUP SYSTEMATIC WHEN DEBUGGED ===\n"; }

my %masses = (120 => ["020", "050"],
	      125 => ["020", "050"],
	      200 => ["020", "050"],
	      400 => ["005", "020", "050", "150"],
	      1000 => ["020", "050", "150", "350"]);

my %used_masses = (120 => ["20", "50"],
		   125 => ["20", "50"],
		   200 => ["20", "50"],
		   400 => ["20", "50", "150"],
		   1000 => ["20", "50", "150", "350"]);

my %nominal_lifetimes = ("1000_350" => 35,
		         "1000_150" => 10,
		         "1000_050" => 4,
		         "1000_020" => 1.5,
		         "400_150" => 40,
		         "400_050" => 8,
		         "400_020" => 4,
		         "200_050" => 20,
		         "200_020" => 7,
			 "125_050" => 50,
			 "125_020" => 13,
		         "120_050" => 50,
		         "120_020" => 13);

# Relative systematic due to tracking plus anything else that is not derived from the .txt files.
my $trackingsys_rel = 0.2;

# These hashes store all the data.
# For the efficiency and errors, the hash keys (are in order): channel, ctau factor,
# hmass, xmass.

my %eff;
my %poserr2;
my %negerr2;
my %efferr;
my %reweightFactor;  # reweighting factor used to obtain this point

sub modifiedCtau($$) {
    my ($ctau, $line) = @_;

    my $totctau = $ctau;
    if ($line =~ /ctaufact_0p1/) {
	$totctau = sprintf("%.3f", $ctau/10);
    }
    elsif ($line =~ /ctaufact_10/) { 
	# For 0.333 and 0.033, add an extra 3 on the end so the multiplication
	# works properly
	if ($ctau =~ /3$/) { $totctau .= "3"; } 
	$totctau = sprintf("%.3f", $totctau * 10);
    }
    elsif ($line =~ /ctaufact/) { warn "Unknown ctau factor found in $line!\n"; }
    
    return $totctau;
}

# Obtain the efficiency for each channel.

foreach my $channel (sort keys %channels) {
    my $filetag = $channels{$channel};

    # For each channel, we have three loops. First, pick up the efficiencies themselves.

    foreach my $ctau (@ctaufactsIn) {
	my $infile;
	if ($ctau eq "1.000") { $infile = "$indir/efficiencies_${filetag}.txt"; }
	else { $infile = "$indir/efficiencies_${filetag}_ctaufact_${ctau}.txt"; }
	open INFILE, $infile or die "Couldn't open $infile: $!\n";
	
	while (my $line = <INFILE>) {
	    chomp $line;
	    next if ($line =~ /validate/); # skip lines which may confuse the script

	    my $totctau = &modifiedCtau($ctau, $line);

	    # Use abs(ln) so that, say, 1/3 and 3 are treated equally. Note that this means
	    # lower is better (0 is best, as it's unreweighted).
	    # Also the reweighting factor depends on the ctau NOT including the factor
	    # already present in the subsample.
	    my $reweightFactor = abs(log($ctau));

	    my @fields = split(" ", $line);
	    
	    if ($fields[0] =~ /Signal_(\d+)_(\d+)/) {
		# If this entry doesn't exist, or we've found one with a better
		# reweighting factor, store it; otherwise, move along
		if (!$eff{$channel}{$totctau}{$1}{$2} || $reweightFactor < $reweightFactor{$channel}{$totctau}{$1}{$2}) {
		    $eff{$channel}{$totctau}{$1}{$2} = $fields[1];
		    $reweightFactor{$channel}{$totctau}{$1}{$2} = $reweightFactor;
		}
	    } else {
		warn "Found unexpected line: $line\n";
	    }
	}
	close INFILE;
    }

    # Nextly, pick up the pileup uncertainty, calculate the relative uncertainty (if applicable),
    # and store it for all ctau.
    # Note -- now that we have the subsamples, we store only for ctaus which yield a reweighting
    # factor which matches the above.

    if ($usePileupUncertainty) {
	my $infile = "$indir/efficiencies_${filetag}_pileup_uncertainty.txt";
	open INFILE, $infile or die "Couldn't open $infile: $!\n";
	
	while (my $line = <INFILE>) {
	    chomp $line;
	    next if ($line =~ /validate/); # skip lines which may confuse the script
	    
	    my $ctauThisLine = &modifiedCtau("1.000", $line);

	    my @fields = split(" ", $line);
	    
	    if ($fields[0] =~ /Signal_(\d+)_(\d+)/) {
		my $poserr = $fields[1];
		my $negerr = $fields[2];
		if ($useRelativePileupUncertainty) {
		    my ($relUncertaintyPos, $relUncertaintyNeg);
		    if ($eff{$channel}{$ctauThisLine}{$1}{$2} == 0) {
			$relUncertaintyPos = 1;
			$relUncertaintyNeg = 1;
		    } else {
			$relUncertaintyPos = $poserr/$eff{$channel}{$ctauThisLine}{$1}{$2};
			$relUncertaintyNeg = $negerr/$eff{$channel}{$ctauThisLine}{$1}{$2};
		    }

		    foreach my $ctau (@ctaufactsIn) {
			my $totctau = &modifiedCtau($ctau, $line);
			my $reweightFactor = abs(log($ctau));
			if ($reweightFactor == $reweightFactor{$channel}{$totctau}{$1}{$2}) {
			    my $thisPosErr = $relUncertaintyPos * $eff{$channel}{$totctau}{$1}{$2};
			    my $thisNegErr = $relUncertaintyNeg * $eff{$channel}{$totctau}{$1}{$2};
			    
			    $poserr2{$channel}{$totctau}{$1}{$2} += $thisPosErr*$thisPosErr;
			    $negerr2{$channel}{$totctau}{$1}{$2} += $thisNegErr*$thisNegErr;
			}
		    } # ctau loop
		} else {
		    foreach my $ctau (@ctaufactsIn) {
			my $totctau = &modifiedCtau($ctau, $line);
			my $reweightFactor = abs(log($ctau));
			if ($reweightFactor == $reweightFactor{$channel}{$totctau}{$1}{$2}) {
			    $poserr2{$channel}{$totctau}{$1}{$2} += $poserr*$poserr;
			    $negerr2{$channel}{$totctau}{$1}{$2} += $negerr*$negerr;
			}
		    } # ctau loop
		} # relative/absolute

	    } else {
		warn "Found unexpected line: $line\n";
	    }
	}
	close INFILE;
    }	
    
    # Now, pick up the statistical uncertainty for all the ctaus.

    foreach my $ctau (@ctaufactsIn) {
	my $infile;
	if ($ctau eq "1.000") { $infile = "$indir/efficiencies_${filetag}_statistical_uncertainty.txt"; }
	else { $infile = "$indir/efficiencies_${filetag}_ctaufact_${ctau}_statistical_uncertainty.txt"; }

	open INFILE, $infile or die "Couldn't open $infile: $!\n";
	
	while (my $line = <INFILE>) {
	    chomp $line;
	    next if ($line =~ /validate/); # skip lines which may confuse the script

	    my $totctau = &modifiedCtau($ctau, $line);

	    my $reweightFactor = abs(log($ctau));
	    my @fields = split(" ", $line);
	    
	    if ($fields[0] =~ /Signal_(\d+)_(\d+)/) {
		# Only store if the reweight factor matches what we've gotten previously
		if ($reweightFactor == $reweightFactor{$channel}{$totctau}{$1}{$2}) {
		    my $poserr = $fields[1];
		    my $negerr = $fields[2];
		    
		    $poserr2{$channel}{$totctau}{$1}{$2} += $poserr * $poserr;
		    $negerr2{$channel}{$totctau}{$1}{$2} += $negerr * $negerr;
		}
	    } else {
		warn "Found unexpected line: $line\n";
	    }
	}
	close INFILE;
    } # loop over uncertainties

    # Now prepare the symmetrized error (could do any other necessary
    # postprocessing here but I think it's now been obsoleted).

    foreach my $hmass (sort {$b <=> $a} keys %masses) {
	my @xmasses = @{$masses{$hmass}};

	foreach my $xmass (@xmasses) {
	    foreach my $ctau (@ctaufactsIn) {
		my $poserr = sqrt($poserr2{$channel}{$ctau}{$hmass}{$xmass});
		my $negerr = sqrt($negerr2{$channel}{$ctau}{$hmass}{$xmass});
		my $symerr = sprintf("%.6f", ($poserr + $negerr)/2);
		$efferr{$channel}{$ctau}{$hmass}{$xmass} = $symerr;

	    } # loop over ctaus
	} # loop over x mass
    } # loop over h mass
} # loop over channels

# Next produce the variables for the fits vs. lifetime.

my $nlifetimes = scalar(@ctaufactsOut);

print "// Results by lifetime\n\n";

print "const int nhmass = ", scalar(keys %used_masses), ";\n";
my $maxnxmass = 0;
my @nxmasses;
foreach my $hmass (sort {$b <=> $a} keys %used_masses) {
    my $thisnxmass = scalar(@{$used_masses{$hmass}});
    if ($thisnxmass > $maxnxmass) {$maxnxmass = $thisnxmass;}
    push @nxmasses, $thisnxmass;
}
print "const int nxmass[nhmass] = {", join(", ", @nxmasses), "};\n";
print "const int maxnxmass = $maxnxmass;\n";

print "const int hmass[nhmass] = {", join(", ", sort {$b <=> $a} keys %used_masses), "};\n";
print "const int xmass[nhmass][maxnxmass] = {";
foreach my $hmass (sort {$b <=> $a} keys %used_masses) {
    my @xmasses = sort {$b <=> $a} @{$used_masses{$hmass}};
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
	foreach my $ctau (@ctaufactsOut) {
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
	    foreach my $ctau (@ctaufactsOut) {
		push @effvals, $eff{$channel}{$ctau}{$hmass}{$xmass};
		push @efferrs, $efferr{$channel}{$ctau}{$hmass}{$xmass};
		
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

	    foreach my $ctau (@ctaufactsOut) {
		my $eff1 = $eff{$channel."1"}{$ctau}{$hmass}{$xmass};
		my $eff2 = $eff{$channel."2"}{$ctau}{$hmass}{$xmass};
		my $efferr1 = $efferr{$channel."1"}{$ctau}{$hmass}{$xmass};
		my $efferr2 = $efferr{$channel."2"}{$ctau}{$hmass}{$xmass};

		my $efffactor = 2*$eff1*$br*(1-$br) + 2*$eff2*$br*$br;
		my $effterm1 = 2*$efferr1*$br*(1-$br);
		my $effterm2 = 2*$efferr2*$br*$br;
		my $efferr = sqrt($effterm1*$effterm1 + $effterm2*$effterm2);

		my $trackerr = $trackingsys_rel*$efffactor;

		my $toterr = sqrt($efferr*$efferr + $trackerr*$trackerr);
		
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

	    foreach my $ctau (@ctaufactsOut) {
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
	foreach my $ctau (@ctaufactsOut) {
	    push @lifetimes, ($ctau * $nominal_lifetimes{$pat});
		
	} # lifetime loop

	my $xmass_int = ${xmass} + 0; # Remove leading zeros, since they confuse python !
	print "\n";
        print "s = SignalSampleInfo(${hmass}, ${xmass_int}, ${nominal_lifetimes{$pat}})\n";

        foreach my $channel ("e1", "mu1" ) {

	    my @effvals;
	    my @errvals;
	    my @relerrs;
	    foreach my $ctau (@ctaufactsOut) {
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
	foreach my $ctau (@ctaufactsOut) {
	    $count = ${count} + 1;
	    # Only put some lifetimes into table, so not too long.
	    if (${count} eq 3 or ${count} eq 6 or ${count} eq 9) {
		if (${first} eq 1) {
		    $first = 0;
		    my $xmass_int = ${xmass} + 0; # Remove leading zeros
		    printf " %6i      &  %6i     &   ", ${hmass} , ${xmass_int} ;
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
