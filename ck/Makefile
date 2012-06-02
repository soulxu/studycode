CFLAGS += `pkg-config --libs dbus-1 ck-connector`
LDFLAGS += `pkg-config --cflags dbus-1 ck-connector`

ck: main.c
	$(CC) main.c -o ck $(CFLAGS) $(LDFLAGS)
