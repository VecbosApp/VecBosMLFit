
root -l -b src/RooLogon.C <<EOF

.L src/GenerateZjets.cc
SetNjets(1)
Generate(1000)

EOF
