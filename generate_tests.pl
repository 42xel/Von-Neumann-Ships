# TODO: argv is only name of the thing to test, input is outline, output is generated test.
#!/usr/bin/perl
use strict;
use warnings;

# Check if correct number of arguments are provided
    if (@ARGV < 1) {
die "Usage: $0 <module_file>\nActual Usage: don't. This script is used for automation purposes only.\n";
}
    my ($module_file) = @ARGV;
    # Print the initial part of the test file
print qq/#include "$module_file"\n#include <stdio.h>\n\nfn result main () {\nresult r;\nreturn\n/;
        # Process each line of the outline file
        while (my $line = <STDIN>) {
    if ($line =~ /^fn\s+result\s+test_([a-zA-Z0-9_]+)/) {
print qq/(printf("$1: "), r = test_$1()) ? printf("KO: %d\\n", r), r : printf("ok\\n"), \n/; }}
    # Print the final part of the test file
print "0; }\n";

exit 0;

