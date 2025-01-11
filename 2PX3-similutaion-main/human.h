#ifndef HUMAN_H
#define HUMAN_H

class human{
    public:
        float stop_time_low;
        float stop_time_high;
        float clear_time_low;
        float clear_time_high ;
        bool has_stopped;

    //operation window:
        
    
};
#endif

class Driver:


    def __init__(self, name, arrival_time):
        self.name = name
        self.arrival_time = arrival_time
     
    #Returns driver instance stop time
    def get_stop_time(self):
        r = random.random()
        if r < 0.5:
            return  self.stop_time_low
        return self.stop_time_high

    #Returns driver instance clear time
    def get_clear_time(self):
        r = random.random()
        if r < 0.5:
            self.clear_time_low
        return self.clear_time_high
