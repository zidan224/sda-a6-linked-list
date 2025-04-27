#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sll.h"

/********** BODY SUB PROGRAM ***********/

/**** Predikat untuk test keadaan LIST  ****/
boolean ListEmpty (List L) {
    return (First(L) == Nil);
}

/**** Konstruktor/Kreator List Kosong ****/
void CreateList (List *L) {
    First(*L) = Nil;
}

/**** Manajemen Memory ****/
address Alokasi (infotype X) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
    }
    return P;
}

void DeAlokasi (address P) {
    if (P != Nil) {
        free(P);
    }
}

/**** Pencarian sebuah elemen List ****/
address Search (List L, infotype X) {
    address P = First(L);
    while (P != Nil) {
        if (strcmp(Info(P).nama, X.nama) == 0) {   // <-- Fix disini
            return P;
        }
        P = Next(P);
    }
    return Nil;
}

boolean FSearch (List L, address P) {
    address PSearch = First(L);
    while (PSearch != Nil) {
        if (PSearch == P) {
            return true;
        }
        PSearch = Next(PSearch);
    }
    return false;
}

address SearchPrec (List L, infotype X) {
    address Prec = Nil;
    address P = First(L);
    while (P != Nil) {
        if (strcmp(Info(P).nama, X.nama) == 0) {   // <-- Fix disini
            return Prec;
        }
        Prec = P;
        P = Next(P);
    }
    return Nil;
}

/**** PRIMITIF BERDASARKAN NILAI ****/
void InsVFirst (List *L, infotype X) {
    address P = Alokasi(X);
    if (P != Nil) {
        InsertFirst(L, P);
    }
}

void InsVLast (List *L, infotype X) {
    address P = Alokasi(X);
    if (P != Nil) {
        InsertLast(L, P);
    }
}

/**** Penghapusan Elemen ****/
void DelVFirst (List *L, infotype *X) {
    address P;
    DelFirst(L, &P);
    *X = Info(P);
    DeAlokasi(P);
}

void DelVLast (List *L, infotype *X) {
    address P;
    DelLast(L, &P);
    if (P != Nil) {
        *X = Info(P);
        DeAlokasi(P);
    }
}

/**** PRIMITIF BERDASARKAN ALAMAT ****/
void InsertFirst (List *L, address P) {
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter (List *L, address P, address Prec) {
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast (List *L, address P) {
    if (ListEmpty(*L)) {
        InsertFirst(L, P);
    } else {
        address Last = First(*L);
        while (Next(Last) != Nil) {
            Last = Next(Last);
        }
        InsertAfter(L, P, Last);
    }
}

/**** Penghapusan sebuah elemen ****/
void DelFirst (List *L, address *P) {
    *P = First(*L);
    if (*P != Nil) {
        First(*L) = Next(*P);
        Next(*P) = Nil;
    }
}

void DelP (List *L, infotype X) {
    address P = First(*L);
    address Prec = Nil;
    while (P != Nil) {
        if (strcmp(Info(P).nama, X.nama) == 0) {   // <-- Fix disini
            if (Prec == Nil) {
                DelFirst(L, &P);
            } else {
                DelAfter(L, &P, Prec);
            }
            DeAlokasi(P);
            return;
        }
        Prec = P;
        P = Next(P);
    }
}

void DelLast (List *L, address *P) {
    address Prec = Nil;
    *P = First(*L);
    if (*P == Nil) {
        return;
    }
    while (Next(*P) != Nil) {
        Prec = *P;
        *P = Next(*P);
    }
    if (Prec == Nil) {
        First(*L) = Nil;
    } else {
        Next(Prec) = Nil;
    }
}

void DelAfter (List *L, address *Pdel, address Prec) {
    *Pdel = Next(Prec);
    if (*Pdel != Nil) {
        Next(Prec) = Next(*Pdel);
        Next(*Pdel) = Nil;
    }
}

/**** PROSES SEMUA ELEMEN LIST  ****/
void PrintInfo (List L) {
    address P = First(L);
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        while (P != Nil) {
            printf("%s", Info(P).nama);
            if (Next(P) != Nil) {
                printf(" -> ");
            }
            P = Next(P);
        }
        printf(" ->\n");
    }
}

void DelAll (List *L) {
    address PDel;
    while (!ListEmpty(*L)) {
        DelFirst(L, &PDel);
        DeAlokasi(PDel);
    }
}


