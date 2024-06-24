#include <iostream>

using namespace std;

class EmptyLinkedListError : public runtime_error
{
  public:
    EmptyLinkedListError() : runtime_error("EmptyLinkedListError: The linked list is empty") {}
};

class NodeNotFoundError : public runtime_error
{
  public:
    NodeNotFoundError() : runtime_error("NodeNotFoundError: The node is not found") {}
};

class Node
{
  public:
    int data;
    Node *next = nullptr;
    static int nodesCount;

  public:
    Node() { nodesCount++; };
};
int Node::nodesCount = 0;

class LinkedList
{
  public:
    Node *head = nullptr;
    Node *tail = nullptr;

  protected:
    int searchCounter = 0;

  public:
    LinkedList() {}

    ~LinkedList()
    {
        Node *current = head;

        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    int findAndHandleErrors()
    {
        bool findError = false;

        try
        {
            if (!head)
            {
                findError = true;
                throw EmptyLinkedListError();
            }
            else if (searchCounter == Node::nodesCount)
            {
                findError = true;
                searchCounter = 0;
                throw NodeNotFoundError();
            }
        }
        catch (const EmptyLinkedListError &e)
        {
            cerr << e.what() << endl;
        }
        catch (const NodeNotFoundError &e)
        {
            cerr << e.what() << endl;
        }

        return findError;
    }

    void insertNode(int value)
    {
        Node *newNode = new Node();
        newNode->data = value;

        if (head)
        {
            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            head = newNode;
            tail = newNode;
        }
    }

    void printNodes()
    {
        Node *temp = head;

        cout << "{";

        while (temp)
        {
            cout << temp->data;
            temp = temp->next;

            if (temp)
            {
                cout << ", ";
            }
        }

        cout << "}" << endl;
    }

    void deleteNode(int target)
    {
        Node *previous = nullptr;
        Node *current = head;

        while (current)
        {
            if (current->data == target)
                break;

            previous = current;
            current = current->next;
            searchCounter++;
        }

        if (findAndHandleErrors())
            return;
        else if (current == head)
        {
            delete head;
            head = current->next;
        }
        else if (current == tail)
        {
            delete tail;
            tail = previous;
            previous->next = nullptr;
        }
        else
        {
            previous->next = current->next;
            delete current;
        }
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
        if (findAndHandleErrors())
            return;

        Node *secondNode = head->next;

        delete head;
        head = secondNode;
    }
};

int main(int argc, char *argv[])
{
    LinkedList nums;

    nums.insertNode(5);
    nums.insertNode(10);
    nums.insertNode(15);
    nums.insertNode(7);
    nums.deleteFirstNode();
    nums.printNodes();

    return 0;
}