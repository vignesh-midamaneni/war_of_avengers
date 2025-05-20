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
