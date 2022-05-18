#pragma once

#include "Core.h"

#include <iterator>
#include <assert.h>

namespace absGL
{
    template <typename T> class ABSGL_API Vector
    {
        T* arr;
        int capacity;
        int current;

    public:
        
        Vector()
        {
            arr = new T[1];
            capacity = 1;
            current = 0;
        }

        void Push(T data)
        {
            if (current == capacity) 
            {

                T* temp = new T[2 * capacity];

                for (int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }

                delete[] arr;
                capacity *= 2;
                arr = temp;
            }

            arr[current] = data;
            current++;
        }

        void Push(T data, int index)
        {
            if (index == capacity)
                push(data);
            else
                arr[index] = data;
        }

        T Get(int index)
        {
            if (index < current)
                return arr[index];
        }

        void Pop() { current--; }
        int Count() { return current; }
        int GetCapacity() { return capacity; }
        
        T& operator[] (int x) 
        {
            return arr[x];
        }

        T& operator[] (unsigned int x)
        {
            return arr[x];
        }

        void Print()
        {
            for (int i = 0; i < current; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    };
}