#!/usr/bin/env python

import paramiko
import time
import sys
import wx
import wx.lib.mixins.listctrl as listmix

class AutoWidthListCtrl(wx.ListCtrl, listmix.ListCtrlAutoWidthMixin):
    def __init__(self, parent, ID, pos=wx.DefaultPosition, size=wx.DefaultSize, style=0):
        wx.ListCtrl.__init__(self, parent, ID, pos, size, style)
        listmix.ListCtrlAutoWidthMixin.__init__(self)


class Appl(wx.Frame, listmix.ColumnSorterMixin):

    def __init__(self, title='appl.py'):
        super(Appl, self).__init__(None, title=title, size=(260, 180))
        self.initUI()
        self.initTimer()
        self.Show(True)

    def initUI(self):
        self.InitMenubar()
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.total = wx.StaticText(self, -1, "Total:")
        self.sizer.Add(self.total, 0, wx.EXPAND)
        self.SetSizer(self.sizer)
        self.list = AutoWidthListCtrl(self, -1, style=wx.LC_REPORT|wx.LC_SORT_ASCENDING)
        self.sizer.AddSpacer(10)
        self.sizer.Add(self.list, 0, wx.EXPAND)
        self.list.InsertColumn(0, 'User ID', width=100)
        self.list.InsertColumn(1, 'Name', width=100)
        self.RetrieveData()
        self.list.SetColumnWidth(0, wx.LIST_AUTOSIZE)
        self.list.SetColumnWidth(1, wx.LIST_AUTOSIZE)
        listmix.ColumnSorterMixin.__init__(self, 2)

    def OnQuit(self, evt):
        self.Close()

    def GetListCtrl(self):
        return self.list

    def InitMenubar(self):
        menubar = wx.MenuBar()
        self.SetMenuBar(menubar)
        fileMenu = wx.Menu()
        menubar.Append(fileMenu, '&File')
        fileItem = fileMenu.Append(wx.ID_EXIT, 'Quit', 'Quit application')
        self.Bind(wx.EVT_MENU, self.OnQuit, fileItem)

    def initTimer(self, interval=3000):
        self.timer = wx.Timer(self)
        self.timer.Start(interval)
        self.Bind(wx.EVT_TIMER, self.RetrieveData)

    def RetrieveData(self, evt=None):
        if evt is not None:
            self.list.DeleteAllItems()
            print "cleared"
        self.itemDataMap = {0:('vsc30140', 'gjb'), 1:('vsc30032', 'other')}
        for key, user in self.itemDataMap.items():
            idx = self.list.InsertStringItem(sys.maxint, user[0])
            self.list.SetStringItem(idx, 1, user[1])
            self.list.SetItemData(idx, key)
        self.total.SetLabel('Total: {0}'.format(int(len(self.itemDataMap))))
        


def main():
    app = wx.App()
    Appl()
    app.MainLoop()

if __name__ == '__main__':
    main()

