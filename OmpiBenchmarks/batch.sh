#!/bin/bash
# all procs
amplxe-cl -collect advanced-hotspots -r results-ah2/1x1x1 ./juliet.intel.mm.r.sh 1 1
amplxe-cl -collect advanced-hotspots -r results-ah2/1x2x1 ./juliet.intel.mm.r.sh 1 2
amplxe-cl -collect advanced-hotspots -r results-ah2/1x4x1 ./juliet.intel.mm.r.sh 1 4
amplxe-cl -collect advanced-hotspots -r results-ah2/1x8x1 ./juliet.intel.mm.r.sh 1 8
amplxe-cl -collect advanced-hotspots -r results-ah2/1x16x1 ./juliet.intel.mm.r.sh 1 16
amplxe-cl -collect advanced-hotspots -r results-ah2/1x24x1 ./juliet.intel.mm.r.sh 1 24
# all threads
amplxe-cl -collect advanced-hotspots -r results-ah2/2x1x1 ./juliet.intel.mm.r.sh 2 1
amplxe-cl -collect advanced-hotspots -r results-ah2/4x1x1 ./juliet.intel.mm.r.sh 4 1
amplxe-cl -collect advanced-hotspots -r results-ah2/8x1x1 ./juliet.intel.mm.r.sh 8 1
amplxe-cl -collect advanced-hotspots -r results-ah2/16x1x1 ./juliet.intel.mm.r.sh 16 1
amplxe-cl -collect advanced-hotspots -r results-ah2/24x1x1 ./juliet.intel.mm.r.sh 24 1
# 24 way combinations
amplxe-cl -collect advanced-hotspots -r results-ah2/2x12x1 ./juliet.intel.mm.r.sh 2 12
amplxe-cl -collect advanced-hotspots -r results-ah2/3x8x1 ./juliet.intel.mm.r.sh 3 8
amplxe-cl -collect advanced-hotspots -r results-ah2/4x6x1 ./juliet.intel.mm.r.sh 4 6
amplxe-cl -collect advanced-hotspots -r results-ah2/6x4x1 ./juliet.intel.mm.r.sh 6 4
amplxe-cl -collect advanced-hotspots -r results-ah2/8x3x1 ./juliet.intel.mm.r.sh 8 3
amplxe-cl -collect advanced-hotspots -r results-ah2/12x2x1 ./juliet.intel.mm.r.sh 12 2
