#!/bin/sh

CURR_DIR=$(dirname $0)

gdb --args ./bin/example-app-tests
