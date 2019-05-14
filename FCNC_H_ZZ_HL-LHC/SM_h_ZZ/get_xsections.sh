 
set +x

SEED=10
NEVENTS=10000
PROCESS=bs_ZZ_4l
mg_dir=/home/me/ihep/soft/MG5_aMC_v2_6_3_2
mg_dir=/home/pmandrik/soft/MG5_aMC_v2_6_3_2
run_tag=tag_$PROCESS
PTHEAVY=0

sdir=`pwd`
wdir=$run_tag
#rm -rf $wdir;
mkdir -p $wdir; cd $wdir

echo $sdir

if [ "$1" == "run" ] ; then
  python $sdir/make_card.py

  for card in match_*txt; do # associated_*txt 
    echo $card
    $mg_dir/bin/mg5_aMC $card
    PROCESS="${card%.*}"

    cp $sdir/run_card_TEMPLATE_matching.dat $PROCESS/Cards/run_card.dat
    sed -i 's/%SEED%/'$SEED'/g' $PROCESS/Cards/run_card.dat
    sed -i 's/%NEVENTS%/'$NEVENTS'/g' $PROCESS/Cards/run_card.dat
    sed -i 's/%PTHEAVY%/'$PTHEAVY'/g' $PROCESS/Cards/run_card.dat

    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/lhapdf6/lib/
    LHAPDFCONFIG="/home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/lhapdf6/bin/lhapdf-config"
    echo "lhapdf = $LHAPDFCONFIG" >> $PROCESS/Cards/me5_configuration.txt
    echo "run_mode = 2" >> $PROCESS/Cards/me5_configuration.txt
    echo "nb_core = 3"  >> $PROCESS/Cards/me5_configuration.txt
    echo "automatic_html_opening = False"  >> $PROCESS/Cards/me5_configuration.txt
    echo "cluster_local_path = `${LHAPDFCONFIG} --datadir`"  >> $PROCESS/Cards/me5_configuration.txt
    
    echo "EVENTS GENERATION ++++++++++++++++++++++++++++++++"
    cp $sdir/delphes_card_CMS_4l.tcl $PROCESS/Cards/delphes_card.dat
    cp $sdir/pythia8_card_matching.dat $PROCESS/Cards/pythia8_card.dat
    
    ls -lat $PROCESS/Cards/
    ./$PROCESS/bin/generate_events $run_tag -f
    ls -lat $PROCESS/Cards/

    #rm -rf $out_dir/$PROCESS/SubProcesses
    #rm -rf $out_dir/$PROCESS/lib
  done
fi






















































