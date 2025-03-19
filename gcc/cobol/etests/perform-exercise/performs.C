#include <algorithm>
#include <stack>
#include <iostream>

#include <err.h>

using std::cout;

enum paragraph_t {
                  no_paragraph,
                  BeginProgram, EndProgram,
                  ANOTHER_SECTION,
                  BUMP_COUNTER,
                  //// DUPLICATED would be invalid as target
                  NOBUMP_COUNTER,
                  PARAGRAPH_AAA,
                  PARAGRAPH_AAA2,
                  PARAGRAPH_BBB,
                  PARAGRAPH_BBB2,
                  PARAGRAPH_CCC,
                  PARAGRAPH_CCC2,
                  PARAGRAPH_DDD,
                  PARAGRAPH_DDD2,
                  SEC1,
                  SEC1_AAA,
                  SEC2,
                  SEC2_AAA,
                  TEST_EXIT_PARAGRAPH,
};

struct return_stack_t : public std::stack<paragraph_t> {
  bool find( const paragraph_t& that ) {
    auto p = std::find(c.begin(), c.end(), that);
    return p != c.end();
  }
} return_stack;

static bool
leave( paragraph_t self ) {
  if( ! return_stack.find(self) ) return false;
  while( self != return_stack.top() ) return_stack.pop();
  return true;
}

static void progfunc( paragraph_t from, paragraph_t to );

static void
perform( size_t n,
         paragraph_t from,
         paragraph_t until = no_paragraph )
{
  for( size_t i=0; i < n; i++ ) {
    progfunc( from, until );
  }
}

class ge_t {
  unsigned char *value, end_value;;
public:
  bool before;

  ge_t(unsigned char *value, unsigned char end_value, bool before = false)
    : value(value), end_value(end_value), before(before) {}
  operator bool() const { return *value < end_value; }
};

static void
perform( ge_t cmp,
         paragraph_t from,
         paragraph_t until = no_paragraph )
{
  if( cmp.before ) {
    while( cmp ) progfunc( from, until );
  } else {
    do { progfunc( from, until ); } while( cmp );
  }
}

static const char SPACE[] = " ";

static inline void
DISPLAY( const char msg[]) { cout << msg << std::endl; }

/*
 * COBOL as big C switch
 */

// IDENTIFICATION DIVISION.
// PROGRAM-ID. performs.
//
// *> This routine exercises inline and outofline
// *>
// *>  PERFORM
// *>  PERFORM UNTIL
// *>  PERFORM VARYING
// *>
// *> with both TEST BEFORE and TEST AFTER

// DATA DIVISION.
// WORKING-STORAGE SECTION.
// 01  counter   PIC 9.
// 01  five     PIC 9 VALUE 5.
//

unsigned char counter, five = 5;
unsigned char& COUNTER = counter;

// PROCEDURE DIVISION.
static void
progfunc( paragraph_t from, paragraph_t to )
{
  return_stack.push(to == no_paragraph? from : to);

  switch( from ) {
  case no_paragraph:
// BeginProgram.
  case BeginProgram:
//  DISPLAY "Perform paragraph-AAA once"
    DISPLAY("Perform paragraph-AAA once");
//  PERFORM PARAGRAPH-AAA
    perform(1, PARAGRAPH_AAA );

//  DISPLAY "Perform paragraph-AAA 3 times"
    DISPLAY("Perform paragraph-AAA 3 times");
//  PERFORM PARAGRAPH-AAA 3 TIMES
    perform(3, PARAGRAPH_AAA);

//  DISPLAY "Perform paragraph-BBB THROUGH paragraph-CCC once"
    DISPLAY("Perform paragraph-BBB THROUGH paragraph-CCC once");
//  PERFORM PARAGRAPH-BBB THROUGH PARAGRAPH-CCC
    perform(1, PARAGRAPH_BBB, PARAGRAPH_CCC);

//  DISPLAY "Perform paragraph-BBB THROUGH paragraph-CCC 3 TIMES"
    DISPLAY("Perform paragraph-BBB THROUGH paragraph-CCC 3 TIMES");
//  PERFORM PARAGRAPH-BBB THROUGH PARAGRAPH-CCC 3 TIMES
    perform(3, PARAGRAPH_BBB, PARAGRAPH_CCC);

//  DISPLAY "Trying (counter=0) PERFORM BUMP-COUNTER UNTIL counter >= 5"
    DISPLAY("Trying (counter=0) PERFORM BUMP-COUNTER UNTIL counter >= 5");
//  MOVE 0 to counter.
    counter = 0;
//  PERFORM BUMP-COUNTER UNTIL counter >= 5
    perform(ge_t(&counter, 5, true),  BUMP_COUNTER);
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=0) PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5"
    DISPLAY("Trying (counter=0) PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5");
//  MOVE 0 to counter.
    counter = 0;
//  PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5
    perform(ge_t(&counter, 5, true),  BUMP_COUNTER);
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=0) PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5"
    DISPLAY("Trying (counter=0) PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5");
//  MOVE 0 to counter.
    counter = 0;
//  PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5
    perform( ge_t(&counter, 5, true), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=5) PERFORM BUMP-COUNTER UNTIL counter >= 5"
    DISPLAY("Trying (counter=5) PERFORM BUMP-COUNTER UNTIL counter >= 5");
//  MOVE 5 to counter.
    counter = 5;
//  PERFORM BUMP-COUNTER UNTIL counter >= 5
    perform( ge_t(&counter, 5, true), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=5) PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5"
    DISPLAY("Trying (counter=5) PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5");
//  MOVE 5 to counter.
    counter = 5;
//  PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5
    perform( ge_t(&counter, 5, true), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=5) PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5"
    DISPLAY("Trying (counter=5) PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5");
//  MOVE 5 to counter.
    counter = 5;
//  PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5
    perform( ge_t(&counter, 5, true), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "PERFORM proc (testing after, start at 0) UNTIL"
//  DISPLAY "Trying (counter=0) PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5"
    DISPLAY("PERFORM proc (testing after, start at 0) UNTIL");
    DISPLAY("Trying (counter=0) PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5");
//  MOVE 0 to counter.
    counter = 0;
//  PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5
    perform( ge_t(&counter, 5, false), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

    DISPLAY("Trying (counter=0) PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5");
//  MOVE 0 to counter.
    counter = 0;
//  PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5
    perform( ge_t(&counter, 5, false), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=5) PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5"
    DISPLAY("Trying (counter=5) PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5");
//  MOVE 5 to counter.
    counter = 5;
//  PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5
    perform( ge_t(&counter, 5, false), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (counter=5) PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5"
    DISPLAY("Trying (counter=5) PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5");
//  MOVE 5 to counter.
    counter = 5;
//  PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5
    perform( ge_t(&counter, 5, false), BUMP_COUNTER );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM PARAGRAPH-AAA VARYING counter FROM 0 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM PARAGRAPH-AAA VARYING counter FROM 0 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA VARYING counter FROM 0 BY 1 UNTIL counter >= 3
    for( counter=0; counter < 3; counter++ ) {
      perform(1, PARAGRAPH_AAA);
    }

//  DISPLAY "Trying PERFORM paragraph-AAA TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3
    for( counter=0; counter < 3; counter++ ) {
      perform(1, PARAGRAPH_AAA);
    }

//  DISPLAY "Trying PERFORM paragraph-AAA WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3
    for( counter=0; counter < 3; counter++ ) {
      perform(1, PARAGRAPH_AAA);
    }

//  DISPLAY "Trying PERFORM PARAGRAPH-AAA VARYING counter FROM 5 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM PARAGRAPH-AAA VARYING counter FROM 5 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA VARYING counter FROM 5 BY 1 UNTIL counter >= 3
    for( counter=5; counter < 3; counter++ ) {
      perform(1, PARAGRAPH_AAA);
    }

//  DISPLAY "Trying PERFORM paragraph-AAA TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3
    for( counter=5; counter < 3; counter++ ) {
      perform(1, PARAGRAPH_AAA);
    }

//  DISPLAY "Trying PERFORM paragraph-AAA WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3
    for( counter=5; counter < 3; counter++ ) {
      perform(1, PARAGRAPH_AAA);
    }

//  DISPLAY "Trying PERFORM paragraph-AAA TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3
    counter=0;
    do { perform(1, PARAGRAPH_AAA); } while ( counter++ < 3 );

//  DISPLAY "Trying PERFORM paragraph-AAA WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3
    counter=0;
    do { perform(1, PARAGRAPH_AAA); } while ( counter++ < 3 );

//  DISPLAY "Trying PERFORM paragraph-AAA TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3
    counter=5;
    do { perform(1, PARAGRAPH_AAA); } while ( counter++ < 3 );

//  DISPLAY "Trying PERFORM paragraph-AAA WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3"
    DISPLAY("Trying PERFORM paragraph-AAA WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3");
//  PERFORM PARAGRAPH-AAA WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3
    counter=5;
    do { perform(1, PARAGRAPH_AAA); } while ( counter++ < 3 );

//  DISPLAY "Trying (count = 0) PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 0) PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 0 TO counter
    counter=0;
//  PERFORM UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    for( counter=0; counter < 5; counter++ ) {
      cout << (int)counter <<  " " << std::flush;
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (count = 0) TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 0) TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 0 TO counter
    counter=0;
//  PERFORM TEST BEFORE UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    while ( counter < 5 ) {
      cout << (int)counter <<  " " << std::flush;
      counter++;
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (count = 0) WITH TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 0) WITH TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 0 TO counter
    counter = 0;
//  PERFORM WITH TEST BEFORE UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    while ( counter < 5 ) {
      cout << (int)counter <<  " " << std::flush;
      counter++;
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (count = 5) PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 5) PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 5 TO counter
    counter = 5;
//  PERFORM UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    while ( counter < 5 ) {
      cout << (int)counter <<  " " << std::flush;
      counter++;
    }

//  DISPLAY "Trying (count = 5) TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 5) TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 5 TO counter
    counter = 5;
//  PERFORM TEST BEFORE UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    while ( counter < 5 ) {
      cout << (int)counter <<  " " << std::flush;
      counter++;
    }

//  DISPLAY "Trying (count = 5) WITH TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 5) WITH TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 5 TO counter
    counter = 5;
//  PERFORM WITH TEST BEFORE UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    while ( counter < 5 ) {
      cout << (int)counter <<  " " << std::flush;
      counter++;
    }

//  DISPLAY "Trying (count = 0) TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 0) TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 0 TO counter
    counter = 0;
//  PERFORM TEST AFTER UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    do {
      cout << (int)counter++ <<  " " << std::flush;
    } while ( counter < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (count = 0) WITH TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 0) WITH TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 0 TO counter
    counter = 0;
//  PERFORM WITH TEST AFTER UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    do {
      cout << (int)counter++ <<  " ";
    } while ( counter < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (count = 5) TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 5) TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 5 TO counter
    counter = 5;
//  PERFORM TEST AFTER UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    do {
      cout << (int)counter++ <<  " ";
    } while ( counter < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying (count = 5) WITH TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5"
    DISPLAY("Trying (count = 5) WITH TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5");
//  MOVE 5 TO counter
    counter = 5;
//  PERFORM WITH TEST AFTER UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 TO COUNTER
//      END-PERFORM
    do {
      cout << (int)counter++ <<  " ";
    } while ( counter < 5 );
//  DISPLAY " "
    DISPLAY(" ");


    static const int five = 5;

//  DISPLAY "Trying PERFORM BUMP-COUNTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER VARYING counter FROM 0 BY 1 UNTIL counter >= five
    for( counter=0; counter < five; counter++ ) {
      perform(1, BUMP_COUNTER);
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= five
    for( counter=0; counter < five; counter++ ) {
      perform(1, BUMP_COUNTER);
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= five
    for( counter=0; counter < five; counter++ ) {
      perform(1, BUMP_COUNTER);
    }

//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM BUMP-COUNTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER VARYING counter FROM 5 BY 1 UNTIL counter >= five
    for( counter=5; counter < five; counter++ ) {
      perform(1, BUMP_COUNTER);
    }

//  DISPLAY "Trying PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= five
    for( counter=5; counter < five; counter++ ) {
      perform(1, BUMP_COUNTER);
    }

//  DISPLAY "Trying PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= five
    for( counter=5; counter < five; counter++ ) {
      perform(1, BUMP_COUNTER);
    }

//  DISPLAY "Trying PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= five
    counter = 0;
    do {
      perform(1, BUMP_COUNTER);
    } while ( ++counter < five );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= five
    counter = 0;
    do {
      perform(1, BUMP_COUNTER);
    } while ( ++counter < five );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= five
    counter = 5;
    do {
      perform(1, BUMP_COUNTER);
    } while ( ++counter < five );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= five
    counter = 5;
    do {
      perform(1, BUMP_COUNTER);
    } while ( ++counter < five );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM VARYING counter FROM 0 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    counter = 0;
    do {
      cout << (int)counter++ <<  " ";
    } while ( counter < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    for( counter=0; counter < 5; counter++ ) {
      cout << (int)counter << " ";
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    for( counter=0; counter < 5; counter++ ) {
      cout << (int)counter << " ";
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM VARYING counter FROM 5 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    for( counter=5; counter < 5; counter++ ) {
      cout << (int)counter << " ";
    }

//  DISPLAY "Trying PERFORM TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    for( counter=5; counter < 5; counter++ ) {
      cout << (int)counter << " ";
    }

//  DISPLAY "Trying PERFORM WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    for( counter=5; counter < 5; counter++ ) {
      cout << (int)counter << " ";
    }

//  DISPLAY "Trying PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    counter = 0;
    do {
      cout << (int)counter <<  " ";
    } while ( counter++ < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5");
//  PERFORM WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    counter = 0;
    do {
      cout << (int)counter <<  " ";
    } while ( counter++ < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    counter = 5;
    do {
      cout << (int)counter <<  " ";
    } while ( counter++ < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5"
    DISPLAY("Trying PERFORM WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5");
//  PERFORM WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      END-PERFORM
    counter = 5;
    do {
      cout << (int)counter <<  " ";
      if( counter < 5 ) counter++;
    } while ( counter < 5 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Trying PERFORM 5 TIMES"
    DISPLAY("Trying PERFORM 5 TIMES");
//  PERFORM 5 TIMES
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      ADD 1 to COUNTER
//      END-PERFORM
    for( int i=0; i < 5; i++ ) {
      cout << (int)counter++ << " ";
    }
//  DISPLAY SPACE
    DISPLAY(SPACE);

//  DISPLAY "PERFORM 10 TIMES; Skip 4, end at 7"
    DISPLAY("PERFORM 10 TIMES; Skip 4, end at 7");
//  MOVE 0 to COUNTER
    counter = 0;
//  PERFORM 10 TIMES
//      ADD 1 to COUNTER
//      IF COUNTER EQUAL 4
//          EXIT PERFORM CYCLE
//          END-IF
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      IF COUNTER EQUAL 7
//          EXIT PERFORM
//          END-IF
//      END-PERFORM
    for( int i=0; i < 10; i++ ) {
      counter++;
      if( counter == 4 ) continue;
      cout << (int)counter << " ";
      if( counter == 7 ) break;
    }
//  DISPLAY SPACE
    DISPLAY(SPACE);

//  DISPLAY "PERFORM TEST AFTER VARYING; skip 4, end at 7"
    DISPLAY("PERFORM TEST AFTER VARYING; skip 4, end at 7");
//  PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 10
//      IF COUNTER EQUAL 4
//          EXIT PERFORM CYCLE
//          END-IF
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      IF COUNTER EQUAL 7
//          EXIT PERFORM
//          END-IF
//      END-PERFORM
    counter = 0;
    do {
      if( counter == 4 ) continue;
      cout << (int)counter << " ";
      if( counter == 7 ) break;
    } while( ++counter < 10 );
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "PERFORM WITH TEST BEFORE VARYING; skip 4, end at 7"
    DISPLAY("PERFORM WITH TEST BEFORE VARYING; skip 4, end at 7");
//  PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 10
//      IF COUNTER EQUAL 4
//          EXIT PERFORM CYCLE
//          END-IF
//      DISPLAY COUNTER " " WITH NO ADVANCING
//      IF COUNTER EQUAL 7
//          EXIT PERFORM
//          END-IF
//      END-PERFORM
    for( counter=0; counter < 10; counter++ ) {
      if( counter == 4 ) continue;
      cout << (int)counter << " ";
      if( counter == 7 ) break;
    }
//  DISPLAY " "
    DISPLAY(" ");

//  DISPLAY "Testing EXIT PARAGRAPH..."
    DISPLAY("Testing EXIT PARAGRAPH...");
//  PERFORM TEST-EXIT-PARAGRAPH.
    perform(1, TEST_EXIT_PARAGRAPH);

//  DISPLAY "Testing EXIT SECTION..."
    DISPLAY("Testing EXIT SECTION...");
//  PERFORM ANOTHER-SECTION.
    perform(1, ANOTHER_SECTION);
//  DISPLAY SPACE
    DISPLAY(SPACE);

//  PERFORM AAA OF SEC2
    perform(1, SEC2_AAA);
//  DISPLAY "Should have been 'AAA of SEC2'"
    DISPLAY("Should have been 'AAA of SEC2'");
//  PERFORM AAA OF SEC1
    perform(1, SEC1_AAA);
//  DISPLAY "Should have been 'AAA of SEC1'"
    DISPLAY("Should have been 'AAA of SEC1'");

//  DISPLAY "Duplicated pass-through 1".
    DISPLAY("Duplicated pass-through 1");
    //// if( leave(BeginProgram) ) return; // end 1st paragraph

//  DUPLICATED.
//  DISPLAY "Duplicated pass-through 2".
    DISPLAY("Duplicated pass-through 2");
//  DUPLICATED.
//  DISPLAY "Duplicated pass-through 3".
    DISPLAY("Duplicated pass-through 3");

//  STOP RUN.
    exit(0);

// PARAGRAPH-AAA.
  case PARAGRAPH_AAA:
//  DISPLAY "      I am paragraph_AAA".
    DISPLAY("      I am paragraph_AAA");
    if( leave(PARAGRAPH_AAA) ) return;

// PARAGRAPH-BBB.
  case PARAGRAPH_BBB:
//  DISPLAY "      I am paragraph_BBB".
    DISPLAY("      I am paragraph_BBB");
    if( leave(PARAGRAPH_BBB) ) return;

// PARAGRAPH-CCC.
  case PARAGRAPH_CCC:
//  DISPLAY "      I am paragraph_CCC".
    DISPLAY("      I am paragraph_CCC");
    if( leave(PARAGRAPH_CCC) ) return;

// PARAGRAPH-DDD.
  case PARAGRAPH_DDD:
//  DISPLAY "      I am paragraph_DDD".
    DISPLAY("      I am paragraph_DDD");
    if( leave(PARAGRAPH_DDD) ) return;

// BUMP-COUNTER.
  case BUMP_COUNTER:
//  DISPLAY COUNTER " " WITH NO ADVANCING
    cout << (int)COUNTER <<  " " << std::flush;
//  ADD 1 TO counter.
    counter++;
    if( leave(BUMP_COUNTER) ) return;

// NOBUMP-COUNTER.
  case NOBUMP_COUNTER:
//  DISPLAY COUNTER " " WITH NO ADVANCING.
    cout << (int)COUNTER <<  " ";
    if( leave(NOBUMP_COUNTER) ) return;

// TEST-EXIT-PARAGRAPH.
  case TEST_EXIT_PARAGRAPH:
//  DISPLAY "Now you see me..."
    DISPLAY("Now you see me...");
//  EXIT PARAGRAPH
    if( ! return_stack.empty() ) return;
//  DISPLAY "And now you shouldn't".
    DISPLAY("And now you shouldn't");
    if( leave(TEST_EXIT_PARAGRAPH) ) return;

// ANOTHER-SECTION SECTION.
  case ANOTHER_SECTION:
// PARAGRAPH-AAA2.
  case PARAGRAPH_AAA2:
//  DISPLAY "PARAGRAPH-AAA2".
    DISPLAY("PARAGRAPH-AAA2");
    if( leave(PARAGRAPH_AAA2) ) return;
// PARAGRAPH-BBB2.
  case PARAGRAPH_BBB2:
//  DISPLAY "PARAGRAPH-BBB2"
    DISPLAY("PARAGRAPH-BBB2");
//  EXIT PARAGRAPH
    // unconditionally, or only in PEFORM ???
    if( leave(PARAGRAPH_BBB2) ) return;
    if( return_stack.top() != ANOTHER_SECTION ) {
//  DISPLAY "PARAGRAPH-BBB2, but this is an error".
      DISPLAY("PARAGRAPH-BBB2, but this is an error");
    }
    if( leave(PARAGRAPH_BBB2) ) return;
// PARAGRAPH-CCC2.
  case PARAGRAPH_CCC2:
//  DISPLAY "PARAGRAPH-CCC2".
    DISPLAY("PARAGRAPH-CCC2");
//  EXIT SECTION.
    if( leave(ANOTHER_SECTION) ) return;
//  DISPLAY "PARAGRAPH-CCC2, but this is an error".
    DISPLAY("PARAGRAPH-CCC2, but this is an error");
    if( leave(PARAGRAPH_CCC2) ) return;
// PARAGRAPH-DDD2.
  case PARAGRAPH_DDD2:
//  DISPLAY "PARAGRAPH-DDD2, but we should never get here.".
    DISPLAY("PARAGRAPH-DDD2, but we should never get here.");
    if( leave(PARAGRAPH_DDD2) ) return;
    if( leave(ANOTHER_SECTION) ) return;

// SEC1 SECTION.
  case SEC1:
// AAA.
  case SEC1_AAA:
//  DISPLAY "                  AAA OF SEC1".
    DISPLAY("                  AAA OF SEC1");
    if( leave(SEC1_AAA) ) return;
    if( leave(SEC1) )     return;
// SEC2 SECTION.
  case SEC2:
// AAA.
  case SEC2_AAA:
//  DISPLAY "                  AAA OF SEC2".
    DISPLAY("                  AAA OF SEC2");
    if( leave(SEC2_AAA) ) return;
    if( leave(SEC2) )     return;

// END PROGRAM performs.
  case EndProgram:
    return;
  }
  errx(1, "errror: control passed through line %d", __LINE__);
}

// public function
void
performs()
{
  progfunc(no_paragraph, EndProgram);
}

int main(int argc, char *argv[])
{
  performs();
  cout << "end program" << std::endl;
  return 0;
}
