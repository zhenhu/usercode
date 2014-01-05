#!/usr/bin/perl -w

use strict;

my %samples = (
	       "2B2Mu_MH_1000_MFF_150_CTau100_8TeV" => 1,
	       "2B2Mu_MH_1000_MFF_20_CTau15_8TeV" => 1,
	       "2B2Mu_MH_1000_MFF_350_CTau350_8TeV" => 1,
	       "2B2Mu_MH_1000_MFF_400_CTau2_8TeV" => 10,
	       "2B2Mu_MH_120_MFF_50_CTau500_8TeV" => 1,
	       "2B2Mu_MH_200_MFF_50_CTau200_8TeV" => 10,
	       "2B2Mu_MH_300_MFF_125_CTau100_8TeV" => 1,
	       "2B2Mu_MH_400_MFF_20_CTau40_8TeV" => 1,
	       "2B2Mu_MH_400_MFF_50_CTau80_8TeV" => 1,
	       "4B_MH_1000_MFF_150_CTau100_8TeV" => 1,
	       "4B_MH_1000_MFF_20_CTau15_8TeV" => 1,
	       "4B_MH_1000_MFF_350_CTau350_8TeV" => 1,
	       "4B_MH_1000_MFF_400_CTau2_8TeV" => 10,
	       "4B_MH_120_MFF_50_CTau500_8TeV" => 1,
	       "4B_MH_200_MFF_50_CTau200_8TeV" => 10,
	       "4B_MH_300_MFF_125_CTau100_8TeV" => 1,
	       "4B_MH_400_MFF_20_CTau40_8TeV" => 1,
	       "4B_MH_400_MFF_50_CTau80_8TeV" => 1,

	       "2B2Mu_MH_1000_MFF_20_CTau15_8TeV" => 1,
	       "4B_MH_1000_MFF_20_CTau15_8TeV" => 1,
	       "4B_MH_1000_MFF_150_CTau100_8TeV" => 1,
	       "2B2Mu_MH_1000_MFF_150_CTau100_8TeV" => 1,
	       "4B_MH_400_MFF_20_CTau40_8TeV" => 1,
	       "2B2Mu_MH_400_MFF_20_CTau40_8TeV" => 1,
	       );

foreach my $sample (keys %samples) {
    system("./qsub_MakePatTuple_mc.sh $sample 1 $samples{$sample}");
}
