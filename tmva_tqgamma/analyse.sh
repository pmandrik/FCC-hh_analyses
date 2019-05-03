#!/bin/bash

dir="fcnc_mar_7_full_2"
dir="fcnc_mar_08"
dir="fcnc_mar_18"
dir="fcnc_apr_03"
#dir="fcnc_may_05_noCUT"
dir="fcnc_may_05"
dir="fcnc_may_29"
input_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/"$dir
input_samples_path="/eos/user/p/pmandrik/fcc/heppy_OUTPUT_tqgamma_2/"$dir
output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/"$dir
output_tmva_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/"$dir"_tmva"
output_plots_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/"$dir"_plots"
output_plots_path_comp="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/"$dir"_plots_comp"
postfix="mar_7"
postfix="mar_08"
postfix="mar_18"
postfix="apr_03"
postfix="may_29"


source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh
source /afs/cern.ch/sw/lcg/contrib/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh

#export PATH=/afs/cern.ch/sw/lcg/external/Python/2.7.3/x86_64-slc6-gcc48-opt/bin:$PATH
#export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/Python/2.7.3/x86_64-slc6-gcc48-opt/lib:$LD_LIBRARY_PATH

if [ "$1" = "anal" ] || [ "$1" = "all" ]; then
  python -m cogapp.__main__ tmva_analyse.cog > tmva_analyse.C

  echo "we are here !!! "
  mkdir -p $output_samples_path
  root -q -b -l "tmva_analyse.C(\"$input_samples_path\", \"$output_samples_path\")"
fi

if [ "$1" = "anal2" ] || [ "$1" = "all" ]; then
  python -m cogapp.__main__ tmva_exra_anal.C > tmva_exra_anal_tmp.C

  echo "we are here !!! "
  mkdir -p $output_samples_path
  root -q -b -l "tmva_exra_anal_tmp.C(\"$input_samples_path\", \"$output_samples_path\")"
fi

if [ "$1" = "train" ] || [ "$1" = "all" ]; then
  mkdir -p $output_tmva_path
  root -q -b -l "tmva_train.C(\"$output_samples_path\", \"$output_tmva_path\", \"tune_5\", \"$postfix\")"
fi

if [ "$1" = "combo" ] || [ "$1" = "all" ]; then
  postfix_tmva="_000"
  #output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_05_noCUT"
  #output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_05"

  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_5\", \"BDT_3\", \"$postfix_tmva\")"
  exit

  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_0\", \"$postfix_tmva\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_1\", \"$postfix_tmva\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_2\", \"$postfix_tmva\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_3\", \"$postfix_tmva\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_4\", \"$postfix_tmva\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_5\", \"$postfix_tmva\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"tune_3\", \"BDT_6\", \"$postfix_tmva\")"
fi

if [ "$1" = "use" ] || [ "$1" = "all" ]; then
  python -m cogapp.__main__ tmva_hist_src.C > tmva_hist.C

  #output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_05_noCUT"
  #output_plots_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_05_noCUT_plots"
  #rm -rf $output_plots_path
  #mkdir -p $output_plots_path
  #root -q -b -l "tmva_hist.C(\"$output_samples_path\", \"$output_plots_path\")" &

  #output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_05"
  #output_plots_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_05_plots"
  rm -rf $output_plots_path
  mkdir -p $output_plots_path
  root -q -b -l "tmva_hist.C(\"$output_samples_path\", \"$output_plots_path\")"
fi

if [ "$1" = "split" ] || [ "$1" = "all" ]; then
  root -q -b -l "tmva_split.C(\"$output_samples_path\")"
fi





exit

if [ "$1" = "vars" ] || [ "$1" = "all" ]; then
  mkdir -p $output_samples_path

  if [ "$2" = "all" ]; then
    for i in $(seq 0 50); do 
      echo $i; 
      root -q -b -l "tmva_prepare.C(\"$input_samples_path\", \"$output_samples_path\", $i)" &
    done
    wait
  else
      root -q -b -l "tmva_prepare.C(\"$input_samples_path\", \"$output_samples_path\", $2)"
  fi
fi

if [ "$1" = "train" ] || [ "$1" = "all" ]; then
  mkdir -p $output_tmva_path
  if [ "$2" = "all" ]; then
    root -q -b -l "tmva_train.C(\"$output_samples_path\", \"$output_tmva_path\", \"b\", \"$postfix\")"
    root -q -b -l "tmva_train.C(\"$output_samples_path\", \"$output_tmva_path\", \"p\", \"$postfix\")"
    root -q -b -l "tmva_train.C(\"$output_samples_path\", \"$output_tmva_path\", \"k\", \"$postfix\")"
  else
    root -q -b -l "tmva_train.C(\"$output_samples_path\", \"$output_tmva_path\", \"$2\", \"$postfix\")"
  fi
fi

if [ "$1" = "combo" ] || [ "$1" = "all" ]; then
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"b\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"p\")"
  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"k\")"

  root -q -b -l "tmva_train.C(\"$output_samples_path\", \"$output_tmva_path\", \"f\", \"$postfix\")"

  root -q -b -l "tmva_combo.C(\"$output_samples_path\", \"weights\", \"$postfix\", \"f\")"
fi

if [ "$1" = "use" ] || [ "$1" = "all" ]; then
  rm -rf $output_plots_path
  mkdir -p $output_plots_path
  root -q -b -l "tmva_use.C(\"$output_samples_path\", \"$output_plots_path\")"
fi

if [ "$1" = "use2" ] || [ "$1" = "all" ]; then
  rm -rf $output_plots_path_comp
  mkdir -p $output_plots_path_comp
  root -q -b -l "tmva_use_comp.C(\"$output_samples_path\", \"$output_plots_path_comp\")"
fi








