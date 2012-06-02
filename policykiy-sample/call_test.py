import dbus
import os

if __name__ == '__main__':
    try:
        bus = dbus.SystemBus()
        proxy = bus.get_object('com.soulxu.test', '/com/soulxu/test')
        test = dbus.Interface(proxy, dbus_interface='com.soulxu.test')
        ret = test.private()
        print ret
        if ret != 'yes':
            auth = dbus.SessionBus().get_object('org.freedesktop.PolicyKit.AuthenticationAgent', '/')
            authiface = dbus.Interface(auth, 'org.freedesktop.PolicyKit.AuthenticationAgent')
            ret = authiface.ObtainAuthorization('com.soulxu.test.private', 0, os.getpid())
            if ret:
                print 'auth success'
                ret = test.private()
                print ret
            else:
                print 'auth fail'
    except dbus.exceptions.DBusException, e:
        print 'exception %s' % e
