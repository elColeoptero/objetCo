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
  while(GTK_IS_LABEL(date_heure)) {
  char tmp[255];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(tmp, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
  gtk_label_set_text(date_heure, tmp);
  sleep(1);
  }
}

void *time_thread_menu_function(void *arg){
  while(GTK_IS_LABEL(date_heure_menu)) {
  char tmp[255];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(tmp, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
  gtk_label_set_text(date_heure_menu, tmp);
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

void cb_suppression_produit(GtkWidget *p_widget, char id[10]) {
  gtk_widget_destroy(p_window_contenu);
  printf("On supprime : %s\n", id);
  suppression_produit(id);
  afficherContenu();
}

void afficherContenu(){
  char tmp[255];
  List_product produits;
  pthread_t time_thread;

  GtkWidget *p_main_box = NULL;
  GtkWidget *box = NULL;
  GtkWidget *tmp_label;
  GtkWidget *name;
  GtkWidget *brand;
  GtkWidget *date;
  GtkWidget *quantity;
  GtkWidget *outside;
  GtkWidget *back;
  GtkWidget *supprimer;
  GtkStyleContext *Context;
  
  /* Creation de la fenetre principale de notre application */
  p_window_contenu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window_contenu), p_main_box);

  header(p_main_box, p_window_contenu, "CONTENU");

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

  supprimer = gtk_label_new("Supprimer");
  gtk_widget_set_hexpand (supprimer, TRUE);
  gtk_widget_set_halign (supprimer, GTK_ALIGN_FILL);
  gtk_grid_attach (GTK_GRID (p_main_box), supprimer, 5, 1, 1, 1);
  Context = gtk_widget_get_style_context(supprimer);
  gtk_style_context_add_class(Context, "Item_tableau");

  produits = retrieveProducts();
  for (int i = 0; i < produits.nb_produits ; i++) {
    ajout_item_tableau(p_main_box, i + 2, 0, produits.produits[i].name);
    ajout_item_tableau(p_main_box, i + 2, 1, produits.produits[i].brand);
    ajout_item_tableau(p_main_box, i + 2, 2, produits.produits[i].date);
    ajout_item_tableau(p_main_box, i + 2, 3, produits.produits[i].quantity);
    ajout_item_tableau(p_main_box, i + 2, 4, produits.produits[i].outside);

    GtkWidget *tmp_label;
    GtkStyleContext *Context;
    tmp_label = gtk_button_new_with_label("X");
    gtk_widget_set_hexpand (tmp_label, TRUE);
    gtk_widget_set_halign (tmp_label, GTK_ALIGN_FILL);
    g_signal_connect (G_OBJECT (tmp_label), "clicked", G_CALLBACK (cb_suppression_produit), produits.produits[i].id);
    gtk_grid_attach (GTK_GRID (p_main_box), tmp_label, 5, i+2, 1, 1);
    Context = gtk_widget_get_style_context(tmp_label);
    gtk_style_context_add_class(Context, "Suppr_button");

  }
  gtk_window_set_destroy_with_parent(GTK_WINDOW(p_window_contenu), false);
  gtk_window_fullscreen(GTK_WINDOW(p_window_contenu));
  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
  gtk_widget_modify_bg(p_window_contenu, GTK_STATE_NORMAL, &grey);
  gtk_widget_show_all (p_window_contenu);
  /* Lancement de la boucle principale */
  gtk_main();

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
  

  date_heure_menu = gtk_label_new("");
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
  
  Context = gtk_widget_get_style_context(date_heure_menu);
  gtk_style_context_add_class(Context, "Date");

  GtkWidget *entry_codebar = gtk_entry_new();
  g_signal_connect (G_OBJECT (entry_codebar), "activate", G_CALLBACK (cb_codebar_out), entry_codebar);
  gtk_grid_attach(GTK_GRID(p_main_box), entry_codebar, 7, 2, 1, 1);
  gtk_widget_hide(entry_codebar);
  gtk_widget_grab_focus(entry_codebar);

  gtk_widget_set_hexpand (date_heure_menu, TRUE);
  gtk_widget_set_halign (date_heure_menu, GTK_ALIGN_FILL);

  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_label_set_justify(GTK_LABEL(date_heure_menu), GTK_JUSTIFY_RIGHT);
  gtk_grid_attach (GTK_GRID (p_main_box), label, 3, 0, 3, 1);
  gtk_grid_attach(GTK_GRID(p_main_box), date_heure_menu, 7, 0, 1, 1);
  pthread_create(&time_thread, NULL, time_thread_menu_function, NULL);

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
    int exist, nb_categorie, flag=0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(tmp, "%02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mday, tm.tm_mon);
    FILE *fp;
    char buffer[5000000], codeBar[MAX_SIZE], codeBarTranslated[MAX_SIZE], url[200], urlImage[MAX_SIZE], tmp2[255];
    char date[20];
    char cat_key[10];
    char tmp_en_name[50];
    char string_en_name[50];
    struct json_object *parsed_json;
    struct json_object *categories;
    struct json_object *produit_json;
    struct json_object *brand;
    struct json_object *status;
    struct json_object *quantity;
    struct json_object *image_front_url;
    struct json_object *name;
    struct json_object *en_name;
    size_t n_friends;
    Product produit;

    fflush(stdin);
    fflush(stdout);
    strcpy(codeBar, gtk_entry_get_text(widget[1]));
    gtk_entry_set_text(widget[1], "");
    gtk_widget_grab_focus(widget[1]);
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
    exist = json_object_object_get_ex(parsed_json, "product", &produit_json);
    json_object_object_get_ex(produit_json, "categories_hierarchy", &categories);
    nb_categorie = json_object_array_length(categories);
    printf("nb of catego : %d\n", nb_categorie -1 );
    sprintf(cat_key, "%d", nb_categorie - 1);
    printf("cat _ key : %s\n",cat_key);
    en_name = json_object_array_get_idx(categories, nb_categorie -1);
    printf("%s\n", json_object_to_json_string(categories));
    printf("Existe ? %d\n", exist);
 
      printf("%s\n", json_object_get_string(en_name));
      strcpy(tmp_en_name, json_object_get_string(en_name));
      int j = 0;
      for (int i=0; i<strlen(tmp_en_name); i++){
          if (flag == 1){
            string_en_name[j] = tmp_en_name[i];
            j++;
          }
          if (tmp_en_name[i] == ':')
            flag = 1;
      }
      flag = 0;
      printf("%s\n", string_en_name);
      strcpy(produit.en_nom, string_en_name);
    exist = json_object_object_get_ex(produit_json, "product_name_fr", &name);
    if (exist != false)
      strcpy(produit.name, json_object_get_string(name));
    else
      strcpy(produit.name, "Not found");
      
    exist = json_object_object_get_ex(produit_json, "image_url", &image_front_url);
    if (exist != false)
    {
      strcpy(urlImage,"curl -s ");
      strcat(urlImage,json_object_get_string(image_front_url));
      strcat(urlImage," >img.jpg");
      printf("%s\n", urlImage);
      system(urlImage);
      GError *error = NULL;
      GdkPixbuf *pix = gdk_pixbuf_new_from_file ("img.jpg", &error);
      if (pix == NULL) {
          g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
          g_error_free (error);
    }
    
    gtk_image_set_from_pixbuf (widget[3], pix);
    }
    exist = json_object_object_get_ex(produit_json, "brands", &brand);
    if (exist != false)
      strcpy(produit.brand, json_object_get_string(brand));
    else
      strcpy(produit.brand, "Not found");
    exist = json_object_object_get_ex(produit_json, "product_quantity", &quantity);
    if (exist != false)
      strcpy(produit.quantity, json_object_get_string(quantity));
    else
      strcpy(produit.quantity, "0");

    strcpy(produit.codebar, codeBarTranslated);
    strcpy(produit.date, tmp);
    strcpy(produit.outside, "0");

    
    get_date_peremption(produit, date);
    strcpy(tmp2, json_object_get_string(name));
    strcat(tmp2, " | Date de péremption : ");
    strcat(tmp2, date);
    gtk_label_set_text(GTK_LABEL(widget[2]), tmp2);
    }
}

void afficherRecette(){
  pthread_t time_thread;
  List_product liste_produit;
  int nb_ingredients = 0, exist=0;
  char buffer[5000000];
  char querry[255];
  FILE *fp;

  struct json_object *parsed_json;
  struct json_object *recette_1;
  struct json_object *recette_2;
  struct json_object *url_image_1;
  struct json_object *url_image_2;
  struct json_object *name_1;
  struct json_object *name_2;
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *notes_label;
  GtkWidget *back;
  GtkWidget *line_header;
  
  GtkWidget *title_recette_1;
  GtkWidget *title_recette_2;
  GtkWidget *image_recette_1;
  GtkWidget *image_recette_2;
  GtkStyleContext *Context;

  strcpy(querry, "");
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  /* Creation du conteneur principal */
  p_main_box = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
  header(p_main_box, p_window, "RECETTES");

  liste_produit = retrieveProducts();

  strcat(querry, "curl -s \"https://api.spoonacular.com/recipes/findByIngredients?apiKey=");
  strcat(querry, "b28256c1c5a1413c8b7a1dfc28ea15ea");
  strcat(querry, "&ingredients=");


  for (int i = 0; i < liste_produit.nb_produits; i++){
    if (strcmp(liste_produit.produits[i].en_nom,"") != 0){
      if (nb_ingredients == 0){
        strcat(querry, liste_produit.produits[i].en_nom);
        nb_ingredients++;
      }
      else {
        strcat(querry, ",+");
        strcat(querry, liste_produit.produits[i].en_nom);
        nb_ingredients++;
      }
    }
  }
  printf("nb ing : %d\n", nb_ingredients);
  if (nb_ingredients != 0){
  strcat(querry, "&number=2\" > recipe.json");
  printf("%s\n", querry);
  system(querry);

  fp = fopen("recipe.json", "r");

  fread(buffer, 5000000, 1, fp);
  fclose(fp);

  parsed_json = json_tokener_parse(buffer);
  recette_1 = json_object_array_get_idx(parsed_json, 0);
  recette_2 = json_object_array_get_idx(parsed_json, 1);
  exist = json_object_object_get_ex(recette_1, "title", &name_1);
  if (exist != false){
    title_recette_1 = gtk_label_new(json_object_get_string(name_1));
    Context = gtk_widget_get_style_context(title_recette_1);
    gtk_style_context_add_class(Context, "item_tableau");
    gtk_grid_attach(GTK_GRID(p_main_box), title_recette_1, 0, 2, 4, 1);

  }
  exist = json_object_object_get_ex(recette_1, "image", &url_image_1);
  if (exist != false){
    strcpy(querry, "");
    strcpy(querry,"curl -s ");
    strcat(querry,json_object_get_string(url_image_1));
    strcat(querry," >recette_1.jpg");
    printf("%s\n", querry);
    system(querry);
    GError *error = NULL;
    GdkPixbuf *pix = gdk_pixbuf_new_from_file ("recette_1.jpg", &error);
    if (pix == NULL) {
        g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
        g_error_free (error);
    }
    image_recette_1 = gtk_image_new();
    gtk_image_set_from_pixbuf (image_recette_1, pix);
    gtk_grid_attach(GTK_GRID(p_main_box), image_recette_1, 0, 3, 4, 4);
  }

  exist = json_object_object_get_ex(recette_2, "title", &name_2);
  if (exist != false){
    title_recette_2 = gtk_label_new(json_object_get_string(name_2));
    Context = gtk_widget_get_style_context(title_recette_2);
    gtk_style_context_add_class(Context, "item_tableau");
    gtk_grid_attach(GTK_GRID(p_main_box), title_recette_2, 4, 2, 3, 1);
  }
  exist = json_object_object_get_ex(recette_2, "image", &url_image_2);
  if (exist != false){
    strcpy(querry, "");
    strcpy(querry,"curl -s ");
    strcat(querry,json_object_get_string(url_image_2));
    strcat(querry," >recette_2.jpg");
    printf("%s\n", querry);
    system(querry);
    GError *error = NULL;
    GdkPixbuf *pix = gdk_pixbuf_new_from_file ("recette_2.jpg", &error);
    if (pix == NULL) {
        g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
        g_error_free (error);
    }
    image_recette_2 = gtk_image_new();
    gtk_image_set_from_pixbuf (image_recette_2, pix);
    gtk_grid_attach(GTK_GRID(p_main_box), image_recette_2, 4, 3, 3, 4);
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
  else
    afficherMenu();

}


char * get_date_peremption(Product produit, char *date){
  char line[256];
  
  system("/home/pi/Documents/julius/adinrec/adinrec -fvad 3 test.wav");
  system("/home/pi/Documents/julius/julius/julius -C ../ENVR-v5.4.Dnn.Bin/julius.jconf -dnnconf ../ENVR-v5.4.Dnn.Bin/dnn2.jconf > output.txt");
  FILE *fp;
  fp = fopen("output.txt", "r");
  while (fgets(line, sizeof(line), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        if (line[0] == 's' && line[1] == 'e' && line[2] == 'n'){
          printf("%s\n", line);
          traduction_date(line, date);
          strcpy(produit.date, date);
        
          break;
        }
    } 
  insertProduct(produit);
  return date;
}

void retrait_produit(GtkWidget *entry_codebar_out){	
    int exist;
    char codeBar[20], codeBarTranslated[20];
    strcpy(codeBar, gtk_entry_get_text(entry_codebar_out));
    gtk_entry_set_text(entry_codebar_out, "");
    transformation(codeBar,codeBarTranslated);
    printf("\ncodebar = %s\n", codeBarTranslated);
    exist = productExist(codeBarTranslated);
    if (exist != 0){
      printf("Produit existe");
      setOutside(codeBarTranslated);
      afficherContenu();
     /* strcpy(url, "curl -s https://world.openfoodfacts.org/api/v0/product/");
      strcat(url,codeBarTranslated);
      strcat(url,".json > file.json");
	printf("%s\n", url);
    system(url);
    fp = fopen("file.json","r");
    fread(buffer, 5000000, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    exist = json_object_object_get_ex(parsed_json, "product", &produit_json);
    exist = json_object_object_get_ex(produit_json, "image_url", &image_front_url);
    if (exist != false)
    {
      strcpy(urlImage,"curl -s ");
      strcat(urlImage,json_object_get_string(image_front_url));
      strcat(urlImage," >img.jpg");
      printf("%s\n", urlImage);
      system(urlImage);
      GError *error = NULL;
      GdkPixbuf *pix = gdk_pixbuf_new_from_file ("img.jpg", &error);
      if (pix == NULL) {
          g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
          g_error_free (error);
    }
	    GtkWidget *p_window = NULL;
	  GtkWidget *p_main_box = NULL;
	  GtkWidget *label = NULL;
		
	  
	  GtkStyleContext *Context = NULL;
	  
	   //Creation de la fenetre principale de notre application 
	  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	   g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(quitter), p_window);		
	   //Creation du conteneur principal 
	  label = gtk_label_new("Produit trouvé");
  

	  GtkWidget *image = NULL;
	  image = gtk_image_new();
	  gtk_image_set_from_pixbuf (image, pix);
	  p_main_box = gtk_grid_new ();
	  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
	  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_grid_attach (GTK_GRID (p_main_box), label, 1, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (p_main_box), image, 1, 2, 1, 1);
	  gtk_widget_set_size_request(p_window, 400, 300);
	  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
	  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
	  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
	  gtk_widget_show_all (p_window);
	  /* Lancement de la boucle principale 
	  gtk_main ();
	}
    }
	else{
GtkWidget *p_window = NULL;
	  GtkWidget *p_main_box = NULL;
	  GtkWidget *label = NULL;
	  
	  GtkStyleContext *Context = NULL;
	p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	  /* Creation du conteneur principal 
	  label = gtk_label_new("Produit non trouvé");
  
	  p_main_box = gtk_grid_new ();
	  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
	  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_grid_attach (GTK_GRID (p_main_box), label, 1, 1, 1, 1);	
	  gtk_widget_set_size_request(p_window, 400, 300);
	  GdkColor grey = {0, 0xaaaa, 0xaaaa, 0xaaaa};
	  //gtk_window_set_resizable(GTK_WINDOW(p_window), FALSE);
	  gtk_widget_modify_bg(p_window, GTK_STATE_NORMAL, &grey);
	  gtk_widget_show_all (p_window);
	gtk_main ();*/
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
  gtk_widget_grab_focus(box_codebar[1]);

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
      case (char)-61 : 
        switch (codeBar[++i]){
          case (char)-87 : strcat(codeBarTranslated,"2");break;
          case (char)-88 : strcat(codeBarTranslated,"7");break;
          case (char)-89 : strcat(codeBarTranslated,"9");break;
          case (char)-96 : strcat(codeBarTranslated,"0");break;
        }     
    }
  }
  return codeBarTranslated;

}

char * traduction_date(char* phrase, char * date){
  char liste_mots[5][20];
  int flag = 0;
  int nb_mot = 0;
  int j=0;
  printf("taille: %ld, phrase : %s\n", strlen(phrase), phrase);
  for (int i=1; i<strlen(phrase);i++){
    if (flag == 1){
      if (phrase[i] == ' '){
        liste_mots[nb_mot][j] = '\0';
        nb_mot++;
        j = 0;
      }
      else {
        liste_mots[nb_mot][j] = phrase[i];
        j++;
      }
    }
    if (phrase[i-1] == '>')
    {
      flag = 1;
    }
    if (phrase[i+1] == ' ' && phrase[i+2] == '<' && phrase[i+3] == '/')
    {
      liste_mots[nb_mot][j] = '\0';
      break;
    }
  }

  getDate(liste_mots, nb_mot + 1, date);
  printf("La date est : %s\n", date);
  return date;
	
}

char * getDate(char liste_mot[5][20], int nb_mot, char *date){

  strcpy(date, "");
  strcat(date, "2021-");
  for (int i=0; i<nb_mot;i++){
    printf("%s\n", liste_mot[i]);
    if (strcmp(liste_mot[i], "one") == 0)
      strcat(date, "01");
    else if (strcmp(liste_mot[i], "two") == 0 || strcmp(liste_mot[i], "to") == 0 )
      strcat(date, "02");
    else if (strcmp(liste_mot[i], "three") == 0)
      strcat(date, "03");
    else if (strcmp(liste_mot[i], "four") == 0 || strcmp(liste_mot[i], "for") == 0 )
      strcat(date, "04");
    else if (strcmp(liste_mot[i], "five") == 0)
      strcat(date, "05");
    else if (strcmp(liste_mot[i], "six") == 0)
      strcat(date, "06");
    else if (strcmp(liste_mot[i], "seven") == 0)
      strcat(date, "07");
    else if (strcmp(liste_mot[i], "eight") == 0)
      strcat(date, "08");
    else if (strcmp(liste_mot[i], "nine") == 0)
      strcat(date, "09");
    else if (strcmp(liste_mot[i], "ten") == 0)
      strcat(date, "10");
    else if (strcmp(liste_mot[i], "eleven") == 0)
      strcat(date, "11");
    else if (strcmp(liste_mot[i], "twelve") == 0)
      strcat(date, "12");
    else if (strcmp(liste_mot[i], "thirteen") == 0)
      strcat(date, "13");
    else if (strcmp(liste_mot[i], "fourteen") == 0)
      strcat(date, "14");
    else if (strcmp(liste_mot[i], "fifteen") == 0)
      strcat(date, "15");
    else if (strcmp(liste_mot[i], "sixteen") == 0)
      strcat(date, "16");
    else if (strcmp(liste_mot[i], "seventeen") == 0)
      strcat(date, "17");
    else if (strcmp(liste_mot[i], "eighteen") == 0)
      strcat(date, "18");
    else if (strcmp(liste_mot[i], "nineteen") == 0)
      strcat(date, "19");
    else if (strcmp(liste_mot[i], "twenty") == 0)
      strcat(date, "20");
    else if (strcmp(liste_mot[i], "twenty-one") == 0)
      strcat(date, "21");
    else if (strcmp(liste_mot[i], "twenty-two") == 0)
      strcat(date, "22");
    else if (strcmp(liste_mot[i], "twenty-three") == 0)
      strcat(date, "23");
    else if (strcmp(liste_mot[i], "twenty-four") == 0)
      strcat(date, "24");
    else if (strcmp(liste_mot[i], "twenty-five") == 0)
      strcat(date, "25");
    else if (strcmp(liste_mot[i], "twenty-six") == 0)
      strcat(date, "26");
    else if (strcmp(liste_mot[i], "twenty-seven") == 0)
      strcat(date, "27");
    else if (strcmp(liste_mot[i], "twenty-eight") == 0)
      strcat(date, "28");
    else if (strcmp(liste_mot[i], "twenty-nine") == 0)
      strcat(date, "29");
    else if (strcmp(liste_mot[i], "thirty") == 0)
      strcat(date, "30");
    else if (strcmp(liste_mot[i], "thirty-one") == 0)
      strcat(date, "31");
    else
      strcat(date, "00");
    if (i == 0)
      strcat(date, "-");
  }
  printf("date : %s\n", date);
  return date;
}

int split (const char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}
