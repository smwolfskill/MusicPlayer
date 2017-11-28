#include "playlist.h"

Playlist::Playlist(const std::string name, const SongVector songs, int length)
{
    this->name = name;
    this->length = length;
    this->songs = songs;
    selected = songs.begin();
    selected_index = 0;
    modified = false;
}

Playlist::Playlist(const std::string representation, const MusicLibrary * const lib)
{
    //TODO
    try
    {
        /*std::size_t lastChar;
        int result = std::stoi(str, &lastChar, 10);
        if(result < 0 || result > 1) {
            //load bool
            //corrupted/invalid representation
        }*/
        //TODO: can just load as "true"/"false"; easy.
    }
    catch (std::invalid_argument&)
    {

    }
    catch (std::out_of_range&)
    {

    }
    selected = songs.begin();
    modified = false;
}

void Playlist::setName(const std::string newName)
{
    name = newName;
    modified = true;
}

const Song * Playlist::getSelected() const
{
    if(selected_index < 0) {
        return nullptr; //none selected.
    }
    return *selected;
}

const Song * Playlist::getNext()
{
    if(selected == songs.end()) { //at end. loop back to beginning.
        selected = songs.begin();
        selected_index = 0;
    } else { //go to next song.
        selected++;
        selected_index++;
    }
    return getSelected();
}

void Playlist::goToFirst()
{
    selected = songs.begin();
    selected_index = 0;
}

bool Playlist::goToSong(const Song * const toGoTo)
{
    SongVector::const_iterator * location = (SongVector::const_iterator *) malloc(sizeof(SongVector::const_iterator));
    int index = findSong(toGoTo, location);
    if(index == -1) {
        free(location);
        return false; //toGoTo not found.
    }
    //toGoTo found.
    selected = *location;
    selected_index = index;
    free(location);
    return true;
}

bool Playlist::containsSong(const Song * const song) const
{
    SongVector::const_iterator * location = (SongVector::const_iterator *) malloc(sizeof(SongVector::const_iterator));
    if(findSong(song, location) != -1) {
        free(location);
        return true;
    }
    return false;
}

void Playlist::addSong(const Song * const toAdd)
{
    addSongAfter(length - 1, toAdd);
}

bool Playlist::addSongAfter(int index, const Song * const toAdd)
{
    if(index < -1 || index >= length) {
        return false;
    }
    if(index == -1) {
        songs.push_front(toAdd);
    } else {
        SongVector::const_iterator iterAt = getIteratorAt(index);
        songs.insert_after(iterAt, toAdd);
    }
    length++;
    modified = true;
    return true;
}

bool Playlist::removeSongAt(int index)
{
    if(index < 0 || index >= length) {
        return false;
    }
    if(length == 1) { //deleted last element
        songs.pop_front();
        selected_index = -1;
    } else {
        if(index == 0) {
            if(selected_index == 0) { //selected first. move to new first element.
                selected++;
            }
            songs.pop_front();
        } else {
            int iterBeforeIndex = -2;
            SongVector::const_iterator iterBefore = getIteratorAt(index - 1, &iterBeforeIndex);
            if(selected_index == iterBeforeIndex + 1) { //selected at index. move to next one.
                selected++;
            }
            songs.erase_after(iterBefore);
        }
    }
    length--;
    modified = true;
    return true;
}

std::string Playlist::toString() const
{
    /*std::string name; //shall not contain linebreaks.
    bool modified;    //if true, has been modified (songs added/removed) since it was created.
    int length;       //length of Playlist: # elements in songs.
    int selected_index; //index of current song selected/playing in songs array.
    FwdList::const_iterator selected;
    FwdList songs;  //std::forward_list<const Song*> list of Ptrs. to Songs in Playlist.*/
    /* Format:
       <name>
       <modified: true/false>
       <length>
       <selected_index>
       {
       <song 1>
       ...
       }
    */
    using namespace std;
    string repr = name + "\n";
    repr += (modified ? string("true") : string("false")) + "\n";
    repr += to_string(length) + "\n";
    repr += to_string(selected_index) + "\n";
    repr += "{\n";
    //for()
    repr += "}\n";
    return repr;
}

SongVector::const_iterator Playlist::getIteratorAt(const int &index, int * const iteratorIndex) const
{
    SongVector::const_iterator iterator = songs.begin();
    int count = 0;
    while(count < index) {
        iterator++;
    }
    if(iteratorIndex != nullptr) {
        *iteratorIndex = count;
    }
    return iterator;
}

int Playlist::findSong(const Song * const song, SongVector::const_iterator * const location) const
{
    //Search through all Songs in songs until find song.
    SongVector::const_iterator iterator = songs.begin();
    int index = 0;
    while(iterator != songs.end()) {
        if(*iterator == song) { //found song
            *location = iterator;
            return index;
        }
        index++;
        iterator++;
    }
    return -1;
}
