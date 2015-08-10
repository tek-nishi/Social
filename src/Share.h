#pragma once

//
// UIActivityViewControllerの薄いラッパー(iOS)
//

#include <string>
#include <functional>

namespace ngs {
namespace Share {

#if defined(CINDER_COCOA_TOUCH)

void post(const std::string& text, UIImage* image, std::function<void()> complete_callback);

#endif

}
}
