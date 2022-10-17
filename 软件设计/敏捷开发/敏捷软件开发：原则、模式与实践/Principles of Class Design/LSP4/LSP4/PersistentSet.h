#pragma once
#include "Set.h"

template <typename T>
class PersistentSet : public Set<T>
{
public:
    void Add(const T& t) override;
};

template <typename T>
void PersistentSet<T>::Add(const T& t)
{
    ParsistentObject& p = dynamic_cast<ParsistentObject&>(t);
    itsThirdPartyPersistentSet.Add(p);
}
