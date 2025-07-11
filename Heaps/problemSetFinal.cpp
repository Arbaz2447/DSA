// 2402. Meeting Rooms III
// Intresting Question after that Freaking k-sum Problem!

// Appproach -> 2 min heaps for tracing lowest rooms first , another if rooms went busy which frees first
// maintain frequency and max

// catch .. when a room is free it should be added back to empty rooms automatically irrespective of meetings
// Question did not state  but this is the behaviour 

class Solution {
public:
    void checkFreq(int&  room,int& freqRoom,int & maxFreq,int& resRoom){
        if(freqRoom == maxFreq){
            resRoom = min(room,resRoom);
        }else if(freqRoom > maxFreq){
            maxFreq = freqRoom;
            resRoom = room;
        }
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Init the req data

        priority_queue< int , vector < int > , greater < int > > freeRooms;
        using p = pair < long long , int > ;
        priority_queue< p , vector < p > , greater < p > > nextFreeTime;
        unordered_map< int , int > freq;

        // fill up the free rooms 
        for(int i = 0; i < n; i++){
            freeRooms.push(i);
        }
        int maxFreq = INT_MIN;
        int resRoom = INT_MAX;

        // Traverse The Meetings
        int size = meetings.size();
        // first in first out booking ..so no wait time
        sort(meetings.begin(),meetings.end());
        for(int i = 0; i < size; i++){
            long long start = meetings[i][0];
            long long end = meetings[i][1];
            // update the data .. the rooms were booked already but empty now can be given
            while(!nextFreeTime.empty() && nextFreeTime.top().first <= start){
                auto data = nextFreeTime.top(); nextFreeTime.pop();
                freeRooms.push(data.second);
            }

            if(!freeRooms.empty()){
                int room = freeRooms.top(); freeRooms.pop();
                freq[room]++;

                checkFreq(room,freq[room],maxFreq,resRoom);
                nextFreeTime.push({end, room});
            }else{
                auto nextRoom = nextFreeTime.top(); nextFreeTime.pop();
                int room = nextRoom.second;
                // Next available solt + current Time
                
                freq[room]++;
                checkFreq(room,freq[room],maxFreq,resRoom);
                nextFreeTime.push({ max((long long)nextRoom.first,start) + (end - start), room}); 
            }
        }
        return resRoom;
    }
};
