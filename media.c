#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONGS 50

// Structure to represent a song
typedef struct {
    char title[50];
    char artist[50];
} Song;

// Structure to represent a node in the media playlist queue
typedef struct Node {
    Song data;
    struct Node* next;
} Node;

// Structure to represent the media playlist queue
typedef struct {
    Node* front;
    Node* rear;
} PlaylistQueue;

// Function to initialize an empty media playlist queue
void initializeQueue(PlaylistQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Function to check if the media playlist queue is empty
int isQueueEmpty(PlaylistQueue* queue) {
    return (queue->front == NULL);
}

// Function to check if the media playlist queue is full (for demonstration purposes)
int isQueueFull(PlaylistQueue* queue) {
    // Assuming a fixed-size array-based representation for demonstration
    return 0;
}

// Function to add a song to the end of the playlist queue
void enqueue(PlaylistQueue* queue, Song song) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = song;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to remove and return a song from the front of the playlist queue
Song dequeue(PlaylistQueue* queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Playlist is empty\n");
        exit(EXIT_FAILURE);
    }

    Node* frontNode = queue->front;
    Song frontSong = frontNode->data;

    queue->front = frontNode->next;
    free(frontNode);

    // If the queue becomes empty after dequeue
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return frontSong;
}

// Function to display the contents of the media playlist queue
void displayQueue(PlaylistQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Playlist is empty\n");
        return;
    }

    Node* current = queue->front;
    printf("Media Playlist:\n");
    while (current != NULL) {
        printf("Title: %s, Artist: %s\n", current->data.title, current->data.artist);
        current = current->next;
    }
}

int main() {
    // Initialize the media playlist queue
    PlaylistQueue playlist;
    initializeQueue(&playlist);

    int choice;
    do {
        printf("\n1. Add Song to Playlist\n");
        printf("2. Play Next Song\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (!isQueueFull(&playlist)) {
                    Song newSong;
                    printf("Enter Song Title: ");
                    scanf("%s", newSong.title);
                    printf("Enter Artist: ");
                    scanf("%s", newSong.artist);
                    enqueue(&playlist, newSong);
                } else {
                    printf("Playlist is full. Cannot add more songs.\n");
                }
                break;
            }
            case 2: {
                if (!isQueueEmpty(&playlist)) {
                    Song playedSong = dequeue(&playlist);
                    printf("Now Playing: %s by %s\n", playedSong.title, playedSong.artist);
                } else {
                    printf("Playlist is empty. Nothing to play.\n");
                }
                break;
            }
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

        // Display the current media playlist
        displayQueue(&playlist);

    } while (choice != 3);

    return 0;
}
