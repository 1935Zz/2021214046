#include<bits/stdc++.h>
using namespace std;



string TimeStampToString(int minutes) {
    string time;
    if (minutes / 60 == 0) time += '0';
    else time += to_string(minutes / 60);
    time += ':';
    if (minutes % 60 < 10) {
        time += '0';
    }
    time += to_string(minutes % 60);
    return time;
}
int StringToTimeStamp(const string s) {
    if (s.length() == 3) {
        return (s[0] - '0') * 60 + ((s[1] - '0') * 10 + (s[2] - '0'));
    } else {
        return ((s[0] - '0') * 10 + (s[1] - '0')) * 60 + ((s[0] - '0') * 10 + (s[1] - '0'));
    }
}
struct Task {
    int id;
    int arrive_time;
    int execute_time;
    int start_time;

    Task(int i, int a, int b) : id(i), arrive_time(a), execute_time(b), start_time(-1) {}
};

bool compareArriveTime(const Task& a, const Task& b) {
    return a.arrive_time < b.arrive_time;
}

bool compareExecuteTime(const Task& a, const Task& b) {
    if (a.execute_time == b.execute_time) return a.arrive_time < b.arrive_time;
    return a.execute_time < b.execute_time;
}

int GetTaskBeginTime(vector<Task> task) {
    int now = 0;
    for (auto t : task) {
        now = max(now, t.arrive_time);
    }
    return now;
}

// 先来先服务FCFS算法
void FCFS(vector<Task> task) {
    sort(task.begin(), task.end(), compareArriveTime); 
    int current_time = GetTaskBeginTime(task);
    for (auto& t : task) {
        t.start_time = current_time; 
        current_time += t.execute_time; 
    }
    cout << "FCFS:\n";
    for (const auto& t : task) {
        cout << "Task " << t.id << " starts at " << TimeStampToString(t.start_time) << "\n";
    }
}

// 短作业优先SJF算法
void SJF(vector<Task> task) {
    sort(task.begin(), task.end(), compareExecuteTime); 
    int current_time = GetTaskBeginTime(task);
    for (auto& t : task) {
        t.start_time = current_time; 
        current_time += t.execute_time; 
    }
    cout << "SJF:\n";
    for (const auto& t : task) {
        cout << "Task " << t.id << " starts at " << TimeStampToString(t.start_time) << "\n";
    }
}

// 最高响应比优先HRN算法
void HRN(vector<Task> task) {
    int current_time = GetTaskBeginTime(task);
    while (1) {
        double Highest_Response_Ratio = 0;
        int next_id = -1;
        for (auto& t : task) {
            if (t.start_time == -1) {
                double Response_Ratio = double(t.execute_time + current_time - t.arrive_time) / t.execute_time;
                if (Response_Ratio > Highest_Response_Ratio) {
                    next_id = t.id - 1;
                    Highest_Response_Ratio = Response_Ratio;
                }
            }
        }
        if (next_id == -1) break;
        task[next_id].start_time = current_time;
        current_time += task[next_id].execute_time;
    }
    cout << "HRN:\n";
    for (const auto& t : task) {
        cout << "Task " << t.id << " starts at " << TimeStampToString(t.start_time) << "\n";
    }
}

int main() {
    vector<Task> task = {
        {1, StringToTimeStamp(string("800")), 50},
        {2, StringToTimeStamp(string("815")), 30},
        {3, StringToTimeStamp(string("830")), 25},
        {4, StringToTimeStamp(string("835")), 20},
        {5, StringToTimeStamp(string("845")), 15},
        {6, StringToTimeStamp(string("900")), 10},
        {7, StringToTimeStamp(string("920")), 5}
    };
    FCFS(task);
    SJF(task);
    HRN(task);
    return 0;
}