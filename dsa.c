#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsa.h"

static Node *playlistHead = NULL;
static Node *playlistTail = NULL;

/* We keep the Node definition private to the C module. */
typedef struct Node {
    Song song;
    struct Node *prev;
    struct Node *next;
} Node;

static Song songQueue[MAX_QUEUE];
static int queueFront = -1;
static int queueRear = -1;

static Song recentStack[MAX_RECENT];
static int stackTop = -1;

/* ---------------- Doubly Linked List ---------------- */

void addToPlaylist(Song song)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed.\n");
        return;
    }

    newNode->song = song;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (playlistHead == NULL)
    {
        playlistHead = newNode;
        playlistTail = newNode;
    }
    else
    {
        playlistTail->next = newNode;
        newNode->prev = playlistTail;
        playlistTail = newNode;
    }

    printf("\nSong added to playlist successfully!\n");
}

void displayPlaylist(void)
{
    Node *temp = playlistHead;

    if (playlistHead == NULL)
    {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\n========== MY PLAYLIST ==========\n");

    while (temp != NULL)
    {
        printf("%d. %s - %s\n",
               temp->song.id,
               temp->song.title,
               temp->song.artist);

        temp = temp->next;
    }
}

void navigatePlaylist(void)
{
    Node *current = playlistHead;
    int choice;

    if (playlistHead == NULL)
    {
        printf("\nPlaylist is empty.\n");
        return;
    }

    while (1)
    {
        printf("\nCurrent Song: %s - %s\n",
               current->song.title,
               current->song.artist);

        printf("1. Next Song\n");
        printf("2. Previous Song\n");
        printf("3. Exit Navigation\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (current->next != NULL)
                current = current->next;
            else
                printf("\nLast song reached.\n");
        }
        else if (choice == 2)
        {
            if (current->prev != NULL)
                current = current->prev;
            else
                printf("\nFirst song reached.\n");
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("\nInvalid choice.\n");
        }
    }
}

void freePlaylist(void)
{
    Node *temp;

    while (playlistHead != NULL)
    {
        temp = playlistHead;
        playlistHead = playlistHead->next;
        free(temp);
    }

    playlistTail = NULL;
}

/* ---------------- Queue ---------------- */

void enqueueSong(Song song)
{
    if (queueRear == MAX_QUEUE - 1)
    {
        printf("\nQueue is full.\n");
        return;
    }

    if (queueFront == -1)
        queueFront = 0;

    queueRear++;
    songQueue[queueRear] = song;

    printf("\nSong added to queue.\n");
}

void displayQueue(void)
{
    int i;

    if (queueFront == -1 || queueFront > queueRear)
    {
        printf("\nQueue is empty.\n");
        return;
    }

    printf("\n========== UPCOMING QUEUE ==========\n");

    for (i = queueFront; i <= queueRear; i++)
    {
        printf("%d. %s - %s\n",
               i - queueFront + 1,
               songQueue[i].title,
               songQueue[i].artist);
    }
}

Song *dequeueSong(void)
{
    static Song playedSong;

    if (queueFront == -1 || queueFront > queueRear)
    {
        printf("\nQueue is empty.\n");
        return NULL;
    }

    playedSong = songQueue[queueFront];
    queueFront++;

    if (queueFront > queueRear)
    {
        queueFront = -1;
        queueRear = -1;
    }

    return &playedSong;
}

/* ---------------- Stack ---------------- */

void pushRecent(Song song)
{
    if (stackTop == MAX_RECENT - 1)
    {
        printf("\nRecently Played stack is full.\n");
        return;
    }

    stackTop++;
    recentStack[stackTop] = song;
}

void displayRecentlyPlayed(void)
{
    int i;

    if (stackTop == -1)
    {
        printf("\nNo recently played songs.\n");
        return;
    }

    printf("\n========== RECENTLY PLAYED ==========\n");

    for (i = stackTop; i >= 0; i--)
    {
        printf("%d. %s - %s\n",
               stackTop - i + 1,
               recentStack[i].title,
               recentStack[i].artist);
    }
}

/* ---------------- Searching ---------------- */

int searchSongByTitle(Song songs[], int count, const char title[])
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(songs[i].title, title) == 0)
            return i;
    }

    return -1;
}

/* ---------------- Sorting ---------------- */

void sortMostPlayed(Song songs[], int count)
{
    int i, j;
    Song temp;

    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (songs[j].playCount < songs[j + 1].playCount)
            {
                temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}

void sortLeastPlayed(Song songs[], int count)
{
    int i, j;
    Song temp;

    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (songs[j].playCount > songs[j + 1].playCount)
            {
                temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}
