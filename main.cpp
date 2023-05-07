/*

 Також перевантажте по одному математичному та логічному оператору, на ваш вибір (звісно вони мають працювати лише з елементом на виході – це ж черга).

 Перевантажте математичні та логічні операції що залишились.

*/


#include <iostream>
#include <string>
#include <ctime>


using namespace std;

// Element
class Node
{

    friend ostream& operator<<(ostream &output, const Node &obj) {
        output << obj.data << endl;
        return output;
    }

public:
    int data;
    Node *prev;
    Node *next;

    Node(int d)
    {
        data = d;
        prev = 0;
        next = 0;
    }
};

// Queue manager
class Queue
{

public:
    Node *front;
    Node *back;
    int size;

    Queue()
    {
        front = 0;
        back = 0;
        size = 0;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void push(int data) {
        Node* newNode = new Node(data);

        if (isEmpty()) {
            front = back = newNode;
        }
        else {
            newNode->prev = back;
            back->next = newNode;
            back = newNode;
        }

        size++;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return -1;
        }

        int data = front->data;
        Node* temp = front;

        if (front == back) {
            front = back = nullptr;
        }
        else {
            front = front->next;
            front->prev = nullptr;
        }

        size--;
        delete temp;
        return data;
    }

    int top()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }

        return front->data;
    }

    Node& operator[](int index)
    {
        Node *temp = front;
        for(int i = 0; i < index; i++) {
            temp = temp->next;
        }

        return *temp;
    }


    string stringRepr(int priorityForQueue) const
    {
        string response = "";
        if (isEmpty())
        {
            return "";
        }
        else
        {
            Node *temp = front;

            while (temp != 0)
            {
                response += to_string(temp->data) + "(" + to_string(priorityForQueue) + "), ";
                temp = temp->next;
            }
        }
        return response;
    }
};


class QueueManager {
    static const int count = 4;
    Queue arrayOfQueueByPriority[count];

    friend ostream& operator<<(ostream &output, const QueueManager &obj) {
        output << obj.stringOfAllQueue();
        return output;
    }

    // Заповнення рандомним значенням нового елемента для черги, з найнижчим пріорітетом
    friend istream& operator>>(istream &input, QueueManager &obj) {
        int randomValue = rand() % 100 + 1;
        obj.push(randomValue, 1);
        return input;
    }

    friend bool operator== (Node &left, Node &right) {
        return left.data == right.data;
    }

public:
    QueueManager() {
        for(int i = 0; i < count; i++) {
            Queue queue;
            arrayOfQueueByPriority[i] = queue;
        }
    }

    Node& operator[](int takenIndex) {
        int index = takenIndex;
        int dynamicCountOfQueueus = count;
        while(dynamicCountOfQueueus > 0) {
            if (!arrayOfQueueByPriority[dynamicCountOfQueueus-1].isEmpty()) {
                if (arrayOfQueueByPriority[dynamicCountOfQueueus-1].size < index) {
                    index -= arrayOfQueueByPriority[dynamicCountOfQueueus-1].size;
                } else {
                    break;
                }
            }
            dynamicCountOfQueueus--;
        }
        return arrayOfQueueByPriority[dynamicCountOfQueueus-1][index];
    }

    void push(int data, int priority) {
        arrayOfQueueByPriority[priority-1].push(data);
    }

    int pop() {
        for(int i = count; i > 0; i--) {
            if (!arrayOfQueueByPriority[i-1].isEmpty()) {
                return arrayOfQueueByPriority[i-1].pop();
            }
        }
        return 0;
    }

    int top() {
        for(int i = count; i > 0; i--) {
            if (!arrayOfQueueByPriority[i-1].isEmpty()) {
                return arrayOfQueueByPriority[i-1].top();
            }
        }
        return 0;
    }

    string stringOfAllQueue() const
    {
        string response = "";
        for(int i = count; i > 0; i--) {
            if (!arrayOfQueueByPriority[i - 1].isEmpty()) {
                response += arrayOfQueueByPriority[i - 1].stringRepr(i);
            }
        }
        return response;
    }
};

int main()
{
    int data, menu, elementPriority;
    QueueManager queue;
    //system("cls");
    srand(time(0));

    // Menu
    while (true)
    {
//        system("clear");
        cout << "Queue: " << queue << endl;
        cout << "Menu: " << endl;
        cout << "1 - Add element" << endl;
        cout << "2 - Add random element with lower priority" << endl;
        cout << "3 - Pop element" << endl;
        cout << "4 - Get top element" << endl;
        cout << "6 - Quit" << endl;
        cout << "Your choise: ";
        cin >> menu;

        if (menu == 6)
        {
            break;
        }

        switch (menu)
        {
        case 1:
            // Add element
            cout << "Add to queue element: ";
            cin >> data;
            cout << "Add priority to element: ";
            cin >> elementPriority;
            queue.push(data, elementPriority);
            break;
        case 2:
            // Add random element with minimal priority
            cin >> queue;
            break;
        case 3:
            // Pop element
            cout << "Poped element - " << queue.pop() << endl;

            break;
        case 4:
            // Display top element
            cout << "Top element: ";
            cout << queue.top() << endl;
            break;
        case 5:
            cout << queue[0];
            cout << queue[1];
            break;
        }
    }
    return 0;
}