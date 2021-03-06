#pragma once

#include <memory>

#include "../VQ.h"

namespace Vam {

class PluginBundle;
class SharedLibrary;

class VQ_CORE_EXPORT BundleLibrary
{
public:
    BundleLibrary();

    BundleLibrary( std::unique_ptr< SharedLibrary > library,
                   std::unique_ptr< PluginBundle > bundle );

    SharedLibrary * library() const;

    PluginBundle * bundle() const;

    bool isValid() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;


};


}
