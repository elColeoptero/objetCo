#ifndef H_CALLBACK
#define H_CALLBACK

#include <gtk/gtk.h>

void cb_quit (GtkWidget *, gpointer);
void cb_contenu (GtkWidget *, gpointer);
void cb_notes (GtkWidget *, gpointer);
void cb_recette (GtkWidget *, gpointer);
void cb_menu (GtkWidget *, GtkWidget *window);
void cb_ajout_produit (GtkWidget *p_widget, gpointer);
void cb_codebar(GtkWidget *p_widget, GtkWidget *box_codebar[3]);

#endif /* not H_CALLBACK */
