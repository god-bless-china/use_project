//////////////////////////////////////////////////////////////////////
// 文件名称：Composite.h
// 功能描述：组合模式节点类
// 创建标识：fanjialong 2023-08-09
// 文件版权：江西博微新技术有限公司
//////////////////////////////////////////////////////////////////////
#ifndef CCOMPOSITE_H
#define CCOMPOSITE_H
#include "Component.h"
#include <QList>

//! 组合设计模式的节点实现
class CComposite : public CComponent
{
public:
    CComposite();
    /**
     * @brief 为节点添加叶子节点
     * @param pComponet: 添加的子节点
     */
    void add(CComponent* pComponet) override;
    /**
     * @brief 判断是否是节点
     * @return true: 节点，false: 叶节点
     */
    bool isComposite() const override;
    /**
     * @brief 获取节点的高度
     * @return : 当前节点所在xml树的高度
     */
    int getDepth() const override;
    /**
     * @brief 获取当前节点的直系字节点的个数
     * @return : 当前节点下挂的子节点数(包括节点和叶节点)
     */
    int getChildrenListSize() const;
    /**
     * @brief 利用标记清除父子关系
     */
    void clearChildParentsRelate();
protected:
    QList<QSharedPointer<CComponent> > _childrenList; // 存储节点的子节点
};

#endif // CCOMPOSITE_H
