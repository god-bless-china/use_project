#include <QCoreApplication>
#include <XmlToHtmlConverter.h>

/**
 * 这里采用实现动态转换的思想(核心点)：
 * 1. 首先需要动态获取当前html最大行数。(这里即可以拿到最大行宽，列宽根据节点下所挂在的元素可以确定。)
 * 2. 通过DFS算法在遍历xml节点的时候，根据遍历的层数向数据对象中注入html行信息。
 * 3. 通过DFS获取到所有节点后，对节点进行拆解，即(有无)父节点无子节点即注入最大行宽，节点下挂即注入列宽。
 * 4. 将确定好行宽和列宽的节点元素剥离，重复步骤3操作，即可确定所有的节点元素的(行/列)宽。
 * 5. 通过步骤2中注入的html行信息，一行一行对元素进行<tr>标记，通过步骤4注入的行列宽进行<td>标记。
 * 6. 最后拼接html头即可。
 */

// ! 函数入口
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CXmlToHtmlConverter converter;
    converter.readXml("安装主材价差汇总表.xml");
    converter.analysisXml();
    converter.setHtmlSpanAuto();
    converter.concatHtmlTabAuto();
    converter.saveToHtml("表头.html");
    return a.exec();
}
