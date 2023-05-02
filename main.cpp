/*
 Вона повинна мати аналоги методів push, top та pop.

 Перевантажте >> щоб вони працювали як push з найнижчим пріоритетом.
 Також перевантажте по одному математичному та логічному оператору, на ваш вибір (звісно вони мають працювати лише з елементом на виході – це ж черга).

 Перевантажте математичні та логічні операції що залишились.

 Нехай черга постійно буде на екрані, щоб можна було спостерігати за її змінами.

*/


#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Element
class Node
{
public:
    int data;
    int priority;
    Node *prev;
    Node *next;

    Node(int d, int givenPriority)
    {
        data = d;
        priority = givenPriority;
        prev = 0;
        next = 0;
    }
};

// Queue manager
class Queue
{
private:
    Node *front;
    Node *back;
    int size;
    static const int maxPrioritet = 4;
    int currentMaxPrioritetInQueue;


public:
    Queue()
    {
        front = 0;
        back = 0;
        size = 0;
        currentMaxPrioritetInQueue = 0;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void push(int data, int priority=1)
    {
        if (priority <= maxPrioritet && priority > 0)
        {
            currentMaxPrioritetInQueue = priority > currentMaxPrioritetInQueue ? priority : currentMaxPrioritetInQueue;
            Node *newNode = new Node(data, priority);
            if (isEmpty())
            {
                front = back = newNode;
            }
            else
            {
                newNode->prev = back;
                back->next = newNode;
                back = newNode;
            }
            size++;
        }
        else {
            cout << "Error!!! Priority is not correct!!!";
        }
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
        }
        else
        {
            Node *temp = front;

            while (temp != 0)
            {
                cout << temp->data << "(" << temp->priority << ")" << ", ";
                temp = temp->next;
            }

            cout << endl;
        }
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }

        int data = front->data;
        Node *temp = front;

        if (front == back)
        {
            front = back = 0;
        }
        else
        {
            front = front->next;
            front->prev = 0;
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

        Node *temp = front;
        while (temp->priority != currentMaxPrioritetInQueue) {
            temp = temp->next;
        }

        return temp->data;
    }


    // Вивід усієї черги TODO: maybe remove .display method and write all functional here
    friend ostream& operator<<(ostream &output, const Queue &obj) {
        obj.display();
        return output;
    }

    // Заповнення рандомним значенням нового елемента для черги, з найнижчим пріорітетом
    friend istream& operator>>(istream &input, Queue &obj) {
        int randomValue = rand() % 100 + 1;
        obj.push(randomValue);
        return input;
    }
};

int main()
{
    int data, menu, elementPriority;
    Queue queue;

    srand(time(0));

    // Menu
    while (true)
    {
        cout << "Menu: " << endl;
        cout << "1 - Add element" << endl;
        cout << "? - Add random element with lower priority" << endl;
        cout << "2 - Pop element" << endl;
        cout << "3 - Display queue" << endl;
        cout << "4 - Display top element" << endl;
        cout << "5 - Quit" << endl;
        cout << "Your choise: ";
        cin >> menu;

        if (menu == 5)
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

            cout << "queue: ";
            cout << queue;
            break;
        case 2:
            // Pop element
            if (!queue.isEmpty())
            {
                cout << "Poped element - " << queue.pop() << endl;
                cout << "queue: ";
                cout << queue;
            }
            else
            {
                cout << "queue is empty" << endl;
            }
            break;
        case 3:
            // Display queue
            if (!queue.isEmpty())
            {
                cout << "queue: ";
                cout << queue;
            }
            else
            {
                cout << "queue is empty" << endl;
            }
            break;
        case 4:
            // Display top element
            if (!queue.isEmpty())
            {
                cout << "Top element: ";
                cout << queue.top() << endl;
            }
            else
            {
                cout << "queue is empty" << endl;
            }
            break;
        }
    }
    return 0;
}