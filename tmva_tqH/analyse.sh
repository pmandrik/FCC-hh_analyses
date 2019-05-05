

source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh
source /afs/cern.ch/sw/lcg/contrib/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh

if [ "$1" = "combo" ] || [ "$1" = "all" ]; then
  postfix_tmva="_000"
  #output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/OUTPUT/fcnc_may_05_noCUT"
  #output_samples_path="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/OUTPUT/fcnc_may_05"

  root -q -b -l "combo.C(\"BDT_0a\")"
  root -q -b -l "combo.C(\"BDT_2a\")"
  root -q -b -l "combo.C(\"BDT_4a\")"
  root -q -b -l "combo.C(\"BDT_0b\")"
  root -q -b -l "combo.C(\"BDT_2b\")"
  root -q -b -l "combo.C(\"BDT_4b\")"
  root -q -b -l "combo.C(\"BDT_0c\")"
  root -q -b -l "combo.C(\"BDT_2c\")"
  root -q -b -l "combo.C(\"BDT_4c\")"
  exit
fi
