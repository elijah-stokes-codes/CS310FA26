#include <iostream>
#include <deque>
#include <vector>

using namespace std;

// SECTION 1: Linked-List Queue

struct Node
{
    int data;
    Node* next;

    Node(int val)
    {
        data = val;
        next = nullptr;
    }
};

class LinkedListQueue
{
private:
    Node* head; // Points to the front of the queue
    Node* tail; // Points to the back of the queue

public:
    // Constructor: Starts with an empty queue
    LinkedListQueue()
    {
        head = nullptr;
        tail = nullptr;
    }

// Destructor: Deletes all nodes to prevent memory leaks
~LinkedListQueue()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
}

// Add a new item to the back of the queue
// Time Complexity: O(1)
void enqueue(int value)
{
    // Create a new node
    Node* newNode = new Node(value);

    // If the queue is empty
    if (tail == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Connect the new node to the last node
        tail->next = newNode;

        // Update the tail
        tail = newNode;
    }
}
// Remove the first item from the queue
// Time Complexity: O(1)
void dequeue()
{
    // Check if the queue is empty
    if (head == nullptr)
    {
        cout << "Queue is empty. Cannot dequeue." << endl;
        return;
    }

    // Save the first node before removing it
    Node* temp = head;

    // Move head to the next node
    head = head->next;

    // Delete the old first node
    delete temp;

    // If the queue becomes empty, reset tail
    if (head == nullptr)
    {
        tail = nullptr;
    }
}
// Return the value at the front of the queue
// Time Complexity: O(1)
int front()
{
    if (head == nullptr)
    {
        cout << "Queue is empty." << endl;
        return -1;
    }

    return head->data;
}
// Check whether the queue is empty
// Time Complexity: O(1)
bool isEmpty()
{
    return head == nullptr;
}
};
// SECTION 2: Circular Queue

class MyCircularQueue
{
private:
    vector<int> data;
    int head;
    int tail;
    int count;
    int capacity;

public:
    // Constructor
    MyCircularQueue(int k)
    {
        capacity = k;

        if (capacity < 0)
        {
            capacity = 0;
        }

        data.resize(capacity);

        head = 0;
        tail = 0;
        count = 0;
    }

    // Add an item to the circular queue
    // Time Complexity: O(1)
    bool enQueue(int value)
    {
        if (isFull())
        {
            return false;
        }

        data[tail] = value;
        tail = (tail + 1) % capacity;
        count++;

        return true;
    }

    // Remove an item from the circular queue
    // Time Complexity: O(1)
    bool deQueue()
    {
        if (isEmpty())
        {
            return false;
        }

        head = (head + 1) % capacity;
        count--;

        return true;
    }

    // Return the front value
    int Front()
    {
        if (isEmpty())
        {
            return -1;
        }

        return data[head];
    }

    // Return the rear value
    int Rear()
    {
        if (isEmpty())
        {
            return -1;
        }

        int rearIndex = (tail - 1 + capacity) % capacity;
        return data[rearIndex];
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return count == 0;
    }

    // Check if queue is full
    bool isFull()
    {
        return count == capacity;
    }
};

// SECTION 3: Sliding Window Maximum
// Time Complexity: O(n)

vector<int> maxSlidingWindow(const vector<int>& nums, int k)
{
    vector<int> result;
    deque<int> dq;

    if (k <= 0 || k > static_cast<int>(nums.size()))
    {
        return result;
    }

    for (int i = 0; i < static_cast<int>(nums.size()); i++)
    {
        // Remove indices outside the current window
        while (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }

        // Remove smaller values from the back
        while (!dq.empty() && nums[dq.back()] <= nums[i])
        {
            dq.pop_back();
        }

        // Add the current index
        dq.push_back(i);

        // Save the maximum when a full window exists
        if (i >= k - 1)
        {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}
// MAIN FUNCTION: Test all three sections

int main()
{
    cout << "===== SECTION 1: LINKED-LIST QUEUE =====" << endl;

    LinkedListQueue q;

    cout << "Queue empty: " << q.isEmpty() << endl;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front after adding 10, 20, 30: "
         << q.front() << endl;

    q.dequeue();

    cout << "Front after removing 10: "
         << q.front() << endl;

    q.dequeue();
    q.dequeue();

    cout << "Queue empty after removing all: "
         << q.isEmpty() << endl;

    cout << endl;

    cout << "===== SECTION 2: CIRCULAR QUEUE =====" << endl;

    MyCircularQueue cq(3);

    cout << "Add 1: " << cq.enQueue(1) << endl;
    cout << "Add 2: " << cq.enQueue(2) << endl;
    cout << "Add 3: " << cq.enQueue(3) << endl;

    cout << "Add 4 when full: " << cq.enQueue(4) << endl;

    cout << "Rear: " << cq.Rear() << endl;
    cout << "Full: " << cq.isFull() << endl;

    cout << "Remove front: " << cq.deQueue() << endl;
    cout << "Add 4 after removal: " << cq.enQueue(4) << endl;

    cout << "Front: " << cq.Front() << endl;
    cout << "Rear: " << cq.Rear() << endl;

    cout << endl;

    cout << "===== SECTION 3: SLIDING WINDOW MAXIMUM =====" << endl;

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> answer = maxSlidingWindow(nums, k);

    cout << "Input: 1 3 -1 -3 5 3 6 7" << endl;
    cout << "Window size: " << k << endl;
    cout << "Maximum values: ";

    for (int i = 0; i < static_cast<int>(answer.size()); i++)
    {
        cout << answer[i] << " ";
    }

    cout << endl;

    return 0;
}



