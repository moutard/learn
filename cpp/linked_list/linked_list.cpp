// A templated C++ singly linked list.

template <class T>

// Rq: when defining a classes in C++ particularly in template form is best to
// explicitly add copy constructors and assignement operators.
class ListElement {
  public:
    ListElement(const T &value): next(NULL), data(value){}
    ~ListElement(){}

    ListElement *getNext() const {return next;}
    const T& value() const {return data;}
    void setNext(ListElement *elem) {next = elem;}
    void setValue(const T &value) {data = value;}

  private:
    ListElement *next;
    T data;
};


typedef struct IntElement {
  struct IntElement *next;
  int data;
} IntElement;

/*
bool insertInFront( IntElement *head, int data ){
  IntElement *newElem = malloc( sizeof(IntElement) ); if( !newElem ) return false;
  newElem->data = data;
  newElem->next = head;
  head = newElem; // Incorrect! Updates only the local head pointer return true;
}
*/
// Pointer are passeb by copy !
bool insertInFront(IntElement **head, int data){
  IntElement *newElement = malloc(sizeof(IntElement));
  if(!newElement) return false; // malloc do not find enough space.

  newElement->data = data;
  newElement->next = *head;
  *head = newElement;
  return true;
};
// in C++ the head pointer could also be passe in by reference.

bool deleteElement( IntElement **head, IntElement *deleteMe ) {
  IntElement *elem;
  if (!head || !*head || !deleteMe ) /* Check for null pointers */ return false;
  elem = *head;
  if( deleteMe == *head ){ /* special case for head */
    *head = elem->next; free(deleteMe); return true;
  }
  while( elem ){
    if( elem->next == deleteMe ){
    /* elem is element preceding deleteMe */
    elem->next = deleteMe->next;
    free(deleteMe);
    return true;
  }
  elem = elem->next; }
  /* deleteMe not found */
  return false;
};

void deleteList( IntElement **head ) {
  IntElement *deleteMe = *head;
  while( deleteMe ){
    IntElement *next = deleteMe->next;
    free(deleteMe);
    deleteMe = next;
  }
  *head = NULL;
};
