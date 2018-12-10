export JAVA_HOME=/usr/lib/jvm/java-8-oracle
export JRE_HOME=/usr/lib/jvm/java-8-oracle/jre
export SPARK_HOME='/usr/local/software/spark/2.4'   
export PYTHONPATH=$SPARK_HOME/python:$PYTHONPATH   
export PYSPARK_DRIVER_PYTHON="jupyter"   
export PYSPARK_DRIVER_PYTHON_OPTS="notebook"   
export PYSPARK_PYTHON=python3   
export PATH=$SPARK_HOME:$PATH:$JAVA_HOME/bin:$JAVA_HOME/jre/bin
