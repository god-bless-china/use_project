#include "Composite.h"

CComposite::CComposite()
{

}

void CComposite::add(CComponent *pComponet)
{
    _childrenList.push_back(QSharedPointer<CComponent>(pComponet));
    pComponet->setParents(sharedFromThis().data());
}

bool CComposite::isComposite() const
{
    return true;
}

int CComposite::getDepth() const
{
    int nDepth = 1;
    if (!_childrenList.isEmpty())
    {
        for (auto& child : _childrenList)
        {
            nDepth = qMax(child->getDepth() + 1, nDepth);
        }
    }
    return nDepth;
}

int CComposite::getChildrenListSize() const
{
    return _childrenList.size();
}

void CComposite::clearChildParentsRelate()
{
    for (auto& child : _childrenList)
    {
        child->setTag(true);
    }
    return;
}
