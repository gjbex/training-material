#!/usr/bin/env python

import cmd


class HelloShell(cmd.Cmd):
    intro = 'Welcome to the HelloShell, type ? to see a list of commands'
    prompt = 'hello> '

    def __init__(self):
        '''constructor'''
        super().__init__()
        self._people = set()

    def do_hi(self, args):
        '''say hi'''
        if args in self._people:
            print('already said hi to {0}'.format(args))
        else:
            self._people.add(args)
            print('hi {0}'.format(args))

    def do_bye(self, args):
        '''say bye'''
        if args in self._people:
            self._people.remove(args)
            print('bye {0}'.format(args))
        else:
            print('never said hi to {0}'.format(args))

    def do_show_friends(self, args):
        '''show all current friends'''
        if self._people:
            print('all friends: {0}'.format(', '.join(self._people)))
        else:
            print('lonely, no friends')

    def do_quit(self, args):
        '''quit the HelloShell'''
        print('thanks for coming by')
        return True

if __name__ == '__main__':
    HelloShell().cmdloop()
