#!/bin/bash

cat includes/* | grep ');' > inc
cat srcs/**/** | grep -v '**' > s
