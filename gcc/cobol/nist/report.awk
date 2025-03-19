#! /usr/bin/awk -f

{
  sub(/^[[:blank:]]+/, "")
  sub(/[[:space:]]+$/, "")
  names[FILENAME]++
}

/TESTS WERE EXECUTED SUCCESSFULLY/ {
  results[FILENAME,1] = $1
  results[FILENAME,2] = $3
  if( $1 != $3 ) {
    print FILENAME ":\t" $0
  }
}

/TEST[(]S[)] FAILED/ {
  results[FILENAME,3] = 0 + $1
  if( 0 + $1 > 0 ) {
    print "\tfailed: \t" 0 + $1
  }
}

/TEST[(]S[)] DELETED/ {
  results[FILENAME,4] = 0 + $1
  if( 0 + $1 > 0 ) {
    print "\tdeleted:\t" 0 + $1
  }
}

/TEST[(]S[)] REQUIRE INSPECTION/ {
  results[FILENAME,5] = 0 + $1
  if( 0 + $1 > 0 ) {
    print "\tinspect:\t" 0 + $1
  }
}

END {
  for( name in names ) {
    numerator   += results[name,1]
    denominator += results[name,2]
    failed  += results[name,3]
    deleted += results[name,4]
    inspect += results[name,5]
  }

  printf "%3.2f%% of %d tests succeeded for %d test modules\n", \
    100 * (numerator / denominator), denominator, length(names)

  if( failed || deleted || inspect ) {
    printf "%d failed, %d deleted, %d need inspection\n", failed, deleted, inspect
    exit( failed > 0 )
  }
  exit( numerator == denominator? 0 : 1 )

}
