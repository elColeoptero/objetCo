#include "callback.h"
#include "main.h"

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

void cb_menu (GtkWidget *p_widget, GtkWidget *window)
{
  gtk_widget_destroy(window);
  /* Parametres inutilises */
}


void cb_contenu (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();
  afficherContenu();
  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

void cb_notes (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();
  afficherNotes();
  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

void cb_recette (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();
  afficherRecette();
  (void)p_widget;
  (void)user_data;
}

void cb_ajout_produit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();
  afficherAjout();

  (void)p_widget;
  (void)user_data;
}

void cb_codebar(GtkWidget *p_widget, GtkWidget *box_codebar[3]) {
  refresh_produit(box_codebar);
}

void cb_codebar_out(GtkWidget *p_widget, GtkWidget *entry_codebar_out) {
  printf("Retrait du produit");
  retrait_produit(entry_codebar_out);
}

void quitter(GtkWidget *p_widget, GtkWidget *window) {
  gtk_widget_destroy(window);
}

