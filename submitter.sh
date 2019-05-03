
src_dir=`pwd`

total_folders=0
good_folders=0
for file in *_Chunk*; do
  cd $src_dir; cd $file
  total_folders=$((total_folders+1))
  if [ -d "heppy.FCChhAnalyses.FCChh.FCNC_h.TreeProducer.TreeProducer_1" ]
  then
      echo $file "+";   
      good_folders=$((good_folders+1))
      continue
  fi
  echo $file "-";   
done

echo $good_folders"/"$total_folders
exit

cd $src_dir
for file in *_Chunk*; do
  cd $src_dir
  echo $file

  cd $file
  
  LS_SUBCWD=`pwd`
  HEPPY="/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/"

  cp batchScript.sh batchScript_htcondor.sh
  sed -i 's+$LS_SUBCWD+'$LS_SUBCWD'+g' batchScript_htcondor.sh
  sed -i 's+$HEPPY+'$HEPPY'+g' batchScript_htcondor.sh
  sed -i 's+`find . -type d | grep /`+'$file'+g' batchScript_htcondor.sh
  
  if [ -d "heppy.FCChhAnalyses.FCChh.FCNC_h.TreeProducer.TreeProducer_1" ]
  then
      echo "skip folder ... "
      continue
  fi

  python $src_dir/submitter.py > condor_job.txt
  condor_submit condor_job.txt
  sleep 0.1
done





