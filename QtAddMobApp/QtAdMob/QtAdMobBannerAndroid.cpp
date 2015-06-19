#include "QtAdMobBannerAndroid.h"

#if (__ANDROID_API__ >= 9)

#include <QAndroidJniObject>
#include <QPA/QPlatformNativeInterface.h>
#include <QApplication>

QtAdMobBannerAndroid::QtAdMobBannerAndroid()
    : m_Activity(0)
{
    QPlatformNativeInterface* interface = QApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }
}

QtAdMobBannerAndroid::~QtAdMobBannerAndroid()
{
    HideAd();
    if (m_Activity)
    {
        delete m_Activity;
    }
}

void QtAdMobBannerAndroid::Initialize()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("InitializeAdBanner");
}

void QtAdMobBannerAndroid::Shutdown()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShutdownAdBanner");
}

void QtAdMobBannerAndroid::SetAdUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
    m_Activity->callMethod<void>("SetAdBannerUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());
}

void QtAdMobBannerAndroid::SetAdSize(IQtAdMobBanner::BannerSize size)
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdBannerSize", "(I)V", (int)size);
}

void QtAdMobBannerAndroid::SetPosition(const QPoint& position)
{    
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdBannerPosition", "(II)V", position.x(), position.y());
}

QSize QtAdMobBannerAndroid::GetDimensions()
{
    int width = m_Activity->callMethod<int>("GetAdBannerWidth");
    int height = m_Activity->callMethod<int>("GetAdBannerHeight");

    return QSize(width, height);
}

bool QtAdMobBannerAndroid::IsShow() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isShow = m_Activity->callMethod<jboolean>("IsAdBannerShowed", "()Z");
    return isShow;
}

bool QtAdMobBannerAndroid::IsLoaded() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isLoaded = m_Activity->callMethod<jboolean>("IsAdBannerLoaded", "()Z");
    return isLoaded;
}

void QtAdMobBannerAndroid::ShowAd()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShowAdBanner");
}

void QtAdMobBannerAndroid::HideAd()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("HideAdBanner");
}

void QtAdMobBannerAndroid::AddTestDevice(const QString& hashedDeviceId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(hashedDeviceId);
    m_Activity->callMethod<void>("AddAdTestDevice", "(Ljava/lang/String;)V", param1.object<jstring>());
}

bool QtAdMobBannerAndroid::IsValid() const
{
    return (m_Activity != 0 && m_Activity->isValid());
}

#endif // __ANDROID_API__
