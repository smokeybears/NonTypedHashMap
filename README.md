This is a non-typed HashMap implemented in C, collision resolution is done with a LinkedList. The HashMap is fully functional but still in progress. Pointer warnings are not suppressed in relevant areas and the testing is janky at best (e.g. to test the conflicts you must manually set the HASHSIZE to 1, along with a general lack of uniformity in the testing)

The hashing is done with each byte in the key string cyclic shift'd by it's position in the string and xor'd against the previous bytes (UINT\_MAX for the first byte). Since the hashing works byte by byte if a hash of size 255 is fully filled you are guaranteed to have collisions.

To use the HashMap download pull the source and `#include "NonTypedHashMap.c"` to generate a hash `hashDefault newHash = newHash()` the HashMap exposes the following Methods:

\#add `add(char *, void *, size_t, struct hashDefault *)`

\#remove `remove(char *, struct hashDefault *)`

\#find `find(char *, struct hashDefault *)`

\#hash `hash(char *)`


Design Notes (mostly for me when I come back to working on this):

-Currently new keys that cause a collisions are pushed on to the linked list. This should maybe be changed to shifting because new additions are in most cases likely to be accessed sooner than old additions

-When a location that previously had a collision is reduced down to only one entry again the entry remains on a conflict list, instead of resolving it back to a normal entry. This was done because in my mind keys that are removed that caused a collision are likely to be added again and I wanted to save the overhead of creating a conflict list on the second add of a conflicting key. However, this could prove to be wrong

