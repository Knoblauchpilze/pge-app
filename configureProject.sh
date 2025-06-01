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

echo "Updating CMakeLists files..."
for file in $(find . -name CMakeLists.txt);
do
  sed -i "s/pge_app_lib/${PROJECT_NAME}_lib/g" $file
  sed -i "s/pge_app_tests/${PROJECT_NAME}_tests/g" $file
  sed -i "s/pge_app/${PROJECT_NAME}/g" $file
  sed -i "s/pge_app_interface_library/${PROJECT_NAME}_interface_library/g" $file
  sed -i "s/pge_app_interface_test_library/${PROJECT_NAME}_interface_test_library/g" $file
done
sed -i "s/pge-app\b/${PROJECT_NAME}/g" CMakeLists.txt
sed -i "s/pge_app_interface_library/${PROJECT_NAME}_interface_library/g" CMakeLists.txt
sed -i "s/pge_app_interface_test_library/${PROJECT_NAME}_interface_test_library/g" CMakeLists.txt

echo "Updating Makefile..."
sed -i "s/pge_app_tests/${PROJECT_NAME}_tests/g" Makefile
sed -i "s/pge_app/${PROJECT_NAME}/g" Makefile

echo "Updating code..."
sed -i "s/pge-app/${PROJECT_NAME}/g" src/pge/olc/olcPixelGameEngine.h
sed -i "s/pge-app/${PROJECT_NAME}/g" src/main.cc

echo "Cleaning data..."
make clean
make cleanSandbox

echo "Rebuilding..."
make copyRelease

echo "Reset git versions..."
rm -rf .git
git init

echo "Remove configuration script..."
rm configureProject.sh

echo "Success !"
