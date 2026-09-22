#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <ncurses.h>

// Represents one card in the memory game
struct Card
{
    char value;
    bool isFaceUp;
    bool isMatched;

    Card(char val) : value(val), isFaceUp(false), isMatched(false)
    {
    }
};

// Represents one node in the linked list
struct Node
{
    Card data;
    Node* next;

    Node(Card card) : data(card), next(nullptr)
    {
    }
};

// Unsorted singly linked list used to store the cards
class LinkedList
{
private:
    Node* head;
    int length;

public:
    LinkedList() : head(nullptr), length(0)
    {
    }

    ~LinkedList()
    {
        Node* current = head;

        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Adds a card to the end of the list
    void insert(Card card)
    {
        Node* newNode = new Node(card);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;

            while (temp->next != nullptr)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        length++;
    }

    // Gets a card at a certain position
    Card& getAt(int index)
    {
        if (index < 0 || index >= length)
        {
            throw std::out_of_range("Invalid index");
        }

        Node* temp = head;

        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }

        return temp->data;
    }

    // Removes a card at a certain position
    void removeAt(int index)
    {
        if (index < 0 || index >= length)
        {
            return;
        }

        if (index == 0)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node* previous = head;

            for (int i = 0; i < index - 1; i++)
            {
                previous = previous->next;
            }

            Node* temp = previous->next;
            previous->next = temp->next;
            delete temp;
        }

        length--;
    }

    // Returns the number of cards in the list
    int size() const
    {
        return length;
    }
};

// Controls the memory matching game
class MemoryGame
{
private:
    LinkedList cards;
    int rows;
    int cols;
    int firstFlipIndex;
    int secondFlipIndex;

    // Creates two cards for each letter A through H
    void initializeDeck()
    {
        char values[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

        for (char value : values)
        {
            cards.insert(Card(value));
            cards.insert(Card(value));
        }
    }

    // Shuffles the cards using a temporary vector
    void shuffle()
    {
        std::vector<Card> temp;

        for (int i = 0; i < cards.size(); i++)
        {
            temp.push_back(cards.getAt(i));
        }

        std::random_device rd;
        std::mt19937 generator(rd());

        std::shuffle(temp.begin(), temp.end(), generator);

        while (cards.size() > 0)
        {
            cards.removeAt(0);
        }

        for (const Card& card : temp)
        {
            cards.insert(card);
        }
    }

public:
    MemoryGame(int r = 4, int c = 4)
        : rows(r), cols(c), firstFlipIndex(-1), secondFlipIndex(-1)
    {
        initializeDeck();
        shuffle();
    }

    // Flips the card selected by the player
    bool flipCard(int row, int col)
    {
        int index = row * cols + col;

        if (row < 0 || row >= rows ||
            col < 0 || col >= cols ||
            index < 0 || index >= cards.size())
        {
            return false;
        }

        Card& card = cards.getAt(index);

        if (card.isFaceUp || card.isMatched)
        {
            return false;
        }

        card.isFaceUp = true;

        if (firstFlipIndex == -1)
        {
            firstFlipIndex = index;
            return false;
        }

        secondFlipIndex = index;
        return true;
    }

    // Checks if the two flipped cards match
    void checkMatch()
    {
        if (firstFlipIndex == -1 || secondFlipIndex == -1)
        {
            return;
        }

        Card& firstCard = cards.getAt(firstFlipIndex);
        Card& secondCard = cards.getAt(secondFlipIndex);

        if (firstCard.value == secondCard.value)
        {
            firstCard.isMatched = true;
            secondCard.isMatched = true;
        }
        else
        {
            firstCard.isFaceUp = false;
            secondCard.isFaceUp = false;
        }

        firstFlipIndex = -1;
        secondFlipIndex = -1;
    }

    // Checks if every card has been matched
    bool allMatched()
    {
        for (int i = 0; i < cards.size(); i++)
        {
            if (!cards.getAt(i).isMatched)
            {
                return false;
            }
        }

        return true;
    }
        // Runs the memory game using ncurses
    void displayTerminalNcurses()
    {
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);

        if (has_colors())
        {
            start_color();
            init_pair(1, COLOR_WHITE, COLOR_BLUE);
            init_pair(2, COLOR_BLACK, COLOR_WHITE);
            init_pair(3, COLOR_GREEN, COLOR_BLACK);
        }

        int cursorRow = 0;
        int cursorCol = 0;

        while (!allMatched())
        {
            clear();

            // Draw the 4x4 card grid
            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < cols; c++)
                {
                    int index = r * cols + c;
                    Card& card = cards.getAt(index);

                    int x = c * 4;
                    int y = r * 2;

                    // Highlight the selected card
                    if (r == cursorRow && c == cursorCol)
                    {
                        attron(A_BOLD | A_REVERSE);
                    }

                    if (card.isMatched)
                    {
                        mvprintw(y, x, "[ ]");
                    }
                    else if (card.isFaceUp)
                    {
                        if (has_colors())
                        {
                            attron(COLOR_PAIR(2));
                        }

                        mvprintw(y, x, "[%c]", card.value);

                        if (has_colors())
                        {
                            attroff(COLOR_PAIR(2));
                        }
                    }
                    else
                    {
                        if (has_colors())
                        {
                            attron(COLOR_PAIR(1));
                        }

                        mvprintw(y, x, "[*]");

                        if (has_colors())
                        {
                            attroff(COLOR_PAIR(1));
                        }
                    }

                    attroff(A_BOLD | A_REVERSE);
                }
            }

            mvprintw(rows * 2 + 1, 0,
                     "Use arrows to move, SPACE or ENTER to flip. Q to quit.");

            refresh();

            int key = getch();

            switch (key)
            {
                case KEY_UP:
                    if (cursorRow > 0)
                        cursorRow--;
                    break;

                case KEY_DOWN:
                    if (cursorRow < rows - 1)
                        cursorRow++;
                    break;

                case KEY_LEFT:
                    if (cursorCol > 0)
                        cursorCol--;
                    break;

                case KEY_RIGHT:
                    if (cursorCol < cols - 1)
                        cursorCol++;
                    break;

                case ' ':
                case '\n':
                    if (flipCard(cursorRow, cursorCol))
                    {
                        // Show the second card before checking the pair
                        clear();

                        for (int r = 0; r < rows; r++)
                        {
                            for (int c = 0; c < cols; c++)
                            {
                                int index = r * cols + c;
                                Card& card = cards.getAt(index);

                                int x = c * 4;
                                int y = r * 2;

                                if (card.isMatched)
                                    mvprintw(y, x, "[ ]");
                                else if (card.isFaceUp)
                                    mvprintw(y, x, "[%c]", card.value);
                                else
                                    mvprintw(y, x, "[*]");
                            }
                        }

                        refresh();
                        napms(1000);
                        checkMatch();
                    }
                    break;

                case 'q':
                case 'Q':
                    endwin();
                    return;
            }
        }

        clear();
        mvprintw(rows, 0, "You Win!");
        refresh();
        getch();
        endwin();
    }
};

int main()
{
    MemoryGame game;

    game.displayTerminalNcurses();

    return 0;
}