#!/bin/bash -l

job_id=`qsub fail.pbs`
if [ $? ]
then
    echo ${job_id}
    qsub -W depend=afterok:${job_id} \
         -v after=${job_id},state=ok   \
         succeed.pbs
fi
