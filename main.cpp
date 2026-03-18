#include <iostream>
#include <exception>

template< class T >
struct List {
    T val;
    List< T >* next;
};

template< class T >
struct Vec {
    T* data;
    size_t s, cap;
};

template< class T >
Vec< List< T >* > balanced_move(Vec< List< T >* > v, size_t k) {
    if (k == 0) return { nullptr, 0, 0 };

    size_t total_nodes = 0;
    for (size_t i = 0; i < v.s; ++i) {
        for (List<T>* curr = v.data[i]; curr; curr = curr->next) {
            total_nodes++;
        }
    }

    List<T>** all_nodes = nullptr;
    List<T>** new_data = nullptr;
    try {
        if (total_nodes > 0) {
            all_nodes = new List<T>*[total_nodes];
        }
        new_data = new List<T>*[k]();
    } catch (...) {
        delete[] all_nodes;
        delete[] new_data;
        throw;
    }

    size_t idx = 0;
    for (size_t i = 0; i < v.s; ++i) {
        for (List<T>* curr = v.data[i]; curr; curr = curr->next) {
            all_nodes[idx++] = curr;
        }
    }

    size_t nodes_per_list = total_nodes / k;
    size_t extra = total_nodes % k;
    size_t current_node_idx = 0;

    for (size_t i = 0; i < k; ++i) {
        size_t count = nodes_per_list + (i < extra ? 1 : 0);
        if (count > 0) {
            new_data[i] = all_nodes[current_node_idx];
            for (size_t j = 0; j < count - 1; ++j) {
                all_nodes[current_node_idx + j]->next = all_nodes[current_node_idx + j + 1];
            }
            all_nodes[current_node_idx + count - 1]->next = nullptr;
            current_node_idx += count;
        } else {
            new_data[i] = nullptr;
        }
    }

    delete[] all_nodes;
    
    return { new_data, k, k };
}

int main()
{}
