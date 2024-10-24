#include "freeList.h"

freeList::freeList(long int* inRAM, int size) {
    head = inRAM;
    head[0] = size; 
    head[1] = 0;    

long int* freeList::reserve_space(int size) {
    long int* current = head;
    long int* previous = nullptr;

    while (current != nullptr) {
        if (current[0] >= size) {
            
            long int* allocated = current;
            int remaining = current[0] - size;

            if (remaining > 0) {
                current += size;
                current[0] = remaining;
            }
            else {
                
                if (previous) {
                    previous[1] = current[1];
                }
                else {
                    head = (long int*)current[1];
                }
            }

            return allocated;
        }
        previous = current;
        current = (long int*)current[1];
    }

    
    return nullptr;
}

void freeList::free_space(long int* location) {
    location[1] = (long int)head; 
    head = location;              
}
void freeList::coalesce_forward() {
    long int* current = head;

    while (current != nullptr && current[1] != 0) {
        long int* next = (long int*)current[1];

        
        if (current + current[0] == next) {
            // Merge the blocks
            current[0] += next[0];      
            current[1] = next[1];       

        else {
            current = next;
        }
    }
}
// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
