# commandlinePlay
Uses VLC media player and a music database to search for and play music from the linux command line.

It works in two parts. The first one, the play python module, does most of the work. It accepts a series of search terms and then looks through a compatible SQLite3 database (the Lollypop music player database, by default) for the songs before launching VLC media player.

The second part, the key listener, will listen for arguments for the python module from the keyboard without changing window focus, with audio feedback to ensure that the user knows that they are inputing into the program. This part will need to be run by a user added to the `input` user group.

### Archived
For updates, see https://github.com/Markil3/LollypopInt

## Building

The listener can be built with the following command
```
gcc capture.c -o play_capture
```
The Python module does not require any external dependencies as far as execution goes.

## Song Database

By default, the Python module will pull music from the databases maintained by the Lollypop music player at ~/.local/share/lollypop (specifically, lollpop.db and playlists.db). However, you can supply your own and pass the directory containing the two databases via the --directory argument.

In either case, there must be two databases. The lollypop.db database will contain the tracks as well as additional information like albums and artists. There is also a playlists.db that contains playlist information.

### lollypop.db

commandlinePlay requires 4 tables from lollypop.db: tracks, albums, artists, and track_artists.

#### tracks
This row contains tracks.
| column | type | description |
| --- | ------ | ---------------- |
| id | INTEGER | The ID of the track. This is used to join this table with other tables. |
| uri | TEXT | The URI to the file of the song. |
| name | TEXT | The title of the song. |
| album_id | INTEGER | The ID of the album the song belongs to. This corresponds to an album in the `albums` table. |

#### albums
This row contains albums.
| column | type | description |
| --- | ------ | ---------------- |
| id | INTEGER | The ID of the album. This is used to join this table with `tracks`. |
| name | TEXT | The name of the album. |

#### artists
This table contains artists, with each row being an artist.
| column | type | description |
| --- | ------ | ---------------- |
| id | INTEGER | The ID of the artist. This is used to join this table with `track_artists`. |
| name | TEXT | The name of the artist. |

#### track_artists
This table joins tracks and artists, with each row being an artist that contributed to a song.
| column | type | description |
| --- | ------ | ---------------- |
| track_id | INTEGER | The ID of a song. This is used to join this table with `tracks`. |
| artist_id | INTEGER | The ID of an artist that contributed to the song. This corresponds to an id in `artists`. |

### playlists.db
This database contains playlist information. It is separate from the `lollypop.db` database, as tracks are represented using only their file paths here.

#### playlists
This table contains all playlists, with each row being a playlist.
| column | type | description |
| --- | ------ | ---------------- |
| id | INTEGER | The ID of a playlist. |
| name | TEXT | The name of a playlist. |

#### tracks
This table contains all tracks that are part of a playlist. Each row corresponds to a single track.
| column | type | description |
| --- | ------ | ---------------- |
| playlist_id | INT | The ID of the playlist that this track belongs to. This corresponds to a playlist in the `playlists` table. |
| uri | TEXT | The link to the track as a URI path. |
