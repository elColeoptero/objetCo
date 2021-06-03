#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"

typedef struct {
   char  id[10];
   char  name[50];
   char  brand[50];
   char  date[50];
   char  quantity[50];
   char  outside[2];
   char  codebar[50];
} Product;  

typedef struct {
   Product produits[256];
   int nb_produits;
} List_product;

typedef struct {
  char texte[255];
  char date[50];
} note;

typedef struct {
  note list_note[50];
  int nb_list;
} list_note;

#define MAX_SIZE 20


GtkWidget * date_heure;

void afficherMenu();
void afficherProduit();
void afficherContenu();
void afficherNotes();
void header(GtkWidget *p_main_box, GtkWidget *p_window, char title[20]);
void ajout_item_tableau(GtkWidget * p_window, int row, int column, char * item_text);
char* transformation(char* codeBar, char* codeBarTranslated);
list_note getNotes();