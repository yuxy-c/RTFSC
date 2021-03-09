

/* Allocate SIZE bytes of memory.  */
extern void *malloc (size_t __size) __THROW __attribute_malloc__
     __attribute_alloc_size__ ((1)) __wur;

/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
extern void *calloc (size_t __nmemb, size_t __size)
__THROW __attribute_malloc__ __attribute_alloc_size__ ((1, 2)) __wur;

/* Re-allocate the previously allocated block in __ptr, making the new
   block SIZE bytes long.  */
/* __attribute_malloc__ is not used, because if realloc returns
   the same pointer that was passed to it, aliasing needs to be allowed
   between objects pointed by the old and new pointers.  */
extern void *realloc (void *__ptr, size_t __size)
__THROW __attribute_warn_unused_result__ __attribute_alloc_size__ ((2));

/* Re-allocate the previously allocated block in PTR, making the new
   block large enough for NMEMB elements of SIZE bytes each.  */
/* __attribute_malloc__ is not used, because if reallocarray returns
   the same pointer that was passed to it, aliasing needs to be allowed
   between objects pointed by the old and new pointers.  */
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
__THROW __attribute_warn_unused_result__ __attribute_alloc_size__ ((2, 3));

/* Free a block allocated by `malloc', `realloc' or `calloc'.  */
extern void free (void *__ptr) __THROW;

/* Allocate SIZE bytes allocated to ALIGNMENT bytes.  */
extern void *memalign (size_t __alignment, size_t __size)
__THROW __attribute_malloc__ __attribute_alloc_size__ ((2)) __wur;

/* Allocate SIZE bytes on a page boundary.  */
extern void *valloc (size_t __size) __THROW __attribute_malloc__
     __attribute_alloc_size__ ((1)) __wur;

/* Equivalent to valloc(minimum-page-that-holds(n)), that is, round up
   __size to nearest pagesize. */
extern void *pvalloc (size_t __size) __THROW __attribute_malloc__ __wur;

/* Underlying allocation function; successive calls should return
   contiguous pieces of memory.  */
extern void *(*__morecore) (ptrdiff_t __size) __MALLOC_DEPRECATED;

/* Default value of `__morecore'.  */
extern void *__default_morecore (ptrdiff_t __size)
__THROW __attribute_malloc__  __MALLOC_DEPRECATED;

/* SVID2/XPG mallinfo structure */

struct mallinfo
{
  int arena;    /* non-mmapped space allocated from system */
  int ordblks;  /* number of free chunks */
  int smblks;   /* number of fastbin blocks */
  int hblks;    /* number of mmapped regions */
  int hblkhd;   /* space in mmapped regions */
  int usmblks;  /* always 0, preserved for backwards compatibility */
  int fsmblks;  /* space available in freed fastbin blocks */
  int uordblks; /* total allocated space */
  int fordblks; /* total free space */
  int keepcost; /* top-most, releasable (via malloc_trim) space */
};

/* SVID2/XPG mallinfo2 structure which can handle allocations
   bigger than 4GB.  */

struct mallinfo2
{
  size_t arena;    /* non-mmapped space allocated from system */
  size_t ordblks;  /* number of free chunks */
  size_t smblks;   /* number of fastbin blocks */
  size_t hblks;    /* number of mmapped regions */
  size_t hblkhd;   /* space in mmapped regions */
  size_t usmblks;  /* always 0, preserved for backwards compatibility */
  size_t fsmblks;  /* space available in freed fastbin blocks */
  size_t uordblks; /* total allocated space */
  size_t fordblks; /* total free space */
  size_t keepcost; /* top-most, releasable (via malloc_trim) space */
};

/* Returns a copy of the updated current mallinfo. */
extern struct mallinfo mallinfo (void) __THROW __MALLOC_DEPRECATED;

/* Returns a copy of the updated current mallinfo. */
extern struct mallinfo2 mallinfo2 (void) __THROW;

/* SVID2/XPG mallopt options */
#ifndef M_MXFAST
# define M_MXFAST  1    /* maximum request size for "fastbins" */
#endif
#ifndef M_NLBLKS
# define M_NLBLKS  2    /* UNUSED in this malloc */
#endif
#ifndef M_GRAIN
# define M_GRAIN   3    /* UNUSED in this malloc */
#endif
#ifndef M_KEEP
# define M_KEEP    4    /* UNUSED in this malloc */
#endif

/* mallopt options that actually do something */
#define M_TRIM_THRESHOLD    -1
#define M_TOP_PAD           -2
#define M_MMAP_THRESHOLD    -3
#define M_MMAP_MAX          -4
#define M_CHECK_ACTION      -5
#define M_PERTURB           -6
#define M_ARENA_TEST        -7
#define M_ARENA_MAX         -8

/* General SVID/XPG interface to tunable parameters. */
extern int mallopt (int __param, int __val) __THROW;

/* Release all but __pad bytes of freed top-most memory back to the
   system. Return 1 if successful, else 0. */
extern int malloc_trim (size_t __pad) __THROW;

/* Report the number of usable allocated bytes associated with allocated
   chunk __ptr. */
extern size_t malloc_usable_size (void *__ptr) __THROW;

/* Prints brief summary statistics on stderr. */
extern void malloc_stats (void) __THROW;

/* Output information about state of allocator to stream FP.  */
extern int malloc_info (int __options, FILE *__fp) __THROW;

/* Hooks for debugging and user-defined versions. */
extern void (*__MALLOC_HOOK_VOLATILE __free_hook) (void *__ptr,
                                                   const void *)
__MALLOC_DEPRECATED;
extern void *(*__MALLOC_HOOK_VOLATILE __malloc_hook)(size_t __size,
                                                     const void *)
__MALLOC_DEPRECATED;
extern void *(*__MALLOC_HOOK_VOLATILE __realloc_hook)(void *__ptr,
                                                      size_t __size,
                                                      const void *)
__MALLOC_DEPRECATED;
extern void *(*__MALLOC_HOOK_VOLATILE __memalign_hook)(size_t __alignment,
                                                       size_t __size,
                                                       const void *)
__MALLOC_DEPRECATED;
extern void (*__MALLOC_HOOK_VOLATILE __after_morecore_hook) (void)
  __MALLOC_DEPRECATED;