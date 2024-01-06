#include<bits/stdc++.h>
using namespace std;

// FIFO
void FIFO(vector<int>& pageRequests, int blockSize) {
    queue<int> FIFOQueue;
    set<int> frameSet;

    int pageFaults = 0;

    cout << "FIFO Algorithm:" << endl;
    for (int page : pageRequests) {
        if (frameSet.find(page) == frameSet.end()) {
            if (FIFOQueue.size() == blockSize) {
                int frontPage = FIFOQueue.front();
                cout << "Eliminate "<<frontPage << "\n";
                FIFOQueue.pop();
                frameSet.erase(frontPage);
            }
            FIFOQueue.push(page);
            frameSet.insert(page);
            pageFaults++;
        }
    }

    cout << "Page Faults: " << pageFaults << endl;
    cout << "Page Fault Rate: " << (double)(pageFaults) / pageRequests.size() << endl;
    cout << endl;
}

// LRU
void LRU(vector<int>& pageRequests, int num_frames) {
    list<int> pageList;  
    set<int> frameSet;  
    int pageFaults = 0;

    cout << "LRU Algorithm:" << endl;
    for (int page : pageRequests) {
        if (frameSet.find(page) == frameSet.end()) {
            if (pageList.size() == num_frames) {
                int last_page = pageList.back();
                pageList.pop_back();
                frameSet.erase(last_page);
                cout << "Eliminate "<<last_page << "\n";
            }
            pageList.push_front(page);
            frameSet.insert(page);
            pageFaults++;
        } else {
            pageList.remove(page);
            pageList.push_front(page);
        }
    }

    cout << "Page Faults: " << pageFaults << endl;
    cout << "Page Fault Rate: " << (double)(pageFaults) / pageRequests.size() << endl;
    cout << endl;
}

int main() {
    // 进程的页面请求序列
    vector<int> pageRequests = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    // 空闲内存块数
    int blockSize = 3;

    // 使用FIFO算法模拟页面调度
    FIFO(pageRequests, blockSize);

    // 使用LRU算法模拟页面调度
    LRU(pageRequests, blockSize);

    return 0;
}