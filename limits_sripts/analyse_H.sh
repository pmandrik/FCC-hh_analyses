#!/bin/bash

fitter_path=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/
workdir=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/H


mkdir -p $workdir
cd $workdir

cd /afs/cern.ch/user/p/pmandrik/public/analysis/MSU_statistics_13TEV/theta_13tev_global/comb_new/CMSSW_8_1_0/src/ttqgamma; eval `scramv1 runtime -sh`; cd -;           

do_fit(){
  bdt_name=$1"_"$2"_"$3
  root -l -b -q "../prep_hists.C(\"$1\", \"$workdir\", $2, $3, true)"

  cp ../card_bsH.txt .
  cp ../card_bdH.txt .
  echo $bdt_name
  
  sed -i -e "s/%BDT_NAME%/$bdt_name/g" card_bsH.txt
  combine card_bsH.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root $bdt_name"_bsH.root"

  sed -i -e "s/%BDT_NAME%/$bdt_name/g" card_bdH.txt
  combine card_bdH.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root $bdt_name"_bdH.root"
}

# 25.6% 24.8%
#do_fit "H_m_xfactor" 5 1
#do_fit "H_m_xfactor_1" 5 1
#do_fit "H_m_xfactor_2" 5 1

do_fit "weight_BDT_3b_003_xfactor" 25 1
do_fit "weight_BDT_3b_003_xfactor" 25 2
do_fit "weight_BDT_3b_003_xfactor" 25 3
do_fit "weight_BDT_3b_003_xfactor" 25 4
do_fit "weight_BDT_3b_003_xfactor" 25 5
do_fit "weight_BDT_3b_003_xfactor" 25 10
do_fit "weight_BDT_3b_003_xfactor" 25 20
do_fit "weight_BDT_3b_003_xfactor" 25 25
do_fit "weight_BDT_3b_003_xfactor" 25 50
do_fit "weight_BDT_3b_003_xfactor" 25 100
do_fit "weight_BDT_3b_003_xfactor" 25 200
do_fit "weight_BDT_3b_003_xfactor" 25 500
do_fit "weight_BDT_3b_003_xfactor" 25 1000



exit
do_fit "weight_BDT_3b_000_xfactor" 25 1
do_fit "weight_BDT_3b_000_xfactor" 25 2
do_fit "weight_BDT_3b_000_xfactor" 25 3
do_fit "weight_BDT_3b_000_xfactor" 25 4
do_fit "weight_BDT_3b_000_xfactor" 25 5
do_fit "weight_BDT_3b_000_xfactor" 25 10
do_fit "weight_BDT_3b_000_xfactor" 25 20
do_fit "weight_BDT_3b_000_xfactor" 25 25
do_fit "weight_BDT_3b_000_xfactor" 25 50
do_fit "weight_BDT_3b_000_xfactor" 25 100
do_fit "weight_BDT_3b_000_xfactor" 25 200
do_fit "weight_BDT_3b_000_xfactor" 25 500
do_fit "weight_BDT_3b_000_xfactor" 25 1000
exit

do_fit "weight_BDT_0a_000_xfactor" 20 1
do_fit "weight_BDT_1a_000_xfactor" 20 1
do_fit "weight_BDT_2a_000_xfactor" 20 1
do_fit "weight_BDT_3a_000_xfactor" 20 1

do_fit "weight_BDT_0b_000_xfactor" 20 1
do_fit "weight_BDT_1b_000_xfactor" 20 1
do_fit "weight_BDT_2b_000_xfactor" 20 1
do_fit "weight_BDT_3b_000_xfactor" 20 1

do_fit "weight_BDT_0c_000_xfactor" 20 1
do_fit "weight_BDT_1c_000_xfactor" 20 1
do_fit "weight_BDT_2c_000_xfactor" 20 1
do_fit "weight_BDT_3c_000_xfactor" 20 1

exit
do_fit "H_m_xfactor_3" 30 5
do_fit "H_m_xfactor_3" 30 10
do_fit "H_m_xfactor_3" 30 50
do_fit "H_m_xfactor_3" 30 100
do_fit "H_m_xfactor_3" 30 200
do_fit "H_m_xfactor_3" 30 500
do_fit "H_m_xfactor_3" 30 1000
do_fit "H_m_xfactor_3" 30 5000
do_fit "H_m_xfactor_3" 30 10000
do_fit "H_m_xfactor_3" 30 25000
do_fit "H_m_xfactor_3" 30 50000
do_fit "H_m_xfactor_3" 30 100000
exit

do_fit "H_m_xfactor_3" 5 2
do_fit "H_m_xfactor_3" 5 3
do_fit "H_m_xfactor_3" 5 4
do_fit "H_m_xfactor_3" 5 5
do_fit "H_m_xfactor_3" 5 10
do_fit "H_m_xfactor_3" 5 20
do_fit "H_m_xfactor_3" 5 25
do_fit "H_m_xfactor_3" 5 50
do_fit "H_m_xfactor_3" 5 100
do_fit "H_m_xfactor_3" 5 200
do_fit "H_m_xfactor_3" 5 500
do_fit "H_m_xfactor_3" 5 1000
exit

do_fit "weight_BDT_0a_000" 25 1 % r < 0.0161
do_fit "weight_BDT_2a_000" 25 1 % r < 0.0122
do_fit "weight_BDT_4a_000" 25 1 % r < 0.0083

do_fit "weight_BDT_0b_000" 25 1 % r < 0.0161
do_fit "weight_BDT_2b_000" 25 1 % r < 0.0132
do_fit "weight_BDT_4b_000" 25 1 % 0.0044

do_fit "H_m_xfactor_3" 25 1 % 0.0034 0.0054 
do_fit "weight_BDT_2c_000" 25 1 % 0.0034 0.0024
do_fit "weight_BDT_4c_000" 25 1 % 0.0044 0.0034
exit


