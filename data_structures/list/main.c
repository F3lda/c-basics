#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
//#include <conio.h>

typedef struct element {
    int data;
    struct element *next;
} ELEMENT;

typedef struct {
    ELEMENT *first;
} LIST;

LIST* ListCreate()
{
    LIST *List = (LIST*)malloc(sizeof(LIST));
    if (List != NULL) {
        List->first = NULL;
    }
    return List;
}

int ListAddElementToTheTop(LIST *List, int data)
{
    ELEMENT *added = (ELEMENT*)malloc(sizeof(ELEMENT));
    if (added == NULL) {return 1;}
    added->data = data;
    added->next = List->first;
    List->first = added;
    return 0;
}

int ListAddElementToTheEnd(LIST *List, int data)
{
    if (List->first == NULL) {
        return ListAddElementToTheTop(List,data);
    }

    ELEMENT *temp = List->first;
    ELEMENT *added = (ELEMENT*)malloc(sizeof(ELEMENT));
    if (added == NULL) {return 1;}
    added->data = data;
    added->next = NULL;

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = added;
    return 0;
}

ELEMENT* ListFindElement(LIST *List, int data)
{
    ELEMENT *temp = List->first;
    while(temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    return temp;
}

int ListAddElementBeforeTheSearchedElement(LIST *List, int data, int searched)
{
    if(List->first == NULL || ListFindElement(List,searched) == NULL) {
        return 2;
    }

    ELEMENT *added = (ELEMENT*)malloc(sizeof(ELEMENT));
    if (added == NULL) {return 1;}
    added->data = data;

    ELEMENT *found = ListFindElement(List,searched);
    if (found == List->first) {
        added->next = found;
        List->first = added;
    } else {
        ELEMENT *temp = List->first;
        while(temp->next != found) {
            temp = temp->next;
        }
        added->next = found;
        temp->next = added;
    }
    return 0;
}

int ListAddElementBehindTheSearchedElement(LIST *List, int data, int searched)
{
    if (List->first == NULL || ListFindElement(List,searched) == NULL) {
        return 2;
    }

    ELEMENT *added = (ELEMENT*)malloc(sizeof(ELEMENT));
    if (added == NULL) {return 1;}
    added->data = data;

    ELEMENT *found = ListFindElement(List,searched);
    added->next = found->next;
    found->next = added;
    return 0;
}

int ListPrint(LIST *List)
{
    ELEMENT *temp = List->first;
    while(temp != NULL) {
        printf("%d\n",temp->data);
        temp = temp->next;
    }
    return 0;
}

int ListPopElementFromTheBeginning(LIST *List, int *data)
{
    if (List->first == NULL) {
        return 2;
    }
    ELEMENT *destroy = List->first;
    List->first = destroy->next;
    *data = destroy->data;
    free(destroy);
    return 0;
}

int ListPopElementFromTheEnd(LIST *List, int *data)
{
    if (List->first == NULL) {
        return 2;
    }
    if (List->first->next == NULL) {
        *data = List->first->data;
        free(List->first);
        List->first = NULL;
    } else {
        ELEMENT *temp = List->first;
        while(temp->next->next != NULL){
            temp = temp->next;
        }
        *data = temp->next->data;
        free(temp->next);
        temp->next = NULL;
    }
    return 0;
}

int ListPopTheSearchedElement(LIST *List, int *data, int searched)
{
    if (List->first == NULL || ListFindElement(List,searched) == NULL) {
        return 2;
    }

    ELEMENT *found = ListFindElement(List,searched);
    if (found == List->first) {
        *data = found->data;
        List->first = found->next;
        free(found);
    } else {
        ELEMENT *temp = List->first;
        while(temp->next != found) {
            temp = temp->next;
        }
        *data = found->data;
        temp->next = found->next;
        free(found);
    }
    return 0;
}

int ListIsEmpty(LIST *List)
{
    if (List->first == NULL) {
        return 1;
    }
    return 0;
}

int ListClear(LIST *List)
{
    ELEMENT *temp = List->first;
    ELEMENT *destroy;
    while(temp != NULL) {
        destroy = temp;
        temp = temp->next;
        free(destroy);
    }
    List->first = NULL;
    return 0;
}

int ListDestroy(LIST *List)
{
    ELEMENT *temp = List->first;
    ELEMENT *destroy;
    while(temp != NULL) {
        destroy = temp;
        temp = temp->next;
        free(destroy);
    }
    free(List);
    List = NULL;
    return 0;
}

int ListError(int number)
{
    if (number == 1) {
        printf("ERROR - ELEMENT NOT CREATED: not enough memory space!\n");
        //exit(number);
        return 1;
    } else if(number == 2) {
        printf("ERROR - ELEMENT NOT FOUND: the list is empty or the element does not exist!\n");
        return 2;
    }
    return 0;
}

void draw_main_menu()
{
    system("cls||clear");
    printf("SELECT LIST ACTION (by pressing a number and Enter):\n1) Add element\n2) Remove element\n3) Find element\n4) Print the list\n5) Empty the list\n6) Exit\n-------------------\n");
}

char get_char()
{
    char ch;
    printf("> ");
    scanf(" %c", &ch); // leading blank to skip optional white space and get char
    scanf("%*c"); // remove <enter> char from buffer
    return ch-48;
    //return getch()-48;
}

int main()
{
    LIST *List;
    List = ListCreate();
    if (List == NULL) {printf("ERROR - LIST NOT CREATED: not enough memory space!\nPROGRAM ENDED!\n"); return -1;}
    draw_main_menu();
    printf("> List successfully created\n");
    int choice = 0,subchoice = 0;
    do {
        choice = get_char();
        if (choice == 1) {
            system("cls||clear");
            printf("CHOOSE FROM OPTIONS:\nAdd an element:\n1) to the beginning of the list\n2) to the end of the list\n3) before the searched element\n4) after the searched element\n5) Back <-\n-------------------\n");
            subchoice = get_char();
            if (subchoice == 1) {
                int number;
                system("cls||clear");
                printf("Adding an element to the beginning of the list:\n> Enter the value of the new element: ");
                scanf(" %d",&number);
                ListAddElementToTheTop(List,number);
                draw_main_menu();
                printf("> An element with value %d was added to the beginning of the list\n",number);
            } else if (subchoice == 2) {
                int number;
                system("cls||clear");
                printf("Adding an element to the end of the list:\n> Enter the value of the new element: ");
                scanf(" %d",&number);
                ListAddElementToTheEnd(List,number);
                draw_main_menu();
                printf("> An element with value %d was added to the end of the list\n",number);
            } else if (subchoice == 3) {
                int number,searched;
                system("cls||clear");
                printf("Adding an element before the searched element:\n> Enter the value of the new element: ");
                scanf(" %d",&number);
                printf("> Enter the element you are looking for: ");
                scanf(" %d",&searched);
                if (ListFindElement(List,searched) == NULL) {
                    draw_main_menu();
                    printf("> ERROR: The element with the value %d was NOT added - the element with the value %d does not exist\n",number,searched);
                } else {
                    ListAddElementBeforeTheSearchedElement(List,number,searched);
                    draw_main_menu();
                    printf("> An element with value %d was added before the searched element with value %d\n",number,searched);
                }
            } else if (subchoice == 4) {
                int number,searched;
                system("cls||clear");
                printf("Adding an element after the searched element:\n>Enter the value of the new element: ");
                scanf(" %d",&number);
                printf("> Enter the element you are looking for: ");
                scanf(" %d",&searched);
                if (ListFindElement(List,searched) == NULL) {
                    draw_main_menu();
                    printf("> ERROR: The element with the value %d was NOT added - the element with the value %d does not exist\n",number,searched);
                } else {
                    ListAddElementBehindTheSearchedElement(List,number,searched);
                    draw_main_menu();
                    printf("> An element with value %d was added after the searched element with value %d\n",number,searched);
                }
            } else {
                draw_main_menu();
            }
        } else if (choice == 2) {
            system("cls||clear");
            printf("SELECT FROM OPTIONS:\nRemove element:\n1) from start of list\n2) from end of list\n3) searched\n4) Back <-\n-------------------\n");
            subchoice = get_char();
            if (subchoice == 1) {
                int number;
                ListPopElementFromTheBeginning(List,&number);
                draw_main_menu();
                printf("> The element from the beginning of the list with the value %d has been removed\n",number);
            } else if (subchoice == 2) {
                int number;
                ListPopElementFromTheEnd(List,&number);
                draw_main_menu();
                printf("> The element from the end of the list with value %d has been removed\n",number);
            } else if (subchoice == 3) {
                int number,searched;
                system("cls||clear");
                printf("Remove the searched element:\n> Enter the value of the searched element: ");
                scanf(" %d",&searched);
                if (ListFindElement(List,searched) == NULL) {
                    draw_main_menu();
                    printf("> ERROR: Searched element with value %d DOES NOT EXIST\n",searched);
                } else {
                    ListPopTheSearchedElement(List,&number,searched);
                    draw_main_menu();
                    printf("> The searched element with value %d has been removed\n",number);
                }
            } else {
                draw_main_menu();
            }
        } else if (choice == 3) {
            int searched;
            system("cls||clear");
            printf("Element search:\n>Enter the value of the element you are looking for: ");
            scanf(" %d",&searched);
            if (ListFindElement(List,searched) == NULL) {
                draw_main_menu();
                printf("> Searched element with value %d DOES NOT EXIST\n",searched);
            } else {
                draw_main_menu();
                printf("> Searched element with value %d FOUND\n",searched);
            }
        } else if (choice == 4) {
            system("cls||clear");
            printf("DETAILED LIST:\n-------------------\n");
            ListPrint(List);
            if (List->first == NULL) {printf("(EMPTY)\n");}
            printf("-------------------\n");
            system("pause");
            draw_main_menu();
        } else if (choice == 5) {
            ListClear(List);
            draw_main_menu();
            printf("> The list has been emptied\n");
        }
    } while(choice != 6);

    ListDestroy(List);
    return 0;
}
