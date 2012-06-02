#include "Boy.h"

#include <glib.h>
static void boy_base_init(BoyClass *klass) {
	g_print(G_STRFUNC);
	g_print("\n");
}
static void boy_base_finalize(BoyClass *klass) {
	g_print(G_STRFUNC);
	g_print("\n");
}

static GObject *boy_constructor(GType type, guint n_construct_properties, GObjectConstructParam *construct_properties) {
	g_print(G_STRFUNC);
	g_print("\n");
	//g_print("typename: %s\n", g_type_name(type));
	Boy *boy = NULL;
	GObjectClass *parent_class = g_type_class_peek_parent(g_type_class_peek(BOY_TYPE));  //要用HUMAN_TYPE宏，参数的type是当前类的type，如果子类没有覆盖该方法，子类也会调用该constructor，因此type可能是子类，造成四循环
	boy = BOY(G_OBJECT_CLASS(parent_class)->constructor(type, n_construct_properties, construct_properties)); //从父类返回GObject对象
	return G_OBJECT(boy);
}

static void boy_class_init(BoyClass *klass, gpointer class_data) {
	g_print(G_STRFUNC);
	g_print("\n");
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->constructor = boy_constructor;
}
static void boy_class_finalize(BoyClass *klass, gpointer class_data) {
	g_print(G_STRFUNC);
	g_print("\n");
	
}
static void boy_init(Boy *boy) {
	g_print(G_STRFUNC);
	g_print("\n");
}
static void boy_instance_init(Boy *boy) {
	g_print(G_STRFUNC);
	g_print("\n");
}


GType boy_get_type(void) {
	static GType boy_type = 0;

	if (!boy_type) {
		static const GTypeInfo boy_info = {
			sizeof(BoyClass),
			(GBaseInitFunc) boy_base_init,
			(GBaseFinalizeFunc)boy_base_finalize,
			(GClassInitFunc)boy_class_init,
			NULL, //(GClassFinalizeFunc)human_class_finalize,
			NULL,
			sizeof(Boy),
			0,
			(GInstanceInitFunc)boy_instance_init,
			NULL
		};
		boy_type = g_type_register_static(HUMAN_TYPE, "Boy", &boy_info, 0);

	}

	return boy_type;
}

//G_DEFINE_TYPE(Boy, boy, G_TYPE_OBJECT);

Boy *boy_new(void) {
	Boy *boy;
	boy = g_object_new(BOY_TYPE, NULL);
	return boy;
}

