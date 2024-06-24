#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *head = NULL;

void insertNode(int value);
void display();
void deleteNode(int value);
void insertFirst(int value);
void deleteFirstNode();

int main(int argc, char *argv[])
{
    deleteFirstNode();
    display();

    return 0;
}

void insertNode(int value)
{
    Node *newNode, *last;
    newNode = new Node;
    newNode->data = value;

    if (head == NULL)
    {
        head = newNode;
        newNode->next = NULL;
    }
    else
    {
        last = head;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = newNode;
        newNode->next = NULL;
    }
}

void display()
{
    if (head == NULL)
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        Node *currentNode = head;

        while (currentNode != NULL)
        {
            cout << currentNode->data << "\t";
            currentNode = currentNode->next;
        }
    }

    cout << endl;
}

void deleteNode(int value)
{
    Node *previous;
    Node *current = head;

    if (current->data == value)
    {
        head = current->next;
        free(current);
        return;
    }

    while (current->data != value)
    {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
    free(current);
}

void insertFirst(int value)
{
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void deleteFirstNode()
{
    if (head == nullptr)
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        Node *firstNode = head;
        
        head = firstNode->next;
        delete(firstNode);
    }
}