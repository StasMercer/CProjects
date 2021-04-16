#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct node{
    int num;
    struct node * left;
    struct node * right;
};

void add_new_node(int num, struct node * tree){
         if(num > tree->num){
          
            if(!tree->right){
                tree->right = (struct node *) malloc(sizeof(struct node));
                
                tree->right->left = NULL;
                tree->right->right = NULL;

                tree->right->num = num;
               
       
            }else{
           
                
                add_new_node(num, tree->right);
                
                
            }
        } 


        if(num < tree->num){
       
            if(!tree->left){
                tree->left = (struct node *) malloc(sizeof(struct node));
                
                tree->left->left = NULL;
                tree->left->right = NULL;
               
                
                tree->left->num = num;

              
            }else{

                add_new_node(num, tree->left);
                
                
            }
        }
    
    
    
};


bool cmp_tree(struct node * t1, struct node * t2){
    
    if((!(bool)t1 && !(bool) t2)){
        return true;
    }
    
    if((bool)t1 && (bool) t2){
        return cmp_tree(t1->right, t2->right) && cmp_tree(t1->left , t2->left);
        
    }

    return false;

}

void dealocate(struct  node * t){
    
    if((bool) t){
        dealocate(t->left);
        dealocate(t->right);
        free(t);
    }
    

    
}

int get_different(int n, int k, int arr[n][k]){

    struct node ** treeList = malloc(sizeof(struct node) * n);
    for (int i = 0; i< n; i++){
        
        struct node * tree = (struct node *) malloc(sizeof(struct node));
        tree->left = NULL;
        tree->right = NULL;
        tree->num = arr[i][0];
  
 
        for(int j = 1; j < k; j++){
            //printf("%d\n",arr[i][j]);
            add_new_node(arr[i][j], tree);
            
        }

        treeList[i] = tree;
        
    }
    int amount = n;

    for(int i = 0; i < n -1; i++){
        
        for(int j = i+1; j < n; j++){
            if(treeList[j]->num > 0 && cmp_tree(treeList[i], treeList[j])){
                treeList[j]->num = -j;
                //printf("%d\n", treeList[i]->num);
                amount --;
            }
            
         
            

        }
        dealocate(treeList[i]);
        treeList[i] = NULL;
    }
    dealocate(treeList[n-1]);
    treeList[n-1] = NULL;
    free(treeList);

    return amount;

}

int main(){
    
    int n=0; 
    int k=0;

    scanf("%d %d", &n, &k);

    int arr[n][k];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k-1; j++){
            scanf("%d ",&arr[i][j]);
        }
        scanf("%d\n", &arr[i][k-1]);
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < k; j++){
    //         printf("%d ", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    
    
    printf("%d\n", get_different(n, k, arr));
    
    return 0;
}