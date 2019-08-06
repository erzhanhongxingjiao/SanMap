#include "SM_Thread.h"
#include "SM_LoaderTile.h"
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
SM_Thread::SM_Thread()
    :m_pLoader(NULL),
     m_nNumReq(0),
     m_bCancel(false)
{

}
void SM_Thread::run()
{
    while(!m_bCancel)
    {
        if(m_nNumReq && m_pLoader)
        {
            m_pLoader->RealRender();
            m_nNumReq -= 1;
        }
    }



}

