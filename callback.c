#include "callback.h"
#include "main.h"

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

void cb_menu (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();
  afficherMenu();

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
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

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

void cb_ajout_produit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();
  afficherAjout();

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}