#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define heap_size (64*1024*1024)

typedef struct list
{    
  int flag; //size is not needed if we are making linkedlist
  int index;
  struct list* next;

} list;

list a[4194304];
int c_s;
int no_of_blocks = 0;
int p = 0;
int dummy =0;
list *m;
bool in = true;
bool overflow = false;

void init()
{
  int i =0;
  for (i = 0; i < 4194304; i++ )
  {
    a[i].index = i;
    a[i].flag = 0;
    a[i].next = NULL;
  }  
}



struct alloc_hdr 
{
  unsigned int chunck_size;
  unsigned int alloc_size;
  struct alloc_hdr *freelist_next;
} alloc;



void *allocate (size_t request, size_t *info)
{

//heap initialization

  if (in) //works fine
  {
    init();
    in = false;
  }

  int i=0;
  for (i = 0; i < 4194304; i++ )
  {
    //printf("hii\n");
    if (a[i].next == NULL && (a[i].flag == 0 || a[i].flag  == 2))
    {
      p = i; //first free block in the memory
      break;
    }
  }

  /*
  list *first = &a[0];
  list *current = first;
  
  
  while (first != NULL)
  {
    first = first->next;
  }
  */

  if (request == 0 || request > heap_size) 
  {
    //info = 0;
    printf("size too large or no size requested\n");
    info = 0;
    return NULL;
  }

  else if(request%16 == 0)
  {
    no_of_blocks = request/16;  
  }

  else 
  {
   c_s = request + (request/16);
   no_of_blocks = c_s /16 + 1;
  }


  info = no_of_blocks * 16;

  printf("allocated memory for this allocation is %p bytes\n", info);

  int j = p + 1;
  int k = p;
  int block_allocated = 0;
 
  //a[j].next = NULL;

  //a[p].size = no_of_blocks;
   

  while(block_allocated != no_of_blocks)
  {
    if(a[j].next == NULL && (a[j].flag == 0 || a[j].flag  == 2)) //edge case will fail or maybe not mostly will
    {
      if (j == 4194304)
      {
        printf("memory full\n");
        if (overflow == false && (block_allocated == no_of_blocks-1))
        {
          overflow = true;
          return &a[p];
        }
        else
        {
          info = 0;
          return NULL;
        }
        
      }
      //printf("%d  %d\n", k, j);
      a[k].next = &a[j];
      a[k].flag = 1;
      
      j = j + 1;
      k = j - 1;
    
      block_allocated += 1;
    }

    else
    { 
      j = j+ 1;
    }
  }
    printf("this k is getting null %d\n", k-1);

    a[k-1].next = NULL; //last element is null. 
    a[p].flag = 3;
    m = &a[p]; //testing purpose
     
    printf("address of p is %p\n", &a[p]);
    //p = p + no_of_blocks; 
     
    printf("p is %d\n", p);

    printf("total blocks are %d\n", no_of_blocks);
    
    return m;
    
}





int deallocate (void *ptr)
{
  //printf("%p\n", ptr);
  int i=0;
  for (i = 0; i < 4194304; i++ )
  {
    if (&a[i] == ptr)
    {
      //printf("%d\n", a[i].flag);

      if (a[i].flag == 2)
      {
        return -2;
      }
      else if (a[i].flag != 3 && a[i].flag != 0)
      {
        return -3;
      }
      else if (a[i].flag == 0)
      {
        return -4;
      }
      else if (a[i].flag == 3)
      {
        int v = i;
        int t;
        //printf("a[v].next is %p\n", a[v].next);
        while(a[v].next != NULL)
        {
          //printf("v is %d\n", v);
          t = v;
          a[t].flag = 2; //explicitly deallocated all nodes
          v = a[t].next->index;
          a[t].next = NULL;
          //a[t].flag = 0;
        }
        //printf("v is %d and it stops\n", v);
        a[v].flag = 2;
        
        a[i].flag = 2;
        int j;

        for (j=i-1; j>= 0; j--)
        {
          if(a[j].flag == 0)
          {
            a[j].next = &a[i];
            break;
          }
        }
        return 0;
      }
    }
   
  }

   return -1;
}


size_t heap_max ()
{

  if (in)
  {
    return heap_size;
  }


  size_t count = 0;

  int i=0;
  for (i = 0; i < 4194304; i++ )
  {
    if (a[i].next == NULL) //Null meaning the block is free.
    {
      count = count + 1;
    }
  }

  count = count*16;
  return count;
}

int blocksize()
{
  return (heap_size/sizeof(list));
}






int main()
{
  //llist l;
 // list_init();

  int ret;

  int *rp,*rp1,*rp2,*rp3,*rp4;



  size_t a;
  size_t *b;
  printf("\nEnter request");
  scanf("%zd%p" ,&a,&b);
  rp = allocate (a,b);
  printf("%p\n", rp);
  
  printf("\nEnter request");
  scanf("%zd%p" ,&a,&b);
  rp1 = allocate (a,b);
  printf("%p\n", rp1);


  printf("\nEnter request");
  scanf("%zd%p" ,&a,&b);
  rp2 = allocate (a,b);

  ret = deallocate(rp1);
  printf("%d\n",ret);

  printf("\nEnter request");
  scanf("%zd%p" ,&a,&b);
  rp3 = allocate (a,b);

  printf("\nEnter request");
  scanf("%zd%p" ,&a,&b);
  rp4 = allocate (a,b);

  //ret = deallocate(rp);
  //printf("%d\n",ret);
  //allocate (a,b);

  printf("%zu\n", heap_max());

  //ret = deallocate(rp);

  //printf("%d\n",ret);

  //printf("\nEnter request");
  //scanf("%zd%p" ,&a,&b);
  //sp = allocate (a,b);
  //rp = allocate (a,b);
  //ret = deallocate(rp);
  //printf("%d\n",ret);
  //ret1 = deallocate(sp);

  return 0;
}