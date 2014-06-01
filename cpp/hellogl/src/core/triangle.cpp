#include "triangle.h"

using namespace std;

ostream & operator<< (ostream & output, const Triangle & t) {
    output << t.getVertex (0) << " " << t.getVertex (1) << " " << t.getVertex (2);
    return output;
}
