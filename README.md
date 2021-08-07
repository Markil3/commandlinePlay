# commandlinePlay
Uses VLC media player and a music database to search for and play music from the command line.

It works in two parts. The first one, the play python module, does most of the work. It accepts a series of search terms and then looks through a compatible database (the Lollypop music player database, by default) for the songs before launching VLC media player.

The second part, the key listener, will listen for arguments for the python module from the keyboard without changing window focus, with audio feedback to ensure that the user knows that they are inputing into the program.
