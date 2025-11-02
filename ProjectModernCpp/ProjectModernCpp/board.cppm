export module board;
import peon;
#import "Money.h";
export class board {
private: 
    int zone = 0;
public: 
    void checkZone();
    int getZone() const { return zone;}
}