#include "Component.h"

CComponent::CComponent()
{

}

CComponent::~CComponent()
{

}

void CComponent::setParents(CComponent *pParent)
{
    _parentPtr.reset(pParent);
}

CComponent *CComponent::getParents() const
{
    return _parentPtr.get();
}

void CComponent::add(CComponent *pComponet)
{
    Q_UNUSED(pComponet);
}

bool CComponent::isComposite() const
{
    return false;
}

void CComponent::setName(const QString &strName)
{
    _strName = strName;
}

QString CComponent::getName() const
{
    return _strName;
}

void CComponent::getSpan(int& nRow, int& nCol) const
{
    nRow = _nRowSpan;
    nCol = _nColSpan;
    return;
}

void CComponent::setRowSpan(int nNewRowSpan)
{
    _nRowSpan = nNewRowSpan;
}

void CComponent::setColSpan(int nNewColSpan)
{
    _nColSpan = nNewColSpan;
}

void CComponent::setTag(bool bTag)
{
    _bTag = bTag;
}

bool CComponent::getTag() const
{
    return _bTag;
}

void CComponent::setRowNum(int nRowNum)
{
    _nRowNum = nRowNum;
    return;
}

int CComponent::getRowNum() const
{
    return _nRowNum;
}
