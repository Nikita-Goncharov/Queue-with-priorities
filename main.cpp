#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Element
class Node
{
    friend bool operator== (Node &left, Node &right) {
        return left.data == right.data;
    }

    friend bool operator!= (Node &left, Node &right) {
        return left.data != right.data;
    }

    friend bool operator> (Node &left, Node &right) {
        return left.data > right.data;
    }

    friend bool operator< (Node &left, Node &right) {
        return left.data < right.data;
    }

    friend bool operator>= (Node &left, Node &right) {
        return left.data >= right.data;
    }

    friend bool operator<= (Node &left, Node &right) {
        return left.data <= right.data;
    }

    friend int operator+ (Node &left, Node &right) {
        return left.data + right.data;
    }

    friend int operator- (Node &left, Node &right) {
        return left.data - right.data;
    }

    friend int operator* (Node &left, Node &right) {
        return left.data * right.data;
    }

    friend int operator/ (Node &left, Node &right) {
        return left.data / right.data;
    }

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
        int i = 0;
        Node *temp = front;
        while(i != index) {
            temp = temp->next;
            i++;
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

public:
    QueueManager() {
        for(int i = 0; i < count; i++) {
            Queue queue;
            arrayOfQueueByPriority[i] = queue;
        }
    }

    Node& operator[](int takenIndex) {
        int index = takenIndex;
        int dynamicCountOfQueues = count;

        while(dynamicCountOfQueues > 0) {
            if (!arrayOfQueueByPriority[dynamicCountOfQueues-1].isEmpty()) {
                if (arrayOfQueueByPriority[dynamicCountOfQueues-1].size-1 < index) {
                    index -= arrayOfQueueByPriority[dynamicCountOfQueues-1].size;
                } else {
                    break;
                }
            }
            dynamicCountOfQueues--;
        }
        return arrayOfQueueByPriority[dynamicCountOfQueues-1][index];
    }

    void push(int data, int priority) {
        if (priority > 0 && priority <= count) {
            arrayOfQueueByPriority[priority-1].push(data);
        }
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
    int data, menu, elementPriority, firstElement, secondElement, intResult;
    bool boolResult;
    QueueManager queue;
    //system("cls");
    srand(time(0));

    // Menu
    while (true)
    {
        // system("clear");
        cout << endl;
        cout << "Queue: " << queue << endl;
        cout << "Menu: " << endl;
        cout << "1 - Add element" << endl;
        cout << "2 - Add random element with lower priority" << endl;
        cout << "3 - Pop element" << endl;
        cout << "4 - Get top element" << endl;
        cout << "5 - Make arithmetic operations with elements by index" << endl;
        cout << "6 - Make logic operations with elements by index" << endl;
        cout << "7 - Quit" << endl;
        cout << "Your choise: ";
        cin >> menu;

        if (menu == 7)
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
            cout << "Menu: " << endl;
            cout << "1 - +" << endl;
            cout << "2 - -" << endl;
            cout << "3 - *" << endl;
            cout << "4 - /" << endl;
            cout << "Your choise: ";
            cin >> menu;

            cout << "Index of first element: ";
            cin >> firstElement;

            cout << "Index of second element: ";
            cin >> secondElement;

            switch (menu) {
                case 1:
                    intResult = queue[firstElement] + queue[secondElement];
                    break;
                case 2:
                    intResult = queue[firstElement] - queue[secondElement];
                    break;
                case 3:
                    intResult = queue[firstElement] * queue[secondElement];
                    break;
                case 4:
                    intResult = queue[firstElement] / queue[secondElement];
                    break;
            }
            cout << "Result: " << intResult << endl;
            break;
        case 6:
            cout << "Menu: " << endl;
                cout << "1 - ==" << endl;
                cout << "2 - !=" << endl;
                cout << "3 - >" << endl;
                cout << "4 - <" << endl;
                cout << "5 - >=" << endl;
                cout << "6 - <=" << endl;
                cout << "Your choise: ";
                cin >> menu;

                cout << "Index of first element: ";
                cin >> firstElement;

                cout << "Index of second element: ";
                cin >> secondElement;

                switch (menu) {
                    case 1:
                        boolResult = queue[firstElement] == queue[secondElement];
                        break;
                    case 2:
                        boolResult = queue[firstElement] != queue[secondElement];
                        break;
                    case 3:
                        boolResult = queue[firstElement] > queue[secondElement];
                        break;
                    case 4:
                        boolResult = queue[firstElement] < queue[secondElement];
                        break;
                    case 5:
                        boolResult = queue[firstElement] >= queue[secondElement];
                        break;
                    case 6:
                        boolResult = queue[firstElement] <= queue[secondElement];
                        break;
                }
                cout << "Result: " << (boolResult ? "True" : "False") << endl;
            break;
        }
    }
    return 0;
}