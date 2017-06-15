#!/bin/bash -l

job_id=`qsub fail.pbs`
if [ $? ]
then
    echo ${job_id}
    qsub -l depend=afterok:${job_id} \
         -v after=${job_id},state=ok   \
         succeed.pbs
fi
