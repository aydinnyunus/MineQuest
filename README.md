# MineQuest

**Decoding the Enigma: A Journey into Minesweeper's Reverse Engineering**

**Introduction:**
Minesweeper, a timeless Windows game, challenges players to unveil hidden mines on a grid while avoiding explosive mishaps. Beyond its seemingly uncomplicated gameplay, the depths of Minesweeper's intricate coding and design hold fascination for curious minds. This blog post takes us on an expedition of reverse engineering Minesweeper, unraveling its underlying mechanics to uncover the hidden secrets that infuse this deceptively simple game with complexity and intrigue.

![MineSweeper](https://i.imgur.com/3Kezw82.jpg)

**Peeling Back the Layers: Dissecting Minesweeper Through Reverse Engineering**
Minesweeper's apparent simplicity belies the intricacies woven into its fabric. Reverse engineering opens the door to explore the coding techniques shaping its essence. The journey commences with unraveling the game's architecture and data structures, providing a bedrock for comprehending its intricate mechanics.

**Deciphering the Grid:**
At the core of Minesweeper lies a grid of cells that players systematically uncover. By dissecting the memory representation of this grid, we can demystify the game's approach to storing information about mines, numbers, and covered/uncovered cells. This exploration unveils the binary framework of the grid and the manipulations that unfold during gameplay.

**Cracking the Algorithms:**
Minesweeper harnesses algorithms to compute numbers in cells adjacent to mines and to orchestrate the cascading effect of opening empty cells. Reverse engineering these algorithms grants insights into the game's real-time logic processing.

**Revealing the Veil of Randomness:**
The seemingly random mine placement in Minesweeper harbors subtle patterns and predictability. By delving into the mechanics of its random number generation, we can uncover the enigmatic method behind mine placement, potentially influencing strategic gameplay.

![Srand Function](https://i.imgur.com/7aRDB9X.png)

It's important to understand that the random numbers generated using 'srand' are not truly random but rather pseudorandom. This means that given the same seed value, the same sequence of numbers will be produced every time. As Minesweeper's random number generation relies on 'srand', the same seed (often derived from the system time) guarantees consistent results in repeated gameplay sessions.

**Delving into the User Interface:**
Reverse engineering the game's user interface unveils the mechanics of rendering graphics, capturing interactions, and implementing flag placements. This exploration uncovers the synergy between the game's logic and the visual representation experienced by players.

**Unraveling the Challenge: Deciphering the Bomb Count Through Reverse Engineering**
The display of the bomb count is pivotal in Minesweeper. While in the game, players can reduce this count through flag placements. Reverse engineering unveils an avenue to manipulate this value, potentially reshaping the game's dynamics.

**Cheat Engine: A Toolkit for Exploration**
Cheat Engine emerges as a potent ally for game hacking and reverse engineering. This tool allows us to delve into the memory of a running game, pinpoint specific values like the bomb count in Minesweeper, and peer into its inner workings.

![Cheat Engine](https://upload.wikimedia.org/wikipedia/commons/c/c2/Cheat_Engine_7.1.png)

**Navigating the Mutable Value Predicament:**
In Minesweeper, the memory address housing the bomb count shifts with each new game initiation. This dynamic behavior poses a challenge when pinpointing the precise memory address responsible for storing this vital information.

**Hunting for the Bomb Count:**
Leveraging Cheat Engine, we embark by scanning for the initial bomb count value. However, owing to the ever-changing nature of this value, the scan yields numerous memory addresses bearing the same value. Cheat Engine captures snapshots of memory at varying intervals, leading to multiple matches.

**Refinement via Iteration:**
To sieve out false positives, strategic in-game actions that influence the bomb count are executed. Placing a flag, for instance, decreases the count by one. Following such actions, a "Next Scan" in Cheat Engine narrows down the list of potential addresses, guiding us closer to the target.

**Gradual Convergence:**
Through an iterative dance of gameplay and Cheat Engine scans, we incrementally whittle down the roster of addresses linked to the bomb count. This systematic elimination aids in pinpointing the precise memory address that governs this crucial value.

**Decoding Click Tallies: A Revelation Awaits**
Observant players might have discerned allusions to tracking click counts within Minesweeper. Employing Cheat Engine, we can lift the veil on the mechanics underpinning this counter, shedding light on how the game monitors player interactions.

**The Quandary of Pointer Scans:**
As we embark on the odyssey to uncover Minesweeper's concealed facets, Cheat Engine's potent pointer scan feature becomes invaluable. This tool enables the tracing of pointer chains, revealing memory addresses holding vital values such as bomb counts or click records. However, this powerful tool yields a plethora of potential candidates, complicating the search.

![Pointer Scan](https://i.imgur.com/adlb0jO.png)


**Sifting the Transient from the Enduring:**
The initial pointer scan inundates us with around 60 outcomes, each leading to diverse addresses within the game's memory. Amidst this sea of data, not all addresses hold the answers we seek. Many might be transient or unrelated to our target information. Our pursuit requires the identification of consistent, reliable pointers amidst the multitude.

![Pointer Scan with Previous Scans](https://i.imgur.com/QmzyDGc.png)


**A Fresh Start: Restarting the Game and Redefining Approach:**
Acknowledging the fluid memory layout of Minesweeper, we opt for a fresh commencement. We close the game and restart, initializing a new session with distinct memory configurations. By re-performing a pointer scan within this renewed context, we aim to isolate memory addresses consistently harboring the bomb count and click tallies we seek.

**Emergence of Stable Offsets:**
Upon restarting and conducting a new pointer scan, a promising pattern emerges. Two offsets consistently surface within the results, retaining their presence across various game sessions. These stable offsets stand out amidst the ever-shifting landscape of memory addresses. This revelation marks a crucial stride in our quest to fathom Minesweeper's cryptic internals.

![Candidates for Pointer Scan](https://i.imgur.com/5qrDp4c.png)

![Second Candidate](https://i.imgur.com/2HaX2Rj.png)

**Setting the Scene: Navigating Debugging Essentials:**
Debugging unfurls as a process of dissecting program execution, tracking memory changes, and identifying pivotal functions influencing gameplay behavior. Our initial focus lands on a pivotal memory address—the cell players click during gameplay. Peering into the activities surrounding this memory location promises insights into the functions interwoven with Minesweeper's mechanics.

**Hardware Breakpoints: Unearthing Code Footprints:**
To gain clarity on events triggered by a cell click, we wield a formidable debugging technique—hardware breakpoints. By setting a breakpoint at the clicked cell's memory address, the debugger intervenes whenever the memory location undergoes access or modification. This tactic bestows a microscopic view of the code's sequence during and post-click.

**Illuminating Code in Action:**
Initiating the hardware breakpoint transports us to a realm of precision debugging. Every interaction with the clicked cell's memory address prompts a pause, enabling scrutiny of registers, stacks, and code in real time. Through meticulous analysis, we unravel the code's behavior, unveiling additional functions and interactions that shape Minesweeper's dynamic gameplay.

**Unearthing Hidden Jewels: Anticipating New Revelations:**
By dissecting the code's response to interactions with the clicked cell's memory address, we uncover latent functions influencing Minesweeper's gameplay logic. These revelations span diverse facets—unveiling mechanics, cascading algorithms, and more. With each breakpoint, we inch closer to comprehending the intricate tapestry of Minesweeper's codebase.

![x64dbg](https://i.imgur.com/JQEJMqH.png)

Upon clicking any grid square, the breakpoint triggers. Notably, [rcx+1C] designates the click count, with 1C as the offset.

![x64dbg breakpoint](https://i.imgur.com/pzjxH1X.png)

Investigating the conditional jump ('jne') action leads to address calculations, offsets, and comparisons like 'cmp byte ptr [rsi+rcx], dil'. It becomes evident that 'dil' remains constant at 0, while [rsi+rcx] pertains to 'isBomb'. If not a bomb, the jump directs to address 2EE, advancing the offset (click count) through comparison 'cmp dword ptr [rbx+38], 0', influencing the game's progression.

![isNotBomb](https://i.imgur.com/4N6n740.png)

Dissecting the registers during the 'isNotBomb' function exposes the roles of 'rsi' (rowPtr) and 'rbp' (column), both persistently anchored at 0. This realization facilitates offset calculations and loop construction to ascertain bomb presence. Our formula becomes Minesweeper.exe + 0xAAA38] + 0x18] + 0x58] + 0x10] + 0x8* column] + 0x10] + row.

![isNotBomb Registers](https://i.imgur.com/Q3pFPbL.png)

Memory analysis uncovers valuable data. Notably, 38f207c stores 09, reflecting row and column counts. The highlighted value, 1C offset, signifies click count. Others indicate elapsed time. This memory region encapsulates Minesweeper's critical variables.

![base Memory](https://i.imgur.com/K0ByiO7.png)

**C++ Code:**

GitHub: github.com/aydinnyunus/Minesweeper

![Result](https://i.imgur.com/Fuz89ql.png)

**Conclusion: Decrypting Minesweeper's Reverse Engineering Delight**
Reverse engineering Minesweeper unveils a vibrant blend of coding techniques, algorithms, and data structures. This expedition extends an appreciation for software development, unearthing memory management intricacies, UI design, and more, encapsulated within a seemingly modest game. The journey illuminates the craftsmanship underlying seemingly straightforward games, underscoring that even in simplicity, complexity thrives.
