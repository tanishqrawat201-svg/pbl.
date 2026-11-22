#ifndef DSA_H
#define DSA_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_QUEUE 20
#define MAX_RECENT 20

typedef struct {
    int id;
    char title[50];
    char artist[50];
    char genre[30];
    char mood[30];
    int playCount;
} Song;

void addToPlaylist(Song song);
void displayPlaylist(void);
void navigatePlaylist(void);
void freePlaylist(void);

void enqueueSong(Song song);
void displayQueue(void);
Song* dequeueSong(void);

void pushRecent(Song song);
void displayRecentlyPlayed(void);

int searchSongByTitle(Song songs[], int count, const char title[]);
void sortMostPlayed(Song songs[], int count);
void sortLeastPlayed(Song songs[], int count);

#ifdef __cplusplus
}
#endif

#endif
