//
//  main.cpp
//  TernarySearchTree
//
// Copy from: http://www.cs.princeton.edu/~rs/strings/tstdemo.c
//

#include "Ternary.h"

/* TIMING */

int qscomp(const void *p, const void *q )
{   return strcmp(* (char**) p, * (char**) q );
}
#define DOQSORT qsort((void *) a, (size_t) n, sizeof(char *), qscomp)

int instype;

void rinsall(char *a[], int n)
{   int m;
    if (n < 1) return;
    m = n/2;
    switch (instype) {
        case 1: insertstr = a[m]; root = insert(root,a[m]); break;
        case 2: insertstr = a[m]; root = insert2(root,a[m]); break;
        case 3: insert3(a[m]); break;
    }
    rinsall(a, m);
    rinsall(a + m+1, n-m-1);
}

void insall(char *a[], int n)
{   root = 0; bufn = freen = 0;
	rinsall(a, n);
}

int searchtype;

void searchall(char *a[], int n)
{   int i, j;
	char s[100];
    for (i = 0; i < n; i++) {
		strcpy(s, a[i]);
		/* s[0]++;  Uncomment for unsuccessful searches */
		switch(searchtype) {
            case 1: j = search(s); break;
            case 2: srchtop = 0; pmsearch(root, s); j = srchtop; break;
            case 3: srchtop = 0; nearsearch(root, s, 0); j = srchtop; break;
            case 4: j = hsearch(s); break;
            case 5: j = rsearch(root, s); break;
            case 9: j = 1; break;
		}
		if (j != 1)  /* Uncomment for unsuccessful searches */
			printf("search bug at %d, val %d\n", i, j);
	}
}

int	n = 0, starttime,  rptctr;

#define TASK(s)	printf("%s", s);
#define CIN		starttime = clock();
#define COUT	printf("\t%d", clock()-starttime);
#define NL	printf("\n")
#define REPEAT(s)	for (rptctr=0; rptctr<5; rptctr++) { s }; NL;

#define MAXWORDS 250000
#define MAXCHARS 3000000
char space[MAXCHARS], *a[MAXWORDS];

void timeall()
{   TASK("Build TST");
    instype = 1; REPEAT(CIN; insall(a, n); COUT; cleanup(root);)
    TASK("Build TST 2");
    instype = 2; REPEAT(CIN; insall(a, n); COUT; cleanup2();)
    TASK("Build TST 3");
    instype = 3; REPEAT(CIN; insall(a, n); COUT; cleanup2();)
    TASK("Build TST for searches");
    CIN; instype = 2; insall(a, n); COUT; NL;
    TASK("Null Search");
    searchtype = 9; REPEAT(CIN; searchall(a, n); COUT;)
    TASK("TST Search");
    searchtype = 1; REPEAT(CIN; searchall(a, n); COUT;)
    TASK("Rec TST Search");
    searchtype = 5; REPEAT(CIN; searchall(a, n); COUT;)
    TASK("PM TST Search");
    searchtype = 2; REPEAT(CIN; searchall(a, n); COUT;)
    TASK("Near TST Search");
    searchtype = 3; REPEAT(CIN; searchall(a, n); COUT;)
	TASK("Remove TST")
    CIN; cleanup2(); COUT; NL;
	TASK("Build Hash");
    CIN; hbuild(a, n); COUT; NL;
    TASK("Hash Search");
    searchtype = 4; REPEAT(CIN; searchall(a, n); COUT;)
    /* Hash table is still using space */
}

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

void trysearch()
{	char s[100];
	int i, d;
	instype = 2; insall(a, n);
	printf("Enter searches: <distance> <word>\n");
	while (scanf("%d %s", &d, s) != EOF) {
		nodecnt = srchtop = 0;
		CIN;
		if (d < 0)
			pmsearch(root, s);
		else
			nearsearch(root, s, d);
		printf(" matches=%d nodes=%d clicks=", srchtop, nodecnt);
		COUT; NL;
		for (i = 0; i < min(srchtop, 40); i++)
			printf("  %s", srcharr[i]);
		NL;
	}
}


int main(int argc, char *argv[])
{	int	i, globalstarttime;
	char *s = space, *t, *fname;
	FILE *fp;
	if (argc == 1) { /* no args */
		fname = "dictwords.txt"; /* default dict file */
	} else /* at least one arg: file name */
		fname = argv[1];
	setbuf(stdout, 0);
	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "  Can't open file\n");
		exit(1);
	}
	globalstarttime = clock();
	TASK("Big Malloc");
    CIN; t = (char *) malloc(8000000*sizeof(char));
    free(t); COUT; NL;
	TASK("Reading Input");
    CIN;
    a[0] = s;
    while ((i = getc(fp)) != EOF) {
        if (i == '\n') {
            *s++ = 0;
            a[++n] = s;
        } else
            *s++ = i;
    }
    COUT; NL;
	TASK("System Qsort");
    CIN; DOQSORT; COUT; NL;
	if (argc < 3) { /* at most one arg: file name */
		timeall();
	} else {
		if (strcmp(argv[2], "trysearch") == 0) {
			trysearch();
		} else if (strcmp(argv[2], "traverse") == 0) {
			instype = 2; insall(a, n); traverse(root);
		} else
			printf("Unrecognized option\n");
	}
	i = clock() - globalstarttime;
	printf("Total clicks\t%d\nTotal secs\t%4.3f\n",
           i, (double) i / CLOCKS_PER_SEC);
	return 0;
}
