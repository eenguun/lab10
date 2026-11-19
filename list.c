#include "DS.h"

/* p-ийн зааж буй List-д x утгыг төгсгөлд хийнэ */
void l_push_back(List *p, Student x)
{
	if (p == NULL) return;

    Elm *new_elm = (Elm *)malloc(sizeof(Elm));
    if (new_elm == NULL) return;

    new_elm->x = x;
    new_elm->next = NULL;

    if (p->tail == NULL){
        p->tail = new_elm;
        p->head = new_elm;
    }
    else{
        p->tail->next = new_elm;
        p->tail = new_elm;
    }
    p->len++;
}

/* p-ийн зааж буй List-д x утгыг эхэнд хийнэ
   Бүх элементүүд нэг нэг байрлал хойшилно.
 */
void l_push_front(List *p, Student x)
{
	if (p == NULL) return;

    ELm *new_elm = (Elm *)malloc(sizeof(ELm));
    if (new_elm == NULL) return;

    new_elm->x = x;
    new_elm->next = p->head;

    if (p->head == NULL){
        p->head = new_elm;
        p->tail = new_elm;
    }
    else{
        p->head = new_elm;
    }
    p->len++;
}

/*
  p-ийн зааж буй List-д x утгыг pos байрлалд хийнэ
  pos болон түүнээс хойшхи элементүүд нэг байрлал ухарна.
  Тухайн байрлал List-ийн сүүлийн индексээс их бол төгсгөлд орно.
 */
void l_insert(List *p, Student x, int pos)
{
	if (p == NULL) return;

    if (pos <= 0 || p->head == NULL){
        l_push_front(p, x);
        return;
    }
    if (pos >= p->len){
        l_push_back(p, x);
        return;
    }

    Elm *cur = p->head;
    while (cur->next != p->tail){
        cur = cur->next;
    }

    Elm *new_elm = (Elm *)malloc(sizeof(ELm));
    if (new_elm == NULL) return;

    new_elm->x = x;
    new_elm->next = cur->next;
    cur->next = new_elm;
    p->len++;
}


/*
  p-ийн зааж буй List-н эхлэлээс гаргана.
  List-ийн бүх элементүүд нэг нэг байрлал урагшилна
 */
void l_pop_front(List *p)
{
	if (p == NULL || pos < 0 || pos >= p-len) return;

    Elm *temp = p->head;
    p->head = p->head->next;

    if (p->head == NULL){
        p->tail = NULL;
    }

    free(temp);
    p->len--;
}

/* p-ийн зааж буй List-н төгсгөлөөс гаргана */
void l_pop_back(List *p)
{
	if (p == NULL) return;

    if (p->head == p->tail){
        free(p->head);
        p->head = NULL;
        p->tail = NULL;
        p->len = 0;
        return;
    }

    Elm *cur = p->head;
    while (cur->next != p->tail){
        cur = cur->next;
    }

    free(p->tail);
    cur->next = NULL;
    p->tail = cur;
    p->len--;
}

/* p-ийн зааж буй List-н pos байрлалаас гаргана.
   pos болон түүнээс хойшхи элементүүд нэг байрлал урагшилна.
   pos байрлалаас гарах боломжгүй бол юу ч хийхгүй.
 */
void l_erase(List *p, int pos)
{
	if (p == NULL || pos < 0 || pos >= p->len) return;

    if (pos == 0){
        l_pop_front(p);
        return;
    }

    if (pos == p->len - 1){
        l_pop_back(p);
        return;
    }

    Elm *cur = p->head;
    for(int i = 0; i < pos - 1; i++){
        cur = cur->next;
    }

    Elm *target = cur->next;
    cur->next = target->next;
    free(target);
    p->len--;
}

/*
  p-ийн зааж буй List-н утгуудыг хэвлэнэ.
  Хамгийн эхний элементээс эхлэн дарааллаар, нэг мөрөнд
  нэг л элемент хэвлэнэ.
 */
void l_print(List *p)
{
    if (p == NULL) return;

    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL){
        perror("output.txt neej chadsangui.");
        return;
    }

    Elm *cur = p->head;
    while (cur != NULL){
        student_print(fp, &cur->x);
        cur = cur->next;
    }
    fclose(fp);
}

/*
  p-ийн зааж буй List-с id-тай оюутныг хайн олдсон хаягийг буцаана.
  Олдохгүй бол NULL хаяг буцаана.
 */
Elm *l_search(List *p, const char id[])
{
        if (p == NULL || id == NULL) return NULL;

        Elm *cur = p->head;
        while (cur != NULL){
            if (strcmp(cur->x.id, id) == 0) return cur;
            cur = cur->next;
        }
        return NULL;
}
