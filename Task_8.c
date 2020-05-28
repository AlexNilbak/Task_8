#include <stdio.h>
#include <stdlib.h>


typedef struct Triangle{
    int x1, y1, x2, y2, x3, y3;
    struct Triangle* next;
    struct Triangle* previous;
}Triangle;


int Check_intersc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

int Add_tr(Triangle** last, Triangle** first, int x1, int y1, int x2, int y2, int x3, int y3){
    Triangle* newtr;
    newtr=(Triangle*)malloc(sizeof(Triangle));
    if(!newtr){
        printf("Error: cannot allocate memory\n");
        exit(-1);
    }
    newtr->x1 = x1;
    newtr->y1 = y1;
    newtr->x2 = x2;
    newtr->y2 = y2;
    newtr->x3 = x3;
    newtr->y3 = y3;
    (*last)->next = newtr;
    newtr->previous = (*last);
    newtr->next = (*first);
    (*first)->previous = newtr;
    (*last)= newtr;
    return 0;
}


int* Get_tr(Triangle** trtr, int number){
    int q;
    int* c;
    c = (int*)malloc(6*sizeof(int));
    if(!c){
        printf("Error: cannot allocate memory\n");
        exit(-1);
    }

    printf("Enter coordinates of new triangle\n");
    printf("x1: ");
    scanf("%d", &c[0]);
    printf("y1: ");
    scanf("%d", &c[1]);
    printf("x2: ");
    scanf("%d", &c[2]);
    printf("y2: ");
    scanf("%d", &c[3]);
    printf("x3: ");
    scanf("%d", &c[4]);
    printf("y3: ");
    scanf("%d", &c[5]);

    for(int i=0; i<number; i++){
        q=Check_intersc(c[0], c[1], c[2], c[3], (*trtr)->x1, (*trtr)->y1, (*trtr)->x2, (*trtr)->y2);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[0], c[1], c[2], c[3], (*trtr)->x1, (*trtr)->y1, (*trtr)->x3, (*trtr)->y3);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[0], c[1], c[2], c[3], (*trtr)->x3, (*trtr)->y3, (*trtr)->x2, (*trtr)->y2);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[4], c[5], c[2], c[3], (*trtr)->x1, (*trtr)->y1, (*trtr)->x2, (*trtr)->y2);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[4], c[5], c[2], c[3], (*trtr)->x1, (*trtr)->y1, (*trtr)->x3, (*trtr)->y3);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[4], c[5], c[2], c[3], (*trtr)->x3, (*trtr)->y3, (*trtr)->x2, (*trtr)->y2);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[0], c[1], c[4], c[5], (*trtr)->x1, (*trtr)->y1, (*trtr)->x2, (*trtr)->y2);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[0], c[1], c[4], c[5], (*trtr)->x1, (*trtr)->y1, (*trtr)->x3, (*trtr)->y3);
        if(q==1){
            free(c);
            return NULL;
        }
        q=Check_intersc(c[0], c[1], c[4], c[5], (*trtr)->x3, (*trtr)->y3, (*trtr)->x2, (*trtr)->y2);
        if(q==1){
            free(c);
            return NULL;
        }
        (*trtr)=(*trtr)->next;
    }
    return c;
}


int Printer(Triangle** first, int number){
    Triangle* tempry;
    tempry = (*first);
    for (int i = 0; i < number; i++){
        printf("Triangle %d: (%d,%d) (%d,%d) (%d,%d)\n", i+1,
               tempry->x1, tempry->y1, tempry->x2, tempry->y2, tempry->x3, tempry->y3);
        tempry = tempry->next;
    }
    return 0;
}


int Check_intersc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    int s, p, r;
    p=0;
    s = (x1-x3)*(y2-y3) - (y1-y3)*(x2-x3);
    r = (x1-x4)*(y2-y4) - (y1-y4)*(x2-x4);
    if(s*r<=0){
        p++;
    }
    s = (x3-x1)*(y4-y1) - (y3-y1)*(x4-x1);
    r = (x3-x2)*(y4-y2) - (y3-y2)*(x4-x2);
    if(s*r<=0){
        p++;
    }
    if(p==2){
        return 1;
    }
    return 0;
}


int main(void){
    int* c;
    int number;
    Triangle** del;
    Triangle** led;
    Triangle* newtr;
    Triangle* first;
    Triangle* last;

    newtr = (Triangle*)malloc(sizeof(Triangle));
    if(!newtr){
        printf("Error: cannot allocate memory\n");
        exit(-1);
    }
    newtr->x1 = 0;
    newtr->y1 = 0;
    newtr->x2 = 0;
    newtr->y2 = 3;
    newtr->x3 = -2;
    newtr->y3 = 0;
    newtr->previous = NULL;
    newtr->next = NULL;

    first=newtr;
    last=newtr;

    Add_tr(&last, &first, 1, -1, 3, 0, 1, 2);

    Add_tr(&last, &first, 2, 2, 3, 4, 4, 1);

    number=3;

    printf("Initial list of triangles:\n");
    Printer(&first, number);
    printf("\n");

    c=Get_tr(&first, number);
    if(c==NULL){
        printf("New triangle intersects another one\n");
        printf("Please repeat\n");
        del=&newtr;
        for (int i = 0; i < number-1; i++){
            led=&((*del)->next);
            free(*del);
            del=led;
        }
        free(*del);
        return 1;
    }

    Add_tr(&last, &first, c[0], c[1], c[2], c[3], c[4], c[5]);

    number++;
    printf("\n");
    printf("New list of triangles:\n");
    Printer(&first, number);
    del=&newtr;
    for (int i = 0; i < number-1; i++){
        led=&((*del)->next);
        free(*del);
        del=led;
    }
    free(*del);
    return 0;
}
