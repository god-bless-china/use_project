//////////////////////////////////////////////////////////////////////
// 文件名称：Leaf.h
// 功能描述：组合模式叶子节点类
// 创建标识：fanjialong 2023-08-09
// 文件版权：江西博微新技术有限公司
//////////////////////////////////////////////////////////////////////
#ifndef CLEAF_H
#define CLEAF_H
#include "Component.h"

//! 组合设计模式的叶子节点的实现
class CLeaf : public CComponent
{
public:
    CLeaf();
    /**
     * @brief 获取当前节点的高度
     * @return : 当前叶子节点在html中的高度
     */
    int getDepth() const override;
};

#endif // CLEAF_H
