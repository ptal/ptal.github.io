#!/bin/sh

if gcc $1.c -o $1 -Wall -ansi -pedantic -Wall -Werror -std=c99; then
  ./$1
fi
