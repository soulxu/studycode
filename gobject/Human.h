#ifndef __HUMAN_H
#define __HUMAN_H

#include  <glib-object.h>

#define HUMAN_TYPE (human_get_type())
#define HUMAN(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),HUMAN_TYPE, Human))

typedef struct _Human Human;

typedef struct _HumanClass HumanClass;

struct _Human {
	GObject parent;
};

struct _HumanClass {
	GObjectClass parent_class;	
};

GType human_get_type(void);

Human *human_new(void);








#endif


