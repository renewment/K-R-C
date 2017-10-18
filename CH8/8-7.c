/*
 * malloc accepts a size request without checking its plausibility; free believs
 * that the block it is asked to free contains a valid size field. Improve these
 * routines so they take more pains with error checking.
 */
// deal with malloc(0), header->s.size = 0 or 1
//

#include <stdio.h>

typedef long Align;  /* for alignment to long boundary */

union header {       /* block header: */
   struct {
      union header *ptr; /* next block if on free list */
      unsigned size;     /* size of this block */
   } s;
   Align x;          /* force alignment of blocks */
};
typedef union header Header;

struct usedBlock {
   void *ptr;
   struct usedBlock *next;
};
typedef usedBlock _usedBlock;

static Header base;       /* empty list to get started */
static Header *freep = NULL;     /* start of free list */

static _usedBlock used;

/* malloc:  general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
   Header *p, *prevp;
   Header *morecore(unsigned);
   unsigned nunits;
   
   if (nbytes == 0) {
      printf("error, size of requested memory can not be 0.");
      exit();
   }
   
   nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
   if ((prevp = freep) == NULL) {  /* no free list yet */
      base.s.ptr = freep = prevp = &base;
      base.s.size = 0;
   }
   for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
      if (p->s.size >= nunits) {     /* big enough */
         if (p->s.size == nunits)       /* exactly */
            prevp->s.ptr = p->s.ptr;
         else {
            p->s.size -= nunits;
            p += p->s.size;
            p->s.size = nunits;
         }
         freep = prevp;
         return (void *)(p+1);
      }
      if (p == freep)  /* wrapped around free list */
         if ((p = morecore(nunits)) == NULL)
            return NULL;    /* none left */
   }
}

#define NALLOC  1024    /* minimum #units to request */

/* morecore:  ask system for more memory */
static Header *morecore(unsigned nu)
{
   char *cp, *sbrk(int);
   Header *up;
   
   if (nu < NALLOC)
      nu = NALLOC;
   cp = sbrk(nu * sizeof(Header));
   if (cp == (char *) -1)  /* nospace at all */
      return NULL;
   up = (Header *) cp;
   up->s.size = nu;
   free((void *)(up+1));
   return freep;
}

/* free:  pur block ap in free list */
void free(void *ap)
{
   Header *bp, *p;
   
   bp = (Header *)ap - 1;     /* point to block header */
   
   if (bp->s.size <= 1){
      printf("error, size of memory to be freed is less than 1.");
      exit();
   }
      
   for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
      if (p >= p->s.ptr && (bp > p || bp <p->s.ptr))
         break;   /* freed block at start or end of arena */
   
   if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
      bp->s.size += p->s.ptr->s.size;
      bp->s.ptr = p->s.ptr->s.ptr;
   } else
      bp->s.ptr = p->s.ptr;
   if (p + p->s.size == bp) {          /* join to lower nbr */
      p->s.size += bp->s.size;
      p->s.ptr = bp->s.ptr;
   } else
      p->s.ptr = bp;
   freep = p;
}

