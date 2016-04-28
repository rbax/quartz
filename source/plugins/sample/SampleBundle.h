#pragma once

#include <QString>

#include <quartz_core/PluginBundle.h>


namespace Vam {

class SampleBundle : public Quartz::PluginBundle
{
public:
    SampleBundle();

    static const QString BUNDLE_ID;

    static const QString BUNDLE_NAME;

private:

};

}
