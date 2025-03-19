# The `-x` (language) Option on the `gcobol` Command

When your source file has no "suffix" or its suffix is not one of those automatically recognized by `gcobol` as a COBOL source code file (.cbl, .cob, .cobol, etc.) you must specify the "-x cobol" option. This tells gcobol that the file is COBOL source.

## Notes

The Option preprocessor is handling “-x <language>” properly. as of commit 416ec6e4f8b, late Thursday night.

So, “gcobol -x cobol xyz” will read “xyz” as a cobol source file and generate the executable a.out

Notes:

“cobol” is case sensitive.  The gcc program will refuse to accept “Cobol”, just like it refuses to accept “C++” instead of “c++”.

If for some reason you need to explicitly link in static libraries, the language needs to be “none” when the object file is processed.

That’s because the command “gcobol -x cobol xyz somelib.a” will result in the compiler treating the file somelib.a as a text source file.

One solution:

    gcobol -x cobol xyz -x none somelib.a

Another solution:

    gcobol somelib.a -main -x cobol xyz

Another possibility:

    gcobol -c -x cobol xyz -o xyz.o
    gcobol -o <executable> xyz.o somelib.a

My advice:  Do not read the following paragraphs.  Just use one of the given solutions if you want to link in a static library.

The TL;DR explanation requires an understanding that the GCC preprocessor makes no distinction between .a object modules and text source files.  They are just files, and the preprocessor doesn’t examine them to see if they are source code or object modules.  If the current language is “none”, then the downstream processor does check to see if a file is an object module.  If a -x <language> is in effect, then a file without a -<something> switch is treated as if it is that language.

So, by putting the .a file first in a single-command-line compilation, the language is “none” and it gets handled as an object file.  “-x cobol” changes the language to “cobol”, but now we need a -main switch, because otherwise my preprocessor thinks the main() entry routine is supposed to get compiled into the first source file, which it thinks is the somelib.a file.  Putting -main in front of the “xyz” file causes the main() entry point to be compiled into it.

Doing a two-command compilation does an end run around the whole “-main” and “avoid processing somelib.a as a text file” problems.

