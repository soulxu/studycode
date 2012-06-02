#include "Human.h"

#include <glib.h>

static void human_base_init(HumanClass *klass) {
	g_print(G_STRFUNC);
	g_print("\n");
}
static void human_base_finalize(HumanClass *klass) {
	g_print(G_STRFUNC);
	g_print("\n");
}

static GObject *human_constructor(GType type, guint n_construct_properties, GObjectConstructParam *construct_properties) {
	g_print(G_STRFUNC);
	g_print("\n");
	//g_print("typename: %s\n", g_type_name(type));
	Human *human = NULL;
	GObjectClass *parent_class = g_type_class_peek_parent(g_type_class_peek(HUMAN_TYPE));  //要用HUMAN_TYPE宏，参数的type是当前类的type，如果子类没有覆盖该方法，子类也会调用该constructor，因此type可能是子类，造成四循环
	human = HUMAN(G_OBJECT_CLASS(parent_class)->constructor(type, n_construct_properties, construct_properties)); //从父类返回GObject对象
	return G_OBJECT(human);
}

static void human_class_init(HumanClass *klass, gpointer class_data) {
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->constructor = human_constructor;
	g_print(G_STRFUNC);
	g_print("\n");
}
static void human_class_finalize(HumanClass *klass, gpointer class_data) {
	g_print(G_STRFUNC);
	g_print("\n");
}
static void human_init(Human *human) {
	g_print(G_STRFUNC);
	g_print("\n");
}
static void human_instance_init(Human *human) {
	g_print(G_STRFUNC);
	g_print("\n");
}

GType human_get_type(void) {
	static GType human_type = 0;

	if (!human_type) {
		static const GTypeInfo human_info = {
			sizeof(HumanClass),
			(GBaseInitFunc) human_base_init,
			(GBaseFinalizeFunc)human_base_finalize,
			(GClassInitFunc)human_class_init,
			NULL, //(GClassFinalizeFunc)human_class_finalize,
			NULL,
			sizeof(Human),
			0,
			(GInstanceInitFunc)human_instance_init,
			NULL
		};
		human_type = g_type_register_static(G_TYPE_OBJECT, "Human", &human_info, 0);

	}

	return human_type;
}

//G_DEFINE_TYPE(Human, human, G_TYPE_OBJECT);

Human *human_new(void) {
	Human *human;
	human = g_object_new(HUMAN_TYPE, NULL);
	
	return human;
}

