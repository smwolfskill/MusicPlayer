#include "playlist.h"
#include <QDir>

Playlist::Playlist(const std::string name)
{
    this->name = name;
    songs = SongVector(0); //init Songs list
    selected = 0;
    modified = false;
}

Playlist::Playlist(const std::string representation, const MusicLibrary * const lib)
{
    //TODO
    /*try
    {
        //std::size_t lastChar;
        //int result = std::stoi(str, &lastChar, 10);
        //if(result < 0 || result > 1) {
            //load bool
            //corrupted/invalid representation
        //}
        //TODO: can just load as "true"/"false"; easy.
    }
    catch (std::invalid_argument&)
    {

    }
    catch (std::out_of_range&)
    {

    }*/
    selected = 0;
    modified = false;
}

void Playlist::setName(const std::string newName)
{
    name = newName;
    modified = true;
}

Song * Playlist::getSelected() const
{
    if(selected < 0 || (std::size_t) selected >= songs.size()) {
        return nullptr; //none selected.
    }
    return songs[selected];
}

Song * Playlist::getNext(bool returnBeginning)
{
    if((std::size_t) selected + 1 == songs.size()) { //at end. loop back to beginning.
        selected = 0;
        if(!returnBeginning) {
            return nullptr; //don't return beginning if requested. Indicates Playlist finished.
        }
    } else { //go to next song.
        selected++;
    }
    return getSelected();
}

Song * Playlist::getPrevious(bool returnEnd)
{
    if((std::size_t) selected == 0) { //at beginning. loop back to end.
        selected = ((int)songs.size()) - 1;
        if(!returnEnd) {
            return nullptr; //don't return end if requested. Indicates Playlist skipped back to end song.
        }
    } else { //go to previous song.
        selected--;
    }
    return getSelected();
}

void Playlist::goToFirst()
{
    selected = 0;
}

bool Playlist::goToSong(Song * const toGoTo)
{
    int index = songs.find(toGoTo);
    if(index == -1) {
        return false; //not found
    }
    selected = index;
    return true;
}

bool Playlist::goToIndex(int index)
{
    if(index < 0 || index >= songs.size()) {
        return false; //out of bounds
    }
    selected = index;
    return true;
}

SongVector Playlist::getRemaining()
{   
    SongVector remaining = SongVector(0);
    if(songs.size() == 0) { //no songs in playlist
        return remaining;
    }
    int origSelected = selected;
    Song * select = getSelected();
    if(select = nullptr) { //none selected. start at beginning
        selected = 0;
        origSelected = 0;
        select = getSelected();
    }
    //Go until end of playlist
    while(select != nullptr) {
        //remaining->addMedia(QUrl(select->url.c_str()));
        remaining.push_back(select);
        select = getNext(false); //don't return beginning element
    }
    //remaining->setCurrentIndex(1); //TODO: determine if 0-based or 1-based index

    //Set selected back to original
    selected = origSelected;
    return remaining;
}

std::string Playlist::toString() const
{
    /*std::string name; //shall not contain linebreaks.
    bool modified;    //if true, has been modified (songs added/removed) since it was created.
    int selected_index; //index of current song selected/playing in songs array.
    FwdList::const_iterator selected;
    FwdList songs;  //std::forward_list<const Song*> list of Ptrs. to Songs in Playlist.*/
    /* Format:
       <name>
       <modified: true/false>
       <selected_index>
       {
       <song 1>
       ...
       }
    */
    using namespace std;
    string repr = name + "\n";
    repr += (modified ? string("true") : string("false")) + "\n";
    repr += to_string(selected) + "\n";
    repr += "{\n";
    //TODO
    //for()
    repr += "}\n";
    return repr;
}
