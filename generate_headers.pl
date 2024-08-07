use strict;
use warnings;
# Usage:
# perl generate_headers.pl <define>
# input: outline file from which to generate the header
# output: the header file

my $keep = qr<
^pub|
^///|
^/\*\*|
^\#\s*include\b
>x;

(my ($define) = @ARGV); $define =~ s"/"_s_"g; #"#
print "#ifndef $define"."_h\n";
print "#define $define"."_h\n";
            while (my $line = <STDIN>) {
        if ($line =~ $keep) {
$line =~ s/\t/\n/g;
print $line; } }
print "#endif\n";
