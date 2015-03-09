#!/bin/perl

use strict;
use warnings;

sub usage() {
	print "randomMatrix columnsCount rowsCount\n";
	exit();
}
my ($cols,$rows) = @ARGV;

usage() unless(defined($cols) and defined($rows));
$cols = int($cols);
$rows = int($rows);

for(my $i=0;$i<$rows;$i++) {
    my @line;
    for(my $j=0;$j<$cols;$j++) {
        push(@line,rand(100));
    }
    print join("\t",@line)."\n";
}
