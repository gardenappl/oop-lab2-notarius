# oop-lab2-notarius
Notarius is a note-taking app written in Qt.

The user interface is similar to an IDE - the user is presented with multiple tabs, each one is used to edit its own file. Notes are stored in separate files.
Continuing with the IDE analogy, notes are split into "contexts", which are similar to projects in IDEs. Each context contains some metadata (in JSON format) and has a folder associated with it. The folder contains every single note file.

This implements subtasks 1 (contexts), 3 (switching to recent contexts) and 7 (an entire context can be exported into a single file).
