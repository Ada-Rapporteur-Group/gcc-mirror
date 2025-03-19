#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct cblc_field_t                                                                              
    {                                                                                                    
    // This structure must match the code in structs.cc                                                  
    unsigned char *data;              // The runtime data. There is no null terminator                   
    unsigned long  capacity;          // The size of data                                                
    unsigned long  allocated;         // The number of bytes available for capacity                      
    unsigned long  offset;            // Offset from our ancestor (see note below)                       
    char          *name;              // The null-terminated name of this variable                       
    char          *picture;           // The null-terminated picture string.                             
    char          *initial;           // The null_terminated initial value                               
    struct cblc_field_t *parent;      // This field's immediate parent field                             
    struct cblc_field_t *depending_on;// The subject of a DEPENDING ON clause                            
    struct cblc_field_t *depends_on;  // Points downward in heirachy to the subordinate DEPENDING ON     
    unsigned long occurs_lower;       // non-zero for a table                                            
    unsigned long occurs_upper;       // non-zero for a table                                            
    unsigned long attr;               // See cbl_field_attr_t                                            
    signed char type;                 // A one-byte copy of cbl_field_type_t                             
    signed char level;                // This variable's level in the naming heirarchy                   
    signed char digits;               // Digits specified in PIC string; e.g. 5 for 99v999               
    signed char rdigits;              // Digits to the right of the decimal point. 3 for 99v999          
    int         dummy;                // Fills out to a four-byte boundary                               
    } cblc_field_t;                                                                                      

typedef struct cblc_refer_t
    {
    // This structure must match the code in structs.cc
    cblc_field_t     *field;
    unsigned char    *qual_data;   // As qualified by subscripts or refmods
    size_t            qual_size;   // As qualified by refmods or depending_on
    int               flags;       // combines all_flags, move_all, and address_of
    int               dummy;       // Fill out to a multiple of eight bytes
    } cblc_refer_t;


int nlines_c()
  {
  static cblc_field_t field;
  static cblc_refer_t refer;
  __asm__("# int n = 0;\n");
  int n = 0;
  __asm__("# refer.field = (cblc_field_t *)&field;\n");
  refer.field = (cblc_field_t *)&field;
  __asm__("# refer.flags = 0;\n");
  refer.flags = 0;
  __asm__("# refer.qual_data = field.data;\n");
  refer.qual_data = field.data;
  __asm__("# refer.qual_size = 32;\n");
  refer.qual_size = 32;
  }

int main(){nlines_c();}

