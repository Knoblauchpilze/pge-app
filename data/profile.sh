#!/bin/sh

# Delete previous profiling.
rm callgrind.out.*

CURR_DIR=$(dirname $0)
valgrind --tool=callgrind --log-file="analysis" ./bin/pge-app

gprof2dot -f callgrind callgrind.out.* | dot -Tpng -o output.png
gimp output.png
