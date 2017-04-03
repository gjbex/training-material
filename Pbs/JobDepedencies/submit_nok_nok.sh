#!/bin/bash -l

job_id=`qsub fail.pbs`
if [ $? ]
then
    echo ${job_id}
    qsub -l depend=afternotok:${job_id} \
         -v after=${job_id},state=nok   \
         succeed.pbs
fi
