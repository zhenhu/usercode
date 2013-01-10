#!/usr/bin/perl -w

# A simple script to sum up the number of events (and their
# uncertainties) in a text file. Can be used for either data
# or background MC.

use strict;

my $filename      = shift || die "Usage: $0 infileNormalCuts inFileLooseCuts\n";
my $filenameloose = shift || die "Usage: $0 infileNormalCuts inFileLooseCuts\n";
open INFILE,      $filename      or die "Couldn't open $filename: $!\n";
open INFILEloose, $filenameloose or die "Couldn't open $filenameloose: $!\n";

# Loop over candidates with loose cuts.
my $totevloose = 0;
my $toterr2loose = 0;
my $largestweightloose = 0;

while (my $line = <INFILEloose>) {
    chomp $line;

    my @fields = split(" ", $line);

    # Old files have two columns: mass, weight
    # while newer files have three: mass, Lxy/sigma, weight
    my $mass = $fields[0];
    my $weight = $fields[-1];

    if ($mass > 15.0) {
	$totevloose += $weight;
	$toterr2loose += $weight*$weight;
        if ($largestweightloose < $weight) {
	    $largestweightloose = $weight;
        }
    }
}

# loop over candidates with normal cuts
my $totev = 0;
my $toterr2 = 0;
my $largestweight = 0;

while (my $line = <INFILE>) {
    chomp $line;

    my @fields = split(" ", $line);

    # Old files have two columns: mass, weight
    # while newer files have three: mass, Lxy/sigma, weight
    my $mass = $fields[0];
    my $weight = $fields[-1];

    if ($mass > 15.0) {
	$totev += $weight;
	$toterr2 += $weight*$weight;
        if ($largestweight < $weight) {
	    $largestweight = $weight;
        }
    }
}

my $effi = $totev/$totevloose;
my $toterrloose = sqrt($toterr2loose);
# naive estimate of uncertainty on events passing normal cuts.
my $toterr = sqrt($toterr2);
# more precise estimate, with +ve and -ve errors.
my $central = ($totev + $toterr2loose/(2*$totevloose));
my $sigma   = sqrt(($toterr2loose/$totevloose)*($totev + $toterr2loose/(4*$totevloose)));
my $uperr   = ($central + $sigma) - $totev;
my $downerr = $totev - ($central - $sigma);
print sprintf("\n === Results ===\n");
print sprintf("Candidates passing loose cuts = %.3f +- %.3f\n",$totevloose,$toterrloose);
print sprintf("Candidates passing normal cuts = %.3f\n",$totev);
print sprintf("    with +ve and -ve uncertainties: + %.3f - %.3f\n",$uperr,$downerr);
print sprintf("    or naive error estimate %.3f\n",$toterr);
print sprintf("Efficiency of normal cuts relative to loose ones = %.5f (ideally should be << 1)\n",$effi);

# To determine stability of uncertainty calculation, repeat calculation after killing the candidate with the 
# biggest weight (since a statistical fluctuation could easily remove this one event).
# If results change significantly, then they are not statistically precise.
print sprintf("\n === Checking stability of results ===\n");
print sprintf("Largest event weight in loose sample = %.3f and in normal sample = %.3f\n",$largestweightloose,$largestweight);
$totevloose   = $totevloose   - $largestweightloose;
$toterr2loose = $toterr2loose - $largestweightloose * $largestweightloose;
$totev        = $totev        - $largestweight;
$toterr2      = $toterr2      - $largestweight * $largestweight;
print sprintf("%.3f %.3f\n",$totev,$totevloose);
$central = ($totev + $toterr2loose/(2*$totevloose));
$sigma   = sqrt(($toterr2loose/$totevloose)*($totev + $toterr2loose/(4*$totevloose)));
$uperr   = ($central + $sigma) - $totev;
$downerr = $totev - ($central - $sigma);
print sprintf("If candidate with largest weight is removed, +ve and -ve uncertainties become: + %.3f - %.3f\n",$uperr,$downerr);
print sprintf("(If these differ significantly from those above, then the uncertainties are statistically imprecise)\n");
