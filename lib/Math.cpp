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

long long math::setBitCount(long long n) {
    int count = 0;

    while (n) {
        count += n & 1;
        n >>= 1;
    }

    return count;
}

long long math::setBitDiff(long long n1, long long n2) {
    return math::setBitCount(n1 ^ n2);
}
