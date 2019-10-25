# LogicToolbox - Open source framework for logic computations
# Build status: ![alt text](https://travis-ci.org/dinkoosmankovic/LogicToolbox.svg?branch=master)

# 1. Building LogicToolbox

Run commands:

  $ mkdir build

  $ cd build

  $ cmake --DCMAKE_INSTALL_PREFIX=../installed ..
  
  $ make install

  $ cmake .
  
  $ make

In order to configure project successfully in Qt Creator it is necessary to check "Select all kits" and then "Cofigure project".

# 2. Building docs

Run command:

  $ make doc


# 3. Building tests

Run command: 

  $ make check

