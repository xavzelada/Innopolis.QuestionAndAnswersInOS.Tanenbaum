#include <stdio.h>
#include <stdlib.h>

#define member_size(type, member) sizeof(((type *)0)->member)

typedef struct page
{
    int id;
    unsigned int counter;
} page_t;

// Looks for a page with the given id in the given page table
page_t* find_page(page_t *pages, int id, size_t pages_count)
{
    for(int i=0; i<pages_count; i++)
    {
        if(pages[i].id == id)
            return pages+i;
    }
    return NULL;
}

// Finds and returns the address of the first available page frames
// That is either an empty frame (id == 0) or the one with the lowest counter
page_t* available_page(page_t *pages, size_t pages_count)
{
    unsigned int lowest_counter = 1<<31;
    int lowest_id = 0;
    for(int i=0; i<pages_count; i++)
    {
        if(pages[i].id == 0)
            return pages+i;

        if(pages[i].counter < lowest_counter)
        {
            lowest_counter = pages[i].counter;
            lowest_id = i;
        }
    }
    return pages+lowest_id;
}

int main(int argc, char *argv[])
{

    if(argc != 2 && argc != 3)
    {
        printf("Usage: %s <number of page frames> [input file name]\n", argv[0]);
        return 1;
    }

    int page_count = strtol(argv[1], NULL, 10);

    page_t *pages = calloc(page_count, sizeof(page_t));		// page table
    if(pages == NULL)
    {
        printf("Error allocating memory for page table!\n");
        return 2;
    }

    char *filename = (argc == 3) ? argv[2] : "input.txt";
    FILE *input = fopen(filename, "r");
    if(input == NULL)
    {
        printf("Cannot read input file ('%s')!\n", filename);
        return 3;
    }

    int page_id;
    int faults  = 0;
    while(fscanf(input, "%d", &page_id) == 1)
    {
        // Do we already have this page in the table?
        page_t *page = find_page(pages, page_id, page_count);
        if(page != NULL)	// Yes we do!
        {
        }
        else
        {
            faults++;
            page = available_page(pages, page_count);	// find a place for that page

            // Claim it for this page
            page->id = page_id;
            page->counter = 0;
        }

        // Shift all pages' counters to the right
        for(int i=0; i<page_count; i++)
            pages[i].counter >>= 1;

        // Then add the R bit of the new page
        page->counter |= 1 << (member_size(page_t, counter)*8 - 1);
    }

    int page_faults_per_thousand = (faults*1000)/page_count;
    printf("The number of page faults per 1000 = %d",page_faults_per_thousand);

    free(pages);
    fclose(input);

    return 0;
}
