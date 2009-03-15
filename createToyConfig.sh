#! /bin/sh

# usage: ./createToyConfigW jetmult jetflavour (ex.: ./createToyConfig 1 calojet)

jetmult=$1
jetflavour=$2

echo ""
echo "   [Parameters]   "
echo ""

grep sig_Mt shapesWenu/config/fitMinimum-Wonly-$jetmult$jetflavour.config 
echo ""
grep ttbar_Mt shapesWenu/config/fitMinimum-TTbaronly-$jetmult$jetflavour.config
echo ""
grep other_Mt shapesWenu/config/fitMinimum-otheronly-$jetmult$jetflavour.config
echo ""
grep sig_sinMHTphiJet shapesWenu/config/fitMinimum-Wonly-$jetmult$jetflavour.config
echo ""
grep ttbar_sinMHTphiJet shapesWenu/config/fitMinimum-TTbaronly-$jetmult$jetflavour.config
echo ""
grep other_sinMHTphiJet shapesWenu/config/fitMinimum-otheronly-$jetmult$jetflavour.config
echo ""
echo "bveto_acc_p1 =  1.0000 C L(-2 - 2)"
echo "bveto_acc_p2 =  0.0000 C L(-2 - 2)"
echo "bveto_rej_p1 = -1.000000 C L(-2 - 2)"
echo "bveto_rej_p2 =  0.0000 C L(-2 - 2)"
echo ""

# yields for calojets:
echo "$jetflavour" | grep -q 'calojet'

if [ $? -eq 0 ] ; then

    # W 1 calojet
    if [ $1 -eq 1 ] ; then
        echo "N_sig =  20359 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.884 +/- 0.0022246  L(0 - 1)"
        echo ""
        echo "N_ttbar =  1364 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar =  0.377 +/- 0.0010562  L(0 - 1)"
        echo ""
        echo "N_other =  3072 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.823 +/- 0.0013478   L(0 - 1)"
    fi

    # W 2 calojet
    if [ $1 -eq 2 ] ; then
        echo "N_sig =  2570 +/- 0.54950 L(-100 - 900000)"
        echo "eff_sig =  0.803 +/- 0.000044403  L(0 - 1)"
        echo ""
        echo "N_ttbar =  1004 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar =  0.354 +/- 0.50000  L(0 - 1)"
        echo ""
        echo "N_other =  624 +/- 50.000  L(-500 - 10000)"
        echo "eff_other = 0.752  +/- 0.50000   L(0 - 1)"
    fi

    # W 3 calojet
    if [ $1 -eq 3 ] ; then
        echo "N_sig =  355 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.739 +/- 0.0022246  C L(0 - 1)"
        echo ""
        echo "N_ttbar =  442 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar = 0.320  +/- 0.0010562  C L(0 - 1)"
        echo ""
        echo "N_other =  96 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.581 +/- 0.0013478 C L(0 - 1)"
    fi

    # W 4 calojet
    if [ $1 -eq 4 ] ; then
        echo "N_sig =  49 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.634 +/- 0.0022246  C L(0 - 1)"
        echo ""
        echo "N_ttbar =  114 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar = 0.292  +/- 0.0010562 C L(0 - 1)"
        echo ""
        echo "N_other =  14 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.581 +/- 0.0013478 C L(0 - 1)"
    fi

fi


# yields for trackjets:
echo "$jetflavour" | grep -q 'trackjet'

if [ $? -eq 0 ] ; then

    # W 1 trackjet
    if [ $1 -eq 1 ] ; then
        echo "N_sig =  51066 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.826 +/- 0.0022246  L(0 - 1)"
        echo ""
        echo "N_ttbar =  1350 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar =  0.141 +/- 0.0010562  L(0 - 1)"
        echo ""
        echo "N_other =  6973 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.703 +/- 0.0013478  L(0 - 1)"
    fi

    # W 2 trackjet
    if [ $1 -eq 2 ] ; then
        echo "N_sig =  8215 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.710 +/- 0.0022246  L(0 - 1)"
        echo ""
        echo "N_ttbar =  1258 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar =  0.135 +/- 0.0010562  L(0 - 1)"
        echo ""
        echo "N_other =  1673 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.626 +/- 0.0013478  L(0 - 1)"
    fi

    # W 3 trackjet
    if [ $1 -eq 3 ] ; then
        echo "N_sig =  1573 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.601 +/- 0.0022246 C L(0 - 1)"
        echo ""
        echo "N_ttbar =  869 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar =  0.121 +/- 0.0010562 C L(0 - 1)"
        echo ""
        echo "N_other =  324 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.547 +/- 0.0013478 C L(0 - 1)"
    fi

    # W 4 trackjet
    if [ $1 -eq 4 ] ; then
        echo "N_sig =  292 +/- 220.00  L(-100 - 900000)"
        echo "eff_sig =  0.508 +/- 0.0022246 C L(0 - 1)"
        echo ""
        echo "N_ttbar =  394 +/- 50.000  L(-500 - 10000)"
        echo "eff_ttbar =  0.103 +/- 0.0010562 C L(0 - 1)"
        echo ""
        echo "N_other =  67 +/- 20.855 L(-500 - 10000)"
        echo "eff_other =  0.421 +/- 0.0013478 C L(0 - 1)"
    fi

fi

echo ""
echo "   [Observables]"
echo ""
echo "Mt             = 90 C L(30 - 250)      // [GeV]"
echo "sinMHTphiJet   = 0  C L(-0.85 - 0.85)"
echo "BVETO          = 1  C L(-1 - 1)"

