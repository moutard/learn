I made the comparison between loaded all the value of the dict in memory and
just reading the file many times.
Here is some results.

              | Read          | Load in memory  |
Memory usage  | 500B          | 5 MB            | (x 10 000)
valgrind time | 16s           | 3s              | (x 5)
without valg  | 0.49s         | 0.07s           | (x 7)
real distance | 17s           | 16.67s          |

so the levensthein distance is so long that it doesn't make difference to
load all the dict in memory.
