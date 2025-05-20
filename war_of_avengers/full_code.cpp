/*
---------------------------------------------------------------
Quantum Nano Suit (QNS) - Avengers Battle Simulator
---------------------------------------------------------------
DESCRIPTION:
This program simulates a battle between heroes (Avengers) and enemies, each equipped with customizable and upgradable Quantum Nano Suits (QNS). Each Avenger or enemy has a suit with parameters:
    - Power (P)
    - Durability (D)
    - Energy (E)
    - Heat (H)

Classes:
1. QNS: Represents the Quantum Nano Suit. Supports operations like fusion, damage, power boost, repair, and comparisons.
2. Avenger: Represents an individual character (hero or enemy) with a name, suit, and attack strength. Supports actions like attacking, repairing, upgrading the suit, and printing status.
3. Battle: Manages the overall simulation including creation of heroes and enemies, processing of battle commands, and logging events.

Battle Procedure:
- Read number of suits and details, then enqueue them.
- Assign suits to heroes and enemies (based on availability).
- Enter command processing loop:
    -> Attack: One character attacks another (reducing durability, increasing energy and heat).
    -> Repair: Repairs a character's suit.
    -> BoostPowerByFactor: Boosts suit's power by a given factor.
    -> BoostPower: Boosts suit's power by fusing it with a new QNS.
    -> Upgrade: Uses a new suit from the pool to upgrade an existing suit.
    -> AvengerStatus: Displays the current status of a character.
    -> PrintBattleLog: Shows a log of all battle events.
    -> BattleStatus: Displays who is currently winning.
    -> End: Terminates the simulation.

Constraints:
- Max Power: 5000
- Overheat threshold: Heat > 500 -> suit is overheated
- Durability <= 0 -> suit is destroyed

The simulation handles all operations dynamically and tracks outcomes to determine the final battle result.

Author: Vignesh Midamaneni
---------------------------------------------------------------
*/
#include <bits/stdc++.h>
using namespace std;


// QNS = Quantum Nano Suit
class QNS
{
public:
    // Constructors
    QNS(int powerLevel, int durability, int energyStorage, int heatLevel) : P(min(5000, powerLevel)), D(durability), E(energyStorage), H(heatLevel) {}
    QNS(const QNS &Q) : P(min(5000, Q.P)), D(Q.D), E(Q.E), H(Q.H) {}
    QNS() : P(1000), D(500), E(300), H(0) {}

    // Operator overloads for custom suit behavior
    void operator+(QNS Q); // (P1, D1, E1,H1) + (P2, D2, E2,H2) = (P1 + E2, D1 + D2, E1 + P2,H1)
    void operator-(int X); // (P, D, E, H) - X = (P, D - X, E + X, H + X)
    void operator*(int X); // (P, D, E, H) * X = (P+(P * (X/100)), D, E + 5X, H + X)
    void operator/(int X); // (P, D, E, H) / X = (P, D + X, E, H - X)

    // Power boosting mechanisms
    void boostPower(int factor);    // Boosts(add) power, but increases overheating risk.
    void boostPower(QNS otherSuit); // Transfers energy from another suit to boost durability.

    // Comparison operators
    bool operator==(QNS Q); // checks the power and durability of two suits.
    bool operator<(QNS Q);

    // Accessors (getters returning references)
    int &getP() { return P; }
    int &getD() { return D; }
    int &getE() { return E; }
    int &getH() { return H; }

private:
    int P, D, E, H; // Power, Durability, Energy, Heat
    /* constraints for P,D,E,H.
        P<5000 if not assign P=5000.
        durability>0 if not suit will be destroyed.
        heatlevel<=500 if not the suit shuts down.
    */
};

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

// Battle class manages full simulation
class Battle
{
public:
    void startBattle();                                             // Runs the full simulation
    void printBattleLog();                                          // Shows all events
    int Result();                                                   // status of war ( who has the upperhand )
    void Createhero(string avName, QNS &suit, int attackStrength);  // it creates a hero and adds it to heros
    void Createenemy(string avName, QNS &suit, int attackStrength); // it creates a enemy and adds it to enemy
private:
    map<string, Avenger> heros;
    map<string, Avenger> enemies;
    vector<string> battlelog; // Logs all actions
};

// -------------------- QNS -------------------------------

// QNS Operator Overloads
void QNS::operator+(QNS Q)
{
    P += Q.E;
    D += Q.D;
    E += Q.P;
    if (P > 5000)
        P = 5000;
}
void QNS::operator-(int X)
{
    D -= X;
    E += X;
    H += X;
}
void QNS::operator*(int X)
{
    P += (P * X) / 100;
    E += 5 * X;
    H += X;
    if (P > 5000)
        P = 5000;
}
void QNS::operator/(int X)
{
    D += X;
    H -= X;
    if (H < 0)
        H = 0;
}
void QNS::boostPower(int X)
{
    (*this) * X;
}
void QNS::boostPower(QNS otherSuit)
{
    (*this) + otherSuit;
    if (P > 5000)
        P = 5000;
}
bool QNS::operator==(QNS Q)
{
    if (P == Q.P && D == Q.D)
        return true;
    return false;
}
bool QNS::operator<(QNS Q)
{
    if (P + D < Q.P + Q.D)
        return true;
    return false;
}

// -------------------- QNS -------------------------------

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

// -------------------- BATTLE -------------------------------

// Battle methods
void Battle::printBattleLog()
{
    for (auto s : battlelog)
        cout << s << endl;
}
void Battle::Createhero(string avName, QNS &suit, int attackStrength)
{
    Avenger hero(avName, suit, attackStrength);
    heros[avName] = hero;
}
void Battle::Createenemy(string avName, QNS &suit, int attackStrength)
{
    Avenger enemy(avName, suit, attackStrength);
    enemies[avName] = enemy;
}
int Battle::Result()
{
    int herosum = 0;
    int villansum = 0;
    for (auto h : heros)
    {
        if (h.second.getsuit().getD() > 0)
        {
            herosum += h.second.getsuit().getP();
            herosum += h.second.getsuit().getD();
        }
    }
    for (auto e : enemies)
    {
        if (e.second.getsuit().getD() > 0)
        {
            villansum += e.second.getsuit().getP();
            villansum += e.second.getsuit().getD();
        }
    }
    if (herosum > villansum)
        return 1;
    if (herosum < villansum)
        return -1;
    return 0;
}

// -------------------- BATTLE -------------------------------

void Battle::startBattle()
{
    int k, n, m;
    cin >> k >> n >> m; // k = number of suits , n = number of heros , m = number of enemies.
    queue<QNS> suits;

    // Reading all available suits
    for (int i = 0; i < k; i++)
    {
        int power, durability, energy, heat;
        cin >> power >> durability >> energy >> heat;
        QNS Q(power, durability, energy, heat);
        suits.push(Q);
    }

    // Creating heroes
    for (int i = 0; i < n; i++)
    {
        string name;
        int attackstrength;
        cin >> name >> attackstrength;
        if (!suits.empty())
        {
            Createhero(name, suits.front(), attackstrength);
            suits.pop();
        }
        else
            cout << name << " is out of fight" << endl;
    }

    // Creating enemies
    for (int i = 0; i < m; i++)
    {
        string name;
        int attackstrength;
        cin >> name >> attackstrength;
        if (!suits.empty())
        {
            Createenemy(name, suits.front(), attackstrength);
            suits.pop();
        }
        else
            cout << name << " is out of fight" << endl;
    }
    string command;
    cin >> command;
    assert(command == "BattleBegin");

    // Command processing loop
    while (cin >> command)
    {
        if (command == "Attack")
        {
            string attacker, target;
            cin >> attacker >> target;
            if (heros.find(attacker) != heros.end())
            {
                if (heros.find(target) != heros.end())
                {
                    if (heros[attacker].getsuit().getD() > 0 && heros[attacker].getsuit().getH() <= 500 && heros[target].getsuit().getD() > 0)
                    {
                        string msg = "";
                        if (heros[target].getsuit().getD() > 0)
                        {
                            heros[attacker].attack(heros[target]);
                            msg = attacker + " attacks " + target;
                            battlelog.push_back(msg);
                        }
                        if (heros[target].getsuit().getD() <= 0)
                        {
                            msg = target + " suit destroyed";
                            battlelog.push_back(msg);
                        }
                        else if (heros[target].getsuit().getH() > 500)
                        {
                            msg = target + " suit overheated";
                            battlelog.push_back(msg);
                        }
                    }
                }
                else
                {
                    if (heros[attacker].getsuit().getD() > 0 && heros[attacker].getsuit().getH() <= 500 && enemies[target].getsuit().getD() > 0)
                    {
                        string msg = "";
                        if (enemies[target].getsuit().getD() > 0)
                        {
                            heros[attacker].attack(enemies[target]);
                            msg = attacker + " attacks " + target;
                            battlelog.push_back(msg);
                        }
                        if (enemies[target].getsuit().getD() <= 0)
                        {
                            msg = target + " suit destroyed";
                            battlelog.push_back(msg);
                        }
                        else if (enemies[target].getsuit().getH() > 500)
                        {
                            msg = target + " suit overheated";
                            battlelog.push_back(msg);
                        }
                    }
                }
            }
            else
            {
                if (enemies.find(attacker) != enemies.end())
                {
                    if (heros.find(target) != heros.end())
                    {
                        if (enemies[attacker].getsuit().getD() > 0 && enemies[attacker].getsuit().getH() <= 500 && heros[target].getsuit().getD() > 0)
                        {
                            string msg = "";
                            msg = attacker + " attacks " + target;
                            if (heros[target].getsuit().getD() > 0)
                            {
                                enemies[attacker].attack(heros[target]);
                                msg = attacker + " attacks " + target;
                                battlelog.push_back(msg);
                            }
                            if (heros[target].getsuit().getD() <= 0)
                            {
                                msg = target + " suit destroyed";
                                battlelog.push_back(msg);
                            }
                            else if (heros[target].getsuit().getH() > 500)
                            {
                                msg = target + " suit overheated";
                                battlelog.push_back(msg);
                            }
                        }
                    }
                    else
                    {
                        if (enemies[attacker].getsuit().getD() > 0 && heros[attacker].getsuit().getH() <= 500 && enemies[target].getsuit().getD() > 0)
                        {
                            string msg = "";
                            if (enemies[target].getsuit().getD() > 0)
                            {
                                enemies[attacker].attack(enemies[target]);
                                msg = attacker + " attacks " + target;
                                battlelog.push_back(msg);
                            }
                            if (enemies[target].getsuit().getD() <= 0)
                            {
                                msg = target + " suit destroyed";
                                battlelog.push_back(msg);
                            }
                            else if (enemies[target].getsuit().getH() > 500)
                            {
                                msg = target + " suit overheated";
                                battlelog.push_back(msg);
                            }
                        }
                    }
                }
            }
        }
        else if (command == "Repair")
        {
            string name;
            cin >> name;
            int x;
            cin >> x;
            if (heros.find(name) != heros.end())
            {
                heros[name].repair(x);
            }
            else
            {
                enemies[name].repair(x);
            }
            string msg = "";
            msg = name + " repaired";
            battlelog.push_back(msg);
        }
        else if (command == "BoostPowerByFactor")
        {
            string name;
            cin >> name;
            int fac;
            cin >> fac;
            string msg = "";
            msg = name + " boosted";
            battlelog.push_back(msg);
            if (heros.find(name) != heros.end())
            {
                heros[name].getsuit().boostPower(fac);
                if (heros[name].getsuit().getH() > 500)
                {
                    msg = name + " suit overheated";
                    battlelog.push_back(msg);
                }
            }
            else
            {
                enemies[name].getsuit().boostPower(fac);
                if (enemies[name].getsuit().getH() > 500)
                {
                    msg = name + " suit overheated";
                    battlelog.push_back(msg);
                }
            }
        }
        else if (command == "BoostPower")
        {
            string name;
            cin >> name;
            int p, d, e, h;
            cin >> p >> d >> e >> h;
            QNS q1(p, d, e, h);
            string msg = "";
            msg = name + " boosted";
            if (heros.find(name) != heros.end())
            {
                heros[name].getsuit() + q1;
                if (heros[name].getsuit().getH() > 500)
                {
                    msg = name + " suit overheated";
                    battlelog.push_back(msg);
                }
            }
            else
            {
                enemies[name].getsuit() + q1;
                if (enemies[name].getsuit().getH() > 500)
                {
                    msg = name + " suit overheated";
                    battlelog.push_back(msg);
                }
            }
        }
        else if (command == "AvengerStatus")
        {
            string name;
            cin >> name;
            if (heros.find(name) != heros.end())
            {
                heros[name].printStatus();
            }
            else
            {
                enemies[name].printStatus();
            }
        }
        else if (command == "Upgrade")
        {
            string name;
            cin >> name;
            string msg = "";
            if (heros.find(name) != heros.end())
            {
                if (!suits.empty())
                {
                    heros[name].getsuit() + suits.front();
                    suits.pop();
                    msg = name + " upgraded";
                }
                else
                {
                    msg = name + " upgrade Fail";
                }
            }
            else
            {
                if (!suits.empty())
                {
                    enemies[name].getsuit() + suits.front();
                    suits.pop();
                    msg = name + " upgraded";
                }
                else
                {
                    msg = name + " upgrade Fail";
                }
            }
            battlelog.push_back(msg);
        }
        else if (command == "PrintBattleLog")
        {
            printBattleLog();
        }
        else if (command == "BattleStatus")
        {
            int r = Result();
            if (r == 1)
                cout << "heroes are winning" << endl;
            else if (r == -1)
                cout << "enemies are winning" << endl;
            else
                cout << "tie" << endl;
        }
        else if (command == "End")
            break;
    }
}

// test main.......

int main()
{
    Battle b;
    b.startBattle();
}