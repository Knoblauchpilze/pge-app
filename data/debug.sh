#!/bin/sh

CURR_DIR=$(dirname $0)

gdb --args ./bin/main-app
