#!/bin/bash

fitter_path=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/
workdir=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/tqH


mkdir -p $workdir
cd $workdir

cd /afs/cern.ch/user/p/pmandrik/public/analysis/MSU_statistics_13TEV/theta_13tev_global/comb_new/CMSSW_8_1_0/src/ttqgamma; eval `scramv1 runtime -sh`; cd -;           

do_fit(){
  bdt_name=$1"_"$2"_"$3
  root -l -b -q "../prep_hists.C(\"$1\", \"$workdir\", $2, $3, true)"

  cp ../card_tuH.txt .
  cp ../card_tcH.txt .
  echo $bdt_name
  
  sed -i -e "s/%BDT_NAME%/$bdt_name/g" card_tuH.txt
  combine card_tuH.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root $bdt_name"_tau.root"

  sed -i -e "s/%BDT_NAME%/$bdt_name/g" card_tcH.txt
  combine card_tcH.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root $bdt_name"_tac.root"
}

do_fit "weight_BDT_0c_000" 25 1
do_fit "weight_BDT_0c_000" 25 2
do_fit "weight_BDT_0c_000" 25 3
do_fit "weight_BDT_0c_000" 25 4
do_fit "weight_BDT_0c_000" 25 5
do_fit "weight_BDT_0c_000" 25 10
do_fit "weight_BDT_0c_000" 25 20
do_fit "weight_BDT_0c_000" 25 25
do_fit "weight_BDT_0c_000" 25 50
do_fit "weight_BDT_0c_000" 25 100
do_fit "weight_BDT_0c_000" 25 200
do_fit "weight_BDT_0c_000" 25 500
do_fit "weight_BDT_0c_000" 25 1000
exit

do_fit "weight_BDT_0a_000" 25 1 % r < 0.0161
do_fit "weight_BDT_2a_000" 25 1 % r < 0.0122
do_fit "weight_BDT_4a_000" 25 1 % r < 0.0083

do_fit "weight_BDT_0b_000" 25 1 % r < 0.0161
do_fit "weight_BDT_2b_000" 25 1 % r < 0.0132
do_fit "weight_BDT_4b_000" 25 1 % 0.0044

do_fit "weight_BDT_0c_000" 25 1 % 0.0034 0.0054 
do_fit "weight_BDT_2c_000" 25 1 % 0.0034 0.0024
do_fit "weight_BDT_4c_000" 25 1 % 0.0044 0.0034


exit
