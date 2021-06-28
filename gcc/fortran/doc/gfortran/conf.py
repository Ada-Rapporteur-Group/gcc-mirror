# Configuration file for the Sphinx documentation builder.

import sys
sys.path.append('../../../..//doc')

from baseconf import *

project = 'Using GNU Fortran'
copyright = '1999-%s Free Software Foundation, Inc.' % YEAR
authors = 'The gfortran team'

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
latex_documents = [
  ('index', 'gfortran.tex', project, authors, 'manual'),
]

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    ('gnu-fortran-command-options', 'gfortran', 'GNU Fortran compiler', [authors], 1),
]

texinfo_documents = [
  ('index', 'gfortran', project, authors, None, None, None, True)
]

tags.add('gfortran')

if gcc_DEVPHASE == 'experimental':
    tags.add('development')
