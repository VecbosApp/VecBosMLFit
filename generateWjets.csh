
root -l -b src/RooLogon.C <<EOF

.L src/GenerateWjets.cc
SetNjets(1) 
Generate(1000)

SetNjets(2) 
Generate(1000)

SetNjets(3) 
Generate(1000)

SetNjets(4) 
Generate(1000)


EOF

