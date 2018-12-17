#!/bin/env bash

for f in $(find . -name '*.txt')
do
  p1_pakkelevering ${f} >> test_data.txt
done
