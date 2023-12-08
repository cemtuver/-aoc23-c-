#include "Math.hpp"

long long math::gcd(long long n1, long long n2) {
    if(n2 == 0) {
        return n1;
    }

    return gcd(n2, n1 % n2);
}

long long math::lcm(long long n1, long long n2) {
    if (n1 > n2) {
        return (n1 / gcd(n1, n2)) * n2;
    } else {
        return (n2 / gcd(n1, n2)) * n1;
    }
} 