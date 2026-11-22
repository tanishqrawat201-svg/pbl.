MUSIC PLAYLIST MANAGER - CLEAN VS CODE VERSION

FILES
-----
dsa.h      -> C DSA declarations
dsa.c      -> C DSA implementation
main.cpp   -> C++ OOP application

DSA IN C
--------
1. Doubly Linked List -> Playlist
2. Queue -> Upcoming Songs
3. Stack -> Recently Played
4. Linear Search -> Song Search
5. Bubble Sort -> Most/Least Played

OOP IN C++
----------
1. Classes and Objects
2. Encapsulation
3. Inheritance
4. Polymorphism
5. User
6. NormalUser
7. PremiumUser
8. MusicLibrary
9. Playlist
10. RecommendationSystem
11. FavoriteManager
12. FileManager

WINDOWS / MINGW
----------------
Open this folder in VS Code.

Run these commands in the VS Code terminal:

gcc -c dsa.c -o dsa.o
g++ main.cpp dsa.o -o MusicPlaylistManager.exe

Then:

.\MusicPlaylistManager.exe

MAC / LINUX
-----------
gcc -c dsa.c -o dsa.o
g++ main.cpp dsa.o -o MusicPlaylistManager
./MusicPlaylistManager

IMPORTANT
---------
The project does not use a database.
Audio playback/API are not included in this core academic version.
