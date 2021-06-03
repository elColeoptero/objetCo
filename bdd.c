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
  sprintf(querry, "INSERT INTO t_produit(nom,quantite,peremption,codeBarre,marque,outside) VALUES('%s','%s','%s','%s','%s','%s')",produit.name, produit.quantity, produit.date, produit.codebar, produit.brand, produit.outside);
  printf("%s", querry);
  return mysql_query(con, querry);
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
      i++;
  }
  list_product.nb_produits = i;
  return list_product;
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
