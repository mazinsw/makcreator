#include "utils.h"
#include <string.h>
#include <stdlib.h>

GSList * gtk_open_file(GtkWindow *parent, const char *path, 
	const char *title, const char *description, int mimec, 
	const char * mimes[], gboolean select_multiple)
{
	GtkWidget *fs;
	GSList *files;
	GtkFileFilter *filter;
	int response;
	
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter, description);
	int i;
	for(i = 0; i < mimec; i++)
	{
		gtk_file_filter_add_mime_type (filter, mimes[i]);
	}
	g_object_ref_sink (filter);
	
	fs = gtk_file_chooser_dialog_new (title,
			parent,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_ADD, GTK_RESPONSE_ACCEPT,
			NULL);
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (fs), filter);

	gtk_dialog_set_default_response (GTK_DIALOG(fs), GTK_RESPONSE_ACCEPT);
	gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER(fs), select_multiple);
	gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER(fs), FALSE);
	
	if (path != NULL) 
	{
		if (!gtk_file_chooser_set_current_folder
			(GTK_FILE_CHOOSER (fs), path))
		{
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(fs),
				g_get_home_dir());
		}
	}
	else
	{
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(fs),
			g_get_home_dir());		
	}
	
	response = gtk_dialog_run(GTK_DIALOG(fs));

	if (response != GTK_RESPONSE_ACCEPT) {
		gtk_widget_destroy(fs);
		return NULL;
	}

	files = gtk_file_chooser_get_uris(GTK_FILE_CHOOSER(fs));
	if (files == NULL) {
		gtk_widget_destroy(fs);
		return NULL;
	}

	g_object_unref(filter);
	gtk_widget_destroy(fs);
	
	return files;
}

gboolean file_exists(const char * filename)
{
	GFile *file = g_file_new_for_uri (
		g_filename_to_uri(filename, NULL, NULL));
	if (file != NULL) {
		if (g_file_query_exists(file, NULL)) {
			g_object_unref(file);
			return TRUE;
		}
		g_object_unref(file);
	}
	return FALSE;
}

char * get_file_ext(char * filename)
{
	int i;
	char * ext = "";
	int count = 0;
	for(i = strlen(filename); i != 0; i--)
	{
		count++;
		if(filename[i] == '/')
		{
			break;
		}
		if(filename[i] == '.')
		{
			ext = (char *) malloc(sizeof(char)*(count + 1));
			strncpy(ext, filename + i, count);
			break;
		}
	}	
	return ext;
}

char * get_file_name(char * filename)
{
	int i;
	char * name;
	int count = 0;
	for(i = strlen(filename); i >= 0; i--)
	{
		count++;
		if((filename[i] == '/') || (i == 0))
		{
			name = (char *) malloc(sizeof(char)*(count));
			strncpy(name, filename + (i==0?0:i + 1), count);
			break;
		}
	}	
	return name;
}

