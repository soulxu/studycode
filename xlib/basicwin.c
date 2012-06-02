#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <limits.h>

#define DISPLAY_NAME ":2"

int errorHandler(Display *display, XErrorEvent *event) {
	fprintf(stderr, "error handler\n");
}

int IOErrorHandler(Display *display) {
	fprintf(stderr, "io error handler\n");
}

int main(int argc, char **argv) {
	Display *display = NULL;
	int screenNum = 0;
	Window win;
	XEvent event;

	XSetErrorHandler(errorHandler);
	XSetIOErrorHandler(IOErrorHandler);
	
	display = XOpenDisplay(DISPLAY_NAME);

	if (display == NULL) {
		fprintf(stderr, "Can not connect to X server.\n");
		exit(-1);
	}

	screenNum = DefaultScreen(display);

	printf("DefaultScreen: %d\n", screenNum);
	printf("ScreenCount: %d\n", ScreenCount(display));
	
	printf("DisplayWidth: %d\n", DisplayWidth(display, screenNum));
	printf("DisplayHeight: %d\n", DisplayHeight(display, screenNum));

	//create window
	win = XCreateSimpleWindow(display, RootWindow(display, screenNum), 
		0, 0, 
		400, 500, 
		10, 
		BlackPixel(display, screenNum), WhitePixel(display, screenNum));

	//load an x bitmap from file
	int picWidth = 0;
	int picHeight = 0;
	int xHot = 0;
	int yHot = 0;
	Pixmap pixmap;
/*	
	if (XReadBitmapFile(display, win, 
	                    "./test.xbm", 
	                    &picWidth, &picHeight, 
	                    &pixmap, 
	                    &xHot, &yHot) != BitmapSuccess) {
		fprintf(stderr, "can not load bitmap.\n");
		exit(1);
	}
*/

	// set XWMHints
	XWMHints *wmHints;
	wmHints = XAllocWMHints();
	wmHints->initial_state = NormalState;
	wmHints->input = True;
	wmHints->icon_pixmap = pixmap;
	wmHints->flags = StateHint | IconPixmapHint | InputHint;

	XSetWMHints(display, win, wmHints);

	// set ClassHint
	XClassHint *classHint = XAllocClassHint();
	classHint->res_name = "basicwin";
	classHint->res_class = "basicwin";
	XSetClassHint(display, win, classHint);
	
	//set all WM Properties. if not set pass NULL to arguments.
	Xutf8SetWMProperties(display, win, "basicwin", "basicwin_icon", argv, argc, NULL, NULL, NULL);

	XSetWindowBackgroundPixmap(display, win, ParentRelative);
	//specific which WM_PROTOCOLS will take part in.
	Atom wmProtocols = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, win, &wmProtocols, 1);

	XWindowAttributes attr;
	XGetWindowAttributes(display, win, &attr);

	printf("save under: %d\n", attr.save_under);
	
	XSelectInput(display, win, PropertyChangeMask | ExposureMask | StructureNotifyMask);
	XMapWindow(display, win);
	XFlush(display);
	
	while (1) {
		XNextEvent(display, &event);

		switch (event.type) {
		case Expose:
			printf("Expose event\n");
			XSetWindowBackgroundPixmap(display, win, ParentRelative);
			break;

		case ConfigureNotify:
			printf("ConfigureNotify event\n");
			XSetWindowBackgroundPixmap(display, win, ParentRelative);
			XFlush(display);
			break;
				
		case ClientMessage:
			printf("client event: %s\n", XGetAtomName(display, event.xclient.message_type));

			//process windows close. it's using WM_PROTOCOLS.
			if (event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False)) {
				XFreePixmap(display, pixmap);
				XCloseDisplay(display);
				exit(0);
			}

			break;
		}
	}

	XFreePixmap(display, pixmap);
	XCloseDisplay(display);
	
	return 0;
}
