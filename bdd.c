#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define HOST "192.168.171.41"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "FridgeIt"

int insertCache(MYSQL *con,int codebar){
  char querry[100];
  sprintf(querry, "INSERT INTO t_cache VALUES(%d)",codebar);
  return mysql_query(con, querry);
}

int insertProduct(MYSQL *con,Product produit){
  char querry[500];
  sprintf(querry, "INSERT INTO t_produit(nom,quantite,peremption,codeBarre,marque,outside) VALUES('%s',%d,'%s',%d,'%s',%d)",produit.name, produit.quantity, produit.date, produit.codebar, produit.brand, produit.outside);
  return mysql_query(con, querry);
}

Product * retreiveProduct(MYSQL *con){
if (mysql_query(con, "SELECT * FROM t_produit"))
  {
      return -1;
  }

  MYSQL_RES *result = mysql_store_result(con);
  if (result == NULL)
  {
      return -1;
  }
  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          printf("%s ", row[i] ? row[i] : "NULL");
      }
      printf("\n");
  }



}

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);


  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL)
  {

      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }
  if(insertCache(con,1)){
    fprintf(stderr, "%s\n", mysql_error(con));
  }
  if(insertProduct(con,"Poudre", 100, "Nutella", "2008-7-04",1,0)){
    fprintf(stderr, "%s\n", mysql_error(con));
  }
  if(insertProduct(con,"Poudre", 100, "Nutella", "2008-7-04",1,0)){
    fprintf(stderr, "%s\n", mysql_error(con));
  }
  if(insertProduct(con,"Poudre", 100, "Nutella", "2008-7-04",1,0)){
    fprintf(stderr, "%s\n", mysql_error(con));
  }
  if(insertProduct(con,"Poudre", 100, "Nutella", "2008-7-04",1,0)){
    fprintf(stderr, "%s\n", mysql_error(con));
  }
  if(insertProduct(con,"Poudre", 100, "Nutella", "2008-7-04",1,0)){
    fprintf(stderr, "%s\n", mysql_error(con));
  }
  retreiveProduct(con);



  mysql_close(con);
  exit(0);
}
