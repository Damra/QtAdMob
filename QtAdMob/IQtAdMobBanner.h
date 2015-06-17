#ifndef IQTADMOBBANNER_H
#define IQTADMOBBANNER_H

#include <QString>
#include <QSize>
#include <QPoint>

#define UNUSED(x) (void)(x)

class IQtAdMobBanner
{
public:
    enum BannerSize
    {
        Banner = 0,
        FullBanner,
        LargeBanner,
        MediumRectangle,
        SmartBanner,
        WideSkyscraper
    };

public:
    IQtAdMobBanner() {}
    virtual ~IQtAdMobBanner() {}

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual void SetAdUnitId(const QString& unitId) = 0;
    virtual void SetAdSize(BannerSize size) = 0;
    virtual void SetPosition(const QPoint& position) = 0;
    virtual QSize GetDimensions() = 0;
    virtual bool IsShowed() const = 0;
    virtual bool IsLoaded() const = 0;
    virtual void ShowAd() = 0;
    virtual void HideAd() = 0;

    virtual void AddTestDevice(const QString& hashedDeviceId) = 0;
};

#endif // IQTADMOBBANNER_H

