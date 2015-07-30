//
// SNS投稿(iOS以外のダミー)
//

#include "Social.h"
#include <string>
#include <cassert>
#include <functional>


namespace ngs {
namespace Social {

bool canPost(const Type) { return false; }

void post(const Type, const std::string&, std::function<void()> complete_callback) {
  complete_callback();
}

}
}
