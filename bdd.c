#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "bdd.h"

#define HOST "localhost"
#define USER "julien"
#define PASSWORD "Lnpj&c1b"
#define DATABASE "FridgeIT"

int insertCache(char codebar[50]){
  MYSQL *con = connection();
  char querry[100];
  sprintf(querry, "INSERT INTO t_cache VALUES(%d)",atoi(codebar));
  return mysql_query(con, querry);
}

int insertProduct(Product produit){
  MYSQL *con = connection();
  char querry[500];
  sprintf(querry, "INSERT INTO t_produit(nom,quantite,peremption,codeBarre,marque,outside,en_nom) VALUES('%s','%s','%s','%s','%s','%s','%s')",produit.name, produit.quantity, produit.date, produit.codebar, produit.brand, produit.outside, produit.en_nom);
  printf("%s\n", querry);
  return mysql_query(con, querry);
}

int productExist(char codebar[20]){
  MYSQL *con = connection();
  char querry[500];
  sprintf(querry, "SELECT * FROM t_produit where codeBarre = %s", codebar);
  printf("%s", querry);
  if (mysql_query(con, querry))
  {
    fprintf(stderr, "Erreur dans la connexion");
  }

  MYSQL_RES *result = mysql_store_result(con);
  int num_rows = mysql_num_rows(result);
  return num_rows;
}

void setOutside(char codebar[20]){
  MYSQL *con = connection();
  char outside[2];
  char querry[500];
  sprintf(querry, "SELECT outside from t_produit where codeBarre = %s", codebar);
  printf("%s\n",querry);
  if (mysql_query(con, querry))
  {
    fprintf(stderr, "Erreur dans la connexion");
  }
  MYSQL_RES *result1 = mysql_store_result(con);
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result1)))
  {
      strcpy(outside, row[0]);
      break;
  }
  printf("%s", outside);
  if (strcmp(outside, "0") == 0)
    sprintf(querry, "UPDATE t_produit SET outside='1' where codeBarre = %s", codebar);
  else
    sprintf(querry, "UPDATE t_produit SET outside='0' where codeBarre = %s", codebar);
  printf("%s\n",querry);
  if (mysql_query(con, querry))
  {
    fprintf(stderr, "Erreur dans la connexion");
  }
  MYSQL_RES *result = mysql_store_result(con);
}

List_product retrieveProducts(){
  MYSQL *con = connection();
  if (mysql_query(con, "SELECT * FROM t_produit"))
  {
      fprintf(stderr, "Erreur dans la connexion");
  }

  MYSQL_RES *result = mysql_store_result(con);
  if (result == NULL)
  {
      fprintf(stderr, "Erreur dans le résultat");
  }
  List_product list_product;

  int num_fields = mysql_num_fields(result);
  printf("Nb field : %d\n", num_fields);
  MYSQL_ROW row;

  int i = 0;
  while ((row = mysql_fetch_row(result)))
  {
      strcpy(list_product.produits[i].id       , row[0]);
      strcpy(list_product.produits[i].name     , row[1]);
      strcpy(list_product.produits[i].quantity , row[2]);
      strcpy(list_product.produits[i].date     , row[3]);
      strcpy(list_product.produits[i].codebar  , row[4]);
      strcpy(list_product.produits[i].brand    , row[5]);
      strcpy(list_product.produits[i].outside  , row[6]);
      strcpy(list_product.produits[i].en_nom   , row[7]);
      i++;
  }
  list_product.nb_produits = i;
  return list_product;
}

void suppression_produit(char id[10]){
  MYSQL *con = connection();
  char querry[500];
  sprintf(querry, "DELETE from t_produit where id = %s", id);
  printf("%s", querry);
  if (mysql_query(con, querry))
  {
    fprintf(stderr, "Erreur dans la connexion");
  }

  MYSQL_RES *result = mysql_store_result(con);
}

list_note retrieveNotes(){
  MYSQL *con = connection();
  if (mysql_query(con, "SELECT * FROM t_note"))
  {
      fprintf(stderr, "Erreur dans la connexion");
  }

  MYSQL_RES *result = mysql_store_result(con);
  if (result == NULL)
  {
      fprintf(stderr, "Erreur dans le résultat");
  }
  list_note list_notes;

  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;

  int i = 0;
  while ((row = mysql_fetch_row(result)))
  {
      strcpy(list_notes.list_note[i].id       , row[0]);
      strcpy(list_notes.list_note[i].date     , row[1]);
      strcpy(list_notes.list_note[i].texte    , row[2]);
      strcpy(list_notes.list_note[i].auteur   , row[3]);
      i++;
  }
  list_notes.nb_list = i;
  return list_notes;
}

MYSQL  * connection()
{
  MYSQL *con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
  }

  if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL)
  {

      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
  }
  return con;
}
