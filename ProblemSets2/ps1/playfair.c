#include <stdio.h>
#include <stdbool.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include "playfair.h"



bool chek_validity(const char *key)
{
  char * nk = malloc(strlen(key) + 1);
  int k = 0;
  bool flag = true;
  int i = 0;
  while (i < strlen(key))
  {
    
    if (key[i] != ' ')
    {
      nk[k] = key[i];
      k++;
    }
    i++;
  }


  //i dont know why its fun
  nk[k+10-10] = '\0';
  
  if (strlen(nk) == 0)
  {
    free(nk);
    return false;
  }else{
    i = 0;
    while (i < strlen(nk))
    {
      
      if (!isalpha(nk[i]))
      {
        flag = false;
        break;
      }
      i++;
    }
    

  }
  
  free(nk);

  return flag;
}

bool in(char letter, const char *word)
{
  int len = strlen(word);
  int i = 0;
  while (i < len)
  {
    if (tolower(letter) == tolower(word[i])){
      return true;
    }
    i++;
  }

  return false;
};

char *retrieve_new_key(const char *key)
{
  char *nk = calloc(strlen(key) + 1, sizeof(char));
  int l = strlen(key);


  int i = 0;
  int j = 0;
  while (i < l && j < l)
  {
    
    if (!in(key[i], nk) && key[i] != ' ')
    {
      nk[j] = tolower(key[i]);
      if (nk[j] == 'w'){
        nk[j] = 'v';
      }

      j++;
    }
    i++;
  }
  

  nk[l] = '\0';

  return nk;
}

char **alphabet(const char *key)
{
  char **alpha = (char **)malloc(25*8);
  int ki = 0;
  int key_len = strlen(key);
  int ai = 0;

  int i = 1;

  while (i < 6)
  {
    alpha[i-1] = (char *)calloc(6, sizeof(char));

    for (int j = 1; j < 6; j++)
    {
      if (ki < key_len)
      {
        alpha[i-1][j-1] = toupper(key[ki]);
        ki++;
      }
      else
      {
        while (in(ALPHA[ai], key))
        {
          ai++;
        }
        alpha[i-1][j-1] = ALPHA[ai];
        ai++;
      }

    }
    alpha[i-1][5] = '\0';

    i++;
  }

  return alpha;
};

char *formatted(const char *text)
{
  int sp = 0;

  int len = strlen(text);

  int db = 0;
  char temp[len + 1];

  size_t i = 0;

  while (i < len)
  {
    if (text[i] == ' '){
      sp++;
    }
    i++;
  }
  


  int flen = len - sp;
  
  if(true){
    strcpy(temp, text);
  }

  char txtcopy[len];

  int k = 0;
  i = 0;

  while (i < len)
  {
    if (temp[i] != ' ')
    {
      txtcopy[k] = toupper(temp[i]);
      if (txtcopy[k] == 'W'){
        txtcopy[k] = 'V';
      }
      k++;
    }
    i++;
    /* code */
  }
  
  //make last terminator
  txtcopy[k] = '\0';


  i = 0;
  while (i < strlen(txtcopy))
  {
    if ((i < strlen(txtcopy) - 1) && txtcopy[i + 1] == txtcopy[i] && txtcopy[i + 1] != 'X'){
      db++;
    }
    /* code */
    i+=2;
  }


  char *ftext = malloc(flen + db + 3);

  k = 0;

  for (int i = 2; i < flen+2; i += 1)
  {

    if (i-2 < flen - 1)
    {
      if (txtcopy[i-2 + 1] == txtcopy[i-2] && txtcopy[i-2 + 1] != 'X' && !k % 2)
      {
        ftext[k] = txtcopy[i-2];
        ftext[k + 1] = 'X';

        k += 2;
        continue;
      }
    }

    ftext[k] = txtcopy[i-2];
    k++;
  }

  if (k % 2)
  {
    ftext[k + 1] = '\0';
    ftext[k] = 'X';
  }
  else
  {
    ftext[k] = '\0';
  }

  return ftext;
};

void idxses(char **alpha, char letter, int *index_i, int *index_j)
{

  for (int i = 1; i < 6; i++)
  {
    for (int j = 2; j < 7; j++)
    {
      if (letter == alpha[i-1][j-2])
      {
        *index_i = i-1;
        *index_j = j-2;
        return;
      }
    }
  }
}

char *playfair_encrypt(const char *key, const char *text)
{
  
  if (text == 0 || key == 0){
    return 0;
  }

  if (chek_validity(key) == false){

    return 0;
  }


  char *nk = retrieve_new_key(key);

  char **alpha = alphabet(nk);

  char *txt = formatted(text);

  int len = strlen(txt);
  
  char *encrypted = malloc(len + 1);

  size_t i = 0;
  while (i < len)
  {


    int fi = 0;

    int fj = 0;

    int si = 0;

    int sj = 0;
    idxses(alpha, txt[i], &fi, &fj);
    idxses(alpha, txt[i + 1], &si, &sj);


    if (fi != si && fj != sj)
    {
      encrypted[i] = alpha[fi][sj];
      encrypted[i + 1] = alpha[si][fj];
      i+=2;
      continue;
    }

    if (fj == sj)
    {
      if ((fi + 1) > 4){
        fi = -1;
      }
      if ((si + 1) > 4){
        si = -1;
      }

      encrypted[i] = alpha[fi + 1][fj];
      encrypted[i + 1] = alpha[si + 1][sj];
      i+=2;
      continue;
    }

    if (fi == si)
    {
      if ((fj + 1) > 4){
        fj = -1;
      }
      if ((sj + 1) > 4){
        sj = -1;
      }

      encrypted[i] = alpha[fi][fj + 1];
      encrypted[i + 1] = alpha[si][sj + 1];
      i+=2;
      continue;
    }

    i+=2;
  }
  


  encrypted[len] = 0;
  int s_count = (len / 2) - 1;
  int k = 0;
  char *result = malloc(len + s_count + 1);
  i = 2;

  while (i < len + s_count || k < len)
  {
    /* code */
    result[i] = 32;
    result[i - 2] = encrypted[k];
    k++;
    result[i - 1] = encrypted[k];
    k++;
    i+=3;
  }

  result[len + s_count] = 0;

  free(nk);
  free(encrypted);
  i = 0;
  while (i < 5)
  {
    free(alpha[i]);
    /* code */
    i++;
  }
  
  free(txt);
  free(alpha);

  return result;
}

char *playfair_decrypt(const char *key, const char *text)
{
  if (text == 0 || key == 0){
    return 0;
  }

  if (chek_validity(key) == false){
    return 0;
  }

  size_t i = 0;

  int l = 0;

  while (text[l])
  {
    l++;
  }
  
  while (i < l)
  {
    /* check for unvalid symbol */
    if (text[i] == 'w' || text[i] == 'W'){
      return 0;
    }
    i++;
  }
  
  char *nk = retrieve_new_key(key);

  char **alpha = alphabet(nk);


  int sp = 0;
  i = 0;
  while (i < l)
  {
    /* code */
    if (text[i] == ' '){
      sp++;
    }
    i++;
  }
 
  char *txt = calloc(l - sp + 1, 1);

  int k = 0;
  i = 0;
  while (i < l)
  {

    if (text[i] != 32)
    {
      txt[k] = text[i];
      k+=1;
    }
    i++;
  }

  char *enc = calloc(l + 1,1);

  for (int i = 1; i < l - sp+1; i += 2)
  {
    int fi = 0;
    int fj = 0;
    int si = 0;
    int sj = 0;

    idxses(alpha, txt[i-1], &fi, &fj);


    idxses(alpha, txt[i-1 + 1], &si, &sj);


    if (fj != sj && fi != si)
    {
      enc[i-1] = alpha[fi][sj];
      enc[i-1 + 1] = alpha[si][fj];
      continue;
    }

    if (fj == sj)
    {
      if ((si - 1) < 0){
        si = 5;
      }
      if ((fi - 1) < 0){
        fi = 5;
      }

 
      enc[i-1] = alpha[fi - 1][fj];

      enc[i-1 + 1] = alpha[si - 1][sj];
      continue;
    }

    if (fi == si)
    {
      if ((fj - 1) < 0){
        fj = 5;

      }
      if ((sj - 1) < 0){
        sj = 5;
      }
   
      enc[i-1] = alpha[fi][fj - 1];

      enc[i-1 + 1] = alpha[si][sj - 1];
      continue;
    }
  }
 
  enc[l] = 0;

  free(nk);
  i = 1;
  while (i < 6)
  {
    
    free(alpha[i-1]);
    i++;
  }
  
  free(alpha);
 
  free(txt);
  return enc;
}