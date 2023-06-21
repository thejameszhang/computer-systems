#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photoalbum.h"

/* 
1. This method dynamically allocates memory for its Photo
struct and fields. It initializes fields and returns the 
photo struct if description is not NULL. Otherwise, photo
is set to NULL and NULL is returned.
Args:
    - int num
    - const char *desc
Returns:
    - Photo *photo
*/
Photo *create_photo(int id, const char *description) {    
    
    Photo *photo;
    photo = malloc(sizeof(Photo));
    
    /* check if memory allocated correctly */
    if (photo == NULL) {
        return NULL;
    }
    photo->id = id;

    /* null check */
    if (description) {

        /* make space for description and copy desc to it*/
        photo->description = malloc(strlen(description) + 1);
        if (photo->description == NULL) {
            return NULL;
        } 
        /* initialize photo fields */
        strcpy(photo->description, description);
    } else {
        photo->description = NULL;
    }
    return photo;
}

/*
2. This method is given a pointer to a Photo and prints its
identifer and description. 
Args:
    - Photo *photo
*/
void print_photo(Photo *photo) {

    /* null check */
    if (photo) {
        if (photo->description) {
            printf("Photo Id: %d, Description: %s\n", photo->id, photo->description);
        } else {
            printf("Photo Id: %d, Description: None\n", photo->id);
        }
    }
}

/*
3. This method deallocates any dynamically-allocated memory associated
with the given photo pointer.
Args:
    - Photo *photo
*/
void destroy_photo(Photo *photo) {

    /* null check */
    if (photo) {

        /* free memory; we must free description first */
        /* note that even if photo->description not initialized, 
        free(NULL) is fine*/
        if (photo->description) {
            free(photo->description);
        }
        free(photo);
    }
}

/* 
4. This method initializes an album and sets the size to 0.
Args:
    - Album *album
*/
void initialize_album(Album *album) {

    /* null check */
    if (album) {
        album->size = 0;
    }
}

/*
5. This method prints the contents of the album. If 
the album has no photos, the message prints "Album has 
no photos."
Args:
    - const Album *album
*/
void print_album(const Album *album) {

    /* null check */
    if (album) {

        int i; 
        /* case 1 */
        if (album->size == 0) {
            printf("Album has no photos.\n");
        } 
        
        /* case 2 */
        else {
            for (i = 0; i < album->size; i++) {
                print_photo(album->all_photos[i]);
            }
        }
    }
}

/* 
6. This method deallocates any dynamically-allocated 
memory associated with the album and sets album size to 0.
Args:
    - Album *album
*/
void destroy_album(Album *album) {

    /* null check */
    if (album) {
        int i;
        for (i = 0; i < album->size; i++) {
            destroy_photo(album->all_photos[i]);
        }
        album->size = 0;
    }
}

/*
7. This method appends a photo to an album if there's adequate space.
There isn't enough space when the size of the album is smaller than 
MAX_ALBUM_SIZE. No photo is added if a photo cannot be created (if 
create_photo() returns NULL).
Args:
    - Album *album
    - int id
    - const char *description
*/
void add_photo_to_album(Album *album, int id, const char *description) {

    if (album) {
        
        Photo *photo = create_photo(id, description);

        if (photo && album->size < MAX_ALBUM_SIZE) {
            album->all_photos[album->size] = photo;
            album->size += 1;
        } else {
            destroy_photo(photo);
        }
    }
}