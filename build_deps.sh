#!/bin/sh

set -e
cd ./libs/
cd ./glfw
cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 .
make
cd ../


cd glad
cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 .
make
cd ../../

