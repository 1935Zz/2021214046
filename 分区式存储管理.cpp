#include<bits/stdc++.h>
using namespace std;

struct MemoryBlock {
    int startAddress; 
    int size; 

    MemoryBlock(int _startAddress, int _size) : startAddress(_startAddress), size(_size) {}
};

// First Fit Algorithm
void firstFit(vector<MemoryBlock> memory, vector<int> processSize) {
    cout << "First Fit Algorithm:" << endl;
    for (int processSize : processSize) {
        bool f = false;
        for (int i = 0; i < memory.size(); ++i) {
            if (memory[i].size >= processSize) {
                f = true;
                cout << "Allocated block at address " << memory[i].startAddress << " for process of size " 
                << processSize << endl;
                memory[i].startAddress += processSize;
                memory[i].size -= processSize;
                break;
            }
        }
        if (!f) cout << "Unable to allocate block for process of size " << processSize << endl;
    }
    // 分配完成后的空闲分区队列
    cout << "After allocation:" << endl;
    for (const auto& block : memory) {
        if (block.size > 0)
            cout << "Start: " << block.startAddress << ", Size: " << block.size << endl;
    }
}

// Best Fit Algorithm
void bestFit(vector<MemoryBlock> memory, vector<int> processSize) {
    cout << "Best Fit Algorithm:" << endl;
    for (int processSize : processSize) {
        int id = -1;
        for (int i = 0; i < memory.size(); ++i) {
            if (memory[i].size >= processSize) {
                if (id == -1) id = i;
                else if (memory[i].size < memory[id].size) id = i;
            }
        }
        if (id != -1) {
            cout << "Allocated block at address " << memory[id].startAddress << " for process of size "
             << processSize << endl;
            memory[id].startAddress += processSize;
            memory[id].size -= processSize;
        } else {
            cout << "Unable to allocate block for process of size " << processSize << endl;
        }
    }

    // 分配完成后的空闲分区队列
    cout << "After allocation:" << endl;
    for (const auto& block : memory) {
        if (block.size > 0)
            cout << "Start: " << block.startAddress << ", Size: " << block.size << endl;
    }
}

// Worst Fit Algorithm
void worstFit(vector<MemoryBlock> memory, vector<int> processSize) {
    cout << "\nWorst Fit Algorithm:" << endl;
    for (int processSize : processSize) {
        int id = -1;
        for (int i = 0; i < memory.size(); ++i) {
            if (memory[i].size >= processSize) {
                if (id == -1) id = i;
                else if (memory[i].size > memory[id].size) id = i;
            }
        }
        if (id != -1) {
            cout << "Allocated block at address " << memory[id].startAddress << " for process of size "
             << processSize << endl;
            memory[id].startAddress += processSize;
            memory[id].size -= processSize;
        } else {
            cout << "Unable to allocate block for process of size " << processSize << endl;
        }
    }

    // 空闲分区队列
    cout << "After allocation:" << endl;
    for (const auto& block : memory) {
        if (block.size > 0)
            cout << "Start: " << block.startAddress << ", Size: " << block.size << endl;
    }
}

int main() {
    vector<MemoryBlock> memory = {{0, 40}, {60, 30}, {100, 60}, {200, 10}};
    

    vector<int> processSize = {20, 10, 30, 5};

    firstFit(memory, processSize);
    bestFit(memory, processSize);
    worstFit(memory, processSize);

    return 0;
}
