# Usage:
# perl outline.pl
# stdin: the file to outline
# stdout: the outline file

# TODO: rewrite sing prrsing grammars, fr example lua and LPEG
# TODO : test multiline dquotes.

use strict;
use warnings;
use re 'strict';

my $dquote = qr/"(?:[^"\\]++|\\.)*+"/;

my $line_comment = qr"//\N*+\n?";
my $multine_comment = qr"/\* #(?!\*)
(?:
    [^*]++
    |
    \*[^/]
)*
\*/
"xs;

my $balanced_parens = qr/
(?<balanced_parens>
    \(
    (?:
        $dquote
        |
        # (?0)
        (?-1)
        # (?<balanced_parens>)?
        |
        [^)]
    )*+
    \)
)
/xs;

my $balanced_brackets = qr/
(?<balanced_brackets>
    \{
    (?:
        $dquote
        |
        # (?0)
        (?-1)   #never trust anyone
        # (?<balanced_brackets>)?
        |
        [^}]
    )*+
    \}
)
/xs;

# my $preprocessor = qr/#\N*(?{ print "$&\n"; })/;
my $preprocessor = qr/^\#\s*
(
    include\b\N*+(?{ print "$&\n"; })
    |
    \N*+
)
/mx;

my $rhs = qr/
 (
  [^({";]++|
  $balanced_parens|
  $dquote|
  $balanced_brackets
 )*+
 ;
/xns;

my $item = qr<
(?:
[^=({;])++
(
(?{return $& ;})=$rhs
	(?{(my $v = "$^R ;") =~ s/\n/\t/g; print "$v\n" ;})
|$balanced_parens
    (?{return $& ;})
    [^{]*+$balanced_brackets
    (?{(my $v = "$^R ;") =~ s/\n/\t/g; print "$v\n" ;})
|;
	(?{(my $v = "$&") =~ s/\n/\t/g; print "$v\n" ;})
)
>xns;

my $typedef = qr<typedef\s+$rhs
(?{(my $v = "$&") =~ s/\n/\t/g; print "$v\n";})>xns;

my $toplevel_item = qr<
# dedup mutiple line breaks in a row.
(\s*)(?{
      my $v = $&;
      for (1..2) { if (!($v =~ m"\n"gs)) {return;}}
      print "\n";
})
(
|$preprocessor
|$line_comment     (?{ if ((my $v = $&) =~ '///'){ print "$v"; } })
|$multine_comment  (?{ if ((my $v = $&) =~ '/\*\*'){ $v =~ s/\n/\t/g; print "$v\n"; } })
|$typedef
|$item
)
>xms;

$_ = "";
while(my $l = <>) {
$_ .= $l;
}

while(/($toplevel_item)/gs) {}
# TODO : post-process to avoid a bunch of of empty new lines
# in place of preprocessor instructions and comments

