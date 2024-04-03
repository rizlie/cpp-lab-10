#include <iostream>

using namespace std;

template<typename T>
class MyPriorityQueue 
{
private:
    // Структура узла очереди
    struct Node 
    {
        T data; // данные элемента
        int priority; // приоритет элемента
        Node* next; // указатель на следующий элемент
    };

    Node* head; // указатель на начало очереди
    size_t count; // количество элементов в очереди

public:
    // Конструктор по умолчанию
    MyPriorityQueue() : head(nullptr), count(0) {}

    // Деструктор
    ~MyPriorityQueue() 
    {
        while (head) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Добавление элемента в очередь с учетом приоритета
    void push(const T& item, int priority) 
    {
        Node* newNode = new Node{ item, priority, nullptr };
        if (!head || priority < head->priority) 
        { 
            newNode->next = head;
            head = newNode;
        }
        else 
        {
            Node* prev = nullptr;
            Node* curr = head;
            while (curr && priority >= curr->priority) 
            { 
                prev = curr;
                curr = curr->next;
            }
            if (prev)
                prev->next = newNode;
            else
                head = newNode;
            newNode->next = curr;
        }
        count++;
    }

    // Извлечение и удаление элемента с наивысшим приоритетом
    void pop() 
    {
        if (head) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            count--;
        }
    }

    // Получение элемента с наивысшим приоритетом без удаления
    T peek() const 
    {
        if (head) 
        {
            return head->data;
        }
        throw "Queue is empty";
    }

    // Возвращает количество элементов в очереди
    size_t size() const 
    {
        return count;
    }

    // Перегрузка оператора << для вывода объекта в поток
    friend ostream& operator<<(ostream& os, const MyPriorityQueue<T>& pq) 
    {
        typename MyPriorityQueue<T>::Node* temp = pq.head;
        while (temp) 
        {
            os << temp->data << " ";
            temp = temp->next;
        }
        return os;
    }
};

int main() 
{
    MyPriorityQueue<int> pq;

    pq.push(3, 1);
    pq.push(5, 2);
    pq.push(7, 3);

    cout << "Queue: " << pq << endl;

    cout << "Size of queue: " << pq.size() << endl;

    cout << "Peek element: " << pq.peek() << endl;

    pq.pop();

    cout << "Queue after pop: " << pq << endl;

    return 0;
}