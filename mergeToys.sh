#! /bin/sh

# usage: ./mergeToys calodir trackdir

calodir=$1

touch $calodir/merged-results-W1calojet.dat
touch $calodir/merged-results-W2calojet.dat
touch $calodir/merged-results-W3calojet.dat
touch $calodir/merged-results-W4calojet.dat

cat $calodir/results-W1calojet-*dat >> $calodir/merged-results-W1calojet.dat
cat $calodir/results-W2calojet-*dat >> $calodir/merged-results-W2calojet.dat
cat $calodir/results-W3calojet-*dat >> $calodir/merged-results-W3calojet.dat
cat $calodir/results-W4calojet-*dat >> $calodir/merged-results-W4calojet.dat


trackdir=$2

touch $trackdir/merged-results-W1trackjet.dat
touch $trackdir/merged-results-W2trackjet.dat
touch $trackdir/merged-results-W3trackjet.dat
touch $trackdir/merged-results-W4trackjet.dat

cat $trackdir/results-W1trackjet-*dat >> $trackdir/merged-results-W1trackjet.dat
cat $trackdir/results-W2trackjet-*dat >> $trackdir/merged-results-W2trackjet.dat
cat $trackdir/results-W3trackjet-*dat >> $trackdir/merged-results-W3trackjet.dat
cat $trackdir/results-W4trackjet-*dat >> $trackdir/merged-results-W4trackjet.dat

