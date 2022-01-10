#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
pnode getNode(pnode *head, int id);
void deleteGraph_cmd(pnode *head);
void printGraph_cmd(pnode head);
void delete_node_cmd(pnode *head);
int min(int a, int b);
int help (pnode head, int src, int dst);

int size = 0;
int counter = 0;


void build_graph_cmd(pnode *head)
{

  int size = 0;
  scanf("%d", &size);
  char n = 'B';
  scanf("%c", &n);

  for (int i = 0; i < size; ++i)
  {
    scanf("%c", &n);
    insert_node_cmd(head);
  }
}

void insert_node_cmd(pnode *head)
{

  int id = -1;
  scanf("%d", &id);
  pnode src = getNode(head, id);

  if (src == NULL)
  {
    src = (pnode)malloc(sizeof(node));
    if (src == NULL)
    {
      return;
    }
    src->node_num = id;

    src->edges = NULL;
    src->next = *head;
    *head = src;
  }
  else
  {

    pedge index = src->edges;

    while (index != NULL)
    {
      pedge temp = index->next;
      free(index);
      index = temp;
    }
    src->edges = NULL;
  }
  pedge *lastEdge = &(src->edges);
  int dest = -1;

  while (scanf("%d", &dest) != 0)
  {
    pnode destNode = getNode(head, dest);
    if (destNode == NULL)
    {
      destNode = (pnode)malloc(sizeof(node));
      if (destNode == NULL)
      {
        return;
      }

      destNode->node_num = dest;
      destNode->edges = NULL;
      destNode->next = *head;
      *head = destNode;
    }
    int weight = -1;
    scanf("%d", &weight);

    *lastEdge = (pedge)malloc(sizeof(edge));
    if ((*lastEdge) == NULL)
    {
      return;
    }

    (*lastEdge)->endpoint = destNode;
    (*lastEdge)->weight = weight;
    counter++;
    (*lastEdge)->next = NULL;
    lastEdge = &((*lastEdge)->next);

    
  }
  return;
}

void printGraph_cmd(pnode head)
{
  pnode nodeIndex = head;

  while (nodeIndex != NULL)
  {
    printf("Node %d: ", nodeIndex->node_num);
    pedge edgeIndex = nodeIndex->edges;
    while (edgeIndex != NULL)
    {
      printf("dest %d: weight %d, ", edgeIndex->endpoint->node_num, edgeIndex->weight);
      edgeIndex = edgeIndex->next;
    }
    printf("\n");
    nodeIndex = nodeIndex->next;
  }
}

pnode getNode(pnode *head, int id)
{
  pnode index = *head;
  while (index != NULL)
  {
    if (index->node_num == id)
    {
      return index;
    }
    index = index->next;
  }
  return NULL;
}

void delete_node_cmd(pnode *head)
{
 int key = -1;
    scanf("%d", &key);
    pnode nodeIndex = *head;
    pnode *isFirst = NULL;
    pnode prevAns = NULL;
    if (nodeIndex->node_num == key)
    {
        isFirst = head;
    }

    while (nodeIndex != NULL)
    {
        if (nodeIndex->next != NULL && nodeIndex->next->node_num == key)
        {
            prevAns = nodeIndex;
        }
        if (nodeIndex->edges != NULL && nodeIndex->edges->endpoint->node_num == key)
        {
            pedge temp = nodeIndex->edges;
            nodeIndex->edges = nodeIndex->edges->next;
            free(temp);
            nodeIndex = nodeIndex->next;
            continue;
        }
        pedge edgeIndex = nodeIndex->edges;
        if (edgeIndex != NULL)
        {
            while (edgeIndex->next != NULL)
            {
                if (edgeIndex->next->endpoint->node_num == key)
                {
                    pedge temp = edgeIndex->next;
                    edgeIndex->next = temp->next;
                    free(temp);
                }
                else
                {
                    edgeIndex = edgeIndex->next;
                }
            }
        }
        nodeIndex = nodeIndex->next;
    }

    if (isFirst != NULL)
    {
        pedge edgeIndex = (*isFirst)->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex;
            edgeIndex = edgeIndex->next;
            free(temp);
        }
        pnode temp = *isFirst;
        *isFirst = temp->next;
        free(temp);
    }
    else if (prevAns != NULL)
    {
        pnode remove = prevAns->next;
        pedge edgeIndex = remove->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex;
            edgeIndex = edgeIndex->next;
            free(temp);
        }
        prevAns->next = remove->next;
        free(remove);
    }
}

void deleteGraph_cmd(pnode *head)
{

  int i;
  for (i = 0; i < size; i++)
  {

    pnode nodeind = *head;
    pedge edgeind = nodeind->edges;

    while (edgeind != NULL)
    {
      pedge temp = edgeind->next;
      edgeind = edgeind->next;
      free(temp);
    }
    pnode temp = nodeind;
    nodeind = nodeind->next;
    free(temp);
  }

  *head = NULL;
}

int min(int a, int b)
{
  if (a == 0)
  {
    return b;
  }
  if (b == 0)
  {
    return a;
  }

  if (a < b)
  {
    return a;
  }
  return b;
}

int help (pnode head, int src, int dst)
{


  if (!head)
  {
    return -1;
  }

  int max = 0;
  pnode temp = head;

  while (temp)
  {

    if (max < (temp)->node_num)
    {
      max = (temp)->node_num;
    }
    
    temp = (temp)-> next;
  }

  int arr [max+1][max+1];
  for(int i =0; i <max+1 ; i++){
    for (int j = 0; j < max+1; j++)
    {
      arr[i][j]=infinity;
    }
  }


  temp = head;

  while(temp) {

    pedge edgeIndex = temp->edges;

    while(edgeIndex){
    arr[temp->node_num][edgeIndex->endpoint->node_num]=edgeIndex->weight;
    edgeIndex=edgeIndex->next;
    }

    temp = temp->next;

  }


  for (int k = 0; k < max+1; k++)
  {
    for (int i = 0; i < max+1; i++)
    {
      for (int j = 0; j < max+1; j++)
      {

        if (i == j)
        {
          arr[i][j] = 0;
        }

        else if (i == k || k == j)
        {
          arr[i][j] = arr[i][j];
        }
        else
        {
          int sum = arr[i][k] + arr[k][j];
          if (arr[i][k] == 0 || arr[k][j] == 0)
          {
            sum = 0;
          }
          arr[i][j] = min(arr[i][j], sum);
        }
      }
    }
  }

 

  if(arr[src][dst]==infinity){
    return -1;
  }
  return ((int)arr[src][dst]);

}

int shortsPath_cmd(pnode head, int src, int dst)
{

  int val = 0;
  val = help(head, src, dst);

  return val;
}
