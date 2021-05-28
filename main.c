#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include<stdio.h>
#include<json-c/json.h>
 #include <unistd.h>

#define MAX_SIZE 20
char* transformation(char* codeBar, char* codeBarTranslated);
int main (int argc, char **argv){
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
