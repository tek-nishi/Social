﻿//
// SNS投稿(iOS専用)
//


namespace ngs {
namespace Share {

void post(const std::string& text, UIImage* image,
          std::function<void()> complete_callback) {

  NSString* str = [[[NSString alloc] initWithCString:text.c_str() encoding:NSUTF8StringEncoding]
                      autorelease];

  // FIXME:もっと賢いNSArrayの構築方法があると思う...
  NSArray* activity_items = image ? @[str, image]
                                  : @[str];
  
  UIActivityViewController* view_controller = [[[UIActivityViewController alloc] initWithActivityItems:activity_items
                                                                                 applicationActivities:@[]]
                                                  autorelease];

  void (^completion) (NSString *activityType, BOOL completed) = ^(NSString *activityType, BOOL completed) {
    complete_callback();
  };
  view_controller.completionHandler = completion;
  
  UIViewController* app_vc = ci::app::getWindow()->getNativeViewController();

  if ([view_controller respondsToSelector:@selector(popoverPresentationController)]) {
    // iOS8
    view_controller.popoverPresentationController.sourceView = app_vc.view;
  }
  
  [app_vc presentViewController:view_controller animated:YES completion:nil];
}

}
}
