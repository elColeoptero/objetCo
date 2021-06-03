#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int insertCache(char codebar[50]);
int insertProduct(Product produit);
List_product retrieveProducts();
list_note retrieveNotes();
MYSQL  * connection();