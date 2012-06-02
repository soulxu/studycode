#ifndef __BOY_H
#define __BOY_H

#include  <glib-object.h>
#include "Human.h"

#define BOY_TYPE (boy_get_type())
#define BOY(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),BOY_TYPE, Boy))

typedef struct _Boy Boy;

typedef struct _BoyClass BoyClass;

struct _Boy {
	Human parent;
	gint age;
};

struct _BoyClass {
	HumanClass parent_class;	
};

GType boy_get_type(void);

Boy *boy_new(void);








#endif


