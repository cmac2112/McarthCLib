/* define basic error types */
typedef enum{
  LL_ERR_OK,
  LL_ERR_NOT_FOUND,
  LL_ERR_ENTRY_ALLOC,
  LL_ERR_DATA_ALLOC,
} ll_error_e;

/*structure of a given node */
struct ll_node{
  void *data; //see void pointer, allows us to be type agnostic. Think of typeparams in C# kinda
  struct ll_node *next;
};

typedef struct{
  size_t len;
  side_t d_size;

  //byom: caller owns the data, we only store pointers
  //!byom: we malloc and memcpy each insert
  bool byom;
  bool (*match)(void *const, void *const)

  struct ll_node *head;
  struct ll_node *tail;
}ll_t;

ll_error_e ll_insert(ll_t *const ll, void *const data){

  struct ll_node *new = malloc(sizeof(struct ll_node));
  if(new == NULL) return LL_ERR_ENTRY_ALLOC;

  if (ll->byom){
    new->data = data;
  }else{
    new->data = malloc(ll->d_size);
    if(new->data == NULL){
      free(new);
      return LL_ERR_DATA_ALLOC;
    }
    memcpy(new->data, data, ll->d_size)
}
new->next = NULL;
if(ll->head == NULL){
  ll->head = new;
  ll->tail = new;
}else{
  ll->tail->next = new;
  ll->tail = new;
}
ll->len++;
return LL_ERR_OK;
