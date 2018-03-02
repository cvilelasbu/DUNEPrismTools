#!/bin/bash

FILE=~/pbs_header_4_hr

if [ ! -d "$1" ]; then
  mkdir /home/calcuttj/DUNEPrismSim/RHC/$1
  echo "Made directory /home/calcuttj/DUNEPrismSim/RHC/$1/"
  mkdir RHC/$1
  echo "Made directory RHC/$1/"
fi
 
cat RHC_box_input.list | while read line 
do
  echo $line
  string=$line
  IFS='.'
  array=( $string )
  run=$(echo ${array[0]}.${array[1]})
  IFS=''
  echo $run

  OUTFILE=RHC/$1/dpa.RHC.${array[0]}.${array[1]}.pbs

  cat $FILE > $OUTFILE  
  echo \#PBS -l file=20gb >> ${OUTFILE}
  echo \#PBS -N ${run}_condenser >> ${OUTFILE} 
  echo DATAPATH=/mnt/research/NuInt/Dune_Flux/OptimizedEngineeredSept2017Review/gevgen_fnal/rootracker/RHC >> ${OUTFILE}
  
  echo $(ls /mnt/research/NuInt/Dune_Flux/OptimizedEngineeredSept2017Review/gevgen_fnal/rootracker/RHC/*${array[0]}.${array[1]}.root)
  echo CODE=$(ls /mnt/research/NuInt/Dune_Flux/OptimizedEngineeredSept2017Review/gevgen_fnal/rootracker/RHC/*${array[0]}.${array[1]}.root) >> ${OUTFILE}

  echo XMLPATH=/mnt/research/NuInt/DUNEPrismTools/jake-contrib/${2} >> ${OUTFILE}
  echo PYEXEC=/mnt/research/NuInt/argon_box_repo/argon_box/argon_box_genie.py >> ${OUTFILE}

  echo source /mnt/research/NuInt/argon_box_repo/argon_box/setup.sh 4.10.00.p04 64 >> ${OUTFILE}
  echo export PATH=/mnt/research/NuInt/DUNEPrismTools/jake-contrib/:\$PATH >> ${OUTFILE}
  echo export PATH=/mnt/research/NuInt/DUNEPrismTools/Linux/bin:\$PATH >> ${OUTFILE}
  echo module load GNU/4.9 >> ${OUTFILE}

#  echo PYOUTPUT=${run}.\*.argon_box.root >> ${OUTFILE}
  echo PYOUTPUT=/mnt/scratch/calcuttj/DunePrism/RHC/${3}/${line} >>${OUTFILE}
  echo cp \$\{PYOUTPUT\} \$TMPDIR >> ${OUTFILE}
  echo cd \$TMPDIR >> ${OUTFILE}
  

#  echo python \$PYEXEC --nevents=0 --source=$line --output=\$\{PYOUTPUT\} --enable_edepsim --detX=19.5 --detY=1.5 --detZ=2.5 --shift=1800 >> ${OUTFILE}


  echo dp_DunePrismCondenser -i \$\{PYOUTPUT\} -o ${run}.\$\{PBS_JOBID\}.DPA.root -c \$\{CODE\} -x \$\{XMLPATH\} -n -1 >> ${OUTFILE}
 
  echo cp ${run}.\$\{PBS_JOBID\}.DPA.root ~/DUNEPrismSim/RHC/$1/ >> ${OUTFILE}

 
done