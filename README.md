# GameofLife_Cpp
Simple Game of Life simulation written in C++, working in the console.
Author: Saad Bazaz


Hello there, dear math enthusiast.
I guarantee you that each and every line of code is my own. 
All from my mind.

Except for that cool graphic I got off the internet.

As proof I've attached all the test runs I had. I started with the fileHandler so there's plenty of funny material to go around.


Overview of the program:
- config.ini is the last saved User Configuration i.e. the settings before launching a simulation. It helped me through testing so that's why I started from here.
config.ini is parsed through the code I've written. Any other settings might throw an error or give weird results.
- So for that I gave the option of overwriting config.ini with a new Configuration - right inside the program. This ensures uniform file structure.
- The program maintains a log of the current simulation in a temp file called recent_sim.temp
This file is maintained until the end of the simulation. If the user wishes to save, this temp file is copied onto the User's desired file and then deleted in all cases, to save system space.
- I am horrible at math. But I still wrote an algorithm of sorts. There are 2 main vectors - "alive" (living cells) and "neighbors" (dead cells). These contain the main information
regarding the current cells in the grid.

STEPS OF ALGORITHM:
1. Initialize "alive" with values from userConfig.
2. Display the current values inside "alive".
3. Clear "neighbors" and all temporary vectors
4. Now create new neighbors. We will only check if the space isn't occupied by an "alive" cell, otherwise all neighbors will be entered. Even if it results in duplication (important)
5. Then we scan the array and remove duplicates. During this, we check how many times a duplicate appears. If it appears 3 times, that means that that space is neighbored by 3 "alive" cells.
6. We record all such "births" into a tempBirth vector.
7. Next we scan the "alive" vector for any deaths. We check deaths using a for loop in which we check the number of neighbors of a cell. If that number becomes greater than 4 *during* the loop,
we break because that already means that the cell is dead. This saves us some time.
8. We cannot start removing values immediately as the Rule of Death requires that all the "alive" cells be there to be counted. So instead, we record all the indexes at which deaths occur.
9. After scanning is done, we remove or "kill" all the cells in our death record.
10. Finally, we append the "tempBirth" vector onto the "alive" vector.
11. Our new generation is now ready.

Don't know if it's an O(n) algorithm. Contributions would be appreciated.

