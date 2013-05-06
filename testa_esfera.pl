#!/usr/bin/perl

use strict;
use warnings;

while(<>)
{
    (my $n1, my $n2) = split(" ");
    print "OK" if($n1**2 + $n2**2 == 1);
}
