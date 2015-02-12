#!/bin/bash
# delete any files created by eval, so that we return to a fresh state;
# to be used after a fatal error in eval, and before packing and shipping

rm -rf work/* work-int/* scores.txt `find -iname allres.txt`
rm -rf `find -iwholename "*.tmp"`
rm -rf `find -iname ".tests"`
