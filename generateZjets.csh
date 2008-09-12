
root -l -b src/RooLogon.C <<EOF

.L src/GenerateZjets.cc
SetNjets(1)
Generate(1000)

.L src/GenerateZjets.cc
SetNjets(2)
Generate(1000)

.L src/GenerateZjets.cc
SetNjets(3)
Generate(1000)

.L src/GenerateZjets.cc
SetNjets(4)
Generate(1000)

EOF
