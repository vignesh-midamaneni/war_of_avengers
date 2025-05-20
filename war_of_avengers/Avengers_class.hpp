#include"QNS_class.hpp";
// Avenger class: each Avenger has a name, suit, and attack strength
class Avenger
{
public:
    Avenger() {}
    Avenger(string avName, QNS avSuit, int strength)
        : name(avName), suit(avSuit), attackStrength(strength) {}
    void attack(Avenger &enemy);     // attacking the enemy with factor of attackStrength.
    void upgradeSuit(QNS othersuit); // upgrading suit by other suit ( if exists ).
    void repair(int x);              // repairing suit by incrementing durability by x.
    void printStatus();              // status of his suit.
    QNS &getsuit() { return suit; }

private:
    string name;
    QNS suit;
    int attackStrength;
};

// -------------------- AVENGER -------------------------------

// Avenger methods
void Avenger::attack(Avenger &enemey)
{
    enemey.suit - attackStrength;
}
void Avenger::upgradeSuit(QNS othersuit)
{
    suit + othersuit;
}
void Avenger::repair(int x)
{
    suit / x;
}
void Avenger::printStatus()
{
    cout << name << " " << suit.getP() << " " << suit.getD() << " " << suit.getE() << " " << suit.getH() << endl;
}

// -------------------- AVENGER -------------------------------