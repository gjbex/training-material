#!/usr/bin/env python

from argparse import ArgumentParser
import paramiko
import sys


def connect(host, user):
    ssh = paramiko.SSHClient()
    ssh.load_system_host_keys()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(host, username=user)
    return ssh

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='do ls on remote server')
    arg_parser.add_argument('--host', required=True,
                            help='host name to connect to')
    arg_parser.add_argument('--user', required=True,
                            help='user name to connect as')
    arg_parser.add_argument('dir', nargs='?',
                            help='directory to list')
    options = arg_parser.parse_args()
    ssh = connect(options.host, options.user)
    cmd = 'ls -l'
    if options.dir:
        cmd += ' ' + options.dir
    _, stdout, stderr = ssh.exec_command(cmd)
    for line in stdout:
        print(line.rstrip())
    for line in stderr:
        print(line.rstrip(), file=sys.stderr)
    ssh.close()
