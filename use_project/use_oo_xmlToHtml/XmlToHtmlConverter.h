//////////////////////////////////////////////////////////////////////
// 文件名称：XmlConverter.h
// 功能描述：xml转html转换器类
// 创建标识：fanjialong 2023-08-09
// 文件版权：江西博微新技术有限公司
//////////////////////////////////////////////////////////////////////
#ifndef CXMLConverter_H
#define CXMLConverter_H

#include <QString>
#include <QDomDocument>
#include <QDomNode>
#include <QFile>
#include <QVector>
#include "Component.h"
#include "Composite.h"

//! xml转html转换器类实现
class CXmlToHtmlConverter
{
public:
    CXmlToHtmlConverter();
    ~CXmlToHtmlConverter();
    /**
     * @brief 读取xml文件
     * @param strFileName: 读入的xml文件路径
     * @return : true: 读取成功, false:读取失败
     */
    bool readXml(const QString& strFileName);
    /**
     * @brief 解析xml文件
     */
    void analysisXml();
    /**
     * @brief 自动设置html节点的行列宽(可设置多行)
     */
    void setHtmlSpanAuto() const;
    /**
     * @brief 自动拼接html的标记 (可拼接多行)
     */
    void concatHtmlTabAuto();
    /**
     * @brief 保存为html文件
     * @param _strFilename: 到处的html文件路径
     * @return true: 保存成功, false: 保存失败
     */
    bool saveToHtml(const QString& _strFilename);
private:
    /**
     * @brief 打印报错提示
     * @param tips: 提示
     */
    void printTips(const QString& tips) const;
    /**
     * @brief 迭代访问节点树
     * @param subNode: DOM对象根节点
     * @param parentPtr: 节点对象，后续需要设置对应的子节点
     * @param nRowNum: 当前层数
     */
    void visitSubNode(const QDomNode& subNode, QSharedPointer<CComponent> parentPtr, int nRowNum);
    /**
     * @brief 根据节点树获取html节点树的最大深度
     * @return : 最大深度
     */
    int getMaxDepthByTree(QVector<QSharedPointer<CComponent> >& vecComponent) const;
    /**
     * @brief 拼接html头
     * @param strHtml : 需要拼接html头的字符串元素
     */
    void concatHtmlHead(QString& strHtml) const;
    /**
     * @brief 添加html tr标记，并返回拼接好的元素
     * @param strHtml : 需要加tr标记的元素
     */
    void addTrLable(QString& strHtml) const;
    /**
     * @brief 将html节点的行列宽，用td标记拼接
     * @param strHtml : 需要添加span标记的元素，并返回拼接好的元素
     * @param nRowSpan : 拼接行span对应的值
     * @param nColSpan : 拼接列span对应的值
     */
    void addTdLableRowColSpan(QString& strHtml, int nRowSpan, int nColSpan) const;
    /**
     * @brief 重置tr td标记
     */
    void resetTrTdTab();
private:
    QDomDocument _reader; // 读取xml文件的Dom对象
    QFile _hFile;   // 读取到的xml文件句柄
    QString _strFilename; // 读取到的文件名称
    QString _strHtml; // 转换后的html内容
    QVector<QSharedPointer<CComponent> > _vecComponet; // 存储所有的xml节点
    QString _strTr; // 拼接html tr标签字符
    QString _strTd; // 拼接html td标签字符
};

#endif // CXMLConverter_H
