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
   char  en_nom[50];
} Product;  

typedef struct {
   Product produits[256];
   int nb_produits;
} List_product;

typedef struct {
  char id[10];
  char auteur[20];
  char texte[255];
  char date[50];
} note;

typedef struct {
  note list_note[50];
  int nb_list;
} list_note;


#define MAX_SIZE 20
#define false 0

GtkWidget * date_heure;
GtkWidget *date_heure_menu;
GtkWidget * p_window_contenu;


void afficherMenu();
void afficherProduit();
void afficherContenu();
void afficherNotes();
void afficherRecette();
void afficherAjout();
void refresh_produit(GtkWidget * widget[3]);
void header(GtkWidget *p_main_box, GtkWidget *p_window, char title[20]);
void ajout_item_tableau(GtkWidget * p_window, int row, int column, char * item_text);
char* transformation(char* codeBar, char* codeBarTranslated);
void retrait_produit(GtkWidget *entry_codebar_out);
list_note getNotes();
char * traduction_date(char* phrase, char *date);
int split (const char *str, char c, char ***arr);
char * getDate(char liste_mot[5][20], int nb_mot, char *date);
char * get_date_peremption(Product produit, char *date);
void cb_suppression_produit(GtkWidget *p_widget, char id[10]);
