#! /usr/bin/awk -f

#
# Copy needed tokens from parse.h for use in cdf.y.  Using the same
# token values in both the main parser and the CDF parser lets them
# share one lexer.
#
# This file is not used during a build.  It's used only during
# development, when new tokens are added.
#
# Syntax: cdftok.awk parse.h cdf.y
#
# The new file is written to standard output.
#

BEGIN {
  FS = "[[:blank:],]+"
}

{
  finding_tokens = FILENAME ~ /parse.h/;
}

# The set of tokens could be contructed intelligently or statically,
# but that's not necessary.  This pattern finds more than it needs,
# including some nontokens, but it's fast and only the names that
# match later are used.
finding_tokens && /^ +[[:alnum:]_]+ =/ {
  gsub(/^ +/, "")
  value = $3
  if( match($0, /".+"/) ) {
    alias = substr($0, RSTART, RLENGTH)
    value = value "    " alias
  }
  tokens[$1] = value
  #rint "found:", $1, tokens[$1] > "/dev/stderr"
}

finding_tokens { next }

/%(token|left|right)/ {
  sub(/ +$/, "")
  sub(/["].+/, "") # delete any string value (must be only one on the line)
  for( i=2; i <= NF; i++ ) {
    #rint $i, "becomes", $i " " tokens[$i] >> "/dev/stderr"
    $i = $i " " tokens[$i]  # assign value from parse.h to token
    # delete next field if it holds the token's prior value
    if( i < NF && $(i+1) ~ /^[0-9]+$/ ) {
      i++
      $i = ""
    }
  }
  sub(/ +$/, "")
}

{ print }
