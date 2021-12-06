#!/bin/bash

echo -e "i-node  HardLinks  Path\n"

find / -links +1 -printf '%i \t %n \t %p\n' 2>/dev/null | sort -nk1
