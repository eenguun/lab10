#include "DS.h"

/*
  Оюутны мэдээлэл оруулах функц: `p_hash`-ын зааж байгаа хайш хүснэгтэд
  `x`-д хадгалсан оюутны мэдээллийг оруулна.
 */

void ht_insert(HashTable *p_hash, const Student x)
{
        int h = ht_hash(x.id);
        Elm *p_elm = l_search(&p_hash->h[h], x.id);
        if (p_elm == NULL)
                l_push_back(&p_hash->h[h], x);
}


/*
  Хайш тооцоолох функц: `s` тэмдэгтэн цувааны хайшыг тооцоолоод,
  тооцоолсон хайшыг буцаах функц.
 */
int ht_hash(const char s[])
{
        if (s == NULL) return 0;

        unsigned long hash = 5381;
        int c;

        while ((c = (unsigned char)*s++) ! = '\0'){
            hash = ((hash << 5) + hash) + (unsigned long)c;
        } 

        return (int)(hash % HASH_TABLE_SIZE);
}

/*
  Хайш хүснэгтийн утгуудыг эхлүүлэх функц:  Хайш хүснэгтийн бүх элементийн `head`, `tail` утгуудад
  `NULL` оноох ёстой.
 */
void ht_init(HashTable *p_hash)
{
    int i;
    p_hash->h = (List *)malloc(sizeof(List) * HASH_TABLE_SIZE);

    if (p_hash->h == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    p_hash->len = 0;

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        p_hash->h[i].head = NULL;
        p_hash->h[i].tail = NULL;
        p_hash->h[i].len = 0;
    }
}

/*
  Хайх функц: `p_hash`-ыг зааж буй хайш хүснэгтээс `id`-тай оюутныг хайж,
  олдсон оюутны хаягийг буцаах функц. Олдохгүй бол `NULL` хаяг буцаана.
 */
Student *ht_search(HashTable *p_hash, const char id[])
{
        if (p_hash == NULL || p_hash->h == NULL || id == NULL) return NULL;

        int h = ht_hash(id);
        Elm *found = l_search(&p_hash->h[h], id);

        if (found == NULL) return NULL;

        return &found->x;
}

/*
  Мэдээлэл өөрчлөх функц: `p_hash`-ыг зааж буй хайш хүснэгтээс `x.id`-аар
  оюутныг хайж олоод, овог нэрийг `x.ner`, `x.ovog`-оор солино.
  Олдохгүй бол `x` оюутныг шинээр оруулна.
 */
void ht_update(HashTable *p_hash, const Student x)
{
        if (p_hash == NULL || p_hash->h == NULL) return;

        Student *target = ht_search(p_hash, x.id);

        if (target != NULL){
            strncpy(target->ovog, x.ovog, sizeof(target->ovog) - 1);
            target->ovog[sizeof(target->ovog) - 1] = '\0';

            strncpy(target->ner, x.ner, sizeof(target->ner) - 1);
            target->ner[sizeof(target->ner) - 1] = '\0';
        }
        else{
            ht_insert(p_hash, x);
        }
}

/*
  Устгах функц: `p_hash`-ыг зааж буй хайш хүснэгтээс `id`-тай оюутныг хайж
  олж устгана. Олдохгүй бол юу ч хийхгүй.
 */
void ht_del(HashTable *p_hash, const char id[])
{
        if (p_hash == NULL || p_hash->h == NULL || id == NULL) return;

        int h = ht_hash(id);
        List *bucket = &p_hash->h[h];

        Elm *cur = bucket->head;
        int pos = 0;

        while (cur != NULL){
            if (strcmp(cur->x.id, id) == 0){
                l_erase(bucket, pos);
                return;
            }
            cur = cur->next;
            pos++;
        }
}

/*
  Хайш хүснэгтийг чөлөөлөх: Ойн цоорхой үүсгэлгүй, бүх элементийг устган, хаягийг чөлөөлнө.
 */
void ht_release(HashTable *p_hash)
{
        int i;
        for (i = 0; i < HASH_TABLE_SIZE; i++) {
                while (p_hash->h[i].head != NULL)
                        l_pop_front(&p_hash->h[i]);
        }
        free(p_hash->h);
}

/*
  Оюутны мэдээллийг хэвлэх функц: `p`-ын зааж буй оюутны овог, нэр, ID-г хэвлэнэ.
 */
void student_print(FILE *fout, const Student *p)
{
        if (p == NULL)
                fprintf(fout, "xooson\n");
        else
                fprintf(fout, "%s %s %s\n", p->ovog, p->ner, p->id);
}
