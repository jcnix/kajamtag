#!/bin/bash

aclocal \
&& autoconf \
&& autoheader \
&& libtoolize \
&& automake -a

