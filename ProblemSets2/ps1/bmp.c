#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "bmp.h"

void get_new_key(const char *key, const char *text, char *new_key)
{

  int dlzka = strlen(text);
  int klen = strlen(key);
  for (int k = 0; k < dlzka; k += 1)
  {
    new_key[k] = toupper(key[k % klen]);
  }
}

bool is_key_valid(const char *key)
{
  int k = 0;
  while (key[k])
  {
    if(isalpha(key[k]) == 0){
      return false;
    }
    k++;
  }
  return true;
}

bool *ten_to_two(int num)
{
  int i = 7;
  bool *b = malloc(8*sizeof(bool));
  int k = 0;
  while(i >= 0){
    k = num >> i;

    if (k & 1)
    {
      b[abs(i - 7)] = 1;
    }
    else
    {
      b[abs(i - 7)] = 0;
    }
    i--;
  }

  return b;
}


char *reverse(const char *text)
{
  if (text == 0){
    return 0;
  }else{
    int l = strlen(text);
    char *res = malloc((l + 1)* sizeof(char));
    int i = 0;
    while(i < l){
      res[i] = toupper(text[l - 1 - i]);
      i++;

    }

    res[l] = '\0';
    return res;
  }
  
}

int two_to_ten(bool *bits)
{
  int k = 8;
  double n = 0;
  while(k > 0){
    if (bits[k - 1] == 1)
    {
      n += pow((double)2, (double)abs(k - 8));
    }
    k--;
  }
  return (int)n;
}


char *vigenere_encrypt(const char *key, const char *text)
{

  if (text == 0 || key == 0){
    return 0;
  }

  if (is_key_valid(key) == false){
    return 0;
  }
  int l = strlen(text);

  char *nk = malloc(l * sizeof(char));
  char *r = calloc((l + 1), sizeof(char));
  get_new_key(key, text, nk);

  int k = 0;
  int i = 0;
  while (i < l)
  {
    if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
    {

      r[i] = (toupper(text[i]) - 'A' + nk[k]);

      if (r[i] > 'Z'){
        r[i] = r[i] % 'Z' + 'A' - 1;
      }

      k++;
    }
    else
    {
      r[i] = toupper(text[i]);
    }
    i++;
  }
  //lol
  if(true){
    free(nk);
  }
  return r;
}
char *bit_decrypt(const unsigned char *text)
{
  if (text == 0){
    return 0;
  }
  int dlzka = strlen((char *)text);
  bool **b = calloc(dlzka + 1, 8);


  int i = 0;

  while (i < dlzka)
  {
    b[i] = ten_to_two((int)text[i]);
    i++;
  }

  i = 0;
  
  while (i < dlzka)
  {
    int j = 4;
    while (j < 8)
    {
      b[i][j] = b[i][j - 4] ^ b[i][j];
      j++;
    }
    j = 0;
    while (j < 4)
    {
      bool temp = b[i][j];
      b[i][j] = b[i][j + 1];
      b[i][j + 1] = temp;
      j+=2;
    }
    
    i++;
  }


  char *temp = malloc(sizeof(char) + 1);
  char *res = calloc(dlzka + 1, sizeof(char));
  i = 0;
  while(i < dlzka){
    
    int n = two_to_ten(b[i]);
    sprintf(temp, "%c", n);
    strcat(res, temp);
    free(b[i]);
    i++;
  }

  free(b);
  free(temp);
  return res;
}
char *vigenere_decrypt(const char *key, const char *text)
{
  if (text == 0 || !key){
    return 0;
  }
  if (is_key_valid(key) == false){
    return NULL;
  }
  int length = strlen(text);
  char *nk = malloc(length * sizeof(char));
  char *r = calloc((length + 1), sizeof(char));
  get_new_key(key, text, nk);

  int k = 0;
  int i = 0;
  while (i < length)
  {
    if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
    {
      r[i] = (toupper(text[i]) + 'A' - nk[k]);
      if (r[i] < 'A')
        r[i] = text[i] + 'Z' - nk[k] + 1;
      k++;
    }
    else
    {
      r[i] = toupper(text[i]);
    }
    i++;
  }
  
  free(nk);
  return r;
}

unsigned char *bit_encrypt(const char *text)
{
  if (!text){

    return NULL;
  }else{
  }

  int l = strlen(text);
  
  bool **b = calloc(l * 8, sizeof(bool));

  
  int q = 0;
  while (q < l)
  {
    b[q] = ten_to_two((int)text[q]);
    q++;
  }


  int i = 0;
  
  while (i < l)
  {
    int j = 0;
    while (j < 4)
    {
      bool temp = b[i][j];
      b[i][j] = b[i][j + 1];
      b[i][j + 1] = temp;
      j+=2;
    }
    j = 4;
    while (j < 8)
    {
      b[i][j] = b[i][j - 4] ^ b[i][j];
      j++;
    }
    
    i++;
  }

  i = 0;
  unsigned char* res = calloc(l*(4/2)+1, sizeof(unsigned char));
  while (i < l)
  {
    int j = 0;
    char tmp[8];
    while (j < 8)
    {
      tmp[j] = b[i][j] ? '1' : '0';
      j++;
    }
    res[i] = (unsigned char)strtol(tmp, NULL, 2);
    free(b[i]);
    i++;
  }

  res[l * 2] = '\0';
  free(b);

  return res;
}



char *bmp_decrypt(const char *key, const unsigned char *text)
{
  if (key == 0 || text == 0){

    return 0;
  }else{
    char *b = bit_decrypt(text);
    char *vig_dec = vigenere_decrypt(key, b);
    char *odp = reverse(vig_dec);
    
    free(vig_dec);
    free(b);
    return odp;
  }
  
}

unsigned char *bmp_encrypt(const char *key, const char *text)
{
  if (text == 0 || key == 0){

    return NULL;
  }else{
    char *r = reverse(text);
    char *vig = vigenere_encrypt(key, r);
    unsigned char *m = bit_encrypt(vig);
    free(r);
    free(vig);
    return m;
  }
  
}


