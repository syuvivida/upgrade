#!/bin/bash


bsub -R "type=SLC6_64" -q 2nd $PWD/runJob.csh $PWD
