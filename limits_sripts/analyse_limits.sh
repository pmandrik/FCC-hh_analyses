#!/bin/bash

fitter_path=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/
workdir=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/combo_wd_may_29


mkdir -p $workdir
cd $workdir

cd /afs/cern.ch/user/p/pmandrik/public/analysis/MSU_statistics_13TEV/theta_13tev_global/comb_new/CMSSW_8_1_0/src/ttqgamma; eval `scramv1 runtime -sh`; cd -;           

do_fit(){
  bdt_name=$1"_"$2"_"$3
  root -l -b -q "../prep_hists.C(\"$1\", \"$workdir\", $2, $3, true)"

  cp ../card_tau.txt .
  cp ../card_tac.txt .
  echo $bdt_name
  
  sed -i -e "s/%BDT_NAME%/$bdt_name/g" card_tau.txt
  combine card_tau.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root $bdt_name"_tau.root"

  sed -i -e "s/%BDT_NAME%/$bdt_name/g" card_tac.txt
  combine card_tac.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root $bdt_name"_tac.root"
}

do_fit "weight_tune_5_BDT_3_000" 25 1
do_fit "weight_tune_5_BDT_3_000" 25 2
do_fit "weight_tune_5_BDT_3_000" 25 3
do_fit "weight_tune_5_BDT_3_000" 25 4
do_fit "weight_tune_5_BDT_3_000" 25 5
do_fit "weight_tune_5_BDT_3_000" 25 10
do_fit "weight_tune_5_BDT_3_000" 25 20
do_fit "weight_tune_5_BDT_3_000" 25 25
do_fit "weight_tune_5_BDT_3_000" 25 50
do_fit "weight_tune_5_BDT_3_000" 25 100
do_fit "weight_tune_5_BDT_3_000" 25 200
do_fit "weight_tune_5_BDT_3_000" 25 500
do_fit "weight_tune_5_BDT_3_000" 25 1000

exit

do_fit "weight_tune_5_cut_BDT_2_000" 25 1
do_fit "weight_tune_5_cut_BDT_2_000" 25 2
do_fit "weight_tune_5_cut_BDT_2_000" 25 5
do_fit "weight_tune_5_cut_BDT_2_000" 25 10
do_fit "weight_tune_5_cut_BDT_2_000" 25 20
do_fit "weight_tune_5_cut_BDT_2_000" 25 25
do_fit "weight_tune_5_cut_BDT_2_000" 25 50
do_fit "weight_tune_5_cut_BDT_2_000" 25 100
do_fit "weight_tune_5_cut_BDT_2_000" 25 200
do_fit "weight_tune_5_cut_BDT_2_000" 25 500
do_fit "weight_tune_5_cut_BDT_2_000" 25 1000

exit

do_fit "weight_tune_3_BDT_3_000" 15 1
do_fit "weight_tune_3_BDT_3_000" 20 1
do_fit "weight_tune_3_BDT_3_000" 25 1
do_fit "weight_tune_3_BDT_3_000" 30 1
do_fit "weight_tune_3_BDT_3_000" 35 1

exit

do_fit "weight_tune_3_BDT_0_000" 25 1
do_fit "weight_tune_3_BDT_1_000" 25 1
do_fit "weight_tune_3_BDT_2_000" 25 1
do_fit "weight_tune_3_BDT_3_000" 25 1
do_fit "weight_tune_3_BDT_4_000" 25 1

exit


do_fit "weight_tune_5_cut_BDT_2_000" 25 1
do_fit "weight_tune_5_cut_BDT_2_000" 25 2
do_fit "weight_tune_5_cut_BDT_2_000" 25 5
do_fit "weight_tune_5_cut_BDT_2_000" 25 10
do_fit "weight_tune_5_cut_BDT_2_000" 25 20
do_fit "weight_tune_5_cut_BDT_2_000" 25 25
do_fit "weight_tune_5_cut_BDT_2_000" 25 50
do_fit "weight_tune_5_cut_BDT_2_000" 25 100
do_fit "weight_tune_5_cut_BDT_2_000" 25 200
do_fit "weight_tune_5_cut_BDT_2_000" 25 500
do_fit "weight_tune_5_cut_BDT_2_000" 25 1000

exit

do_fit "weight_tune_5_tac2_BDT_1_000" 20 1
do_fit "weight_tune_5_tac2_BDT_1_000" 20 2
do_fit "weight_tune_5_tac2_BDT_1_000" 20 5
do_fit "weight_tune_5_tac2_BDT_1_000" 20 10
do_fit "weight_tune_5_tac2_BDT_1_000" 20 20
do_fit "weight_tune_5_tac2_BDT_1_000" 20 25
do_fit "weight_tune_5_tac2_BDT_1_000" 20 50
do_fit "weight_tune_5_tac2_BDT_1_000" 20 100
do_fit "weight_tune_5_tac2_BDT_1_000" 20 200
do_fit "weight_tune_5_tac2_BDT_1_000" 20 500
do_fit "weight_tune_5_tac2_BDT_1_000" 20 1000


exit

do_fit "weight_tune_5_cut_BDT_0_000" 30 1
do_fit "weight_tune_5_cut_BDT_0_000" 25 1
do_fit "weight_tune_5_cut_BDT_0_000" 20 1
do_fit "weight_tune_5_cut_BDT_0_000" 15 1
do_fit "weight_tune_5_cut_BDT_0_000" 10 1

do_fit "weight_tune_5_cut_BDT_2_000" 30 1
do_fit "weight_tune_5_cut_BDT_2_000" 25 1
do_fit "weight_tune_5_cut_BDT_2_000" 20 1
do_fit "weight_tune_5_cut_BDT_2_000" 15 1
do_fit "weight_tune_5_cut_BDT_2_000" 10 1

exit

do_fit "weight_tune_5_cut_BDT_1_000" 25 1
do_fit "weight_tune_5_cut_BDT_2_000_20_1"
do_fit "weight_tune_5_cut_BDT_3_000_20_1"
do_fit "weight_tune_5_cut_BDT_4_000_20_1"
do_fit "weight_tune_5_cut_BDT_5_000_20_1"

do_fit "weight_tune_5_nocut_BDT_0_000_20_1"
do_fit "weight_tune_5_nocut_BDT_1_000_20_1"
do_fit "weight_tune_5_nocut_BDT_2_000_20_1"
do_fit "weight_tune_5_nocut_BDT_3_000_20_1"
do_fit "weight_tune_5_nocut_BDT_4_000_20_1"
do_fit "weight_tune_5_nocut_BDT_5_000_20_1"


### RUN 1 ###

do_fit(){
  bdt_name=$1

  source $fitter_path/setupFCC.sh
  cp $fitter_path/config_FCC/ttqgamma/ttgamma.config $workdir/.
  sed -i -e "s/%BDT_NAME%/$bdt_name/g" ttgamma.config

  #"OUTPUT/fcnc_may_05_tune_3_BDT_2_000/tua/Limits/tua.root"
  $fitter_path/myFit.exe hwldpa ttgamma.config
  
  root -l -b -q "../../get_trex_limit.C(\"OUTPUT/fcnc_may_05_$bdt_name/tua/Limits/tua.root\")"
}

do_fit "weight_tune_4_BDT_0_001"
exit

do_fit "weight_tune_4_BDT_1_001"
do_fit "weight_tune_4_BDT_2_001"
do_fit "weight_tune_4_BDT_3_001"
do_fit "weight_tune_4_BDT_4_001"
do_fit "weight_tune_4_BDT_5_001"








