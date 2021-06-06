#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int insertCache(char codebar[50]);
int insertProduct(Product produit);
List_product retrieveProducts();
list_note retrieveNotes();
void setOutside(char codebar[20]);
int productExist(char codebar[20]);
void suppression_produit(char id[10]);
MYSQL  * connection();