#!/usr/bin/env python

from argparse import ArgumentParser
import ssh
import sys


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='do wc on remote server')
    arg_parser.add_argument('--host', required=True,
                            help='host name to connect to')
    arg_parser.add_argument('--user', required=True,
                            help='user name to connect as')
    arg_parser.add_argument('file_name', help='file to do word count on')
    options = arg_parser.parse_args()
    ssh = ssh.connect(options.host, options.user)
    cmd = 'wc -'
    stdin, stdout, stderr = ssh.exec_command(cmd)
    with open(options.file_name) as input_file:
        for line in input_file:
            stdin.write(line)
        stdin.flush()
        stdin.channel.shutdown_write()
    for line in stdout:
        print(line.rstrip())
    for line in stderr:
        print(line.rstrip(), file=sys.stderr)
    ssh.close()
