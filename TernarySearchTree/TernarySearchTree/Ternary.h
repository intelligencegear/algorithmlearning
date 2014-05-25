//
//  Ternary.h
//  TernarySearchTree
//
// Copy from: http://www.cs.princeton.edu/~rs/strings/tstdemo.c
//

#ifndef TernarySearchTree_Ternary_h
#define TernarySearchTree_Ternary_h

/* tstdemo.c -- Demo program for ternary search trees
 This code is described in "Ternary Search Trees" by Jon
 Bentley and Robert Sedgewick in the April, 1998, Dr. Dobb's Journal.
 Usage
 tstdemo dictfile		Basic experiments on dictionary
 tstdemo dictfile trysearch	Exercise search routines
 tstdemo dictfile traverse	Test tree traversal
 The first form runs a set of basic experiments comparing
 ternary search trees to hash tables using the dictionary
 in the file dictfile (one word per line).
 The second form allows one to conduct a sequence of searches.
 The input line
 3 elephant
 reports words within Hamming distance 3 of "elephant", and
 -1 .i.i.i
 reports partial matches (words whose 2nd, 4th and 6th letters are i).
 The third form tests the tree traversal routine by printing
 the input file in sorted order.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/* TERNARY SEARCH TREE ALGS */

typedef struct tnode *Tptr;
typedef struct tnode {
    char splitchar;
    Tptr lokid, eqkid, hikid;
} Tnode;
Tptr root;

char *insertstr;

Tptr insert(Tptr p, char *s)
{   if (p == 0) {
    p = (Tptr) malloc(sizeof(Tnode));
    p->splitchar = *s;
    p->lokid = p->eqkid = p->hikid = 0;
}
    if (*s < p->splitchar)
        p->lokid = insert(p->lokid, s);
    else if (*s == p->splitchar) {
        if (*s == 0)
            p->eqkid = (Tptr) insertstr;
		else
            p->eqkid = insert(p->eqkid, ++s);
    } else
        p->hikid = insert(p->hikid, s);
    return p;
}

void cleanup(Tptr p)
{   if (p) {
    cleanup(p->lokid);
    if (p->splitchar) cleanup(p->eqkid);
    cleanup(p->hikid);
    free(p);
}
}

#define BUFSIZE 1000
Tptr buf;
int bufn, freen;
void * freearr[10000];

Tptr insert2(Tptr p, char *s)
{   if (p == 0) {
    /* p = (Tptr) malloc(sizeof(Tnode)); */
    if (bufn-- == 0) {
        buf = (Tptr) malloc(BUFSIZE *
                            sizeof(Tnode));
        freearr[freen++] = (void *) buf;
        bufn = BUFSIZE-1;
    }
    p = buf++;
    p->splitchar = *s;
    p->lokid = p->eqkid = p->hikid = 0;
}
    if (*s < p->splitchar)
        p->lokid = insert2(p->lokid, s);
    else if (*s == p->splitchar) {
        if (*s == 0)
            p->eqkid = (Tptr) insertstr;
		else
            p->eqkid = insert2(p->eqkid, ++s);
    } else
        p->hikid = insert2(p->hikid, s);
    return p;
}

void cleanup2()
{   int i;
    for (i = 0; i < freen; i++)
        free(freearr[i]);
}

void insert3(char *s)
{   int d;
    char *instr = s;
    Tptr pp, *p;
    p = &root;
    while (pp = *p) {
        if ((d = *s - pp->splitchar) == 0) {
            if (*s++ == 0) return;
            p = &(pp->eqkid);
        } else if (d < 0)
            p = &(pp->lokid);
        else
            p = &(pp->hikid);
    }
    for (;;) {
        /* *p = (Tptr) malloc(sizeof(Tnode)); */
        if (bufn-- == 0) {
            buf = (Tptr) malloc(BUFSIZE *
                                sizeof(Tnode));
            freearr[freen++] = (void *) buf;
            bufn = BUFSIZE-1;
        }
        *p = buf++;
        pp = *p;
        pp->splitchar = *s;
        pp->lokid = pp->eqkid = pp->hikid = 0;
        if (*s++ == 0) {
            pp->eqkid = (Tptr) instr;
            return;
        }
        p = &(pp->eqkid);
    }
}

int search(char *s)
{   Tptr p;
    p = root;
    while (p) {
        if (*s < p->splitchar)
            p = p->lokid;
        else if (*s == p->splitchar)  {
            if (*s++ == 0)
                return 1;
            p = p->eqkid;
        } else
            p = p->hikid;
    }
    return 0;
}

int rsearch(Tptr p, char *s)
{   if (!p) return 0;
    if (*s < p->splitchar)
        return rsearch(p->lokid, s);
    else if (*s > p->splitchar)
        return rsearch(p->hikid, s);
    else {
        if (*s == 0) return 1;
        return rsearch(p->eqkid, ++s);
    }
}

int rsearch2(Tptr p, char *s)
{   return (!p ? 0 : (
                      *s == p->splitchar
                      ? (*s ? rsearch2(p->eqkid, ++s) : 1)
                      : (rsearch2(*s < p->splitchar ?
                                  p->lokid : p->hikid, s))
                      ));
}

char *srcharr[100000];
int	srchtop, nodecnt;

void pmsearch(Tptr p, char *s)
{   if (!p) return;
    nodecnt++;
    if (*s == '.' || *s < p->splitchar)
        pmsearch(p->lokid, s);
    if (*s == '.' || *s == p->splitchar)
        if (p->splitchar && *s)
            pmsearch(p->eqkid, s+1);
    if (*s == 0 && p->splitchar == 0)
        srcharr[srchtop++] =
        (char *) p->eqkid;
    if (*s == '.' || *s > p->splitchar)
        pmsearch(p->hikid, s);
}

void nearsearch(Tptr p, char *s, int d)
{   if (!p || d < 0) return;
    nodecnt++;
    if (d > 0 || *s < p->splitchar)
        nearsearch(p->lokid, s, d);
    if (p->splitchar == 0) {
        if ((int) strlen(s) <= d)
            srcharr[srchtop++] = (char *) p->eqkid;
    } else
        nearsearch(p->eqkid, *s ? s+1:s,
                   (*s == p->splitchar) ? d:d-1);
    if (d > 0 || *s > p->splitchar)
        nearsearch(p->hikid, s, d);
}

void traverse(Tptr p)
{   if (!p) return;
    traverse(p->lokid);
    if (p->splitchar)
        traverse(p->eqkid);
    else
        printf("%s\n", (char *) p->eqkid);
    traverse(p->hikid);
}


/* HASH TABLES */

typedef struct hnode *Hptr;
typedef struct hnode {
    char	*str;
    Hptr	next;
} Hnode;
Hptr *hashtab;
int	tabsize;

int hashfunc(char *s)
{   unsigned n = 0;
	for ( ; *s; s++)
		n = 31 * n + *s;
	return n % tabsize;
}

void hbuild(char **a, int n)
{   int	i, j;
	Hptr	p;
	tabsize = n;
	hashtab = (Hptr *) malloc(tabsize * sizeof(Hptr));
	for (i = 0; i < tabsize; i++)
		hashtab[i] = 0;
	for (i = 0; i < tabsize; i++) {
		j = hashfunc(a[i]);
		p = (Hptr) malloc(sizeof(Hnode));
		p->str = a[i];
		p->next = hashtab[j];
		hashtab[j] = p;
	}
}

int hsearch(char *ins)
{   Hptr p;
	char *s, *t;
	for (p = hashtab[hashfunc(ins)]; p; p = p->next) {
		/* if (strcmp(ins, p->str) == 0) return 1; */
		for (s = ins, t = p->str; *s == *t; s++, t++)
			if (*s == 0)
				return 1;
	}
	return 0;
}

#endif
