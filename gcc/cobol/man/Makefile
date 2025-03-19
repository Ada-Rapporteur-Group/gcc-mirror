.PHONY: rendered

#
# Demonstrate the output of various ways to render a manpage that
# includes a pic(1) diagram.
#

rendered: rendered/gcobol-start.groff.html	\
	  rendered/gcobol-start.mandoc.html	\
	  rendered/gcobol-start.groff.html	\
	  rendered/gcobol-start.pdf

rendered/gcobol-start.groff.html: gcobol-start.3c
	@mkdir -p $(dir $@)
	groff -T html -mdoc -pet  $^ > $@~
	@mv $@~ $@

rendered/gcobol-start.mandoc.html: gcobol-start.3c
	@mkdir -p $(dir $@)
	mandoc -Thtml $^ > $@~
	@mv $@~ $@

rendered/gcobol-start.man.html: gcobol-start.3c
	@mkdir -p $(dir $@)
	man -pp $^ > $@~
	@mv $@~ $@

rendered/gcobol-start.pdf: gcobol-start.3c
	groff -mandoc -pet -Tpdf  $^ > $@~
	@mv $@~ $@

