export module peon;
export class peon {
private:
    int pos = 0;

public:
    peon() = default;

    explicit peon(int initialPos) : pos(initialPos) {}

    int getPos() const { return pos; }

    void setPos(int newPos) { pos = newPos; }

private: 
    void incrementPos() { ++pos; }

    void decrementPos() { --pos; }
public: void move(int steps, bool player);
      void checkZone();
};