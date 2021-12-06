#!/bin/bash

# Using echo command to display the header
echo -e "i-node  HardLinks  Path\n"

# Using find command to find and locate the inodes
find / -links +1 -printf '%i \t %n \t %p\n' 2>/dev/null | sort -nk1
