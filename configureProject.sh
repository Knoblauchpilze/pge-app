#!/bin/bash

## Usage function
display_usage () {
  bold=$(tput bold)
  normal=$(tput sgr0)

  echo "${bold}This script update files to match the provided project name"
  echo "${bold}Usage:${normal}"
  echo "./configureProject.sh project_name"
}

# Make sure that we have at least one argument and
# that it is valid.
if [ $# -lt 1 ]; then
  display_usage
  exit 1
fi

PROJECT_NAME=${1}

if [ "${PROJECT_NAME}" == "" ]; then
  echo "Warning: Empty project name provided"
  display_usage
  exit 1
fi

echo "Renaming project to \"${PROJECT_NAME}\"..."

echo "Updating source files..."
sed -i "s/pge-app/${PROJECT_NAME}/g" src/main.cpp

echo "Updating CMakeLists files..."
sed -i "s/example-app\b/${PROJECT_NAME}/g" CMakeLists.txt

echo "Updating scripts..."
sed -i "s/example-app/${PROJECT_NAME}/g" data/debug.sh
sed -i "s/example-app/${PROJECT_NAME}/g" data/profile.sh
sed -i "s/example-app/${PROJECT_NAME}/g" data/run.sh
sed -i "s/example-app/${PROJECT_NAME}/g" data/valgrind.sh

echo "Updating code..."
sed -i "s/pge-app/${PROJECT_NAME}/g" src/lib/app/olcPixelGameEngine.h

echo "Cleaning data..."
make clean
make cleanSandbox

echo "Rebuilding..."
make sandbox

echo "Reset git versions..."
rm -rf .git
git init

echo "Remove configuration script..."
rm configureProject.sh

echo "Success !"
