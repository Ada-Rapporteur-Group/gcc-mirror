#!/bin/python3

# This program is designed to live in gcc/cobol/tests.  It takes a single .cbl
# and a single known-good.txt file from each directory, and combines them in the
# dejagnu form.


import os
import sys

def get_directories():
  full_list = os.listdir(".")
  retval = []
  for dir in full_list:
    if not "Listing" in dir :
      if( os.path.isdir( dir ) ):
        retval.append(dir)
  return retval

def combine_the_files(dir, cbl, good):
  if not cbl or not good:
    return
  if dir in [ "check_88",
              "c-to-cobol",
              "call-scope-1",
              "tripled",
              "perform-exercise",
              "moves",
              "initialize_1",
              "numeds",
              "compute-1",
              "lineseq"
              ]:
    return
  print("combining", dir, cbl, good)
  cbl_lines = []
  good_lines = []
  with open(dir+"/"+cbl, 'r') as f:
    cbl_lines = f.read().split('\n')
  with open(dir+"/"+good, 'r') as f:
    good_lines = f.read().split('\n')
  print(good, "line count", len(good_lines))
  with open(dir+".cob", 'w') as f:
    print("*> { dg-do run }", file=f)
    line_count = 1
    
    if len(good_lines[-1]) == 0:
      good_lines = good_lines[:-1]

    for good_line in good_lines:
      line_out = "*> { dg-output {"
      for ch in good_line:
        if ch in r".^$*+-?()[]{}\|":
          line_out += "\\"
        line_out += ch
      if line_count < len(good_lines):
        # We don't put the newline detector on the final line, because 
        # newlines being eaten during remote testing is a known problem
        line_out += r"(\n|\r\n|\r)"
      line_count += 1
      line_out += "} }"
      print(line_out, file=f)
    for cbl_line in cbl_lines:
      if len(cbl_line) != 0:
        print(cbl_line, file=f)

def main():
  list_of_dirs = sys.argv[1:]
  if len(list_of_dirs) == 0:
    list_of_dirs = get_directories()
  for dir in list_of_dirs:
    file_cbl  = None
    file_good = None
    list_of_files = os.listdir(dir)
    list_of_cbls = []
    for file in list_of_files:
      if file[-4:] == ".cbl":
        list_of_cbls.append(file)
      if file == "known-good.txt":
        file_good = file
    if len(list_of_cbls) == 1:
      file_cbl = list_of_cbls[0]
      combine_the_files(dir, file_cbl, file_good)
    

main()
