# Memory Matching Card Game

For this lab, I created a memory matching card game in C++ using an unsorted singly linked list. The game uses a 4x4 grid with 16 cards and 8 matching pairs. The goal is to keep flipping two cards until all of the matching pairs are found.

## Linked List

I used an unsorted singly linked list to store the cards. Each node stores a Card and a pointer to the next node. I created functions to insert cards, remove cards, get a card by its position, and return the size of the list.

One challenge with using a linked list for this game is accessing cards by their position. Unlike a vector or array, a linked list cannot go directly to an index. It has to start at the head and move through the list until it reaches the card. This makes random access slower.

## Game Logic

The game creates two cards for each letter from A through H. I used a temporary vector to shuffle the cards and then put them back into the linked list.

The player selects two cards at a time. If the values match, the cards are marked as matched. If they do not match, they are flipped back over. The game continues until every card has been matched.

## Ncurses Terminal

For the terminal version, I used ncurses to make the game more interactive. The arrow keys move between cards and Space or Enter flips a card. The selected card is highlighted, and Q can be used to quit the game.

Ncurses is better than using regular cout for this game because it lets me control where text appears on the screen and lets the player use keys without typing a row and column every time. The main challenge is that ncurses takes more setup and has to be included when compiling the program.

## Build Instructions

Compile the program with:

g++ main.cpp -o memory_game -lncurses

Run the program with:

./memory_game

## Controls

Arrow Keys - Move between cards

Space or Enter - Flip a card

Q - Quit the game