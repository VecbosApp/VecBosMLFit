#! /bin/bash

root -l -b <<EOF
.include /afs/cern.ch/cms/sw/slc5_ia32_gcc434/lcg/roofit/5.26.00-cms8/include/
.L src/createDatasetForTopMockFits.cc+
createDataset("results/treesW/top_Wenu.root","mockTop.root")
EOF

rm -f mockTop.root
mv mockFinal.root results/datasetsJets/

echo "Done. Check the file results/datasetsJets/mockFinal.root "
