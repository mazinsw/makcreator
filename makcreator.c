#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prop.h"
#include "config.h"
#include "utils.h"
#include "about.h"
#include "images.h"

void gtk_menu_item_set_icon(GtkWidget *item, const char * xpm[])
{
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), 
		gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_xpm_data(xpm)));
	gtk_image_menu_item_set_always_show_image(
		GTK_IMAGE_MENU_ITEM(item), TRUE);
}
//common events
void btrem_clicked(GtkWidget *widget, gpointer sender);
void btadd_clicked(GtkWidget *widget, gpointer sender);
//menu file events
void new_item_clicked(GtkWidget *widget, gpointer sender);
void open_item_clicked(GtkWidget *widget, gpointer sender);
void save_item_clicked(GtkWidget *widget, gpointer sender);
void saveas_item_clicked(GtkWidget *widget, gpointer sender);
void close_item_clicked(GtkWidget *widget, gpointer sender);
//menu project events
void run_item_clicked(GtkWidget *widget, gpointer sender);
void build_item_clicked(GtkWidget *widget, gpointer sender);
void prop_item_clicked(GtkWidget *widget, gpointer sender);
//menu configuration events
void opt_item_clicked(GtkWidget *widget, gpointer sender);
//menu help events
void about_item_clicked(GtkWidget *widget, gpointer sender);
void chks_rbtn_clicked(GtkWidget *widget, gpointer sender);
void on_drag_data_received(GtkWidget *wgt, GdkDragContext *context, 
	int x, int y, GtkSelectionData *seldata, guint info, guint time,
	gpointer userdata);
void tree_files_senection_changed(GtkWidget *widget, gpointer sender);
int mfcreator_onclose(GtkWidget *widget, gpointer sender);

GtkWidget *mfcreator;
GtkAccelGroup *accel_group;
GtkWidget *menubar;
//menu file
GtkWidget *file_menu;
GtkWidget *file_item;

GtkWidget *new_item;
GtkWidget *open_item;
GtkWidget *save_item;
GtkWidget *saveas_item;
GtkWidget *file_sep;
GtkWidget *close_item;
//menu project
GtkWidget *prjc_menu;
GtkWidget *prjc_item;

GtkWidget *add_item;
GtkWidget *rem_item;
GtkWidget *prjc_sep1;
GtkWidget *run_item;
GtkWidget *build_item;
GtkWidget *prjc_sep2;
GtkWidget *prop_item;

//menu configuration
GtkWidget *cfg_menu;
GtkWidget *cfg_item;
GtkWidget *opt_item; 

//menu help
GtkWidget *hlp_menu;
GtkWidget *hlp_item;
GtkWidget *about_item;

GtkWidget *vbox;
GtkWidget *painel;
GtkWidget *btadd;
GtkWidget *img_btadd;
GtkWidget *btrem;
GtkWidget *img_btrem;

GtkWidget *frm_apptype;
GtkWidget *vbox_apptype;
GtkWidget *opt_cons;
GtkWidget *opt_gtk;
GtkWidget *opt_sdl;

GtkWidget *frm_proglang;
GtkWidget *vbox_proglang;
GtkWidget *opt_c;
GtkWidget *opt_cpp;

GtkWidget *frm_optm;
GtkWidget *vbox_optm;
GtkWidget *chk_minsz;
GtkWidget *chk_showw;
GtkWidget *chk_optsp;

GtkWidget *tree_files;
GtkWidget *tree_scroll;
GtkTreeStore *treestore;
GtkWidget *statusbar;
GtkTreeSelection *tree_selection;
GtkTreeViewColumn *column;
GtkCellRenderer *text_renderer;
GtkCellRenderer *icon_renderer;
GdkPixbuf * folder_pxb;
GdkPixbuf * c_pxb;
GdkPixbuf * cpp_pxb;
GdkPixbuf * h_pxb;
GdkPixbuf * o_pxb;
	
enum
{
    PIXBUF_COLUMN,
    NAME_COLUMN,
    FILENAME_COLUMN,
    NUM_COLUMNS
};
const char * mimes[] = {"text/x-csrc", "text/x-chdr", "text/x-c++src",
	"application/x-object"};
const char * mimemfc[] = {"application/mfc"};

static GtkTargetEntry drag_types[] = {{ "text/uri-list", 0, 0}};

int main(int argc, char *args[])
{

	gtk_init(&argc, &args);
	mfcreator = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mfcreator), "Makefile Creator");
	gtk_widget_set_size_request(mfcreator, 506, 362);
	gtk_window_set_resizable(GTK_WINDOW(mfcreator), FALSE);
	gtk_window_set_position(GTK_WINDOW(mfcreator), GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(mfcreator), 
		gdk_pixbuf_new_from_xpm_data(icone_xpm));
	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(mfcreator), accel_group);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(mfcreator), vbox);
	painel = gtk_fixed_new();
	
	menubar = gtk_menu_bar_new();
	//menu file
	file_menu = gtk_menu_new();
	file_item = gtk_menu_item_new_with_mnemonic("_File");
	
	new_item = gtk_image_menu_item_new_with_mnemonic("_New");
	gtk_menu_item_set_icon(new_item, new_xpm);
	gtk_widget_add_accelerator(new_item, "activate", accel_group,
		GDK_N, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	open_item = gtk_image_menu_item_new_with_mnemonic("_Open...");
	gtk_menu_item_set_icon(open_item, open_xpm);
	gtk_widget_add_accelerator(open_item, "activate", accel_group,
		GDK_A, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	save_item = gtk_image_menu_item_new_with_mnemonic("_Save");
	gtk_menu_item_set_icon(save_item, save_xpm);
	gtk_widget_add_accelerator(save_item, "activate", accel_group,
		GDK_S, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	saveas_item = gtk_image_menu_item_new_with_mnemonic("S_ave as...");
	gtk_menu_item_set_icon(saveas_item, saveas_xpm);
	gtk_widget_add_accelerator(saveas_item, "activate", accel_group,
		GDK_S, (GdkModifierType)(GDK_CONTROL_MASK| GDK_SHIFT_MASK), 
		GTK_ACCEL_VISIBLE);
	file_sep = gtk_separator_menu_item_new();
	close_item = gtk_image_menu_item_new_with_mnemonic("_Close");
	gtk_menu_item_set_icon(close_item, exit_xpm);
	gtk_widget_add_accelerator(close_item, "activate", accel_group,
		GDK_Q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), saveas_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);
	
	//menu project
	prjc_menu = gtk_menu_new();
	prjc_item = gtk_menu_item_new_with_mnemonic("_Project");
	
	add_item = gtk_image_menu_item_new_with_mnemonic("_Add");
	gtk_menu_item_set_icon(add_item, add_xpm);
	gtk_widget_add_accelerator(add_item, "activate", accel_group,
		GDK_Insert, (GdkModifierType)0, GTK_ACCEL_VISIBLE);
	rem_item = gtk_image_menu_item_new_with_mnemonic("_Remove");
	gtk_menu_item_set_icon(rem_item, remove_xpm);
	gtk_widget_add_accelerator(rem_item, "activate", accel_group,
		GDK_Delete, (GdkModifierType)0, GTK_ACCEL_VISIBLE);
	gtk_widget_set_sensitive(rem_item, FALSE);
	prjc_sep1 = gtk_separator_menu_item_new();
	run_item = gtk_image_menu_item_new_with_mnemonic("R_un");
	gtk_menu_item_set_icon(run_item, run_xpm);
	gtk_widget_add_accelerator(run_item, "activate", accel_group,
		GDK_F5, (GdkModifierType)0, GTK_ACCEL_VISIBLE);
	build_item = gtk_image_menu_item_new_with_mnemonic("_Build");
	gtk_menu_item_set_icon(build_item, build_xpm);
	gtk_widget_add_accelerator(build_item, "activate", accel_group,
		GDK_F9, (GdkModifierType)0, GTK_ACCEL_VISIBLE);
	prjc_sep2 = gtk_separator_menu_item_new();
	prop_item = gtk_image_menu_item_new_with_mnemonic("_Properties...");
	gtk_menu_item_set_icon(prop_item, prop_xpm);
	gtk_widget_add_accelerator(prop_item, "activate", accel_group,
		GDK_Return, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(prjc_item), prjc_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), add_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), rem_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), prjc_sep1);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), run_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), build_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), prjc_sep2);
	gtk_menu_shell_append(GTK_MENU_SHELL(prjc_menu), prop_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), prjc_item);
	
	//menu configuration
	cfg_menu = gtk_menu_new();
	cfg_item = gtk_menu_item_new_with_mnemonic("_Configuration");
	
	opt_item = gtk_image_menu_item_new_with_mnemonic("_Options...");
	gtk_menu_item_set_icon(opt_item, opt_xpm);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(cfg_item), cfg_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(cfg_menu), opt_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), cfg_item);
	
	//menu help
	hlp_menu = gtk_menu_new();
	hlp_item = gtk_menu_item_new_with_mnemonic("_Help");
	
	about_item = gtk_image_menu_item_new_with_mnemonic("_About...");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(hlp_item), hlp_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(hlp_menu), about_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), hlp_item);
	//end menus
	
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(vbox), painel);
	
	//button Add
	btadd = gtk_button_new_with_label("Add");
	gtk_widget_set_size_request(btadd, 82, 28);
	gtk_fixed_put(GTK_FIXED(painel), btadd, 335, 3);
	img_btadd = gtk_image_new_from_pixbuf(
		gdk_pixbuf_new_from_xpm_data(add_xpm));
	gtk_button_set_image(GTK_BUTTON(btadd), img_btadd);
	gtk_widget_show(img_btadd);
	
	//Button Remove
	btrem = gtk_button_new_with_label("Remove");
	gtk_widget_set_size_request(btrem, 82, 28);
	gtk_fixed_put(GTK_FIXED(painel), btrem, 420, 3);
	img_btrem = gtk_image_new_from_pixbuf(
		gdk_pixbuf_new_from_xpm_data(remove_xpm));
	gtk_button_set_image(GTK_BUTTON(btrem), img_btrem);
	gtk_widget_set_sensitive(btrem, FALSE);
	gtk_widget_show(img_btrem);
	
	frm_apptype = gtk_frame_new("Application Type");
	gtk_widget_set_size_request(frm_apptype, 167, 102);
	gtk_fixed_put(GTK_FIXED(painel), frm_apptype, 335, 32);
	
	vbox_apptype = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frm_apptype), vbox_apptype);
	
	opt_cons = gtk_radio_button_new_with_label(NULL, 
		"Console application");
	gtk_box_pack_start(GTK_BOX(vbox_apptype), opt_cons, FALSE, 
		FALSE, 3);
	opt_gtk = gtk_radio_button_new_with_label_from_widget(
		GTK_RADIO_BUTTON(opt_cons), "GTK+ application");
	gtk_box_pack_start(GTK_BOX(vbox_apptype), opt_gtk, FALSE, FALSE, 3);
	opt_sdl = gtk_radio_button_new_with_label_from_widget(
		GTK_RADIO_BUTTON(opt_gtk), "SDL application");
	gtk_box_pack_start(GTK_BOX(vbox_apptype), opt_sdl, FALSE, FALSE, 3);

	frm_proglang = gtk_frame_new("Programing language");
	gtk_widget_set_size_request(frm_proglang, 167, 73);
	gtk_fixed_put(GTK_FIXED(painel), frm_proglang, 335, 135);
	
	vbox_proglang = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frm_proglang), vbox_proglang);
	
	opt_c = gtk_radio_button_new_with_label(NULL, "C");
	gtk_box_pack_start(GTK_BOX(vbox_proglang), opt_c, FALSE, FALSE, 3);
	opt_cpp = gtk_radio_button_new_with_label_from_widget(
		GTK_RADIO_BUTTON(opt_c), "C++");
	gtk_box_pack_start(GTK_BOX(vbox_proglang), opt_cpp, FALSE, 
		FALSE, 3);
	
	frm_optm = gtk_frame_new("Optmizations");
	gtk_widget_set_size_request(frm_optm, 167, 102);
	gtk_fixed_put(GTK_FIXED(painel), frm_optm, 335, 208);
	
	vbox_optm = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frm_optm), vbox_optm);
	
	chk_minsz = gtk_check_button_new_with_label("Minimize size");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk_minsz), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox_optm), chk_minsz, FALSE, FALSE, 3);
	chk_showw = gtk_check_button_new_with_label("Show warnings");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk_showw), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox_optm), chk_showw, FALSE, FALSE, 3);
	chk_optsp = gtk_check_button_new_with_label("Optimize speed");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk_optsp), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox_optm), chk_optsp, FALSE, FALSE, 3);
		
		
	//icons treview
	folder_pxb = gdk_pixbuf_new_from_xpm_data(folder_xpm);
	c_pxb = gdk_pixbuf_new_from_xpm_data(c_xpm);
	cpp_pxb = gdk_pixbuf_new_from_xpm_data(cpp_xpm);
	h_pxb = gdk_pixbuf_new_from_xpm_data(h_xpm);
	o_pxb = gdk_pixbuf_new_from_xpm_data(o_xpm);
	
	tree_scroll = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(tree_scroll),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_fixed_put(GTK_FIXED(painel), tree_scroll, 3, 3);
	
	//tree view
	tree_files = gtk_tree_view_new();
	gtk_widget_set_size_request(tree_files, 328, 305);
	gtk_container_add(GTK_CONTAINER(tree_scroll), tree_files);
	gtk_drag_dest_set(tree_files, GTK_DEST_DEFAULT_ALL, drag_types,
		G_N_ELEMENTS(drag_types), GDK_ACTION_COPY|GDK_ACTION_MOVE|
		GDK_ACTION_LINK);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_files), FALSE);
	tree_selection = 
		gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_files));
	treestore = gtk_tree_store_new(NUM_COLUMNS, GDK_TYPE_PIXBUF, 
		G_TYPE_STRING, G_TYPE_POINTER);
	gtk_tree_view_set_model (GTK_TREE_VIEW(tree_files), 
		GTK_TREE_MODEL(treestore));
	text_renderer = gtk_cell_renderer_text_new();
	icon_renderer = gtk_cell_renderer_pixbuf_new();
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(column, icon_renderer, FALSE);
  	gtk_tree_view_column_set_attributes(column, icon_renderer, "pixbuf",
		PIXBUF_COLUMN, NULL);
  	gtk_tree_view_column_pack_start(column, text_renderer, TRUE);
  	gtk_tree_view_column_set_attributes(column, text_renderer, "text", 
		NAME_COLUMN, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_files), column);
	
	//status bar			   
	statusbar = gtk_statusbar_new();
	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);
		
	g_signal_connect(btadd, "clicked",
		G_CALLBACK(btadd_clicked), NULL);
	g_signal_connect(btrem, "clicked",
		G_CALLBACK(btrem_clicked), NULL);
	g_signal_connect(new_item, "activate",
		G_CALLBACK(new_item_clicked), NULL);
	g_signal_connect(open_item, "activate",
		G_CALLBACK(open_item_clicked), NULL);
	g_signal_connect(save_item, "activate",
		G_CALLBACK(save_item_clicked), NULL);
	g_signal_connect(saveas_item, "activate",
		G_CALLBACK(saveas_item_clicked), NULL);
	g_signal_connect(close_item, "activate",
		G_CALLBACK(close_item_clicked), NULL);
	g_signal_connect(add_item, "activate",
		G_CALLBACK(btadd_clicked), NULL);
	g_signal_connect(rem_item, "activate",
		G_CALLBACK(btrem_clicked), NULL);
	g_signal_connect(run_item, "activate",
		G_CALLBACK(run_item_clicked), NULL);
	g_signal_connect(build_item, "activate",
		G_CALLBACK(build_item_clicked), NULL);
	g_signal_connect(prop_item, "activate",
		G_CALLBACK(prop_item_clicked), NULL);
	g_signal_connect(opt_item, "activate",
		G_CALLBACK(opt_item_clicked), NULL);
	g_signal_connect(about_item, "activate",
		G_CALLBACK(about_item_clicked), NULL);
	g_signal_connect(opt_cons, "toggled",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(opt_gtk, "toggled",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(opt_sdl, "toggled",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(opt_c, "clicked",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(opt_cpp, "clicked",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(chk_minsz, "clicked",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(chk_showw, "clicked",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(chk_optsp, "clicked",
		G_CALLBACK(chks_rbtn_clicked), NULL);
	g_signal_connect(tree_files, "drag_data_received",
		G_CALLBACK(on_drag_data_received), NULL);
	g_signal_connect (G_OBJECT(tree_selection), "changed",
		G_CALLBACK(tree_files_senection_changed), tree_files);
		    
	g_signal_connect(G_OBJECT(mfcreator), "delete_event",
		G_CALLBACK(mfcreator_onclose), NULL);
	g_signal_connect_swapped(G_OBJECT(mfcreator), "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
				
	gtk_widget_show_all(mfcreator);
	
	gtk_main();
	
	return 0;
}


void btrem_clicked(GtkWidget *widget, gpointer sender)
{
	GtkTreeIter iter;
	if (gtk_tree_selection_get_selected(tree_selection, NULL, &iter))
	{
		gtk_tree_store_remove (treestore, &iter);
		//gtk_tree_selection_select_iter(tree_selection, &iter);
	}
}

GtkTreeIter get_tree_folder_by_name(char * name)
{
	GtkTreeIter temp;
	if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL(treestore), &temp)) 
	{
		do 
		{
			char * name_temp;

            gtk_tree_model_get (GTK_TREE_MODEL(treestore), &temp, 
				NAME_COLUMN, &name_temp, -1);
            if (name_temp != NULL && !strcmp(name_temp, name)) 
            {
				return temp;
			}
		} while (gtk_tree_model_iter_next (GTK_TREE_MODEL(treestore), &temp));
	}

	gtk_tree_store_append(treestore, &temp, NULL);
	gtk_tree_store_set(treestore, &temp, NAME_COLUMN, name, 
		PIXBUF_COLUMN, folder_pxb, -1);
	return temp;
}

gboolean get_tree_iter_exist(GtkTreeIter parent, char * filename)
{
	/*GtkTreeIter temp;
	temp = gtk_tree_iter_first(GTK_TREE_MODEL(treestore), &parent, NULL);
	if (temp != NULL) 
	{
		do 
		{
			char * name_temp;

            gtk_tree_model_get (GTK_TREE_MODEL(treestore), &temp, 
				FILENAME_COLUMN, &name_temp, -1);
			printf("%s\n", name_temp);
            if (name_temp != NULL && !strcmp(name_temp, filename)) 
            {
				return TRUE;
			}
		} while ((temp = gtk_tree_iter_first(GTK_TREE_MODEL(treestore), 
			&parent)) != NULL);
	}*/
	return FALSE;
}

void addfiles(char * filename)
{
	GtkTreeIter folder_iter;
	GtkTreeIter temp;
	char * ext = get_file_ext(filename);
	GdkPixbuf * icon;
	
	if(!strcmp(".c", ext))
	{
		folder_iter = get_tree_folder_by_name("Sources");
		icon = c_pxb;
	}
	else if(!strcmp(".cc", ext))
	{
		folder_iter = get_tree_folder_by_name("Sources");
		icon = cpp_pxb;
	}
	else if(!strcmp(".cpp", ext))
	{
		folder_iter = get_tree_folder_by_name("Sources");
		icon = cpp_pxb;
	}
	else if(!strcmp(".h", ext))
	{
		folder_iter = get_tree_folder_by_name("Headers");
		icon = h_pxb;
	} 
	else if(!strcmp(".o", ext))
	{
		folder_iter = get_tree_folder_by_name("Objects");
		icon = o_pxb;
	}
	
	gtk_tree_store_append(treestore, &temp, &folder_iter);
	gtk_tree_store_set(treestore, &temp, NAME_COLUMN, 
		get_file_name(filename), PIXBUF_COLUMN,	icon, FILENAME_COLUMN,
		filename, -1);
}

void btadd_clicked(GtkWidget *widget, gpointer sender)
{
	GSList * files;

	files = gtk_open_file(GTK_WINDOW(mfcreator), NULL, "Open Files",
		"C/C++ files", 4, mimes, TRUE);
	if(files != NULL)
	{
		GSList *l;
		for (l = files ; files != NULL; files = files->next)
		{
			char *data = files->data;
			if (data == NULL)
				continue;
			addfiles(g_filename_from_uri(data, NULL, NULL));
		}
	};
}

void new_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("new_item_clicked\n");
}

void open_item_clicked(GtkWidget *widget, gpointer sender)
{
	GSList * files;

	files = gtk_open_file(GTK_WINDOW(mfcreator), NULL, "Open File",
		"Makefile Creator", 1, mimemfc, FALSE);
	if(files != NULL)
	{
		GSList *l;
		for (l = files ; files != NULL; files = files->next)
		{
			char *data = files->data;
			if (data == NULL)
				continue;
			printf("Project: %s\n", g_filename_from_uri(data, NULL, NULL));
		}
	};
}

void save_item_clicked(GtkWidget *widget, gpointer sender)
{
	
}

void saveas_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("saveas_item_clicked\n");
}

void close_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("close_item_clicked\n");
}

void run_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("run_item_clicked\n");
}

void build_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("build_item_clicked\n");
}

void prop_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("prop_item_clicked\n");
}

void opt_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("opt_item_clicked\n");
}

void about_item_clicked(GtkWidget *widget, gpointer sender)
{
	printf("about_item_clicked\n");
}

void chks_rbtn_clicked(GtkWidget *widget, gpointer sender)
{
	printf("chks_optm_clicked\n");
}

void tree_files_senection_changed(GtkWidget *widget, gpointer sender)
{
	GtkTreeIter iter;
	
	if (gtk_tree_selection_get_selected(tree_selection, NULL, &iter))
	{
		gtk_widget_set_sensitive(btrem, TRUE);
		gtk_widget_set_sensitive(rem_item, TRUE);
		GtkTreeIter parent;
		char * name_temp;
		if (gtk_tree_model_iter_parent(GTK_TREE_MODEL(treestore), 
			&parent, &iter))
		{
			gtk_tree_model_get (GTK_TREE_MODEL(treestore), &iter, 
					FILENAME_COLUMN, &name_temp, -1);
		}
		else
		{
			gtk_tree_model_get (GTK_TREE_MODEL(treestore), &iter, 
					NAME_COLUMN, &name_temp, -1);
		}
		
		gtk_statusbar_push(GTK_STATUSBAR(statusbar),
			gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
			name_temp), name_temp);
	}
	else
	{
		gtk_widget_set_sensitive(btrem, FALSE);
		gtk_widget_set_sensitive(rem_item, FALSE);
	}
}

void on_drag_data_received(GtkWidget *wgt, GdkDragContext *context, 
	int x, int y, GtkSelectionData *seldata, guint info, guint time,
	gpointer userdata)
{
	char **list;
	int i;

	list = g_uri_list_extract_uris ((const char *) seldata->data);

	for (i = 0; list[i] != NULL; i++) 
	{
		char * filename = g_filename_from_uri(list[i], NULL, NULL);
		char * ext = get_file_ext(filename);
		if( !strcmp(ext, ".c") || !strcmp(ext, ".cc")||
			!strcmp(ext, ".cpp") || !strcmp(ext, ".h") ||
			!strcmp(ext, ".o"))
		{
			addfiles(filename);
		}
		else if(!strcmp(ext, ".mfc"))
		{
			printf("open project direct\n");
		}
	}
	g_strfreev(list);
}

int mfcreator_onclose(GtkWidget *widget, gpointer sender)
{
	printf("mfcreator_onclose\n");
	return 0;//close
}
