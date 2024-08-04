use warnings;
use strict;

my ($src) = @ARGV;
(my $obj = $src) =~ s"^unit_tests/src(.*)\.c$"obj$1.o"; #"# my linter is in shambles
while(my $line = <STDIN>) {
    $line =~ s/$obj/$src/;
    print "$line" ;
}

