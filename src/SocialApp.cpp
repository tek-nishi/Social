//
// Social framework テスト(iOS)
//

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Capture.h"
#include "Social.h"
#include "Share.h"


#if defined(_MSC_VER)

// FIXME:double -> floatの暗黙の変換で出る警告
#pragma warning (disable:4244)
#pragma warning (disable:4305)

#endif


using namespace ci;
using namespace ci::app;


class SocialApp : public AppNative {
  bool pause;

  float bg_rotate;
  
  gl::Texture twitter;
  gl::Texture facebook;
  gl::Texture share;
  gl::Texture bg;

  
  void prepareSettings(Settings* settings) override {
    settings->enableMultiTouch();
  }
  
	void setup() override {
    pause = false;

    bg_rotate = 0.0f;

#if defined(CINDER_COCOA_TOUCH)
    // 縦横画面両対応
    getSignalSupportedOrientations().connect([](){ return InterfaceOrientation::All; });
#endif

    twitter  = loadImage(loadAsset("twitter.png"));
    facebook = loadImage(loadAsset("facebook.png"));
    share    = loadImage(loadAsset("share.png"));
    bg       = loadImage(loadAsset("img_miku.png"));

    gl::enableAlphaBlending();
  }

  
  void touchesBegan(TouchEvent event) override {
    auto window_size = getWindowSize();

    for (const auto& touch : event.getTouches()) {
      const auto& touch_pos = touch.getPos();
      
      {
        Vec2i size = twitter.getSize();
        Vec2f pos = window_size / 2 - size / 2 + Vec2i(-150, 0);

        Rectf rect(pos, pos + size);
        if (rect.contains(touch_pos)) {
          console() << "Twitter" << std::endl;

          post(ngs::Social::TWITTER);
          break;
        }
      }
      
      {
        Vec2i size = facebook.getSize();
        Vec2f pos = window_size / 2 - size / 2 + Vec2i(0, 0);

        Rectf rect(pos, pos + size);
        if (rect.contains(touch_pos)) {
          console() << "Facebook" << std::endl;

          post(ngs::Social::FACEBOOK);
          break;
        }
      }
      
      {
        Vec2i size = share.getSize();
        Vec2f pos = window_size / 2 - size / 2 + Vec2i(150, 0);

        Rectf rect(pos, pos + size);
        if (rect.contains(touch_pos)) {
          console() << "Share" << std::endl;

          post();
          break;
        }
      }
    }
  }

  
	void update() override {
    if (pause) return;

    bg_rotate += 1.0f;
  }

  
	void draw() override {
    gl::clear(Color(0.5, 0.5, 0.5));

    auto window_size = getWindowSize();
    
    {
      gl::pushModelView();
      
      Vec2i size = bg.getSize();
      gl::translate(window_size / 2);
      gl::rotate(Vec3f(0.0f, 0.0f, bg_rotate));
      gl::translate(-size / 2);

      gl::draw(bg);
      
      gl::popModelView();
    }

    {
      gl::pushModelView();

      Vec2i size = twitter.getSize();
      Vec2f pos  = window_size / 2 - size / 2 + Vec2i(-150, 0);

      gl::translate(pos);
      gl::draw(twitter);
      
      gl::popModelView();
    }
    
    {
      gl::pushModelView();
      
      Vec2i size = facebook.getSize();
      Vec2f pos  = window_size / 2 - size / 2 + Vec2i(0, 0);
    
      gl::translate(pos);
      gl::draw(facebook);
      
      gl::popModelView();
    }
    
    {
      gl::pushModelView();
      
      Vec2i size = share.getSize();
      Vec2f pos  = window_size / 2 - size / 2 + Vec2i(150, 0);
    
      gl::translate(pos);
      gl::draw(share);
      
      gl::popModelView();
    }
  }


#if defined(CINDER_COCOA_TOUCH)

  void post(const ngs::Social::Type type) {
    if (ngs::Social::canPost(type)) {
      pause = true;
            
      std::string text("ほげ");
      UIImage* image = ngs::captureTopView();

      ngs::Social::post(type,
                        text,
                        image,
                        [this]() {
                          pause = false;
                        });
    }
  }

  void post() {
      pause = true;

      std::string text("ほげ");
      UIImage* image = ngs::captureTopView();

      ngs::Share::post(text, image, [this]() { pause = false; });
  }

#else

  void post(const ngs::Social::Type) {}
  void post() {}
  
#endif
  
};

CINDER_APP_NATIVE(SocialApp, RendererGl)
