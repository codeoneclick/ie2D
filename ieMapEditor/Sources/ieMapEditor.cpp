#include "ieMapEditor.h"
#include "ui_ieMapEditor.h"

#include "ieIOGLWindow.h"
#include "ieIGameTransition.h"
#include "ieMovieClip.h"

#if defined(__OSX__)

#include <Cocoa/Cocoa.h>

#endif

ieMapEditor::ieMapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ieMapEditor)
{
    ui->setupUi(this);
}

ieMapEditor::~ieMapEditor()
{
    delete ui;
}


void ieMapEditor::execute(void)
{
#if defined(__OSX__) || defined(__WIN32__)
    
    NSView *hwnd = reinterpret_cast<NSView *>(ui->oglWindow->winId());
    
    m_gameController = std::make_shared<ieGameController>();
    std::shared_ptr<ieIOGLWindow> window = std::make_shared<ieIOGLWindow>((__bridge void*)hwnd);
    std::shared_ptr<ieIGameTransition> transition = std::make_shared<ieIGameTransition>("demo", window);
    
    m_gameController->registerTransition(transition);
    m_gameController->goToTransition("demo");
    
    std::shared_ptr<ieMovieClip> sprite;
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    path.append("dragon.json");
    sprite = std::make_shared<ieMovieClip>(glm::vec4(250, 250, 100, 100), path);
    transition->addChild(sprite);
    sprite->setPosition(glm::vec2(250, 250));
    sprite->setScale(glm::vec2(0.5f, 0.5f));
    sprite->setBatched(true);
    
#endif
}