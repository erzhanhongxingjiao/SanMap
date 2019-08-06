//**************************************************************************
// 文件：  SM_DemoBase.h
// 描述：  所有Demo的基础，用于初始化QGIS环境
// 作者：  w_s_y
// 最近更新时间：  2019-8-1
// 更新内容：编写第一个版本
//**************************************************************************
#ifndef SM_DEMOBASE_H
#define SM_DEMOBASE_H


class SM_DemoBase
{
public:

    ~SM_DemoBase();
    static SM_DemoBase* Instance();


private:
    SM_DemoBase();

    /**
     * @brief 初始化QGIS环境
     */
    void Init();

private:

};

#endif // SM_DEMOBASE_H
