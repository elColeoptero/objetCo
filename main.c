#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"

int main (int argc, char **argv)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;

  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);

  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

 

    /* Creation du bouton "Nom" */
  {
    GtkWidget *label;
  label = gtk_label_new("NOM PRODUIT");

  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  //gtk_container_add(GTK_CONTAINER(window), label);
  gtk_box_pack_start (GTK_BOX (p_main_box), label, FALSE, FALSE, 0);
  }
  {
    GError *error = NULL;
  GdkPixbuf *pix = gdk_pixbuf_new_from_file ("Tomato.png", &error);
  if (pix == NULL) {
      g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
      g_error_free (error);
      exit (1);
  }

  GtkWidget *image = gtk_image_new_from_pixbuf (pix);
   gtk_box_pack_start (GTK_BOX (p_main_box), image, FALSE, FALSE, 0);
  }

   /* Creation du bouton "Quitter" */
  {
    GtkWidget *p_button = NULL;

    p_button = gtk_button_new_from_stock (GTK_STOCK_QUIT);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_main_box), p_button, FALSE, FALSE, 0);
  }
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
