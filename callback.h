#ifndef H_CALLBACK
#define H_CALLBACK

#include <gtk/gtk.h>

void cb_quit (GtkWidget *, gpointer);
void cb_contenu (GtkWidget *, gpointer);
void cb_notes (GtkWidget *, gpointer);
void cb_recette (GtkWidget *, gpointer);
void cb_menu (GtkWidget *, gpointer);
void cb_ajout_produit (GtkWidget *p_widget, gpointer user_data);

#endif /* not H_CALLBACK */
