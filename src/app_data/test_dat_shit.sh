#!/bin/env bash

for f in $(find . -name '*.txt' | sort -V)
do
  ls ${f}
  p1_pakkelevering ${f} >> test_data.txt
done
