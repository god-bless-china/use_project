//////////////////////////////////////////////////////////////////////
// 文件名称：ComponentBase.h
// 功能描述：组合模式基类
// 创建标识：fanjialong 2023-08-09
// 文件版权：江西博微新技术有限公司
//////////////////////////////////////////////////////////////////////
#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include <QSharedPointer>

//! 组合模式基类实现
class CComponent : public QEnableSharedFromThis<CComponent>
{
public:
    CComponent();
    virtual ~CComponent();
    /**
     * @brief 设置节点的父节点
     * @param pParent:当前节点的父节点
     */
    void setParents(CComponent* pParent);
    /**
     * @brief 获取节点的父节点
     * @return
     */
    CComponent* getParents() const;
    /**
     * @brief 为节点添加子节点
     * @param pComponet:要添加的子节点
     */
    virtual void add(CComponent* pComponet);
    /**
     * @brief 判断是否为节点
     * @return
     */
    virtual bool isComposite() const;
    /**
     * @brief 设置节点名称
     * @param strName: 节点的名称
     */
    virtual void setName(const QString& strName);
    /**
     * @brief 获取节点名称
     * @return
     */
    virtual QString getName() const;
    /**
     * @brief 获取节点树高度
     * @return
     */
    virtual int getDepth() const = 0;
    /**
     * @brief 获取xml节点在html节点时的行列宽
     * @param nRow: 获取当前节点在Html对应的行span
     * @param nCol: 获取当前节点在Html对应的列span
     */
    virtual void getSpan(int& nRow, int& nCol) const;
    /**
     * @brief 设置xml节点在html节点的行宽
     * @param nNewRowSpan: 设置当前节点的行span
     */
    void setRowSpan(int nNewRowSpan);
    /**
     * @brief 设置xml节点在html节点的列宽
     * @param nNewColSpan: 设置当前节点的列span
     */
    void setColSpan(int nNewColSpan);
    /**
     * @brief 用来一些特殊操作的标记
     * @param bTag: 打标记
     */
    void setTag(bool bTag);
    /**
     * @brief 获取标记
     * @return 获取当前节点的标记
     */
    bool getTag() const;
    /**
     * @brief 设置行号
     * @param nRowNum : 设置当前节点在Html中所在行(1~n)
     */
    void setRowNum(int nRowNum);
    /**
     * @brief 获取当前节点在Html所在的行号
     * @return 返回当前元素在Html所在的行
     */
    int getRowNum() const;
protected:
    QSharedPointer<CComponent> _parentPtr = nullptr; // 使用智能指针存储节点对象
    QString _strName; // 存储节点名称
    int _nRowSpan = 1; // html: 默认的行宽
    int _nColSpan = 1; // html: 默认的列宽
    bool _bTag = false; // 用来标记一些操作
    int _nRowNum = 1; // 用来标记节点属于第几行，后续根据标记行数拼接hmtl
};

#endif // ICOMPONENT_H
