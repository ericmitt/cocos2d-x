#include "LabelTestNew.h"
#include "../testResource.h"
#include "renderer/CCRenderer.h"

using namespace ui;

enum {
    kTagTileMap = 1,
    kTagSpriteManager = 1,
    kTagAnimation1 = 1,
    kTagBitmapAtlas1 = 1,
    kTagBitmapAtlas2 = 2,
    kTagBitmapAtlas3 = 3,
};

enum {
    kTagSprite1,
    kTagSprite2,
    kTagSprite3,
    kTagSprite4,
    kTagSprite5,
    kTagSprite6,
    kTagSprite7,
    kTagSprite8,
};

//------------------------------------------------------------------
//
// AtlasDemoNew
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

Layer* nextAtlasActionNew();
Layer* backAtlasActionNew();
Layer* restartAtlasActionNew();

static int sceneIdx = -1; 

static std::function<Layer*()> createFunctions[] =
{
    CL(LabelFNTColorAndOpacity),
    CL(LabelFNTSpriteActions),
    CL(LabelFNTPadding),
    CL(LabelFNTOffset),
    CL(LabelFNTColor),
    CL(LabelFNTHundredLabels),
    CL(LabelFNTMultiLine),
    CL(LabelFNTandTTFEmpty),
    CL(LabelFNTRetina),
    CL(LabelFNTGlyphDesigner),
    CL(LabelTTFUnicodeChinese),
    CL(LabelFNTUnicodeChinese),
    CL(LabelFNTMultiLineAlignment),
    CL(LabelFNTUNICODELanguages),
    CL(LabelTTFAlignmentNew),
    CL(LabelFNTBounds),
    CL(LabelTTFLongLineWrapping),
    CL(LabelTTFLargeText),
    CL(LabelTTFColor),
    CL(LabelTTFFontsTestNew),
    CL(LabelTTFDynamicAlignment),
    CL(LabelTTFCJKWrappingTest),
    CL(LabelTTFUnicodeNew),
    CL(LabelBMFontTestNew),
    CL(LabelTTFDistanceField),
    CL(LabelOutlineAndGlowTest),
    CL(LabelShadowTest),
    CL(LabelCharMapTest),
    CL(LabelCharMapColorTest),
    CL(LabelCrashTest),
    CL(LabelTTFOldNew),
    CL(LabelFontNameTest),
    CL(LabelAlignmentTest),
    CL(LabelIssue4428Test)
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextAtlasActionNew()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backAtlasActionNew()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartAtlasActionNew()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

void AtlasTestSceneNew::runThisTest()
{
    sceneIdx = -1;
    auto layer = nextAtlasActionNew();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

AtlasDemoNew::AtlasDemoNew(void)
{
}

AtlasDemoNew::~AtlasDemoNew(void)
{
}

std::string AtlasDemoNew::title() const
{
    return "No title";
}

std::string AtlasDemoNew::subtitle() const
{
    return "";
}

void AtlasDemoNew::onEnter()
{
    BaseTest::onEnter();
}

void AtlasDemoNew::restartCallback(Ref* sender)
{
    auto s = new AtlasTestSceneNew();
    s->addChild(restartAtlasActionNew()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemoNew::nextCallback(Ref* sender)
{
    auto s = new AtlasTestSceneNew();
    s->addChild( nextAtlasActionNew() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemoNew::backCallback(Ref* sender)
{
    auto s = new AtlasTestSceneNew();
    s->addChild( backAtlasActionNew() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

LabelTTFAlignmentNew::LabelTTFAlignmentNew()
{
    auto s = Director::getInstance()->getWinSize();

    TTFConfig config("fonts/tahoma.ttf",16);

    auto ttf0 = Label::createWithTTF(config,"Alignment 0\nnew line",TextHAlignment::LEFT);
    ttf0->setPosition(Point(s.width/2,(s.height/6)*2 - 30));
    ttf0->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(ttf0);

    auto ttf1 = Label::createWithTTF(config,"Alignment 1\nnew line",TextHAlignment::CENTER);
    ttf1->setPosition(Point(s.width/2,(s.height/6)*3 - 30));
    ttf1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(ttf1);

    auto ttf2 = Label::createWithTTF(config,"Alignment 2\nnew line",TextHAlignment::RIGHT);
    ttf2->setPosition(Point(s.width/2,(s.height/6)*4 - 30));
    ttf2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(ttf2);
}

std::string LabelTTFAlignmentNew::title() const
{
    return "New Label + TTF";
}

std::string LabelTTFAlignmentNew::subtitle() const
{
    return "Tests alignment values";
}

LabelFNTColorAndOpacity::LabelFNTColorAndOpacity()
{
    _time = 0;

    auto col = LayerColor::create( Color4B(128,128,128,255) );
    addChild(col, -10);
    
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Test");
    
    label1->setAnchorPoint( Point(0,0) );
    addChild(label1, 0, kTagBitmapAtlas1);
    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto seq = Sequence::create(fade, fade_in, NULL);
    auto repeat = RepeatForever::create(seq);
    label1->runAction(repeat);
    
    auto label2 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Test");
    label2->setAnchorPoint( Point::ANCHOR_MIDDLE );
    label2->setColor( Color3B::RED );
    addChild(label2, 0, kTagBitmapAtlas2);
    auto tint = Sequence::create(TintTo::create(1, 255, 0, 0),
        TintTo::create(1, 0, 255, 0),
        TintTo::create(1, 0, 0, 255),
        NULL);
    label2->runAction( RepeatForever::create(tint) );
    
    auto label3 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Test");
    label3->setAnchorPoint( Point(1,1) );
    addChild(label3, 0, kTagBitmapAtlas3);
    
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );
    
    schedule( schedule_selector(LabelFNTColorAndOpacity::step) );//:@selector(step:)];
}

void LabelFNTColorAndOpacity::step(float dt)
{
    _time += dt;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", _time);
    
    auto label1 = (Label*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    auto label2 = (Label*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    auto label3 = (Label*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);
}

std::string LabelFNTColorAndOpacity::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTColorAndOpacity::subtitle() const
{
    return "Testing opacity + tint";
}

LabelFNTSpriteActions::LabelFNTSpriteActions()
{
    _time = 0;

    // Upper Label
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Bitmap Font Atlas");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE );
    
    
    auto BChar = (Sprite*) label->getLetter(0);
    auto FChar = (Sprite*) label->getLetter(7);
    auto AChar = (Sprite*) label->getLetter(12);
    
    
    auto rotate = RotateBy::create(2, 360);
    auto rot_4ever = RepeatForever::create(rotate);
    
    auto scale = ScaleBy::create(2, 1.5f);
    auto scale_back = scale->reverse();
    auto scale_seq = Sequence::create(scale, scale_back,NULL);
    auto scale_4ever = RepeatForever::create(scale_seq);
    
    auto jump = JumpBy::create(0.5f, Point::ZERO, 60, 1);
    auto jump_4ever = RepeatForever::create(jump);
    
    auto fade_out = FadeOut::create(1);
    auto fade_in = FadeIn::create(1);
    auto seq = Sequence::create(fade_out, fade_in, NULL);
    auto fade_4ever = RepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    auto label2 = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "00.0");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( Point(s.width/2.0f, 80) );
    label2->setAnchorPoint( Point::ANCHOR_MIDDLE );
    
    auto lastChar = (Sprite*) label2->getLetter(3);
    lastChar->runAction( rot_4ever->clone() );
    
    schedule( schedule_selector(LabelFNTSpriteActions::step), 0.1f);
}

void LabelFNTSpriteActions::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _renderCmd.init(_globalZOrder);
    _renderCmd.func = CC_CALLBACK_0(LabelFNTSpriteActions::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_renderCmd);

}

void LabelFNTSpriteActions::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
    auto s = Director::getInstance()->getWinSize();
    DrawPrimitives::drawLine( Point(0, s.height/2), Point(s.width, s.height/2) );
    DrawPrimitives::drawLine( Point(s.width/2, 0), Point(s.width/2, s.height) );
    
    kmGLPopMatrix();
}

void LabelFNTSpriteActions::step(float dt)
{
    _time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", _time);
    auto label1 = (Label*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string LabelFNTSpriteActions::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTSpriteActions::subtitle() const
{
    return "Using fonts as Sprite objects. Some characters should rotate.";
}

LabelFNTPadding::LabelFNTPadding()
{
    auto label = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "abcdefg");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE );
}

std::string LabelFNTPadding::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTPadding::subtitle() const
{
    return "Testing padding";
}

LabelFNTOffset::LabelFNTOffset()
{
    auto s = Director::getInstance()->getWinSize();

    Label* label = NULL;
    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "FaFeFiFoFu");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2+50) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE ) ;
    
    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "fafefifofu");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE );

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "aeiou");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2-50) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE ); 
}

std::string LabelFNTOffset::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTOffset::subtitle() const
{
    return "Rendering should be OK. Testing offset";
}

LabelFNTColor::LabelFNTColor()
{
    auto s = Director::getInstance()->getWinSize();
    
    Label* label = NULL;
    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Blue");
    label->setColor( Color3B::BLUE );
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/4) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE );

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Red");
    addChild(label);
    label->setPosition( Point(s.width/2, 2*s.height/4) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE );
    label->setColor( Color3B::RED );

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Green");
    addChild(label);
    label->setPosition( Point(s.width/2, 3*s.height/4) );
    label->setAnchorPoint( Point::ANCHOR_MIDDLE );
    label->setColor( Color3B::GREEN );
    label->setString("Green");
}

std::string LabelFNTColor::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTColor::subtitle() const
{
    return "Testing color";
}

LabelFNTHundredLabels::LabelFNTHundredLabels()
{
    // Upper Label
    for ( int i=0 ; i < 100;i ++ ) 
    {
        char str[6] = {0};
        sprintf(str, "-%d-", i);
        auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", str);
        addChild(label);
        
        auto s = Director::getInstance()->getWinSize();

        auto p = Point( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
        label->setPosition( p );
        label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    }
}

std::string LabelFNTHundredLabels::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTHundredLabels::subtitle() const
{
    return "Creating several Labels using the same FNT file; should be fast";
}

LabelFNTMultiLine::LabelFNTMultiLine()
{
    Size s;

    // Left
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", " Multi line\nLeft");
    label1->setAnchorPoint(Point(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    auto label2 = Label::createWithBMFont( "fonts/bitmapFontTest3.fnt", "Multi line\nCenter");
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    auto label3 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Multi line\nRight\nThree lines Three");
    label3->setAnchorPoint(Point(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string LabelFNTMultiLine::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTMultiLine::subtitle() const
{
    return "Multiline + anchor point";
}

LabelFNTandTTFEmpty::LabelFNTandTTFEmpty()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "", TextHAlignment::CENTER, s.width);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label1->setPosition(Point(s.width/2, s.height - 100));

    // LabelTTF
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    auto label2 = Label::createWithTTF(ttfConfig,"", TextHAlignment::CENTER,s.width);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label2->setPosition(Point(s.width/2, s.height / 2));

    auto label3 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(Point(s.width/2, 100));

    schedule(schedule_selector(LabelFNTandTTFEmpty::updateStrings), 1.0f);

    setEmpty = false;
}

void LabelFNTandTTFEmpty::updateStrings(float dt)
{
    auto label1 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas1) );
    auto label2 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas2) );
    auto label3 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas3) );

    if( ! setEmpty )
    {
        label1->setString("not empty");
        label2->setString("not empty");
        label3->setString("hi");
    
        setEmpty = true;
    }
    else
    {
        label1->setString("");
        label2->setString("");
        label3->setString("");
    
        setEmpty = false;
    }
}

std::string LabelFNTandTTFEmpty::title() const
{
    return "New Label : .FNT file & .TTF file";
}

std::string LabelFNTandTTFEmpty::subtitle() const
{
    return "3 empty labels: new Label + FNT/TTF/CharMap";
}

LabelFNTRetina::LabelFNTRetina()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/konqa32.fnt", "TESTING RETINA DISPLAY");
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelFNTRetina::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTRetina::subtitle() const
{
    return "loading arista16 or arista16-hd";
}

LabelFNTGlyphDesigner::LabelFNTGlyphDesigner()
{
    auto s = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/futura-48.fnt", "Testing Glyph Designer");
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelFNTGlyphDesigner::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTGlyphDesigner::subtitle() const
{
    return "Testing Glyph Designer: you should see a font with shawdows and outline";
}

LabelTTFUnicodeChinese::LabelTTFUnicodeChinese()
{
    auto size = Director::getInstance()->getWinSize();
    // Adding "啊" letter at the end of string to make VS2012 happy, otherwise VS will generate errors  
    // like "Error 3 error C2146: syntax error : missing ')' before identifier 'label'"; 
    TTFConfig ttfConfig("fonts/wt021.ttf",28,GlyphCollection::CUSTOM, "美好的一天啊");
    auto label = Label::createWithTTF(ttfConfig,"美好的一天啊", TextHAlignment::CENTER, size.width);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setPosition(Point(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelTTFUnicodeChinese::title() const
{
    return "New Label + .TTF file Chinese";
}

std::string LabelTTFUnicodeChinese::subtitle() const
{
    return "Testing new Label + TTF with Chinese character";
}

LabelFNTUnicodeChinese::LabelFNTUnicodeChinese()
{
    auto size = Director::getInstance()->getWinSize();
    auto label = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", "中国");
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setPosition(Point(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelFNTUnicodeChinese::title() const
{
    return "New Label + .FNT file Chinese";
}

std::string LabelFNTUnicodeChinese::subtitle() const
{
    return "Testing new Label + FNT with Chinese character";
}


/// BitmapFontMultiLineAlignmentNew

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
#define LineBreaksExample    "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
#define MixedExample         "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

#define ArrowsMax 0.95
#define ArrowsMin 0.7

#define LeftAlign 0
#define CenterAlign 1
#define RightAlign 2

#define LongSentences 0
#define LineBreaks 1
#define Mixed 2

static float alignmentItemPadding  = 50;
static float menuItemPaddingCenter = 50;

LabelFNTMultiLineAlignment::LabelFNTMultiLineAlignment()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // ask director the the window size
    auto size = Director::getInstance()->getWinSize();

    // create and initialize a Label
    this->_labelShouldRetain = Label::createWithBMFont("fonts/markerFelt.fnt", LongSentencesExample, TextHAlignment::CENTER, size.width/1.5);
    this->_labelShouldRetain->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->_labelShouldRetain->retain();

    this->_arrowsBarShouldRetain = Sprite::create("Images/arrowsBar.png");
    this->_arrowsBarShouldRetain->retain();
    this->_arrowsShouldRetain = Sprite::create("Images/arrows.png");
    this->_arrowsShouldRetain->retain();

    MenuItemFont::setFontSize(20);
    auto longSentences = MenuItemFont::create("Long Flowing Sentences", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto lineBreaks    = MenuItemFont::create("Short Sentences With Intentional Line Breaks", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto mixed         = MenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto stringMenu    = Menu::create(longSentences, lineBreaks, mixed, NULL);
    stringMenu->alignItemsVertically();

    longSentences->setColor(Color3B::RED);
    _lastSentenceItem = longSentences;
    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    MenuItemFont::setFontSize(30);

    auto left = MenuItemFont::create("Left", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto center = MenuItemFont::create("Center", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto right = MenuItemFont::create("Right", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto alignmentMenu = Menu::create(left, center, right, NULL);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    center->setColor(Color3B::RED);
    _lastAlignmentItem = center;
    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    this->_labelShouldRetain->setPosition(Point(size.width/2, size.height/2));

    this->_arrowsBarShouldRetain->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    this->_arrowsBarShouldRetain->setScaleX(arrowsWidth / this->_arrowsBarShouldRetain->getContentSize().width);
    this->_arrowsBarShouldRetain->setPosition(Point(((ArrowsMax + ArrowsMin) / 2) * size.width, this->_labelShouldRetain->getPosition().y));

    this->snapArrowsToEdge();

    stringMenu->setPosition(Point(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(Point(size.width/2, menuItemPaddingCenter+15));

    this->addChild(this->_labelShouldRetain);
    this->addChild(this->_arrowsBarShouldRetain);
    this->addChild(this->_arrowsShouldRetain);
    this->addChild(stringMenu);
    this->addChild(alignmentMenu);
}

LabelFNTMultiLineAlignment::~LabelFNTMultiLineAlignment()
{
    this->_labelShouldRetain->release();
    this->_arrowsBarShouldRetain->release();
    this->_arrowsShouldRetain->release();
}

std::string LabelFNTMultiLineAlignment::title() const
{
    return "";
}

std::string LabelFNTMultiLineAlignment::subtitle() const
{
    return "";
}

void LabelFNTMultiLineAlignment::stringChanged(cocos2d::Ref *sender)
{
    auto item = (MenuItemFont*)sender;
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LongSentences:
        this->_labelShouldRetain->setString(LongSentencesExample);
        break;
    case LineBreaks:
        this->_labelShouldRetain->setString(LineBreaksExample);
        break;
    case Mixed:
        this->_labelShouldRetain->setString(MixedExample);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void LabelFNTMultiLineAlignment::alignmentChanged(cocos2d::Ref *sender)
{
    auto item = static_cast<MenuItemFont*>(sender);
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LeftAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::LEFT);
        break;
    case CenterAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::CENTER);
        break;
    case RightAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::RIGHT);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void LabelFNTMultiLineAlignment::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches[0];
    auto location = touch->getLocationInView();

    if (this->_arrowsShouldRetain->getBoundingBox().containsPoint(location))
    {
        _drag = true;
        this->_arrowsBarShouldRetain->setVisible(true);
    }
}

void LabelFNTMultiLineAlignment::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    _drag = false;
    this->snapArrowsToEdge();

    this->_arrowsBarShouldRetain->setVisible(false);
}

void LabelFNTMultiLineAlignment::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (! _drag)
    {
        return;
    }

    auto touch = touches[0];
    auto location = touch->getLocationInView();

    auto winSize = Director::getInstance()->getWinSize();

    this->_arrowsShouldRetain->setPosition(Point(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->_arrowsShouldRetain->getPosition().y));

    float labelWidth = fabs(this->_arrowsShouldRetain->getPosition().x - this->_labelShouldRetain->getPosition().x) * 2;

    this->_labelShouldRetain->setMaxLineWidth(labelWidth);
}

void LabelFNTMultiLineAlignment::snapArrowsToEdge()
{
    this->_arrowsShouldRetain->setPosition(Point(this->_labelShouldRetain->getPosition().x + this->_labelShouldRetain->getContentSize().width/2,
        this->_labelShouldRetain->getPosition().y));
}

/// BMFontUnicodeNew
LabelFNTUNICODELanguages::LabelFNTUNICODELanguages()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
    std::string chinese  = strings["chinese1"].asString();
    std::string russian  = strings["russian"].asString();
    std::string spanish  = strings["spanish"].asString();
    std::string japanese = strings["japanese"].asString();

    auto s = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithBMFont("fonts/arial-unicode-26.fnt", spanish, TextHAlignment::CENTER, 200);
    addChild(label1);
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label1->setPosition(Point(s.width/2, s.height/5*3));
    
    auto label2 = Label::createWithBMFont("fonts/arial-unicode-26.fnt", chinese);
    addChild(label2);
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label2->setPosition(Point(s.width/2, s.height/5*2.5));

    auto label3 = Label::createWithBMFont("fonts/arial-26-en-ru.fnt", russian);
    addChild(label3);
    label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label3->setPosition(Point(s.width/2, s.height/5*2));

    auto label4 = Label::createWithBMFont("fonts/arial-unicode-26.fnt", japanese);
    addChild(label4);
    label4->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label4->setPosition(Point(s.width/2, s.height/5*1.5));
}

std::string LabelFNTUNICODELanguages::title() const
{
    return "New Label + .FNT + UNICODE";
}

std::string LabelFNTUNICODELanguages::subtitle() const
{
    return "You should see 4 differnt labels:\nIn Spanish, Chinese, Russian and Korean";
}

LabelFNTBounds::LabelFNTBounds()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);
    
    // LabelBMFont
    label1 = Label::createWithBMFont("fonts/boundsTestFont.fnt", "Testing Glyph Designer", TextHAlignment::CENTER,s.width);
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelFNTBounds::title() const
{
    return "New Label + .FNT + Bounds";
}

std::string LabelFNTBounds::subtitle() const
{
    return "You should see string enclosed by a box";
}

void LabelFNTBounds::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _renderCmd.init(_globalZOrder);
    _renderCmd.func = CC_CALLBACK_0(LabelFNTBounds::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_renderCmd);
}

void LabelFNTBounds::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
    auto labelSize = label1->getContentSize();
    auto origin    = Director::getInstance()->getWinSize();
    
    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Point vertices[4]=
    {
        Point(origin.width, origin.height),
        Point(labelSize.width + origin.width, origin.height),
        Point(labelSize.width + origin.width, labelSize.height + origin.height),
        Point(origin.width, labelSize.height + origin.height)
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
    
    kmGLPopMatrix();
}

LabelTTFLongLineWrapping::LabelTTFLongLineWrapping()
{
    auto size = Director::getInstance()->getWinSize();

    // Long sentence
    TTFConfig ttfConfig("fonts/arial.ttf", 14);
    auto label1 = Label::createWithTTF(ttfConfig, LongSentencesExample, TextHAlignment::CENTER,size.width);
    label1->setPosition( Point(size.width/2, size.height/2) );
    label1->setAnchorPoint(Point(0.5, 1.0));
    addChild(label1);
}

std::string LabelTTFLongLineWrapping::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFLongLineWrapping::subtitle() const
{
    return "Uses the new Label with TTF. Testing auto-wrapping";
}

LabelTTFLargeText::LabelTTFLargeText()
{
    auto size = Director::getInstance()->getWinSize();

    // Long sentence
    TTFConfig ttfConfig("fonts/wt021.ttf",18,GlyphCollection::DYNAMIC);
    std::string text = FileUtils::getInstance()->getStringFromFile("commonly_used_words.txt");
    auto label = Label::createWithTTF(ttfConfig,text, TextHAlignment::CENTER, size.width);
    label->setPosition( Point(size.width/2, size.height/2) );
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label);
}

std::string LabelTTFLargeText::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFLargeText::subtitle() const
{
    return "Uses the new Label with TTF. Testing large text";
}

LabelTTFColor::LabelTTFColor()
{
    auto size = Director::getInstance()->getWinSize();

    TTFConfig ttfConfig("fonts/arial.ttf", 18);
    // Green
    auto label1 = Label::createWithTTF(ttfConfig,"Green", TextHAlignment::CENTER, size.width);
    label1->setPosition( Point(size.width/2, size.height/5 * 1.5) );
    label1->setColor( Color3B::GREEN );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);

    // Red
    auto label2 = Label::createWithTTF(ttfConfig,"Red", TextHAlignment::CENTER, size.width);
    label2->setPosition( Point(size.width/2, size.height/5 * 2.0) );
    label2->setColor( Color3B::RED );
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label2);

    // Blue
    auto label3 = Label::createWithTTF(ttfConfig,"Blue", TextHAlignment::CENTER, size.width);
    label3->setPosition( Point(size.width/2, size.height/5 * 2.5) );
    label3->setColor( Color3B::BLUE );
    label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label3);
}

std::string LabelTTFColor::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFColor::subtitle() const
{
    return "Uses the new Label with TTF. Testing Color";
}

LabelTTFDynamicAlignment::LabelTTFDynamicAlignment()
{
    auto size = Director::getInstance()->getWinSize();
    TTFConfig ttfConfig("fonts/arial.ttf", 23);
    _label = Label::createWithTTF(ttfConfig,LongSentencesExample, TextHAlignment::CENTER, size.width);
    _label->setPosition( Point(size.width/2, size.height/2) );
    _label->setAnchorPoint(Point::ANCHOR_MIDDLE);  
    
    auto menu = Menu::create(
                              MenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentLeft, this)),
                              MenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentCenter, this)),
                              MenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentRight, this)),
                              NULL);
    
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Point(50, size.height / 4 ));
    
    addChild(_label);
    this->addChild(menu);
}

void  LabelTTFDynamicAlignment::updateAlignment()
{
    if (_label)
    {
        _label->setAlignment(_horizAlign);
    }
}

void LabelTTFDynamicAlignment::setAlignmentLeft(Ref* sender)
{
    _horizAlign = TextHAlignment::LEFT;
    this->updateAlignment();
}

void LabelTTFDynamicAlignment::setAlignmentCenter(Ref* sender)
{
    _horizAlign = TextHAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFDynamicAlignment::setAlignmentRight(Ref* sender)
{
    _horizAlign = TextHAlignment::RIGHT;
    this->updateAlignment();
}

std::string LabelTTFDynamicAlignment::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDynamicAlignment::subtitle() const
{
    return "Uses the new Label with TTF. Testing alignment";
}

//
// NewLabelTTF Chinese/Japanese/Korean wrapping test
//
LabelTTFCJKWrappingTest::LabelTTFCJKWrappingTest()
{
    auto size = Director::getInstance()->getWinSize();
    
    auto drawNode = DrawNode::create();
    drawNode->setAnchorPoint(Point(0, 0));
    this->addChild(drawNode);
    drawNode->drawSegment(
        Point(size.width * 0.1, size.height * 0.8),
        Point(size.width * 0.1, 0), 1, Color4F(1, 0, 0, 1));
    drawNode->drawSegment(
        Point(size.width * 0.85, size.height * 0.8),
        Point(size.width * 0.85, 0), 1, Color4F(1, 0, 0, 1));
    
    TTFConfig ttfConfig("fonts/wt021.ttf", 25, GlyphCollection::DYNAMIC);
    auto label1 = Label::createWithTTF(ttfConfig,
        "你好，Cocos2d-x v3的New Label.", TextHAlignment::LEFT, size.width * 0.75);
    label1->setColor(Color3B(128, 255, 255));
    label1->setPosition(Point(size.width * 0.1, size.height * 0.6));
    label1->setAnchorPoint(Point(0, 0.5));
    this->addChild(label1);
    
    auto label2 = Label::createWithTTF(ttfConfig,
        "早上好，Cocos2d-x v3的New Label.", TextHAlignment::LEFT, size.width * 0.75);
    label2->setColor(Color3B(255, 128, 255));
    label2->setPosition(Point(size.width * 0.1, size.height * 0.4));
    label2->setAnchorPoint(Point(0, 0.5));
    this->addChild(label2);
    auto label3 = Label::createWithTTF(ttfConfig,
        "美好的一天啊美好的一天啊美好的一天啊", TextHAlignment::LEFT, size.width * 0.75);
    label3->setColor(Color3B(255, 255, 128));
    label3->setPosition(Point(size.width * 0.1, size.height * 0.2));
    label3->setAnchorPoint(Point(0, 0.5));
    this->addChild(label3);
}

std::string LabelTTFCJKWrappingTest::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFCJKWrappingTest::subtitle() const
{
    return "New Label with CJK + ASCII characters\n"
        "Characters should stay in the correct position";
}

//
// NewLabelTTF unicode test
//
LabelTTFUnicodeNew::LabelTTFUnicodeNew()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
    std::string chinese  = strings["chinese1"].asString();
    
//    std::string russian  = strings["russian"].asString();
//    std::string spanish  = strings["spanish"].asString();
//    std::string japanese = strings["japanese"].asString();
    
    auto size = Director::getInstance()->getWinSize();
    
    float vStep = size.height/9;
    float vSize = size.height;
     
    TTFConfig ttfConfig("fonts/arial.ttf", 23,GlyphCollection::ASCII);
    // Spanish
    auto label1 = Label::createWithTTF(ttfConfig,"Buen día, ¿cómo te llamas?", TextHAlignment::CENTER, size.width);
    label1->setPosition( Point(size.width/2, vSize - (vStep * 4.5)) );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);
    
    // German
    auto label2 = Label::createWithTTF(ttfConfig,"In welcher Straße haben Sie gelebt?", TextHAlignment::CENTER,size.width);
    label2->setPosition( Point(size.width/2, vSize - (vStep * 5.5)) );
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label2);
    
    // chinese
    ttfConfig.fontFilePath = "fonts/wt021.ttf";
    ttfConfig.glyphs = GlyphCollection::CUSTOM;
    ttfConfig.customGlyphs = chinese.c_str();
    auto label3 = Label::createWithTTF(ttfConfig,chinese, TextHAlignment::CENTER,size.width);
    label3->setPosition( Point(size.width/2, vSize - (vStep * 6.5)) );
    label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label3);
}

std::string LabelTTFUnicodeNew::title() const
{
    return "New Label + TTF unicode";
}

std::string LabelTTFUnicodeNew::subtitle() const
{
    return "Uses the new Label with TTF. Testing unicode";
}

LabelTTFFontsTestNew::LabelTTFFontsTestNew()
{
    const char *ttfpaths[] = {
        "fonts/A Damn Mess.ttf",
        "fonts/Abberancy.ttf",
        "fonts/Abduction.ttf",
        "fonts/American Typewriter.ttf",
        "fonts/Paint Boy.ttf",
        "fonts/Schwarzwald Regular.ttf",
        "fonts/Scissor Cuts.ttf",
    };
#define arraysize(ar)  (sizeof(ar) / sizeof(ar[0]))

    auto size = Director::getInstance()->getWinSize();
    TTFConfig ttfConfig(ttfpaths[0],20, GlyphCollection::NEHE);
    for(size_t i=0;i < arraysize(ttfpaths); ++i) {
        ttfConfig.fontFilePath = ttfpaths[i];
        auto label = Label::createWithTTF(ttfConfig, ttfpaths[i], TextHAlignment::CENTER,0);
        if( label ) {
            
            label->setPosition( Point(size.width/2, ((size.height * 0.6)/arraysize(ttfpaths) * i) + (size.height/5)));
            addChild(label);
            
            label->setAnchorPoint(Point::ANCHOR_MIDDLE);
        } else {
            log("ERROR: Cannot load: %s", ttfpaths[i]);
        }
    }
}

std::string LabelTTFFontsTestNew::title() const
{
    return "New Label + TTF";
}

std::string LabelTTFFontsTestNew::subtitle() const
{
    return "";
}

LabelBMFontTestNew::LabelBMFontTestNew()
{
    auto size = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Hello World, this is testing the new Label using fnt file", TextHAlignment::CENTER, size.width);
    label1->setPosition( Point(size.width/2, size.height/2) );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);
}

std::string LabelBMFontTestNew::title() const
{
    return "New Label + FNT";
}

std::string LabelBMFontTestNew::subtitle() const
{
    return "Uses the new Label with .FNT file";
}

LabelTTFDistanceField::LabelTTFDistanceField()
{
    auto size = Director::getInstance()->getWinSize();
    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    auto label1 = Label::createWithTTF(ttfConfig,"Distance Field",TextHAlignment::CENTER,size.width);
    label1->setPosition( Point(size.width/2, size.height * 0.6f) );
    label1->setColor( Color3B::GREEN );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);

    auto action = Sequence::create(
        DelayTime::create(1.0f),
        ScaleTo::create(6.0f,5.0f,5.0f),
        ScaleTo::create(6.0f,1.0f,1.0f),
        NULL);
    label1->runAction(RepeatForever::create(action));

    auto label2 = Label::createWithTTF(ttfConfig,"Distance Field",TextHAlignment::CENTER,size.width);
    label2->setPosition( Point(size.width/2, size.height * 0.3f) );
    label2->setColor( Color3B::RED );
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label2);

}

std::string LabelTTFDistanceField::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDistanceField::subtitle() const
{
    return "Testing rendering base on DistanceField";
}

LabelOutlineAndGlowTest::LabelOutlineAndGlowTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    auto label1 = Label::createWithTTF(ttfConfig,"Glow", TextHAlignment::CENTER, size.width);
    label1->setPosition( Point(size.width/2, size.height*0.7) );
    label1->setColor( Color3B::GREEN );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label1->enableGlow(Color3B::YELLOW);
    addChild(label1);

    ttfConfig.outlineSize = 1;
    auto label2 = Label::createWithTTF(ttfConfig,"Outline", TextHAlignment::CENTER, size.width);
    label2->setPosition( Point(size.width/2, size.height*0.6) );
    label2->setColor( Color3B::RED );
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label2->enableOutline(Color4B::BLUE);
    addChild(label2);

    ttfConfig.outlineSize = 2;
    auto label3 = Label::createWithTTF(ttfConfig,"Outline", TextHAlignment::CENTER, size.width);
    label3->setPosition( Point(size.width/2, size.height*0.48) );
    label3->setColor( Color3B::RED );
    label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label3->enableOutline(Color4B::BLUE);
    addChild(label3);

    ttfConfig.outlineSize = 3;
    auto label4 = Label::createWithTTF(ttfConfig,"Outline", TextHAlignment::CENTER, size.width);
    label4->setPosition( Point(size.width/2, size.height*0.36) );
    label4->setColor( Color3B::RED );
    label4->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label4->enableOutline(Color4B::BLUE);
    addChild(label4);
}

std::string LabelOutlineAndGlowTest::title() const
{
    return "New Label";
}

std::string LabelOutlineAndGlowTest::subtitle() const
{
    return "Testing outline and glow of label";
}

LabelShadowTest::LabelShadowTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    shadowLabelTTF = Label::createWithTTF(ttfConfig,"TTF:Shadow", TextHAlignment::CENTER, size.width);
    shadowLabelTTF->setPosition( Point(size.width/2, size.height*0.6f) );
    shadowLabelTTF->setColor( Color3B::RED );
    shadowLabelTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
    shadowLabelTTF->enableShadow(Color3B::BLACK);
    addChild(shadowLabelTTF);

    shadowLabelBMFont = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "BMFont:Shadow");
    shadowLabelBMFont->setPosition( Point(size.width/2, size.height*0.4f) );
    shadowLabelBMFont->setColor( Color3B::RED );
    shadowLabelBMFont->setAnchorPoint(Point::ANCHOR_MIDDLE);
    shadowLabelBMFont->enableShadow(Color3B::GREEN);
    addChild(shadowLabelBMFont);

    auto slider = ui::Slider::create();
    slider->setTag(1);
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Point(size.width / 2.0f, size.height * 0.15f + slider->getSize().height * 2.0f));
    slider->setPercent(52);
    slider->addEventListenerSlider(this, sliderpercentchangedselector(LabelShadowTest::sliderEvent));
    addChild(slider);

    auto slider2 = ui::Slider::create();
    slider2->setTag(2);
    slider2->setTouchEnabled(true);
    slider2->loadBarTexture("cocosui/sliderTrack.png");
    slider2->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider2->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider2->setPosition(Point(size.width * 0.15f, size.height / 2.0));
    slider2->setRotation(90);
    slider2->setPercent(52);
    slider2->addEventListenerSlider(this, sliderpercentchangedselector(LabelShadowTest::sliderEvent));
    addChild(slider2);
}

void LabelShadowTest::sliderEvent(Ref *pSender, ui::SliderEventType type)
{
    if (type == SLIDER_PERCENTCHANGED)
    {
        Slider*  slider = (Slider*)this->getChildByTag(1);
        Slider*  slider2 = (Slider*)this->getChildByTag(2);

        auto offset = Size(slider->getPercent()-50,50 - slider2->getPercent());
        shadowLabelTTF->enableShadow(Color3B::BLACK,offset);
        shadowLabelBMFont->enableShadow(Color3B::GREEN,offset);
    }
}

std::string LabelShadowTest::title() const
{
    return "New Label";
}

std::string LabelShadowTest::subtitle() const
{
    return "Testing shadow of label";
}

LabelCharMapTest::LabelCharMapTest()
{
    _time = 0.0f;

    auto label1 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( Point(10,100) );
    label1->setOpacity( 200 );

    auto label2 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( Point(10,200) );
    label2->setOpacity( 32 );

    schedule(schedule_selector(LabelCharMapTest::step)); 
}

void LabelCharMapTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);

    auto label1 = (Label*)getChildByTag(kTagSprite1);
    label1->setString(string);

    auto label2 = (Label*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString(string);
}

std::string LabelCharMapTest::title() const
{
    return "New Label + char map file";
}

std::string LabelCharMapTest::subtitle() const
{
    return "Updating label should be fast.";
}

//------------------------------------------------------------------
//
// LabelCharMapColorTest
//
//------------------------------------------------------------------
LabelCharMapColorTest::LabelCharMapColorTest()
{
    auto label1 = Label::createWithCharMap( "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( Point(10,100) );
    label1->setOpacity( 200 );

    auto label2 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( Point(10,200) );
    label2->setColor( Color3B::RED );

    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto cb = CallFunc::create(CC_CALLBACK_0(LabelCharMapColorTest::actionFinishCallback, this));
    auto seq = Sequence::create(fade, fade_in, cb, NULL);
    auto repeat = RepeatForever::create( seq );
    label2->runAction( repeat );    

    _time = 0;

    schedule( schedule_selector(LabelCharMapColorTest::step) ); //:@selector(step:)];
}

void LabelCharMapColorTest::actionFinishCallback()
{
    CCLOG("Action finished");
}

void LabelCharMapColorTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    auto label1 = (Label*)getChildByTag(kTagSprite1);
    label1->setString(string);

    auto label2 = (Label*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString( string );    
}

std::string LabelCharMapColorTest::title() const
{
    return "New Label + CharMap";
}

std::string LabelCharMapColorTest::subtitle() const
{
    return "Opacity + Color should work at the same time";
}

LabelCrashTest::LabelCrashTest()
{
    auto size = Director::getInstance()->getWinSize();

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    auto label1 = Label::createWithTTF(ttfConfig,"Test崩溃123", TextHAlignment::CENTER, size.width);
    label1->setPosition( Point(size.width/2, size.height/2) );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);
}

std::string LabelCrashTest::title() const
{
    return "New Label Crash Test";
}

std::string LabelCrashTest::subtitle() const
{
    return "Not crash and show [Test123] when using unknown character.";
}

LabelTTFOldNew::LabelTTFOldNew()
{
    auto s = Director::getInstance()->getWinSize();
    float delta = s.height/4;

    auto label1 = LabelTTF::create("Cocos2d-x Label Test", "arial", 24);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label1->setPosition(Point(s.width/2, delta * 2));
    label1->setColor(Color3B::RED);

    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label2 = Label::createWithTTF(ttfConfig, "Cocos2d-x Label Test");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label2->setPosition(Point(s.width/2, delta * 2));
}

void LabelTTFOldNew::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);

    auto label1 = (LabelTTF*)getChildByTag(kTagBitmapAtlas1);
    auto labelSize = label1->getContentSize();
    auto origin    = Director::getInstance()->getWinSize();
    
    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Point vertices[4]=
    {
        Point(origin.width, origin.height),
        Point(labelSize.width + origin.width, origin.height),
        Point(labelSize.width + origin.width, labelSize.height + origin.height),
        Point(origin.width, labelSize.height + origin.height)
    };
    DrawPrimitives::setDrawColor4B(Color4B::RED.r,Color4B::RED.g,Color4B::RED.b,Color4B::RED.a);
    DrawPrimitives::drawPoly(vertices, 4, true);

    auto label2 = (Label*)getChildByTag(kTagBitmapAtlas2);
    labelSize = label2->getContentSize();
    origin    = Director::getInstance()->getWinSize();

    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);

    Point vertices2[4]=
    {
        Point(origin.width, origin.height),
        Point(labelSize.width + origin.width, origin.height),
        Point(labelSize.width + origin.width, labelSize.height + origin.height),
        Point(origin.width, labelSize.height + origin.height)
    };
    DrawPrimitives::setDrawColor4B(Color4B::WHITE.r,Color4B::WHITE.g,Color4B::WHITE.b,Color4B::WHITE.a);
    DrawPrimitives::drawPoly(vertices2, 4, true);
    
    kmGLPopMatrix();
}

void LabelTTFOldNew::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _renderCmd.init(_globalZOrder);
    _renderCmd.func = CC_CALLBACK_0(LabelTTFOldNew::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_renderCmd);
}

std::string LabelTTFOldNew::title() const
{
    return "New / Old TTF";
}

std::string LabelTTFOldNew::subtitle() const
{
    return "Comparison between old(red) and new(white) TTF label";
}

LabelFontNameTest::LabelFontNameTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto label1 = Label::create();
    label1->setString("Default Font");
    label1->setPosition( Point(size.width/2, size.height * 0.7) );
    label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label1);

    FontDefinition fontDef;
    fontDef._fontName = "Marker Felt";
    fontDef._fontSize = 32;
    auto label2 = Label::createWithFontDefinition("Create with FontDefinition",fontDef);
    label2->setPosition( Point(size.width/2, size.height * 0.6) );
    label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label2);

    auto label3 = Label::create("Marker Felt","Marker Felt",32);
    label3->setPosition( Point(size.width/2, size.height * 0.5) );
    label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(label3);
}

std::string LabelFontNameTest::title() const
{
    return "New Label Test";
}

std::string LabelFontNameTest::subtitle() const
{
    return "create label by font name,compatible with old labelTTF";
}

LabelAlignmentTest::LabelAlignmentTest()
{
    auto blockSize = Size(200, 160);
    auto s = Director::getInstance()->getWinSize();

    auto pos = Point((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2);
    auto colorLayer = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
    colorLayer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    colorLayer->setPosition(pos);

    this->addChild(colorLayer);

    MenuItemFont::setFontSize(30);
    auto menu = Menu::create(
        MenuItemFont::create("Left", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentLeft, this)),
        MenuItemFont::create("Center", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentCenter, this)),
        MenuItemFont::create("Right", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentRight, this)),
        NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Point(50, s.height / 2 - 20));
    this->addChild(menu);

    menu = Menu::create(
        MenuItemFont::create("Top", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentTop, this)),
        MenuItemFont::create("Middle", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentMiddle, this)),
        MenuItemFont::create("Bottom", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentBottom, this)),
        NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Point(s.width - 50, s.height / 2 - 20));
    this->addChild(menu);

    _horizAlign = TextHAlignment::LEFT;
    _vertAlign = TextVAlignment::TOP;

    TTFConfig ttfConfig("fonts/arial.ttf", 32);
    _label = Label::create();
    _label->setDimensions(200,160);
    _label->setAlignment(_horizAlign,_vertAlign);
    _label->setTTFConfig(ttfConfig);
    _label->setString(getCurrentAlignment());
    _label->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    _label->setPosition(pos);
    addChild(_label);

}

LabelAlignmentTest::~LabelAlignmentTest()
{
    
}

void LabelAlignmentTest::setAlignmentLeft(Ref* sender)
{
    _horizAlign = TextHAlignment::LEFT;
    _label->setHorizontalAlignment(_horizAlign);
    _label->setString(getCurrentAlignment());
}

void LabelAlignmentTest::setAlignmentCenter(Ref* sender)
{
    _horizAlign = TextHAlignment::CENTER;
    _label->setHorizontalAlignment(_horizAlign);
    _label->setString(getCurrentAlignment()); 
}

void LabelAlignmentTest::setAlignmentRight(Ref* sender)
{
    _horizAlign = TextHAlignment::RIGHT;
    _label->setHorizontalAlignment(_horizAlign);
    _label->setString(getCurrentAlignment());
}

void LabelAlignmentTest::setAlignmentTop(Ref* sender)
{
    _vertAlign = TextVAlignment::TOP;
    _label->setVerticalAlignment(_vertAlign);
    _label->setString(getCurrentAlignment());
}

void LabelAlignmentTest::setAlignmentMiddle(Ref* sender)
{
    _vertAlign = TextVAlignment::CENTER;
    _label->setVerticalAlignment(_vertAlign);
    _label->setString(getCurrentAlignment());
}

void LabelAlignmentTest::setAlignmentBottom(Ref* sender)
{
    _vertAlign = TextVAlignment::BOTTOM;
    _label->setVerticalAlignment(_vertAlign);
    _label->setString(getCurrentAlignment());
}

const char* LabelAlignmentTest::getCurrentAlignment()
{
    const char* vertical = NULL;
    const char* horizontal = NULL;
    switch (_vertAlign) {
    case TextVAlignment::TOP:
        vertical = "Top";
        break;
    case TextVAlignment::CENTER:
        vertical = "Middle";
        break;
    case TextVAlignment::BOTTOM:
        vertical = "Bottom";
        break;
    }
    switch (_horizAlign) {
    case TextHAlignment::LEFT:
        horizontal = "Left";
        break;
    case TextHAlignment::CENTER:
        horizontal = "Center";
        break;
    case TextHAlignment::RIGHT:
        horizontal = "Right";
        break;
    }

    return String::createWithFormat("Alignment %s %s", vertical, horizontal)->getCString();
}

std::string LabelAlignmentTest::title() const
{
    return "Testing New Label";
}

std::string LabelAlignmentTest::subtitle() const
{
    return "Select the buttons on the sides to change alignment";
}

LabelIssue4428Test::LabelIssue4428Test()
{
    auto size = Director::getInstance()->getWinSize();

    auto label = Label::createWithBMFont( "fonts/bitmapFontTest3.fnt", "123\n456");
    label->setPosition(Point(size.width /2.0f, size.height / 2.0f));
    label->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    addChild(label);

    int len = label->getStringLength();
    for (int i = 0; i < len; ++i)
    {
        auto sprite = label->getLetter(i);
        if (sprite != nullptr)
        {
            sprite->setFlippedY(true);
        }
    }
}

std::string LabelIssue4428Test::title() const
{
    return "New Label Bugs Test";
}

std::string LabelIssue4428Test::subtitle() const
{
    return "Reorder issue #4428.The label should be flipped vertically.";
}
