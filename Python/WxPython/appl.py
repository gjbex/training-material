#!/usr/bin/env python

from ConfigParser import ConfigParser
import paramiko
import wx

class Appl(wx.Frame):

    def __init__(self, cfg, title='appl.py'):
        super(Appl, self).__init__(None, title=title, size=(260, 180))
        self.initUI()
        self.initSSH(cfg)
        self.Show(True)

    def initUI(self):
        menubar = wx.MenuBar()
        self.SetMenuBar(menubar)
        fileMenu = wx.Menu()
        menubar.Append(fileMenu, '&File')
        fileItem = fileMenu.Append(wx.ID_EXIT, 'Quit', 'Quit application')
        self.Bind(wx.EVT_MENU, self.OnQuit, fileItem)
        # self.text = wx.TextCtrl(self, style=wx.TE_MULTILINE|wx.TE_READONLY)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.list = wx.ListCtrl(self)
        self.sizer.Add(self.list)
        self.list.InsertColumn(0, 'User ID')
        self.list.InsertColumn(1, 'Name')

    def OnQuit(self, evt):
        self.Close()

    def initTimer(self, interval=5000):
        self.timer = wx.Timer(self)
        self.timer.Start(interval)
        self.Bind(wx.EVT_TIMER, self.retrieveUsers)

    def initSSH(self, cfg):
        self.ssh = paramiko.SSHClient()
        self.ssh.load_system_host_keys()
        self.ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.ssh.connect(cfg.get('host', 'name'),
                username=cfg.get('host', 'username')

    def retrieveUsers(self, evt):
        cmd = "/usr/bin/w | /usr/bin/cut -f 1 -d ' ' | /usr/bin/grep -v USER | /usr/bin/sort -u | /usr/bin/grep '[a-z]'"
        stdin, stdout, stderr = self.ssh.exec_command(cmd)
        # self.text.Clear()
        # self.text.WriteText(''.join(stdout.readlines()))
        for line in stdout.readlines():
            self.list.Append((line.strip(), '10'))

def main():
    cfg = ConfigParser()
    cfg.read('confix.txt')
    app = wx.App()
    Appl(cfg)
    app.MainLoop()

if __name__ == '__main__':
    main()

