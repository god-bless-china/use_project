#include "Leaf.h"

CLeaf::CLeaf()
{

}

int CLeaf::getDepth() const
{
    // 叶子节点默认为一层
    return 1;
}
