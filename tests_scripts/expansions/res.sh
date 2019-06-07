#!/bin/bash

old_log_file="./logs/prev"
new_log_file="./logs/new"

echo New Ok : `grep -c OK $new_log_file`
echo Old Ok : `grep -c OK $old_log_file`
echo ""
echo New Ko : `grep -c KO $new_log_file`
echo Old Ko : `grep -c KO $old_log_file`
