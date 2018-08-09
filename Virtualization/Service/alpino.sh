#!/bin/sh
### BEGIN INIT INFO
# Provides:          alpino
# Required-Start:    $local_fs
# Required-Stop:     $local_fs
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# X-Interactive:     false
# Short-Description: Start and stop Alpino server
# Description:       Start/stop Alpino server
### END INIT INFO

DESC="Alpino server"
NAME=alpino
#DAEMON=

do_start()
{
    echo "starting apino server..."
    alpino_server_port=$(cat /conf/port_nr)
    nohup /Alpino/bin/Alpino \
        -notk -veryfast user_max=20000  server_kind=parse  \
        server_port="${alpino_server_port}" -init_dict_p \
        batch_command=alpino_server \
        assume_input_is_tokenized=off \
        > /dev/null < /dev/null &

}

do_stop()
{
   echo "Stopping alpino server"
}


case "$1" in
   start)
     do_start
     ;;
   stop)
     do_stop
     ;;
esac

exit 0
