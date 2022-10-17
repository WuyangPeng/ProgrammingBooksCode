#include "Shape.h"
#include <algorithm>
#include <vector>

using std::vector;

template <typename P>
class Lessp  // utility for sorting containers of pointers
{
public:
    bool operator()(const P p, const P q)
    {
        return (*p) < (*q);
    }
};

void DrawAllShapes(vector<Shape*>& list)
{
    vector<Shape*> orderedList = list;
    sort(orderedList.begin(), orderedList.end(), Lessp<Shape*>());

    vector<Shape*>::iterator i;
    for (i = list.begin(); i != list.end(); i++)
    {
        (*i)->Draw();
    }
}