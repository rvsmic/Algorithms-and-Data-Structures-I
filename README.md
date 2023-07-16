# Algorithms and Data Structures
All assignments and my solutions from the course Algorithms and Data Structures at the Faculty of Mathematics, Physics and Computer Science at the Maria Curie-Skłodowska University in Lublin conducted by PhD Anna Gajos-Balińska (laboratories).

## Assignment 1: "Wyremontujemy wasz dom!" (We will renovate your house) - warm-up task

### Links:
[All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad1) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad1/zad1v8.cpp)

### Description:
In the middle of the Pacific, amidst complete nothingness, lies an island. It is inhabited by a somewhat primitive tribe called Dotnet. The islanders decided to learn how to grow carrots. However, since they didn't know how, they needed tutorials from the Internet. They also had to order seeds and fertilizers from a store in Europe. But both YouTube and online shopping were inaccessible to them. They had no computers, smartphones, or fiber optic connections. In fact, they didn't even have electricity, and the nearest store was 3000 km away. They decided to modernize and digitize the entire island. The Island Chief brought in an IT team led by programmers Ada and Serweryn.

Upon arrival, they decided to select liaisons among the members of each village. These liaisons would be assigned smaller tasks that required frequent interactions with the unfamiliar community. The selection would be based on certain criteria chosen by Ada and Serweryn. They requested the Island Chief to provide a list of all residents from each village with information about them. Each resident would be described by:

* 1 - the number of skills they possessed,
* 2 - their height in centimeters,
* 3 - the average speed expressed as the number of tasks performed per hour.

Based on the information from the lists, they wanted to choose the most talented person (1 - with the most skills) or the tallest person (2 - with the highest height) or the fastest person (3 - performing the most tasks per hour). Sometimes, there would be multiple individuals with the highest value for a particular criterion in a village. In such cases, the next chosen criterion would be used to select among them. If there were still more people meeting the requirements of two criteria, a selection would be made based on the third criterion. For example, with the chosen order of criteria 2 3 1, they would first look for the tallest individuals (2), then the fastest (3), and finally the most talented (1).

### Input:
The input begins with an integer n, indicating the number of villages. This is followed by n sets of data. Each set consists of an integer m, representing the number of residents in the village, and three integers 1, 2, and 3 separated by spaces in any order. These determine the order of criteria for selecting village residents. The next m lines describe the residents. Each resident's description consists of a single-word string s, a natural number u, a real number w, and a natural number c, representing their name, number of skills, height in centimeters, and average speed in tasks per hour, respectively.

1 <= n <= 10
1 <= m <= 2 000 000

### Output:
The output should consist of the name of the resident in each village who meets the specified criteria. In the case of two people with the same values for all criteria, the order of occurrence on the list should be maintained.

### Example:

#### Input:
```
3
5
2 3 1
Abidemi 3 160.5 12 
Bayo 3 172.4 12 
Chika 2 190.2 2 
Dalili 3 167.9 12 
Esi 1 190.2 3 
5
3 1 2
Abidemi 3 160.5 12 
Bayo 3 172.4 12 
Chika 2 190.2 3 
Dalili 3 167.9 12 
Esi 1 190.2 2 
5
1 2 3
Abidemi 3 167.9 12 
Bayo 3 167.9 12 
Chika 2 190.2 3 
Dalili 3 167.9 12 
Esi 1 190.2 2 
```
#### Output:
```
Esi 
Bayo 
Abidemi
```


## Assignment 2: "Szczyty" (Peaks) - insertion sort

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Insertion_sort) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad2) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad2/zad2v5.cpp)

### Description:
Ada and Serweryn, as part of further modernizing the Island, wanted to build transmission towers, and the highest peaks in the area were perfect for this purpose. The most efficient way to distribute the towers was to start the work on the lowest selected peak and gradually move higher until reaching the highest peak.

The Island was a very mountainous terrain, and all the peaks there had their names. The tribe members held a special respect for the peaks whose height above sea level was a power of two. Ada and Serweryn decided to honor their preference and prioritize the peaks with such heights.

### Input:
In the first line of the input, there is an integer t, representing the number of tests. Then, there are t sets of data. Each set consists of an integer n, indicating the number of peaks. In the following n lines, there are descriptions of the peaks. The description includes a single-word string s - the name of the peak, and a positive integer w - the height of the peak in meters above sea level.

1 <= t <= 10

1 <= n <= 50 000

1 <= w < 2^32

### Output:
For each set of data, the program should output an ordered list of peaks in the order of tower placement. Each peak should be displayed in the format s-w. In case of peaks with the same values, the order of occurrence should be preserved on the list.

### Example:

#### Input:
```
3
5
Indrys 3
Fossa 67
Dingo 64
Werweta 10
Kwezal 1
3
Indrys 3
Fossa 2
Dingo 4
1
Indrys 10
```

#### Output:
```
Kwezal-1 Dingo-64 Indrys-3 Werweta-10 Fossa-67
Fossa-2 Dingo-4 Indrys-3
Indrys-10 
```

## Assignment 3: "Fala" (Wave) - linked list

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Linked_list) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad3) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad3/zad3odp.cpp)

### Description:
Children on the Island enjoyed asking Ada and Serweryn about their leisure activities. Recently, they learned about football fans' culture and the Mexican wave performed during matches. The wave fascinated them, so the children tried to recreate it while standing in a circle. However, due to the lack of football excitement and a small number of participants, they got bored after a few rounds. They decided to modify the rules and create a game based on the Mexican wave.

The children paired up and stood in a circle. Then, the person on the left side of each pair swapped places with the person on the left side of the neighboring pair (between the pairs, there was a person on the right side of the left pair and a person on the left side of the right pair). Next, one player initiated the wave by raising their hands, and the neighboring person repeated the action, and so on. If any participant made a mistake (raised their hands too early, too late, out of turn, or forgot), they were eliminated from the game (the other person from the pair could still continue). The game continued with the remaining players, starting from the person who made the last correct move, but with a reversed direction.

The player who just raised their hands could initiate a return wave by changing the direction of the game through a command and raising their hands again. The winning pair was the one that stayed in the game the longest. They also won if only one person from the pair remained in the game.

The children enjoyed this enhanced version of the Mexican wave so much that those who were eliminated early wanted to rejoin the game as soon as possible. Participants agreed that the game itself was more important than winning, so sometimes, after a player's mistake, they allowed pairs that were previously eliminated to return to the circle. The returning pair positioned themselves between two players next to the departing player.

For example:
Initial arrangement with three people next to each other: P1 P2 P3
After a mistake by person P2: P1 P3
After a new pair joins: Pn P1 P3 Pn

Observing the children's activities, Ada and Serweryn decided to simulate their gameplay.

### Input:
The input consists of natural numbers: n, p, k, representing the number of pairs, the index of the starting pair (pairs are indexed from 0, and the game begins with the person on the right), and the initial direction of the game (0 - clockwise, 1 - counterclockwise). It is assumed that at the start, the pairs are arranged in ascending order clockwise.

The next line contains a natural number m, indicating the number of operations. The following m lines describe the operations: op, parameter x, and, in a special case, a flag (so there may be two or three natural numbers in a line). The operations are defined as follows:

* 0 x - performs x moves in the game (raising hands counts as one move for each person) and displays the current state of the game, starting from the person in the pair where the round stops after x moves, according to the current direction of the game.
* 1 x flag - signifies a mistake made by a person and the possible return of an eliminated pair. The person at whom the round stops after x moves leaves the game. Regarding the flag: 1 - the pair that has been absent from the game the longest returns to play, 0 - nothing happens unless there are more than 3 people remaining in the circle after the player's departure, in which case the pair that has been absent from the game the longest returns to play.
* 2 x - changes the direction of the game. After x moves, the person in the x-th position performs an additional move, indicating a change in direction, and subsequent raises are counted in the opposite direction (the additional raise is counted as the first move after the direction change).

3 <= n <= 10 000

k = {0, 1}

1 <= m <= 10 000

op = {0, 1, 2}

### Output:
The program outputs the results of the operations, displaying the current state of the game.

### Example:

#### Input:
```
5 4 1
6
2 6
2 3
1 7 0
0 2
1 3 0
0 5
```

#### Output:
```
4 1 0 2 1 3 2 4 0
2 3 1 2 1 4 0 4
```

## Assignment 4: "Faktury" (Invoices) - binary search tree

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad4) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad4/zad4.cpp)

### Description:
The administration office of the Mayor was not accustomed to handling a large number of invoices. Orders for the construction of infrastructure on the Island kept coming in. Additionally, the Mayor recently hired his nephew from a neighboring village, who was not very skilled with the printer. Many invoices were printed multiple times. Now the entire office is filled with them. The Mayor sought help from Ada and Serweryn. He asked them for a tool to organize all the invoices alphabetically. Ada and Serweryn came up with the idea of using a binary tree structure for this purpose. They also realized that there was no need to enter the same invoice multiple times, which was mistakenly printed by the Mayor's nephew. It was sufficient to store the number of occurrences of each invoice in such a tree.

### Input:
The standard input begins with a line containing the number of printed invoices to be entered, n, followed by n lines containing the names of the invoices. The names may consist of digits and capital letters.

0 <= n <= 3 000 000

### Output:
The list of n entered invoices should be printed in ascending order, with each invoice on a separate line.

### Example:

#### Input:
```
10
AAAAAAA1234
BC21374A12
POAB0986541
XZASQ4689
POAB0986541
SWE1243D23
POAB0986541
DER098765532
VV111111111
VV111111111
```

#### Output:
```
AAAAAAA1234
BC21374A12
DER098765532
POAB0986541
POAB0986541
POAB0986541
SWE1243D23
VV111111111
VV111111111
XZASQ4689
```

## Assignment 5: "Dostawca mleka" (Milk supplier) - graph and breadth-first search

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Breadth-first_search) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad5) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad5/zad5v12.cpp)

### Description:
The milk supplier Kazimierz decided to embrace the modern times and retire his faithful horse, converting the cart into a swing. However, he still needed a new means of transportation to deliver milk. He sought the help of a well-known shaman and inventor on the Island named Leonard. Together, they designed a car for Kazimierz, but they couldn't determine the required size of the milk container. They turned to Ada and Serweryn for assistance. Since Kazimierz didn't visit all the villages on the island, but only a subset of them, the computer scientists decided to determine the number of villages that Kazimierz would pass on his way to the farthest destination. Based on this information, Leonard would be able to calculate the volume of the milk container in Kazimierz's car.

### Input:
The first line of the input contains a natural number n, indicating the total number of villages. The next line consists of a natural number m, which determines the number of villages visited by Kazimierz.

Then, a line appears containing the names of all villages separated by spaces. The names can consist of letters and digits. The next line provides the adjacency lists of all n villages, terminated by the letter "X". The order of the adjacency lists corresponds to the order of entering the village names. In other words, the i-th sequence terminated by the letter "X" specifies the neighbors of the i-th village from the sequence of village names.

The last two lines of the input are, respectively, the name of the starting village and a list of m destination village names for Kazimierz, separated by spaces. Each of the destination villages can be reached from the starting village.

1 <= n <= 30 000
1 <= m <= 100

### Output:
The number of villages visited during the journey to the farthest destination village.

### Example:

#### Input:
```
5
2
Antonin Bulgur Czychawa Drecja Euk
Bulgur Euk X Antonin Czychawa Drecja X Bulgur Drecja X Bulgur Czychawa Euk X Antonin Drecja X
Antonin
Bulgur Drecja
```

#### Output:
```
2
```

## Assignment 6: "Turniej" (Tournament) - divide and conquer

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad6) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad6/zad6v6.cpp)

### Description:
The Dotnet tribe wasn't always peaceful. Warriors from different villages often engaged in bloody battles. These customs faded away as the community became more civilized. However, nostalgia for the old times led the inhabitants of the island to occasionally organize fights among themselves. To observers like Ada and Serweryn, it resembled a friendly Mortal Kombat tournament.

On the battlefield, participants with assigned numbers from 0 to n-1 would position themselves at random locations. They would then engage in a certain number of duels. At any given moment, only one fight takes place. The two individuals standing closest to each other are the first to participate in the fight. The winner is determined based on their strength, and the defeated warrior disappears from the battlefield. The victorious warrior does not change their initial position on the battlefield.

It is assumed that in case of a tie, the warrior with the lower number emerges as the winner. If there are multiple pairs of warriors at the same distance, the fight involving the warrior with the lowest number is resolved first. If, due to the same distance, the warrior can fight with multiple soldiers, they start the fight with the one having the lowest number.

The fights continue until a specified number of participants have fallen. Based on the arrangement of the participants, assess the order in which they leave the battlefield.

### Input:
At the program's input, the first line will contain two positive integers, n and t, representing the number of warriors on the battlefield and the desired number of fights, respectively. The following n lines will consist of three natural numbers, x, y, and w, describing the warriors. Here, x and y denote the coordinates of the warrior on the battlefield, and w represents their strength.

2 <= n <= 10 000

### Output:
The program should output the coordinates of the fallen warriors on the battlefield in the order of their "deaths".

### Example:

#### Input:
```
4 2
1 2 4
3 7 3
2 4 1
5 1 6
```

#### Output:
```
2 4
1 2
```

## Assignment 7: "Premia lub hańba" (Bonus or disgrace) - dynamic programming

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Dynamic_programming) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad7) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad7/zad7v3.cpp)

### Description:
The group of programmers on the Island had to report the performance of their development teams frequently. The Grand Product Owner of the entire digitization project, known as the Sołtys, would ask one of the teams each day to provide information about how many user stories they had recently "delivered". His plan involved checking the performance of n teams in a predetermined order and based on the total number of tasks completed, determining whether the employees of Ada and Serweryn deserved a bonus or, rather, facing disgrace (the highest form of punishment on the Island).

The programmers preferred receiving a bonus and discovered that if the i-th team made a single change in the reporting queue just before submitting the report, the Sołtys wouldn't notice it, even if the result of the same team was added multiple times. This means that before adding the i-th team's result to the queue, they could either leave the order unchanged or swap the positions of any two neighboring teams. The programmers realized that they could maximize their final score and increase their chances of receiving a bonus using this strategy.

### Input:
The first line of the input contains a natural number n - the number of teams. The next line contains n natural numbers ai, which represent the number of delivered user stories by the i-th team.

2 <= n <= 500

1 <= ai <= 10^6

### Output:
The output should display the maximum score that the teams of programmers can achieve at the end of reporting.

### Example:

#### Input:
```
5
3 1 5 4 10
```

#### Output:
```
38
```

## Assignment 8: "Polowanie na kraby" (Crab hunt) - backtracking - eight queens puzzle

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Backtracking) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad8) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad8/zad8.cpp)

### Description:
Part of the island's coastline is home to a numerous population of crabs. Most of the time, these animals are under strict protection, but once a year, hunters from neighboring villages organize a grand hunt. Before the hunt begins, the Grand Huntsman designates a square hunting area, which is divided into a certain number of identical plots so that the number of plots matches the number of participating groups.

The hunting area is oriented with respect to the cardinal directions, meaning that opposite walls represent the N-S or E-W directions. Hunters from each village set up their camp on one of the plots and embark on their hunt, following the tradition of the 8 cardinal directions (N, E, S, W, NE, SE, SW, NW).

No competing hunters' camps can be located on the same hunting route, as islanders have mistakenly taken sleeping companions for crabs' limbs in the past. Furthermore, the beach locations differ from each other. Some require reinforcement before establishing a camp, others need anti-whale barriers (as per the new Safety and Hygiene Hunting regulations), and some simply yield little prey.

In this year's edition, Ada and Serweryn were tasked with providing the most cost-effective distribution of hunter's camps, and in return, they were promised several units for building a crab computer.

### Input:
The first line of input contains the number n, representing the number of camps that need to be distributed on a square hunting area with a side length of n plots. The next n lines consist of sequences of n non-negative integers ai,j, where each number ai,j corresponds to the cost of building a camp on a field with coordinates i, j.

4 <= n <= 30

0 <= ai,j <= 100

### Output:
A sequence of n numbers representing the column numbers where we will place the camps in each row in the least costly, valid distribution. The displayed answer must be the smallest solution in lexicographic order.

### Example:

#### Input:
```
5
1 5 10 1 3
3 10 10 10 5
10 1 1 5 5
1 1 1 1 1
15 15 10 15 15
```

#### Output:
```
3 0 2 4 1
```

## Assignment 9: "Rankingowe polowanie" (Ranked hunt) - linear sorting - counting sort

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Counting_sort) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad9) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad9/zad9.cpp)

### Description:
After each successful hunt, it is necessary to divide the spoils and engage in numerous boasts. The first of these things is regulated on the Island in a very simple way: everyone keeps what they caught. In the case of the latter, the rules are even simpler: there are no rules. This nonchalance combined with the fiery spirit of Dotnet results in the hunt turning into a sporting spectacle... often very brutal. This time, the Grand Huntsman did not want to allow that. To prevent hunters from fighting for the title of the best, he asked Ada and Serweryn to arrange all the participants of the hunt according to their spoils.

### Input:
The first line of input contains the number n of hunters participating in the hunt. The next n lines consist of descriptions of hunters, consisting of: a name composed of at most twenty lowercase and uppercase Latin letters; the declared number of crabs caught k_i and the number of traps received by the hunter p_i.

1 <= n <= 100 000

0 <= k_i <= 99

1 <= p_i <= 9

### Output:
The output should display a list of hunters' names sorted in descending order based on the number of crabs caught. In case of the same number of crabs caught, the hunter who used fewer traps should be listed first. If two individuals caught the same number of crabs using the same number of traps, their original order from the input should be maintained.

### Example:

#### Input:
```
6
Albert 5 3
Bartek 10 1
Cezary 3 2
Dominik 4 3
Eustachy 1 2
Franek 3 2
```

#### Output:
```
Bartek Albert Dominik Cezary Franek Eustachy
```

## Assignment 10: "Awarie" (Malfunctions) - heap

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Heap_(data_structure)) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad10) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad10/zad10v5.cpp)

### Description:
The mayor learned the hard way that cutting costs during tenders for transmission towers was a mistake. The tower failures tarnished the mayor's reputation. The repair teams were overwhelmed, so the mayor came up with the idea of assigning priorities to reported failures and prioritizing the restoration of the most important towers (with the highest priority), possibly even forgoing the repair of some less crucial ones. The mayor tasked one of Ada and Serweryn's teams with developing an application to assist in managing the repair teams.

### Input:
At the input, the program receives the number n of data sets, followed by the data of each set. The data for a single set consists of a number m, followed by m lines describing the operations to be performed. The description of a single operation consists of an integer from the set {0, 1, 2}.

* 0 represents the operation of adding a repair request for a tower. This operation description consists of three numbers. The description 0 a b means that a repair request for tower a with priority b should be added.
* 1 represents the repair of the tower with the highest priority. The corresponding repair request should be removed from memory.
* 2 represents giving up on repairing the tower with the lowest priority. The corresponding repair request should be removed from memory.

It is assumed that at any given time, there is at most one repair request for a tower with a specific priority in the database.

### Output:
The program should print on the standard output the numbers of the transmission towers whose repair requests are being removed from memory. The program should ignore the commands to remove a repair request from an empty list of requests. All input values are limited to a maximum of 3 000 000.

### Example:

#### Input:
```
1
8
0 1 2
1
0 1 2
0 2 1
0 0 3
1
2
1
```

#### Output:
```
1
0
2
1
```

## Assignment 11: "Awaryjna loteria" (Emergency lottery) - median of medians algorithm

### Links:
[Wikipedia](https://en.wikipedia.org/wiki/Median_of_medians) | [All Attempts](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/tree/main/zad11) | [Final Solution](https://github.com/rvsmic/Algorithms-and-Data-Structures-I/blob/main/zad11/zad11v6.cpp)

### Description:
After the recent outages on the Island, there was a lot of unrest. It's easy to get used to comforts, so when the Dotnet community experienced super-fast fiber optic internet and HD carrot planting tutorials on YouTube, internet outages triggered their worst instincts. In response, the Village Chief came up with the idea of organizing a lottery. Every dissatisfied resident who submits the appropriate application has a chance to win a year's supply of root vegetable seeds and a lifetime subscription to Farmer magazine. At the end of each month, the system will draw a winner. Write a program to search for the selected resident of the Island.

### Input:

The program receives on standard input a number n representing the number of applications, followed by a number k randomly chosen by the system. Then it receives the data of n applications. Each application consists of three lines containing the first name, last name, and ID of the applicant. The IDs are integers ranging from 0 to 2^32-1. It is assumed that a person can submit at most one application.

1 <= n <= 500 000
0 <= k < n

### Output:
The program should output on standard output the data from the k-th application according to the following order: first, the ID values are considered; in case of equal IDs, the alphabetical order of last names is considered; and in case of equal IDs and last names, the alphabetical order of first names is considered. The applications are numbered starting from 0.

### Example:

#### Input:
```
4 1
Jan
Kowalski
12
Paulina
Wysocka
6
Robert
Bartecki
12
Aldona
Nowak
14
```

#### Output:
```
Robert
Bartecki
12
```