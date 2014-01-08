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
use warnings FATAL => qw(numeric uninitialized);

# Decide if acceptance corrected efficiencies are required, depending on calling argument of script.
my $inAcceptance;
my $numArg = scalar(@ARGV);
if ($numArg == 1) {
  $inAcceptance = $ARGV[0];
} else {
  print "ERROR: parseEfficiencyFiles.pl expects you to call it with one argument.\n";
  print "  usage: parseEfficiencyFiles.pl 1    - to get the signal efficiencies,\n";
  print "  or     parseEfficiencyFiles.pl 2    - to get the signal efficiencies divided by acceptancies.\n";
  exit;
}

my $infileStem;
if ( $inAcceptance eq 1 ) {
  $infileStem = "InputData2012//EfficiencyFiles/efficiencies_coll_HTo2LongLivedTo4F";
} elsif ( $inAcceptance eq 2 ) {
  $infileStem = "InputData2012//EfficiencyFiles/efficiencyOverAcceptance/efficienciesOverAcceptance_coll_HTo2LongLivedTo4F";
} else {
  print "ERROR: parseEfficiencyFiles.pl must be called with a single argument of value 1 or 2.\n"; 
  exit;
}
print " ===== Will read input efficiency data from files with stem \n ===== ", $infileStem," \n\n";

my $massResFile = "./InputData2012/SignalMassResolutionFiles/massResolutions.txt";
print " ===== Will read input signal mass resolution from file \n ===== ", $massResFile,"\n\n";

my %channels = ("e1" => "2eTrack_one",
		"e2" => "2eTrack_two",
		"mu1" => "2muTrack_one",
		"mu2" => "2muTrack_two");


my %ctaufacts;  # store the various ctau factors we've seen so far

my $br = 0.01;

#=== SYSTEMATICS

# set $usePileupUncertainty 0 to disable pileup entirely.
my $usePileupUncertainty = 1;
if ($usePileupUncertainty == 0) { print "=== WARNING: PILEUP UNCERTAINTY IS OFF ===\n"; }

# Systematic for NLO (included only for 125 for the time being)
# This is expressed as a relative uncertainty
my %nlo_systematic = ("125_020" => .05,
		      "125_050" => .07);

# Relative systematic on signal efficiency, excluding NLO effects.
# Same uncertainty applies to e2 and mu2.
my %signalEffiSys_rel = ("e1"  => 0.12,
                         "mu1" => 0.13);

# No need for separating masses from used masses any more; if you don't want a mass
# to appear in the output, just delete it from here

my %masses = (125 => ["20", "50"],
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

#=== Obtain signal mass resolution for each signal mass & lifetime.

# Thes hashes store all the signal mass resolution data and their uncertainties.
# The hash keys (are in order): channel, ctau factor, hmass, xmass.
my %massRes;
my %massResErr;

# These store the current signal masses for use whilst parsing the file.
my $hm;
my $xm;

open INMASSFILE, $massResFile or die "Couldn't open $massResFile: $!\n";

my $newSect = 0;

while (my $line = <INMASSFILE>) {
    chomp $line;
    #print "line $line\n";

    # search for section header containing masses
    if ($line =~ /HTo2LongLivedTo4F/) {
        # discover which signal masses this new section is for.

        foreach my $hmass (keys %masses) {
    	    my @xmasses = @{ $masses{$hmass}};
	    foreach my $xmass (@xmasses) {	    
	        my $massString = "_MH${hmass}_MFF${xmass}";
                if ($line =~ $massString) {
                    # Note we found one of the expected signal masses in file.
              	    $newSect = 1;
		    # Make a note of the masses of this section.
                    $hm = $hmass;
                    $xm = $xmass;
		    #print "Found new section in mass resolution file $hm $xm\n";
	        }
            }
        }
        if ($newSect == 0) {
	    print "ERROR: unknown signal masses at line = ",$line,"\n";
            exit 1;
        }

    } elsif ($newSect == 1) { # This means we are now going through the data inside a section.
        my @words = split(" ", $line);
        # Check this line has the expected number of columns.
        if (scalar(@words) == 7) {
	   my ($pdg, $ctau, $ctauFactOrig, $res_mu, $err_mu, $res_e, $err_e) = @words;

           if ($ctau ne "ctau") { # skip column headings

   	       # Do not use any results in which the lifetime was scaled upwards, except
	       # that obtained from the longest lifetime exotic. In that case use the efficiency
	       # obtained from a truncated exponential decay distribution, where truncation point
	       # is outside Tracker.
	       next if ($pdg != 6003113 and $ctauFactOrig > 1.01); 

               # correct ctau scalar factor by *10 or /10 depending on which signal PDG code is present.
	       my $ctauFactor = $ctauFactOrig;
	       if ($pdg == 6001113) { $ctauFactor *= 0.1; }
	       elsif ($pdg == 6002113) { $ctauFactor *= 1.; }
	       elsif ($pdg == 6003113) { $ctauFactor *= 10.; }
	       else { warn "Alert: unknown PDG id $pdg\n"; }

   	       # If resolution recorded as -ve, means that it was not available (no statistics).
	       if ($res_mu < 0) { $err_mu = 99999999.; }
	       if ($res_e < 0)  { $err_e  = 99999999.; }

               # Store the resolution data.
	       if (!$massResErr{"mu"}{$ctauFactor}{$hm}{$xm} || $err_mu < $massResErr{"mu"}{$ctauFactor}{$hm}{$xm}) {
                 $massRes   {"mu"}{$ctauFactor}{$hm}{$xm} = $res_mu;
                 $massResErr{"mu"}{$ctauFactor}{$hm}{$xm} = $err_mu;
	       }
	       if (!$massResErr{"e"}{$ctauFactor}{$hm}{$xm} || $err_mu < $massResErr{"e"}{$ctauFactor}{$hm}{$xm}) {
                 $massRes   {"e"}{$ctauFactor}{$hm}{$xm} = $res_e;
                 $massResErr{"e"}{$ctauFactor}{$hm}{$xm} = $err_e;
	       }
               #print "Storing: $hm  $xm  $ctauFactor --> ",$massRes{"mu"}{$ctauFactor}{$hm}{$xm}," ",$massRes{"e"}{$ctauFactor}{$hm}{$xm},"\n";
           }
        } else {
            # must have reached end of section (blank line)
            $newSect = 0; 
        }
    } else {
	#print "skipping line $line \n";
    }
}

# Check that all signal masses were present in the file.
foreach my $hmass (keys %masses) {
    my @xmasses = @{ $masses{$hmass}};
    foreach my $xmass (@xmasses) {	    
        if (!$massRes{"mu"}{1}{$hmass}{$xmass}) {
	    print "ERROR: signal mass $hmass $xmass was not present in $massResFile\n";
            exit 1;
        }
    }
}


# These hashes store all the efficiency data.
# For the efficiency and errors, the hash keys (are in order): channel, ctau factor,
# hmass, xmass.

my %eff;      # efficiency
my %efferr;   # error on efficiency
my %negeff;      # Ditto but efficiency for signal to end up in control region (e.g. -ve d0/sigma)
my %negefferr;   # Ditto
my %pdgused;  # PDG code of exotic chosen (because best) for each point

open COMPFILE, ">", "compare.txt" or die "Couldn't create compare.txt: $!\n";

# Obtain the efficiency for each channel.

foreach my $channel (sort keys %channels) {
    my $filetag = $channels{$channel};

    # The looping is much simpler than with the old-format Kristian files. Just loop
    # over the different H and X masses and then read in the corresponding file. Yay!

    foreach my $hmass (keys %masses) {
	my @xmasses = @{ $masses{$hmass}};
	foreach my $xmass (@xmasses) {
	    
	    my $infile = "${infileStem}_${hmass}_${xmass}_${filetag}.txt";
	    open INFILE, $infile or die "Couldn't open $infile: $!\n";
    
	    while (my $line = <INFILE>) {
		chomp $line;
		next if ($line =~ /Efficiency/); # skip header lines!
		
		my ($pdg, $ctau, $ctauFactOrig, $effi, $staterr, $statrelerr, $puplus, $puminus, $effTrunc, $effTruncStatErr, $puplusTrunc, $puminusTrunc, $negeffi, $negeffstaterr, $negstatrelerr, $negeffTrunc, $negeffTruncStatErr) = split(" ", $line);

		# This code is useful for debugging when to trust truncated vs. normal efficiencies etc.
		# Normal efficiencies tend to be too high for big ctauFactor, as no events at very long c*tau exist to be given large weights in the denominator.
		# The truncated efficiency seems reliable for any ctauFactor, providing the mean c*tau is at least 20 cm or so.
		if ($pdg != 6001113) {
		    if ($channel eq "mu1" or $channel eq "e1") {
			my $Diff = ($effTrunc - $effi)/(1.0e-12 + $effTrunc);
			my $Differr = $staterr/(1.0e-12 + $effTrunc);
			printf COMPFILE "%7i %7.3f %3s %5i %5i  =  %7.3f +- %7.3f  :  %.3f +- %.3f vs. %.3f +- %.3f\n" ,$pdg,$ctauFactOrig,$channel,$hmass,$xmass,$Diff,$Differr,$effi,$staterr,$effTrunc,$effTruncStatErr;
		    }
                }

		# Do not use any results in which the lifetime was scaled upwards, except
		# that obtained from the longest lifetime exotic. In that case use the efficiency
		# obtained from a truncated exponential decay distribution, where truncation point
		# is outside Tracker.
		next if ($pdg != 6003113 and $ctauFactOrig > 1.01); 

		# Convert ctau from mm (which it is in .txt files) to cm.
                $ctau = $ctau/10;

		# Could also just calculate this as $ctau/$nominal_ctau. I'm not sure which way is
		# more preferable, really. This avoids nasty unit conversion, however.
		my $ctauFactor;
		if ($pdg == 6001113) { $ctauFactor = 0.1*$ctauFactOrig; }
		elsif ($pdg == 6002113) { $ctauFactor = 1.*$ctauFactOrig; }
		elsif ($pdg == 6003113) { $ctauFactor = 10.*$ctauFactOrig; }
		else { warn "Alert: unknown PDG id $pdg\n"; }

		# Actually, on second thought, let's make sure this answer makes sense by checking it
		# against the other value.
		my $expected_ctau = $nominal_lifetimes{"${hmass}_${xmass}"} * $ctauFactor; 
		if (abs($expected_ctau - $ctau) > 0.01*$ctau) {  # not sure why string comparison is needed here, but apparently it is
		    warn "Warning: for $hmass $xmass got unexpected ctau ; expected $expected_ctau, got $ctau\n";
                    exit;
		}

		# mark this ctau factor as seen
		$ctaufacts{$ctauFactor} = 1;

		# I've changed the measurement of quality here from the reweighting factor to the
		# relative error. Could also use the old way if preferred.
		
		# If this entry doesn't exist, or we've found one with a better relative error, store it;
		# otherwise, move along

		# This old approach of comparing statistical errors to choose the best result didn't work well, as
		# stat errors not reliable for large weights.
		#if (!$eff{$channel}{$ctauFactor}{$hmass}{$xmass} || $statrelerr < $relerr{$channel}{$ctauFactor}{$hmass}{$xmass}) {
		#    $eff{$channel}{$ctauFactor}{$hmass}{$xmass} = $effi;

		# Instead use the one with the smallest PDG code of the exotic (works because exotics with lifetime scale 
		# factor > 1 were rejected abovem unless they were longest lifetime PDG.
		if (!$pdgused{$channel}{$ctauFactor}{$hmass}{$xmass} || $pdg < $pdgused{$channel}{$ctauFactor}{$hmass}{$xmass}) {

		    if ($ctauFactOrig > 1.01 and $inAcceptance eq 1 ) {
			# --- Replace normal efficiencies by truncated efficiencies in this case.
                        # (Should be OK, as truncation is at 6*orig_ctau = ~120*10 cm for longest lifetime PDG exotic)
			# Truncated efficiencies should only be used for effi, not effi/acc, as Lxy cut makes truncation
			# unnecessary in effi/acc case, and also non-trivial to use.
			$effi    = $effTrunc;
                        $staterr = $effTruncStatErr;
                        $puplus  = $puplusTrunc;
                        $puminus = $puminusTrunc;
                        $negeffi = $negeffTrunc;
                    }

		    $eff{$channel}{$ctauFactor}{$hmass}{$xmass} = $effi;

		    # Compute the total uncertainty, including pileup systematic.
		    my $toterr;
		    if ($usePileupUncertainty == 1) {
		        my $puErrPlus = $puplus - $effi;
		        my $puErrMinus = $effi - $puminus;

     		        my $poserr2 = $staterr*$staterr + $puErrPlus*$puErrPlus;
		        my $negerr2 = $staterr*$staterr + $puErrMinus*$puErrMinus;

		        $toterr = (sqrt($poserr2) + sqrt($negerr2))/2;
	   	    } else{
			$toterr = $staterr;
		    }

		    $efferr{$channel}{$ctauFactor}{$hmass}{$xmass} = $toterr;

		    # Also store efficiency in control region.
		    $negeff{$channel}{$ctauFactor}{$hmass}{$xmass} = $negeffi;

		    # Note which PDG code exotic was used for this point.
		    $pdgused{$channel}{$ctauFactor}{$hmass}{$xmass} = $pdg;

                    # Check that this signal mass & lifetime was also present in mass resolution file.
                    if (!$massRes{"mu"}{$ctauFactor}{$hmass}{$xmass}) {
	                print "ERROR: signal mass $hmass $xmass ctau factor $ctauFactor is present in efficiency files, but not in signal mass resolution file\n";
                        exit 1;
                    }

		    # Check error in input files where efficiency uncertainty is -ve.
		    if ($efferr{$channel}{$ctauFactor}{$hmass}{$xmass} < 0) {
		       # Efficiency is sometimes -1 for dicandidate case, just through lack of stats, so don't print error in that case.
   		       if ($channel eq "mu1" or $channel eq "e1") {
			   print "ERROR: Efficiency uncertainty is negative for channel=",$channel,", masses=(",$hmass,",",$xmass,"), lifetime factor=",$ctauFactor," original factor = ",$ctauFactOrig,"\n";
			   exit 1;
		       }
		    }
		}

	    }
	    close INFILE;

	} # X mass loop
    } # H mass loop

} # loop over channels

# Check that all channels/masses have the same number of lifetime points.
foreach my $channel (keys %channels) {
    foreach my $hmass (keys %masses) {
	my @xmasses = @{ $masses{$hmass}};
	foreach my $xmass (@xmasses) {
	    foreach my $ctau (keys %ctaufacts) {
		if (! exists $eff{$channel}{$ctau}{$hmass}{$xmass}) {
		    print "ERROR: Lifetime factor ",$ctau," was missing for channel=",$channel,", masses=(",$hmass,",",$xmass,")\n";
		    exit 1;
		}
	    }
	}
    }
}

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

		my $effisyserr = $signalEffiSys_rel{$channel."1"}*$efffactor;

		my $nloerr = 0;
		if ($nlo_systematic{$pat}) {
		    $nloerr = $nlo_systematic{$pat}*$efffactor;
		}

		my $toterr = sqrt($efferr*$efferr + $effisyserr*$effisyserr + $nloerr*$nloerr);
		
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

my $ianfile;
if ($inAcceptance == 1) {
  $ianfile = "SignalSampleInfoEffi.py";
} elsif ($inAcceptance == 2) {
  $ianfile = "SignalSampleInfoEffiOverAcc.py";
}

print "will be written to file $ianfile \n";

open IANFILE, ">", $ianfile or die "Couldn't create $ianfile: $!\n";
print IANFILE "# === This file was created by the script parseEfficiencyFiles.pl ===\n";
	
foreach my $hmass (sort {$b <=> $a} keys %masses) {
    my @xmasses = @{$masses{$hmass}};
    foreach my $xmass (sort {$b <=> $a} @xmasses) {
	    
	my $pat = "${hmass}_${xmass}";
	next if (!$nominal_lifetimes{$pat});

        print IANFILE "#\n";
        print IANFILE "s = SignalSampleInfo(${hmass}, ${xmass}, ${nominal_lifetimes{$pat}}, $inAcceptance)\n";

        # Write out ctau scale factors.

        print IANFILE "s.setCtauScales ( [";

	my $numCtau = 0;
	foreach my $ctauFact (sort {$a <=> $b} keys %ctaufacts) {
	    if ($numCtau > 0) {print IANFILE ", ";}
            if ($numCtau%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
            $numCtau += 1;
	    printf IANFILE "%7.3f   ", $ctauFact;	
	} # lifetime loop
	print IANFILE "] )\n";

        # Write out signal mass resolution data.

        foreach my $chan ("e", "mu" ) {

            if ($chan eq "e") {
    	        print IANFILE 's.setWidths (      "Electrons", [';
	    } else {
    	        print IANFILE 's.setWidths (          "Muons", [';
            } 

    	    my $numWidth = 0;
	    foreach my $ctauFact (sort {$a <=> $b} keys %ctaufacts) {
    	        if ($numWidth > 0) {print IANFILE ", ";}
                if ($numWidth%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
                $numWidth += 1;
                printf IANFILE "%7.3f   ", $massRes{$chan}{$ctauFact}{$hmass}{$xmass};
            }
	    print IANFILE "] )\n";
        }

        # Write out efficiency data.

        foreach my $channel ("e1", "mu1" ) {

	    my @effvals;
	    my @errvals;
	    my @relerrs;
	    my @negeffvals;
	    foreach my $ctauFact (sort {$a <=> $b} keys %ctaufacts) {
		push @effvals   , $eff   {$channel}{$ctauFact}{$hmass}{$xmass};
		push @negeffvals, $negeff{$channel}{$ctauFact}{$hmass}{$xmass};
		# Inflate uncertainty to include systematics
		my $effisyserr = $signalEffiSys_rel{$channel} * $eff{$channel}{$ctauFact}{$hmass}{$xmass};
		my $toterr = sqrt($efferr{$channel}{$ctauFact}{$hmass}{$xmass} * $efferr{$channel}{$ctauFact}{$hmass}{$xmass} + $effisyserr * $effisyserr);
		push @errvals, $toterr;
		if ($eff{$channel}{$ctauFact}{$hmass}{$xmass} == 0) {
		    push @relerrs, 9999;
		} else {
		    push @relerrs,  ( $toterr / $eff{$channel}{$ctauFact}{$hmass}{$xmass} );
		}
		
	    } # lifetime loop

	    if ($channel eq "e1") {
                # Electron:
		print IANFILE 's.setEffis (             "Electrons", [';
		my $numEffi = 0;
		foreach (@effvals) {
		  if ($numEffi > 0) {print IANFILE ", ";}
		  if ($numEffi%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
		  $numEffi += 1;
		  printf IANFILE "%9.6f ", $_;
		}
		print IANFILE "] )\n";
		print IANFILE 's.setEffiRelErrs (       "Electrons", [';
		$numEffi = 0;
		foreach (@relerrs) {
		  if ($numEffi > 0) {print IANFILE ", ";}
		  if ($numEffi%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
		  $numEffi += 1;
		  printf IANFILE "%9.6f ", $_;
		}
		print IANFILE "] )\n";
		print IANFILE 's.setEffisInControl (    "Electrons", [';
		$numEffi = 0;
		foreach (@negeffvals) {
		  if ($numEffi > 0) {print IANFILE ", ";}
		  if ($numEffi%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
		  $numEffi += 1;
		  printf IANFILE "%9.6f ", $_;
		}
		print IANFILE "] )\n";
	    } else {
                # Muon: 
		print IANFILE 's.setEffis (             "Muons", [';
		my $numEffi = 0;
		foreach (@effvals) {
		  if ($numEffi > 0) {print IANFILE ", ";}
		  if ($numEffi%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
		  $numEffi += 1;
		  printf IANFILE "%9.6f ", $_;
		}
		print IANFILE "] )\n";
		print IANFILE 's.setEffiRelErrs (       "Muons", [';
		$numEffi = 0;
		foreach (@relerrs) {
		  if ($numEffi > 0) {print IANFILE ", ";}
		  if ($numEffi%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
		  $numEffi += 1;
		  printf IANFILE "%9.6f ", $_;
		}
		print IANFILE "] )\n";
		print IANFILE 's.setEffisInControl (    "Muons", [';
		$numEffi = 0;
		foreach (@negeffvals) {
		  if ($numEffi > 0) {print IANFILE ", ";}
		  if ($numEffi%8 == 0) {print IANFILE "\n";} # break lines every eight entries to help legibility.
		  $numEffi += 1;
		  printf IANFILE "%9.6f ", $_;
		}
		print IANFILE "] )\n";
            } 

	} # lepton loop
	print IANFILE "samples.append(s)\n"
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
	foreach my $ctauFact (sort {$a <=> $b} keys %ctaufacts) {
	    $count = ${count} + 1;
	    # Only put some lifetimes into table, so not too long.
	    if (${ctauFact} eq 0.1 or ${ctauFact} eq 1 or ${ctauFact} eq 10) {
		if (${first} eq 1) {
		    $first = 0;
		    my $xmass = ${xmass} + 0; # Remove leading zeros
		    printf " %6i      &  %6i     &   ", ${hmass} , ${xmass} ;
		} else { 
		    print "             &             &   ";
		}

		my $life = $ctauFact * $nominal_lifetimes{$pat};

		my $n = 3 - int(log(${life})/log(10.));
		for (my $i = 0; $i < $n; $i++) {print "~"}
		printf '%.1f', ${life};
		
		# lepton loop
		foreach my $channel ("e1", "e2", "mu1", "mu2") {
		    if ($eff{$channel}{$ctauFact}{$hmass}{$xmass} > 0.1) {
			printf '   & %.2f~', $eff{$channel}{$ctauFact}{$hmass}{$xmass};
		    } else {
			printf '   & %.3f', $eff{$channel}{$ctauFact}{$hmass}{$xmass};
		    }
#		    print " \pm $efferr{$channel}{$ctauFact}{$hmass}{$xmass}";

		} 
		print "  \\\\ \n"
	    }

	} 
    } 
}
