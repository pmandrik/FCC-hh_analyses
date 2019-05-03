
condor_script="""
executable            = batchScript_htcondor.sh
arguments             = $(ClusterID) $(ProcId)
output                = hello.$(ClusterId).$(ProcId).out
error                 = hello.$(ClusterId).$(ProcId).err
log                   = hello.$(ClusterId).log

+JobFlavour = "workday"

queue
"""

print condor_script

