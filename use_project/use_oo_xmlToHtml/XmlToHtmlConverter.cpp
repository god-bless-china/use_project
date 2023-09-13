#include <QDebug>
#include <QDomElement>
#include <iostream>
#include "XmlToHtmlConverter.h"
#include "Leaf.h"
#include "Composite.h"

CXmlToHtmlConverter::CXmlToHtmlConverter()
{

}

CXmlToHtmlConverter::~CXmlToHtmlConverter()
{
    if (_hFile.isOpen())
    {
        _hFile.close();
    }
}

bool CXmlToHtmlConverter::readXml(const QString &strFileName)
{
    _strFilename = strFileName;
    _hFile.setFileName(strFileName);
    bool bFlag = _hFile.open(QFile::ReadOnly);
    if (!bFlag)
    {
        printTips("Error: Cannot read file ");
        return false;
    }
    bFlag = _reader.setContent(&_hFile);
    if (!bFlag)
    {
        _hFile.close();
        printTips("Error: set Content failed ");
        return false;
    }
    return true;
}

void CXmlToHtmlConverter::analysisXml()
{
    QDomElement xmlElement = _reader.documentElement();
    QDomNode root = xmlElement.firstChild();
    // 遍历所有的节点，并生成对应的对象
    visitSubNode(root, QSharedPointer<CComposite>(), 1);
}

void CXmlToHtmlConverter::setHtmlSpanAuto() const
{
    QVector<QSharedPointer<CComponent> > vecComponet = _vecComponet;
    while (!vecComponet.isEmpty())
    {
        int nMaxDepth = getMaxDepthByTree(vecComponet);
        int nMaxWidth = 0;
        for (auto iterVec = vecComponet.begin(); iterVec != vecComponet.end();)
        {
            auto vec = *iterVec;
            // 无父节点或有标记的情况
            if (vec->getParents() == nullptr || vec->getTag())
            {
                // 无子节点
                if (!vec->isComposite())
                {
                    vec->setRowSpan(nMaxDepth);
                }
                else
                {
                    // 转换为CComposite
                    QSharedPointer<CComposite> nodePtr = iterVec->dynamicCast<CComposite>();
                    nMaxWidth = nodePtr->getChildrenListSize();
                    nodePtr->setColSpan(nMaxWidth);
                    // 剥离父子关系标记
                    nodePtr->clearChildParentsRelate();
                }
                // 从容器中删除
                iterVec = vecComponet.erase(iterVec);
            }
            else
            {
                ++iterVec;
            }
        }
    }
    return;
}

void CXmlToHtmlConverter::concatHtmlTabAuto()
{
    int nRowNum = 1;
    int nRow = 0;
    int nCol = 0;
    QVector<QSharedPointer<CComponent> > vecComponet = _vecComponet;
    while (!vecComponet.isEmpty())
    {
        for (auto iterVec = vecComponet.begin(); iterVec != vecComponet.end();)
        {
            auto vec = *iterVec;
            if (vec->getRowNum() == nRowNum)
            {
                QString strTmp = vec->getName();
                vec->getSpan(nRow, nCol);
                addTdLableRowColSpan(strTmp, nRow, nCol);
                _strTd += strTmp;
                // 从容器中删除
                iterVec = vecComponet.erase(iterVec);
            }
            else
            {
                ++iterVec;
            }
        }
        addTrLable(_strTd);
        _strHtml += _strTd;
        resetTrTdTab();
        nRowNum++;
    }
    concatHtmlHead(_strHtml);
    return;
}

bool CXmlToHtmlConverter::saveToHtml(const QString& strFilename)
{
    if (_strHtml.isEmpty())
    {
        std::cerr << "Error: save to html file content is empty!" << std::endl;
        return false;
    }
    if (_hFile.isOpen())
    {
        std::cout << "Tips: File is Open!" << std::endl;
        _hFile.close();
    }
    _hFile.setFileName(strFilename);
    if (_hFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&_hFile);
        stream << _strHtml << "\n";
    }
    _hFile.close();
    std::cout << "\nFile Convert Over!!!" << std::endl;
    return true;
}

void CXmlToHtmlConverter::printTips(const QString& tips) const
{
    std::cerr << tips.toLocal8Bit().toStdString() << qPrintable(_strFilename)
              << ": " << qPrintable(_hFile.errorString())
              << std::endl;
    return;
}

void CXmlToHtmlConverter::visitSubNode(const QDomNode& subNode, QSharedPointer<CComponent> parentPtr, int nRowNum)
{
    QDomNode root = subNode;
    while (!root.isNull())
    {
        // 是一个DOM元素
        if (root.isElement())
        {
            QSharedPointer<CComponent> subComponetPtr;
            QDomElement subEle = root.toElement();
            QString name = subEle.attribute("显示名");
            // 树节点
            if (root.firstChild().isElement())
            {
                subComponetPtr = QSharedPointer<CComponent>(new CComposite);
                // 迭代树节点
                visitSubNode(root.firstChild(), subComponetPtr, nRowNum + 1);
            }
            else
            {
                // 叶子节点
                subComponetPtr = QSharedPointer<CComponent>(new CLeaf);
            }
            // 过滤根节点
            if (!parentPtr.isNull())
            {
                parentPtr->add(subComponetPtr.get());
            }
            // 存储节点名称
            subComponetPtr->setName(name);
            subComponetPtr->setRowNum(nRowNum);
            _vecComponet.push_back(subComponetPtr);
        }
        // 迭代下一个兄弟节点
        root = root.nextSibling();
    }
    return;
}

int CXmlToHtmlConverter::getMaxDepthByTree(QVector<QSharedPointer<CComponent> > &vecComponent) const
{
    int nMaxDepth = 1;
    // 迭代 _vecComponet 获取最大深度，即获得单列rowspan的值
    for (auto& vec : vecComponent)
    {
        if (vec->isComposite())
        {
            // 迭代遍历children
            nMaxDepth = qMax(nMaxDepth, vec->getDepth());
        }
    }
    return nMaxDepth;
}

void CXmlToHtmlConverter::concatHtmlHead(QString &strHtml) const
{
    const QString strHtmlHead("<body><table border=\"1\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\" >");
    const QString strHtmlEnd("</table></body>");
    strHtml = strHtmlHead + strHtml + strHtmlEnd;
    return;
}

void CXmlToHtmlConverter::addTrLable(QString &strHtml) const
{
    const QString strHtmlTrHead("<tr>");
    const QString strHtmlTrEnd("</tr>");
    strHtml = strHtmlTrHead + strHtml + strHtmlTrEnd;
    return;
}

void CXmlToHtmlConverter::addTdLableRowColSpan(QString &strHtml, int nRowSpan, int nColSpan) const
{
    const QString strHtmlTdHead = QString("<td align=\"center\"rowspan=\"%1\"colspan=\"%2\">").arg(nRowSpan).arg(nColSpan);
    const QString strHtmlTdEnd("</td>");
    strHtml = strHtmlTdHead + strHtml + strHtmlTdEnd;
    return;
}

void CXmlToHtmlConverter::resetTrTdTab()
{
    _strTr = "";
    _strTd = "";
}

