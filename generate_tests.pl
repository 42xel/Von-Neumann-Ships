#!/usr/bin/perl
use strict;
use warnings;

# Check if correct number of arguments are provided
    if (@ARGV < 2) {
die "Usage: $0 <module_file> <test_file>\nActual Usage: don't. This script is used for automation purposes only.\n";
}
    my ($module_file, $test_file) = @ARGV;
open my $module_fh, '<', $module_file or die "Cannot open $module_file: $!";
open my $test_fh, '>', $test_file or die "Cannot open $test_file: $!";
    # Print the initial part of the test file
print $test_fh "#include \"$module_file\"\n#include <stdio.h>\n\nfn result main () {\nresult r;\nreturn\n";
        # Process each line of the module file
        while (my $line = <$module_fh>) {
    if ($line =~ /^\s*fn\s+result\s+test_([a-zA-Z0-9_]+).*/) {
print $test_fh "(r = printf(\"$1\\n\"), test_$1()) ? r :\n"; }}
    # Print the final part of the test file
print $test_fh "0; }\n";
# Close the filehandles
close $module_fh;
close $test_fh;

exit 0;

