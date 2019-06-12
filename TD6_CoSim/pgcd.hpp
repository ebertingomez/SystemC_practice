#ifndef PGCD_HPP
#define PGCD_HPP

int compute_pgdc(unsigned int a,unsigned int b){
    if (a == 0 || b == 0)
        return 0;
    int bigger = (a>b) ? a : b;
    int smaller = (a<b) ? a : b;
    int diff;
    do {
        diff = bigger - smaller;
        bigger = (diff>smaller) ? diff : smaller;
        smaller = (diff<smaller) ? diff : smaller;
    }
    while (diff >0);
    return bigger;
}
#endif