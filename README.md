# movie_directory_avl_tree
AVL tree implementation in a movie directory example

A Data Structures course final project in C++. A movie directory is stored as an AVL tree keyed by
movie title; each movie's satellite data (year, duration) carries its own AVL tree of actor names.
Strings are stored as linked lists of characters (`LinkedString`), so no `std::string` is used.
Search, insert and delete on both trees are `O(log n)`.

## Files

| File | Contents |
| --- | --- |
| `AVL.H` | Generic `AVL<KeyType, SDType>` tree template: `Search`, `insert`, `Delete` with full rebalancing, and `AVLNode` |
| `LinkedString.h` | `LinkedString`: a character linked list with `scan()` (read one line from stdin), `print()`, assignment and a `compare()` ordering |
| `MoviesDirectory.h` | `MovieDirectory` (an AVL of `LinkedString` -> `MovieProperties`) and the per-movie actor AVL; implements all commands |
| `MAIN.CPP` | Command loop reading from stdin |
| `DS_PROJECT_FINAL_DOCUMENTATION.pdf` | Project report (in Persian): design, memory usage and complexity of each operation |

## Commands

The program reads commands from standard input until `exit`. Each name (movie title or actor) is read
as a whole line, so it may contain spaces.

| Command | Input that follows | Effect |
| --- | --- | --- |
| `addmovie` | title (line), year, duration, N, then N actor names (one per line) | insert a movie |
| `deletemovie` | title (line) | remove a movie and its actors |
| `addactor` | title (line), actor name (line) | add an actor to a movie |
| `deleteactor` | title (line), actor name (line) | remove an actor from a movie |
| `findmovie` | title (line) | print title, year, duration and actors, or `not found` |
| `findactor` | actor name (line) | print titles of all movies with this actor |
| `findyear` | year | print titles of movies from that year |
| `findyears` | year1 year2 | print titles of movies with year1 <= year <= year2 |
| `listmovies` | - | print all titles in sorted order |
| `exit` | - | quit |

Example session:

```
addmovie
Inception
2010 148 2
Leonardo DiCaprio
Tom Hardy
findactor
Tom Hardy
exit
```

## Building

The project was written against an older Microsoft toolchain and has no build files. Two things stop
it from building as-is on a modern, case-sensitive setup:

- `MoviesDirectory.h` includes `"AVL.h"` while the file is named `AVL.H`.
- `AVL.H` declares `template <class T> char compare(const T&, const T&)` and calls it as
  `compare<KeyType>(...)`, relying on the non-template `compare(const LinkedString&, const LinkedString&)`
  in `LinkedString.h` to satisfy it. Modern GCC/Clang keep the two separate and fail at link time with an
  undefined reference to `compare<LinkedString>`.

With those two points addressed (fix the include case, include `AVL.H` before `LinkedString.h`, and make the
`LinkedString` `compare` an explicit specialization: `friend char compare<>(...)` in the class and
`template<> char compare<LinkedString>(...)` for the definition), the whole program is a single translation
unit and builds and runs with GCC:

```
g++ -o movies MAIN.CPP
./movies
```
