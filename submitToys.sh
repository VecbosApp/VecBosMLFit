#! /bin/sh

echo "SUBMITTING W + 1 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wcalojets -n 5000 -j 500 -q 1nh -p W -b 1 -f calojet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 2 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wcalojets -n 5000 -j 100 -q 1nh -p W -b 2 -f calojet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 3 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wcalojets -n 5000 -j 10 -q 1nh -p W -b 3 -f calojet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 4 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wcalojets -n 5000 -j 10 -q 1nh -p W -b 4 -f calojet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 1 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wtrackjets -n 5000 -j 500 -q 1nh -p W -b 1 -f trackjet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 2 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wtrackjets -n 5000 -j 100 -q 1nh -p W -b 2 -f trackjet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 3 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wtrackjets -n 5000 -j 10 -q 1nh -p W -b 3 -f trackjet -x src/GenerateWjets.cc 

echo "SUBMITTING W + 4 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Wtrackjets -n 5000 -j 10 -q 1nh -p W -b 4 -f trackjet -x src/GenerateWjets.cc 




echo "SUBMITTING Z + 1 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Zcalojets -n 1000 -j 10 -q 1nh -p Z -b 1 -f calojet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 2 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Zcalojets -n 1000 -j 10 -q 1nh -p Z -b 2 -f calojet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 3 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Zcalojets -n 1000 -j 10 -q 1nh -p Z -b 3 -f calojet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 4 CALOJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Zcalojets -n 1000 -j 10 -q 1nh -p Z -b 4 -f calojet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 1 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Ztrackjets -n 1000 -j 10 -q 1nh -p Z -b 1 -f trackjet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 2 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Ztrackjets -n 1000 -j 10 -q 1nh -p Z -b 2 -f trackjet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 3 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Ztrackjets -n 1000 -j 10 -q 1nh -p Z -b 3 -f trackjet -x src/GenerateZjets.cc 

echo "SUBMITTING Z + 4 TRACKJET..."
./SubmitGenerate.pl -r /afs/cern.ch/user/e/emanuele/scratch0/vecbos/OfflineAnalysis/CMSSW_2_1_17/ -d pccmsrm21.cern.ch:/cmsrm/pc21/emanuele/data/VecBos2.1.X/toys/Ztrackjets -n 1000 -j 10 -q 1nh -p Z -b 4 -f trackjet -x src/GenerateZjets.cc 
