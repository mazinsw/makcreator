#ifndef UTILS_H
#define UTILS_H

#include <gtk/gtk.h>

GSList * gtk_open_file(GtkWindow *parent, const char *path, 
	const char *title, const char *description, int mimec, 
	const char * mimes[], gboolean select_multiple);
gboolean file_exists(const char * filename);
char * get_file_ext(char * filename);
char * get_file_name(char * filename);

#endif
