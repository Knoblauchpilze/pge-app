#!/bin/sh

if [ $# -lt 1 ]; then
  echo "Usage: $0 app_name"
  exit 1
fi

APP_NAME=$1

# Delete previous profiling.
rm -rf callgrind.out.*

valgrind --tool=callgrind --log-file="analysis" ./bin/${APP_NAME}

gprof2dot -f callgrind callgrind.out.* | dot -Tpng -o output.png
gimp output.png
