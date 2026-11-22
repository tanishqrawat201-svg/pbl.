#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>

extern "C" {
#include "dsa.h"
}

using namespace std;

/* =====================================================
                    MUSIC LIBRARY
   ===================================================== */

class MusicLibrary
{
private:
    vector<Song> songs;

public:
    void loadSongs()
    {
        songs = {
            {1, "Believer", "Imagine Dragons", "Pop/Rock", "Energetic", 15},
            {2, "Perfect", "Ed Sheeran", "Pop", "Romantic", 11},
            {3, "Blinding Lights", "The Weeknd", "Pop", "Energetic", 8},
            {4, "Heat Waves", "Glass Animals", "Pop", "Chill", 6},
            {5, "Counting Stars", "OneRepublic", "Pop/Rock", "Motivational", 13},
            {6, "Shape of You", "Ed Sheeran", "Pop", "Happy", 9},
            {7, "Kesariya", "Arijit Singh", "Bollywood", "Romantic", 12},
            {8, "Apna Bana Le", "Arijit Singh", "Bollywood", "Emotional", 5},
            {9, "Brown Munde", "AP Dhillon", "Punjabi", "Party", 10},
            {10, "Heeriye", "Jasleen Royal", "Indie", "Chill", 7}
        };
    }

    vector<Song>& getSongs()
    {
        return songs;
    }

    Song* findSong(int id)
    {
        for (Song& song : songs)
        {
            if (song.id == id)
                return &song;
        }

        return nullptr;
    }

    void displayLibrary() const
    {
        cout << "\n========================================\n";
        cout << "          PRELOADED SONGS LIBRARY\n";
        cout << "========================================\n";

        for (const Song& song : songs)
        {
            cout << song.id << ". "
                 << song.title << " - "
                 << song.artist
                 << " | " << song.genre
                 << " | " << song.mood
                 << " | Plays: " << song.playCount << '\n';
        }
    }

    void searchSong()
    {
        string title;

        cout << "\nEnter exact song title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, title);

        int index = searchSongByTitle(
            songs.data(),
            static_cast<int>(songs.size()),
            title.c_str()
        );

        if (index == -1)
        {
            cout << "\nSong not found.\n";
            return;
        }

        Song& song = songs[index];

        cout << "\n========== SONG FOUND ==========\n";
        cout << "Title  : " << song.title << '\n';
        cout << "Artist : " << song.artist << '\n';
        cout << "Genre  : " << song.genre << '\n';
        cout << "Mood   : " << song.mood << '\n';
    }

    void filterGenre()
    {
        string genre;
        bool found = false;

        cout << "\nEnter genre: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, genre);

        cout << "\n========== " << genre << " SONGS ==========\n";

        for (const Song& song : songs)
        {
            if (song.genre == genre)
            {
                cout << song.id << ". "
                     << song.title << " - "
                     << song.artist << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No songs found.\n";
    }

    void filterMood()
    {
        string mood;
        bool found = false;

        cout << "\nEnter mood: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, mood);

        cout << "\n========== " << mood << " SONGS ==========\n";

        for (const Song& song : songs)
        {
            if (song.mood == mood)
            {
                cout << song.id << ". "
                     << song.title << " - "
                     << song.artist << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No songs found.\n";
    }
};

/* =====================================================
                       USER CLASSES
   ===================================================== */

class User
{
protected:
    string name;

public:
    User(string n) : name(n) {}

    virtual void showFeatures() = 0;

    virtual ~User() {}
};

class NormalUser : public User
{
public:
    NormalUser(string n) : User(n) {}

    void showFeatures() override
    {
        cout << "\n========== NORMAL USER ==========\n";
        cout << "Welcome, " << name << "!\n";
        cout << "Search | Playlist | Queue | Favorites\n";
    }
};

class PremiumUser : public User
{
public:
    PremiumUser(string n) : User(n) {}

    void showFeatures() override
    {
        cout << "\n========== PREMIUM USER ==========\n";
        cout << "Welcome, " << name << "!\n";
        cout << "All Normal Features + Recommendations + Statistics\n";
    }
};

/* =====================================================
                       PLAYLIST
   ===================================================== */

class Playlist
{
public:
    void addSong(Song* song)
    {
        if (song != nullptr)
            addToPlaylist(*song);
        else
            cout << "\nInvalid Song ID.\n";
    }

    void show()
    {
        displayPlaylist();
    }

    void navigate()
    {
        navigatePlaylist();
    }
};

/* =====================================================
                 RECOMMENDATION SYSTEM
   ===================================================== */

class RecommendationSystem
{
public:
    void recommend(const vector<Song>& songs)
    {
        string mood;
        bool found = false;

        cout << "\nEnter mood: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, mood);

        cout << "\n========== SMART RECOMMENDATIONS ==========\n";

        for (const Song& song : songs)
        {
            if (song.mood == mood)
            {
                cout << song.title
                     << " - "
                     << song.artist << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No recommendations available.\n";
    }
};

/* =====================================================
                    FAVORITES
   ===================================================== */

class FavoriteManager
{
private:
    vector<int> favoriteIds;

public:
    void add(Song* song)
    {
        if (song == nullptr)
        {
            cout << "\nInvalid Song ID.\n";
            return;
        }

        if (find(favoriteIds.begin(),
                 favoriteIds.end(),
                 song->id) == favoriteIds.end())
        {
            favoriteIds.push_back(song->id);
            cout << "\n" << song->title
                 << " added to Favorites.\n";
        }
        else
        {
            cout << "\nSong is already in Favorites.\n";
        }
    }

    void show(const vector<Song>& songs)
    {
        cout << "\n========== FAVORITES ==========\n";

        if (favoriteIds.empty())
        {
            cout << "No favorite songs.\n";
            return;
        }

        for (int id : favoriteIds)
        {
            for (const Song& song : songs)
            {
                if (song.id == id)
                {
                    cout << song.title
                         << " - "
                         << song.artist << '\n';
                }
            }
        }
    }
};

/* =====================================================
                     FILE HANDLING
   ===================================================== */

class FileManager
{
public:
    void save(const vector<Song>& songs)
    {
        ofstream file("songs.txt");

        if (!file)
        {
            cout << "\nUnable to open songs.txt\n";
            return;
        }

        for (const Song& song : songs)
        {
            file << song.id << '|'
                 << song.title << '|'
                 << song.artist << '|'
                 << song.genre << '|'
                 << song.mood << '|'
                 << song.playCount << '\n';
        }

        file.close();

        cout << "\nSong data saved to songs.txt\n";
    }
};

/* =====================================================
                    PLAY / STATISTICS
   ===================================================== */

void playSong(MusicLibrary& library)
{
    int id;

    library.displayLibrary();

    cout << "\nEnter Song ID to play: ";
    cin >> id;

    Song* song = library.findSong(id);

    if (song == nullptr)
    {
        cout << "\nInvalid Song ID.\n";
        return;
    }

    song->playCount++;
    pushRecent(*song);

    cout << "\n========== NOW PLAYING ==========\n";
    cout << song->title << " - "
         << song->artist << '\n';
    cout << "Play Count: "
         << song->playCount << '\n';
}

void showMostPlayed(MusicLibrary& library)
{
    vector<Song> copy = library.getSongs();

    sortMostPlayed(copy.data(), static_cast<int>(copy.size()));

    cout << "\n========== MOST PLAYED ==========\n";

    for (const Song& song : copy)
    {
        cout << song.title
             << " - "
             << song.playCount
             << " plays\n";
    }
}

void showLeastPlayed(MusicLibrary& library)
{
    vector<Song> copy = library.getSongs();

    sortLeastPlayed(copy.data(), static_cast<int>(copy.size()));

    cout << "\n========== LEAST PLAYED ==========\n";

    for (const Song& song : copy)
    {
        cout << song.title
             << " - "
             << song.playCount
             << " plays\n";
    }
}

/* =====================================================
                         MAIN
   ===================================================== */

int main()
{
    MusicLibrary library;
    Playlist playlist;
    RecommendationSystem recommendation;
    FavoriteManager favorites;
    FileManager fileManager;

    library.loadSongs();

    string name;

    cout << "========================================\n";
    cout << "       MUSIC PLAYLIST MANAGER\n";
    cout << "========================================\n";

    cout << "\nEnter your name: ";
    cin >> name;

    int userChoice;

    cout << "\n1. Normal User\n";
    cout << "2. Premium User\n";
    cout << "Enter choice: ";
    cin >> userChoice;

    User* user = nullptr;

    if (userChoice == 2)
        user = new PremiumUser(name);
    else
        user = new NormalUser(name);

    user->showFeatures();

    int choice;

    while (true)
    {
        cout << "\n\n========================================\n";
        cout << "              MAIN MENU\n";
        cout << "========================================\n";

        cout << "1. View Music Library\n";
        cout << "2. Search Song\n";
        cout << "3. Filter by Genre\n";
        cout << "4. Filter by Mood\n";
        cout << "5. Add Song to Playlist\n";
        cout << "6. View Playlist\n";
        cout << "7. Navigate Playlist\n";
        cout << "8. Add Song to Queue\n";
        cout << "9. View Queue\n";
        cout << "10. Play Next from Queue\n";
        cout << "11. Play Song\n";
        cout << "12. Recently Played\n";
        cout << "13. Add Favorite\n";
        cout << "14. View Favorites\n";
        cout << "15. Smart Recommendations\n";
        cout << "16. Most Played\n";
        cout << "17. Least Played\n";
        cout << "18. Save Data\n";
        cout << "19. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                library.displayLibrary();
                break;

            case 2:
                library.searchSong();
                break;

            case 3:
                library.filterGenre();
                break;

            case 4:
                library.filterMood();
                break;

            case 5:
            {
                int id;
                library.displayLibrary();

                cout << "\nEnter Song ID: ";
                cin >> id;

                playlist.addSong(library.findSong(id));
                break;
            }

            case 6:
                playlist.show();
                break;

            case 7:
                playlist.navigate();
                break;

            case 8:
            {
                int id;
                library.displayLibrary();

                cout << "\nEnter Song ID: ";
                cin >> id;

                Song* song = library.findSong(id);

                if (song != nullptr)
                    enqueueSong(*song);
                else
                    cout << "\nInvalid Song ID.\n";

                break;
            }

            case 9:
                displayQueue();
                break;

            case 10:
            {
                Song* song = dequeueSong();

                if (song != nullptr)
                {
                    song->playCount++;
                    pushRecent(*song);

                    cout << "\nNow Playing: "
                         << song->title
                         << " - "
                         << song->artist << '\n';
                }

                break;
            }

            case 11:
                playSong(library);
                break;

            case 12:
                displayRecentlyPlayed();
                break;

            case 13:
            {
                int id;

                library.displayLibrary();

                cout << "\nEnter Song ID: ";
                cin >> id;

                favorites.add(library.findSong(id));
                break;
            }

            case 14:
                favorites.show(library.getSongs());
                break;

            case 15:
                recommendation.recommend(library.getSongs());
                break;

            case 16:
                showMostPlayed(library);
                break;

            case 17:
                showLeastPlayed(library);
                break;

            case 18:
                fileManager.save(library.getSongs());
                break;

            case 19:
                fileManager.save(library.getSongs());
                freePlaylist();
                delete user;

                cout << "\nThank you for using Music Playlist Manager!\n";
                return 0;

            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    }
}
