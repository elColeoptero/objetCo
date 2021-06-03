#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdio.h>
#include <json-c/json.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "main.h"


int main (int argc, char **argv){
  gtk_init(&argc, &argv);
  GtkCssProvider* Provider = gtk_css_provider_new();
  GdkDisplay* Display = gdk_display_get_default();
  GdkScreen* Screen = gdk_display_get_default_screen(Display);

  gtk_style_context_add_provider_for_screen(Screen, GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "styles.css", NULL);
  GtkStyleContext *Context;
  afficherMenu();
  //afficherContenu();
  //afficherNotes();
}

void *time_thread_function(void *arg){
  while(1) {
  char tmp[255];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(tmp, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
  gtk_label_set_text(GTK_LABEL(date_heure), tmp);
  sleep(1);
  }
}

void *scan_thread_function(void *arg){
  while(1) {
    scanf("%s", codeBar);
    transformation(codeBar,codeBarTranslated);
    strcat(url,"curl -s https://world.openfoodfacts.org/api/v0/product/");
    strcat(url,codeBarTranslated);
    strcat(url,".json > file.json");
    printf("%s\n",url );
  }
}


List_product getProduits(){
  List_product l_produit;
  strcpy(l_produit.produits[0].id, "0");
  strcpy(l_produit.produits[0].quantity, "200");
  strcpy(l_produit.produits[0].outside, "0");
  strcpy(l_produit.produits[0].codebar, "10525");
  strcpy(l_produit.produits[0].name, "MNM");
  strcpy(l_produit.produits[0].brand, "KELLOGS");
  strcpy(l_produit.produits[0].date, "2020/05/17");
  strcpy(l_produit.produits[1].id, "1");
  strcpy(l_produit.produits[1].quantity, "200");
  strcpy(l_produit.produits[1].outside, "0");
  strcpy(l_produit.produits[1].codebar, "100525");
  strcpy(l_produit.produits[1].name, "Chips");
  strcpy(l_produit.produits[1].brand, "Lays");
  strcpy(l_produit.produits[1].date, "2020/06/17");
  l_produit.nb_produits = 2;
  return l_produit;
}

void afficherNotes(){
  pthread_t time_thread;
  list_note notes;
  
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *notes_label;
  GtkWidget *back;
  GtkWidget *line_header;
  GtkStyleContext *Context;

  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  header(p_main_box, p_window, "NOTES");

  notes = getNotes();

  for (int i = 0; i < notes.nb_list; i++){
    GtkWidget *note_tmp;
    GtkWidget *date_tmp;
    note_tmp = gtk_label_new(notes.list_note[i].texte);
    date_tmp = gtk_label_new(notes.list_note[i].date);

    Context = gtk_widget_get_style_context(date_tmp);
    gtk_style_context_add_class(Context, "Date_notes");
    gtk_grid_attach(GTK_GRID(p_main_box), date_tmp, 0 + 2*i, 2, 2, 1); 
    Context = gtk_widget_get_style_context(note_tmp);
    gtk_style_context_add_class(Context, "Texte_notes");
    gtk_grid_attach(GTK_GRID(p_main_box), note_tmp, 0 + 2*i, 3, 2, 3); 


  }


  /* Affichage de la fenetre principale */
  gtk_widget_set_size_request(p_window, 400, 300);
  gtk_window_fullscreen(GTK_WINDOW(p_window));
  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();

}

list_note getNotes(){
  list_note notes;
  strcpy(notes.list_note[0].texte, "Lorem ipsum inhzoei bniozecb \nvibvz vbozivb ievzeovzb\nve");
  strcpy(notes.list_note[0].date, "Lun 17th 2021");
  strcpy(notes.list_note[1].texte, "Lorem ipsum sdvsdvsdv vibvz \nvbozivb ievzeovzbve");
  strcpy(notes.list_note[1].date, "Lun 18th 2021");
  notes.nb_list = 2;
  return notes;
}

void afficherContenu(){
  char tmp[255];
  List_product produits;
  pthread_t time_thread;

  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *box = NULL;
  GtkWidget *tmp_label;
  GtkWidget *name;
  GtkWidget *brand;
  GtkWidget *date;
  GtkWidget *quantity;
  GtkWidget *outside;
  GtkWidget *back;
  GtkStyleContext *Context;
  
  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  header(p_main_box, p_window, "CONTENU");

  name = gtk_label_new("Nom du produit");
  gtk_widget_set_hexpand (name, TRUE);
  gtk_widget_set_halign (name, GTK_ALIGN_FILL);
  gtk_grid_attach (GTK_GRID (p_main_box), name, 0, 1, 1, 1);
  Context = gtk_widget_get_style_context(name);
  gtk_style_context_add_class(Context, "Item_tableau");

  brand = gtk_label_new("Marque");
  gtk_widget_set_hexpand (brand, TRUE);
  gtk_widget_set_halign (brand, GTK_ALIGN_FILL);
  gtk_grid_attach (GTK_GRID (p_main_box), brand, 1, 1, 1, 1);
  Context = gtk_widget_get_style_context(brand);
  gtk_style_context_add_class(Context, "Item_tableau");

  date = gtk_label_new("Date de péremption");
  gtk_widget_set_hexpand (date, TRUE);
  gtk_widget_set_halign (date, GTK_ALIGN_FILL);
  gtk_grid_attach (GTK_GRID (p_main_box), date, 2, 1, 1, 1);
  Context = gtk_widget_get_style_context(date);
  gtk_style_context_add_class(Context, "Item_tableau");

  quantity = gtk_label_new("Quantité");
  gtk_widget_set_hexpand (quantity, TRUE);
  gtk_widget_set_halign (quantity, GTK_ALIGN_FILL);
  gtk_grid_attach (GTK_GRID (p_main_box), quantity, 3, 1, 1, 1);
  Context = gtk_widget_get_style_context(quantity);
  gtk_style_context_add_class(Context, "Item_tableau");

  outside = gtk_label_new("Sorti");
  gtk_widget_set_hexpand (outside, TRUE);
  gtk_widget_set_halign (outside, GTK_ALIGN_FILL);
  gtk_grid_attach (GTK_GRID (p_main_box), outside, 4, 1, 1, 1);
  Context = gtk_widget_get_style_context(outside);
  gtk_style_context_add_class(Context, "Item_tableau");

  produits = getProduits();
  for (int i = 0; i < produits.nb_produits ; i++) {
    ajout_item_tableau(p_main_box, i + 2, 0, produits.produits[i].name);
    ajout_item_tableau(p_main_box, i + 2, 1, produits.produits[i].brand);
    ajout_item_tableau(p_main_box, i + 2, 2, produits.produits[i].date);
    ajout_item_tableau(p_main_box, i + 2, 3, produits.produits[i].quantity);
    ajout_item_tableau(p_main_box, i + 2, 4, produits.produits[i].outside);
    

  }

  gtk_window_fullscreen(GTK_WINDOW(p_window));
  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();

}

void ajout_item_tableau(GtkWidget * p_window, int row, int column, char * item_text){
    GtkWidget *tmp_label;
    GtkStyleContext *Context;
    tmp_label = gtk_label_new(item_text);
    gtk_widget_set_hexpand (tmp_label, TRUE);
    gtk_widget_set_halign (tmp_label, GTK_ALIGN_FILL);
    gtk_grid_attach (GTK_GRID (p_window), tmp_label, column, row, 1, 1);
    Context = gtk_widget_get_style_context(tmp_label);
    gtk_style_context_add_class(Context, "Item_tableau");
}



void afficherMenu(){
  char tmp[255];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(tmp, "%02d %02d %02d", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900);
  pthread_t time_thread;
  
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *label;

  date_heure = gtk_label_new("");
  GtkStyleContext *Context;
  
  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);


    /* Creation du bouton "Nom" */
  
  label = gtk_label_new(tmp);
  
  gtk_widget_set_hexpand (label, TRUE);
  gtk_widget_set_halign (label, GTK_ALIGN_FILL);
  Context = gtk_widget_get_style_context(label);
  gtk_style_context_add_class(Context, "Date");
  
  Context = gtk_widget_get_style_context(date_heure);
  gtk_style_context_add_class(Context, "Date");


  gtk_widget_set_hexpand (date_heure, TRUE);
  gtk_widget_set_halign (date_heure, GTK_ALIGN_FILL);

  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_label_set_justify(GTK_LABEL(date_heure), GTK_JUSTIFY_RIGHT);
  gtk_grid_attach (GTK_GRID (p_main_box), label, 3, 0, 3, 1);
  gtk_grid_attach(GTK_GRID(p_main_box), date_heure, 7, 0, 1, 1);
  pthread_create(&time_thread, NULL, time_thread_function, NULL);

  GtkWidget *p_button_contenu = NULL;

  p_button_contenu = gtk_button_new_with_label ("CONTENU DU FRIGO");
  Context = gtk_widget_get_style_context(p_button_contenu);
  
  gtk_widget_set_hexpand (p_button_contenu, TRUE);
  gtk_widget_set_halign (p_button_contenu, GTK_ALIGN_FILL);
  gtk_widget_set_vexpand (p_button_contenu, TRUE);
  gtk_widget_set_valign (p_button_contenu, GTK_ALIGN_CENTER);
  gtk_style_context_add_class(Context, "Button_menu");
  g_signal_connect (G_OBJECT (p_button_contenu), "clicked", G_CALLBACK (cb_contenu), NULL);
  gtk_grid_attach (GTK_GRID (p_main_box), p_button_contenu, 2, 1, 2, 1);

  GtkWidget *p_button_notes = NULL;

  p_button_notes = gtk_button_new_with_label ("NOTES");
  Context = gtk_widget_get_style_context(p_button_notes);
  
  gtk_widget_set_hexpand (p_button_notes, TRUE);
  gtk_widget_set_halign (p_button_notes, GTK_ALIGN_FILL);

  gtk_widget_set_vexpand (p_button_notes, TRUE);
  gtk_widget_set_valign (p_button_notes, GTK_ALIGN_CENTER);
  gtk_style_context_add_class(Context, "Button_menu");
  g_signal_connect (G_OBJECT (p_button_notes), "clicked", G_CALLBACK (cb_notes), NULL);
  gtk_grid_attach (GTK_GRID (p_main_box), p_button_notes, 4, 1, 2, 1);

  GtkWidget *p_button_recette = NULL;

  p_button_recette = gtk_button_new_with_label ("RECETTES");
  Context = gtk_widget_get_style_context(p_button_recette);
  
  gtk_widget_set_hexpand (p_button_recette, TRUE);
  gtk_widget_set_halign (p_button_recette, GTK_ALIGN_FILL);
  gtk_widget_set_vexpand (p_button_recette, TRUE);
  gtk_widget_set_valign (p_button_recette, GTK_ALIGN_CENTER);
  gtk_style_context_add_class(Context, "Button_menu");
  g_signal_connect (G_OBJECT (p_button_recette), "clicked", G_CALLBACK (cb_recette), NULL);
  gtk_grid_attach (GTK_GRID (p_main_box), p_button_recette, 6, 1, 2, 1);

  GtkWidget *p_button_ajout = NULL;

  p_button_ajout = gtk_button_new_with_label ("AJOUT DE PRODUITS");
  Context = gtk_widget_get_style_context(p_button_ajout);
  
  gtk_widget_set_hexpand (p_button_ajout, TRUE);
  gtk_widget_set_halign (p_button_ajout, GTK_ALIGN_FILL);

  gtk_widget_set_vexpand (p_button_ajout, TRUE);
  gtk_widget_set_valign (p_button_ajout, GTK_ALIGN_CENTER);
  gtk_style_context_add_class(Context, "Button_menu");
  g_signal_connect (G_OBJECT (p_button_ajout), "clicked", G_CALLBACK (cb_ajout_produit), NULL);
  gtk_grid_attach (GTK_GRID (p_main_box), p_button_ajout, 8, 1, 2, 1);

  
  /* Affichage de la fenetre principale */
  gtk_widget_set_size_request(p_window, 400, 300);
  gtk_window_fullscreen(GTK_WINDOW(p_window));
  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();

}



void afficherAjout(){
  pthread_t time_thread, scan_thread;
  list_note notes;
  
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  /* Initialisation de GTK+ */

  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  header(p_main_box, p_window, "AJOUT DE PRODUITS");
    
  /* Affichage de la fenetre principale */
  gtk_widget_set_size_request(p_window, 400, 300);
  gtk_window_fullscreen(GTK_WINDOW(p_window));
  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
}

void header(GtkWidget *p_main_box, GtkWidget *p_window, char title[20]){
  GtkWidget *title_widget;
  GtkWidget *back;
  GtkWidget *line_header;
  GtkStyleContext *Context;
  pthread_t time_thread;

  date_heure = gtk_label_new("");
  Context = gtk_widget_get_style_context(date_heure);
  gtk_style_context_add_class(Context, "Date");
  gtk_grid_attach(GTK_GRID(p_main_box), date_heure, 4, 0, 1, 1);
  pthread_create(&time_thread, NULL, time_thread_function, NULL);

  title_widget = gtk_label_new(title);
  Context = gtk_widget_get_style_context(title_widget);
  gtk_style_context_add_class(Context, "Date");
  gtk_widget_set_hexpand (title_widget, TRUE);
  gtk_widget_set_halign (title_widget, GTK_ALIGN_FILL);
  gtk_grid_attach(GTK_GRID(p_main_box), title_widget, 2, 0, 1, 1);

  back = gtk_button_new_with_label("Retour");
  g_signal_connect (G_OBJECT (back), "clicked", G_CALLBACK (cb_menu), NULL);
  gtk_grid_attach (GTK_GRID (p_main_box), back, 0, 0, 1, 1);

  line_header = gtk_label_new("");
  gtk_widget_set_hexpand (line_header, TRUE);
  gtk_widget_set_halign (line_header, GTK_ALIGN_FILL);
  Context = gtk_widget_get_style_context(line_header);
  gtk_style_context_add_class(Context, "UpperLine");
  gtk_grid_attach(GTK_GRID(p_main_box), line_header, 0, 1, 6, 1);
}

void afficherProduit()
{
  char codeBar[MAX_SIZE];
  char codeBarTranslated[MAX_SIZE];
  char url[100],urlImage[1000]="";
  scanf("%s", codeBar);
  transformation(codeBar,codeBarTranslated);
  strcat(url,"curl -s https://world.openfoodfacts.org/api/v0/product/");
  strcat(url,codeBarTranslated);
  strcat(url,".json > file.json");
  printf("%s\n",url );

  system(url);
  

  FILE *fp;
  char buffer[50000];
  struct json_object *parsed_json;
  struct json_object *name;
  struct json_object *age;
  struct json_object *status;
  struct json_object *friend;
  struct json_object *image_front_url;
  size_t n_friends;

  size_t i; 

  fp = fopen("file.json","r");
  fread(buffer, 50000, 1, fp);
  fclose(fp);


  parsed_json = json_tokener_parse(buffer);
  json_object_object_get_ex(parsed_json, "status", &status);
  printf("Statut : %d\n", json_object_get_int(status));
  if (json_object_get_int(status)==0){
    printf("Produit introuvable\n");}
  else {
  json_object_object_get_ex(parsed_json, "product", &name);
  json_object_object_get_ex(name, "product_name_fr", &age);
  json_object_object_get_ex(name, "image_url", &image_front_url);
  
  strcpy(urlImage,"curl -s ");
  strcat(urlImage,json_object_get_string(image_front_url));
  strcat(urlImage," >img.jpg");
  system(urlImage);
  printf("Nom : %s\n", json_object_get_string(age));
  printf("Lien Image : %s\n",urlImage);
  }
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;

  /* Initialisation de GTK+ */


  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

 

    /* Creation du bouton "Nom" */
  {
    GtkWidget *label;
  label = gtk_label_new(json_object_get_string(age));

  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  //gtk_container_add(GTK_CONTAINER(window), label);
  gtk_box_pack_start (GTK_BOX (p_main_box), label, FALSE, FALSE, 0);
  }
  {
    GError *error = NULL;
  GdkPixbuf *pix = gdk_pixbuf_new_from_file ("img.jpg", &error);
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

    p_button = gtk_button_new_with_label ("quitter");
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_main_box), p_button, FALSE, FALSE, 0);
  }
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
}

char* transformation(char* codeBar, char* codeBarTranslated)
{
  // TODO : refactor 
  for (int i = 0; i < strlen(codeBar); ++i)
  {
    switch(codeBar[i]){

      case 38: strcat(codeBarTranslated,"1");break;
      case 34: strcat(codeBarTranslated,"3");break;
      case 39: strcat(codeBarTranslated,"4");break;
      case 40: strcat(codeBarTranslated,"5");break;
      case 45: strcat(codeBarTranslated,"6");break;
      case 95: strcat(codeBarTranslated,"8");break;
      case -61 : 
        switch (codeBar[++i]){
          case -87 : strcat(codeBarTranslated,"2");break;
          case -88 : strcat(codeBarTranslated,"7");break;
          case -89 : strcat(codeBarTranslated,"9");break;
          case -96 : strcat(codeBarTranslated,"0");break;
        }     
    }
  }
  return codeBarTranslated;

}
