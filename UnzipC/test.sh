#!/bin/bash

\rm output.txt UnzipC small.test medium.test afsluiten.pdf 2>/dev/null

gcc main.c unzip.c resource_detector.c -o UnzipC

./UnzipC < input.txt > output.txt

diff -q output.txt correct.txt
diff -q small.test small.ok
diff -q medium.test medium.ok
diff -q afsluiten.pdf afsluiten.ok
