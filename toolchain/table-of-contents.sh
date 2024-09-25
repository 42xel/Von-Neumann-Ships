#!/bin/sh
# A cute little kakoune snippet script to genenerate a table of contents from a markdown file.
# Input is the markdown file, output is the table of content.

# is there a flex possible using git ?
        if test -z "$repo" ; then
repo='https://github.com/42xel/Von-Neumann-Ships'
fi

kak -n -f 's^#{1,3}(?= )<ret>xy%<a-d><a-P>s<ret>r<tab>;r*llGl_yi[<esc>a]('$repo$page'#)<esc>;P`s <ret>r-'

