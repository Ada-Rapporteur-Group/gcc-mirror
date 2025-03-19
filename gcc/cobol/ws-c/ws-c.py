#!/usr/bin/env python3

import sys, os, getopt, re, copy, sqlite3

class Elem:
    def __init__(self, type, name, capacity, digits, occurs):
        self.type = type
        self.name = name
        self.capacity = capacity
        self.digits = digits
        self.occurs = occurs

    def print(self, indent):
        if self.type == 'FldAlphanumeric' or self.type == 'FldNumericDisplay':
            occurs = ''
            if self.occurs > 0:
                occurs = '[%d]' % self.occurs
            print(  '%schar %s[%d]%s;' % ( indent, self.name, self.digits, occurs) )
        else:
            print( "error: %s (%s) not printable" % (self.name, self.type) )

class Struct:
    def __init__(self, n, isym, type, name, capacity, digits, occurs):
        self.members = []
        self.n = n
        self.isym = isym
        self.type = type
        self.name = name
        self.capacity = capacity
        self.digits = digits
        self.occurs = occurs

    def print(self, indent):
        occurs = ''
        if self.occurs > 0:
            occurs = '[%d]' % self.occurs
        print(  '%sstruct %s_t {' % ( indent, self.name, ) )
        for member in self.members:
            member.print( '%s%s' % (indent, indent) )
        print( '%s} %s%s;' % ( indent, self.name, occurs) )

class Union:
    def __init__(self, n, isym):
        self.members = []
        self.n = n
        self.isym = isym

    def print(self, indent):
        name = self.members[0].name
        print(  '%sunion %s_u_t {\n' % ( indent, name, ) )
        for member in self.members:
            member.print( '%s%s' % (indent, indent) )
        print( '%s} %s_u;' % ( indent, name) )

def process(dbname):
    db = sqlite3.connect(dbname)
    db.row_factory = sqlite3.Row
    cur = db.cursor()

    U = None
    S = None
    indent = '\t'

    for row in cur.execute('select * from working_storage'):
        if row['nU']:
            nU = 1 + row['nU']
            U = Union( nU, row['isym'] )
            continue

        if row['nelem']:
            nS = 1 + row['nelem']
            S = Struct( nS, row['isym'], row['type'], row['name'],
                            row['capacity'], row['digits'], row['occurs'])
            if U and len(U.members) < nU:
                U.members.append(S)
            continue

        elem = Elem( row['type'], row['name'],
                         row['capacity'], row['digits'], row['occurs'] )

        if S:
            S.members.append(elem)
            if len(S.members) == S.n:
                if U and len(U.members) == U.n:
                    U.print(indent)
                    U = None
                else:
                    S.print(indent)
                    S = None
            continue

        if U:  # no structure
            U.members.append(elem)
            if len(U.members) == U.n:
                U.print(indent)
                U = None
            continue

        elem.print('')

__doc__ = """
syntax:
"""

def main( argv=None ):
    if argv is None:
        argv = sys.argv
    # parse command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["help"])
    except getopt.error as msg:
        print(msg)
        print("for help use --help")
        sys.exit(2)

    # process options

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print(__doc__)
            sys.exit(0)

    # process arguments
    if not args:
        args = ('/dev/stdin',)

    for arg in args:
        process(arg)

if __name__ == "__main__":
    sys.exit(main())
