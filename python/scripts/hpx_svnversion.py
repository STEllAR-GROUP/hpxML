#! /usr/bin/env python 
#
# Copyright (c) 2011 Bryce Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from os.path import exists, join

from sys import path, exit

from optparse import OptionParser

if exists(join(path[0], "../hpx")):
  path.append(join(path[0], ".."))
if exists(join(path[0], "../share/hpx/python/hpx")):
  path.append(join(path[0], "../share/hpx/python"))

from hpx.svn import revision

usage = "usage: %prog [options] [path]" 

parser = OptionParser(usage=usage)

(options, wc_path) = parser.parse_args()

if 0 == len(wc_path):
  # If no path is specified, use the current working directory
  print revision()
elif 1 != len(wc_path):
  print "More than one path specified."
  exit(1)
else:
  print revision(wc_path[0])
