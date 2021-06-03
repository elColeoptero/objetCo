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
#include <X11/Xlib.h>
#include "main.h"
#include "bdd.h"


int main (int argc, char **argv){
  XInitThreads();
  gtk_init(&argc, &argv);
  GtkCssProvider* Provider = gtk_css_provider_new();
  GdkDisplay* Display = gdk_display_get_default();
  GdkScreen* Screen = gdk_display_get_default_screen(Display);

  gtk_style_context_add_provider_for_screen(Screen, GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "styles.css", NULL);
  afficherMenu();
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
  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  header(p_main_box, p_window, "NOTES");

  notes = retrieveNotes();

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

  produits = retrieveProducts();
  for (int i = 0; i < produits.nb_produits ; i++) {
    ajout_item_tableau(p_main_box, i + 2, 0, produits.produits[i].name);
    ajout_item_tableau(p_main_box, i + 2, 1, produits.produits[i].brand);
    ajout_item_tableau(p_main_box, i + 2, 2, produits.produits[i].date);
    ajout_item_tableau(p_main_box, i + 2, 3, produits.produits[i].quantity);
    ajout_item_tableau(p_main_box, i + 2, 4, produits.produits[i].outside);
    

  }
  gtk_window_set_destroy_with_parent(GTK_WINDOW(p_window), false);
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
  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
  
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
  gtk_window_set_destroy_with_parent(GTK_WINDOW(p_window), false);
  gtk_window_fullscreen(GTK_WINDOW(p_window));
  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();

}

void refresh_produit(GtkWidget * widget[3]){
  
    char tmp[255];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(tmp, "%02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mday, tm.tm_mon);
    FILE *fp;
    char buffer[5000000], codeBar[MAX_SIZE], codeBarTranslated[MAX_SIZE], url[200], urlImage[MAX_SIZE];
    struct json_object *parsed_json;
    struct json_object *produit_json;
    struct json_object *brand;
    struct json_object *status;
    struct json_object *quantity;
    struct json_object *image_front_url;
    struct json_object *name;
    size_t n_friends;
    Product produit;

    fflush(stdin);
    fflush(stdout);
    strcpy(codeBar, gtk_entry_get_text(widget[1]));
    gtk_entry_set_text(widget[1], "");
    transformation(codeBar,codeBarTranslated);
    strcpy(url, "");
    strcat(url,"curl -s https://world.openfoodfacts.org/api/v0/product/");
    strcat(url,codeBarTranslated);
    strcat(url,".json > file.json");
    printf("%s\n",url );

    system(url);
    fp = fopen("file.json","r");
    fread(buffer, 5000000, 1, fp);
    fclose(fp);


    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "status", &status);
    if (json_object_get_int(status)==0){
      printf("Produit introuvable\n");}
    else {
    json_object_object_get_ex(parsed_json, "product", &produit_json);
    json_object_object_get_ex(produit_json, "product_name_fr", &name);
    json_object_object_get_ex(produit_json, "image_url", &image_front_url);
    json_object_object_get_ex(produit_json, "brands", &brand);
    json_object_object_get_ex(produit_json, "product_quantity", &quantity);

    strcpy(produit.brand, json_object_get_string(brand));
    strcpy(produit.name, json_object_get_string(name));
    strcpy(produit.codebar, codeBarTranslated);
    strcpy(produit.quantity, json_object_get_string(quantity));
    strcpy(produit.date, tmp);
    strcpy(produit.outside, "0");
    
    strcpy(urlImage,"curl -s ");
    strcat(urlImage,json_object_get_string(image_front_url));
    strcat(urlImage," >img.jpg");
    system(urlImage);


    gtk_label_set_text(GTK_LABEL(widget[2]), json_object_get_string(name));
    
    GError *error = NULL;
    GdkPixbuf *pix = gdk_pixbuf_new_from_file ("img.jpg", &error);
    if (pix == NULL) {
        g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }
    
    gtk_image_set_from_pixbuf (widget[3], pix);
    insertProduct(produit);
    
    }
}


void afficherAjout(){
  pthread_t time_thread;
  pid_t mon_pid;
  list_note notes;

  GtkWidget *p_window = NULL;
  
  GtkWidget *box_codebar[3];
  /* Initialisation de GTK+ */

  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  /* Creation du conteneur principal */
  box_codebar[0] = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), box_codebar[0]);

  header(box_codebar[0], p_window, "AJOUT DE PRODUITS");

  box_codebar[2] = gtk_label_new("");
  gtk_label_set_justify(GTK_LABEL(box_codebar[2]), GTK_JUSTIFY_CENTER);
  gtk_grid_attach (GTK_GRID (box_codebar[0]), box_codebar[2], 1, 2, 1, 1);

  box_codebar[3]  = gtk_image_new ();
  gtk_grid_attach(GTK_GRID (box_codebar[0]), box_codebar[3], 1, 3, 1, 1);
  
  box_codebar[1] = gtk_entry_new();
  g_signal_connect (G_OBJECT (box_codebar[1]), "activate", G_CALLBACK (cb_codebar), box_codebar);
  gtk_grid_attach(GTK_GRID(box_codebar[0]), box_codebar[1], 2, 1, 1, 1);
  

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
  g_signal_connect (G_OBJECT (back), "clicked", G_CALLBACK (cb_menu), p_window);
  gtk_grid_attach (GTK_GRID (p_main_box), back, 0, 0, 1, 1);

  line_header = gtk_label_new("");
  gtk_widget_set_hexpand (line_header, TRUE);
  gtk_widget_set_halign (line_header, GTK_ALIGN_FILL);
  Context = gtk_widget_get_style_context(line_header);
  gtk_style_context_add_class(Context, "UpperLine");
  gtk_grid_attach(GTK_GRID(p_main_box), line_header, 0, 1, 6, 1);
}

char* transformation(char* codeBar, char* codeBarTranslated)
{
  // TODO : refactor 
  strcpy(codeBarTranslated, "");
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
