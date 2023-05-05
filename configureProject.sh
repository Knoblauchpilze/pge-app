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
sed -i "s/pge-app/${PROJECT_NAME}/g" src/main.cc

echo "Updating CMakeLists files..."
for file in $(find . -name CMakeLists.txt);
do
  sed -i "s/example-app/${PROJECT_NAME}/g" $file
done
sed -i "s/example-project\b/${PROJECT_NAME}/g" CMakeLists.txt

echo "Updating scripts..."
for file in data/*.sh;
do
  sed -i "s/example-app/${PROJECT_NAME}/g" $file
done

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
