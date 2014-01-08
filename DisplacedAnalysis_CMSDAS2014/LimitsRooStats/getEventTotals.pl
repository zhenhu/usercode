#!/usr/bin/perl -w

# A simple script to sum up the number of events (and their
# uncertainties) in a text file. Can be used for either data
# or background MC.

use strict;

my $filename = shift || die "Usage: $0 infile\n";
open INFILE, $filename or die "Couldn't open $filename: $!\n";

my $totev = 0;
my $toterr2 = 0;
my $peak5ev = 0;
my $peak15ev = 0;
my $outsideev = 0;

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

	if ($mass > 87.5 && $mass < 92.5) { $peak5ev += $weight; }
	if ($mass > 82.5 && $mass < 97.5) { $peak15ev += $weight; }
	else { $outsideev += $weight; }
	
    }
}

my $toterr = sqrt($toterr2);
print sprintf("Total: %.3f +/- %.3f\n", $totev, $toterr);
print sprintf("Within 5 GeV of Z peak: %.3f\n", $peak5ev);
print sprintf("Within 15 GeV of Z peak: %.3f\n", $peak15ev);
print sprintf("Outside 15 GeV of Z peak: %.3f\n", $outsideev);
