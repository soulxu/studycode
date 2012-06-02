#! /usr/bin/python

import dbus
import dbus.service
import dbus.mainloop.glib
import gobject
import gtk

class Test(dbus.service.Object):
    def __init__(self, object_path, bus):
		self.bus = bus
		dbus.service.Object.__init__(self, bus, object_path)

    @dbus.service.method(dbus_interface='com.soulxu.test', out_signature='s', sender_keyword='sender')
    def private(self, sender=None):
		proxy = self.bus.get_object('org.freedesktop.PolicyKit', '/')
		iface = dbus.Interface(proxy, dbus_interface='org.freedesktop.PolicyKit')
		ret = iface.IsSystemBusNameAuthorized('com.soulxu.test.private', sender, True)
		return "yes"
		

    @dbus.service.method(dbus_interface='com.soulxu.test')
    def unprivate(self):
        print 'unprivate'

if __name__ == '__main__':
    loop = gobject.MainLoop()
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    system_bus = dbus.SystemBus()
    system_bus.request_name('com.soulxu.test')
    t = Test('/com/soulxu/test', system_bus)
    loop.run()

