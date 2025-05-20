#include"Avengers_class.hpp";

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
