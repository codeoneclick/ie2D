#ifndef IEMAPEDITOR_H
#define IEMAPEDITOR_H

#include <QMainWindow>

#include "ieGameController.h"

namespace Ui {
class ieMapEditor;
}

class ieMapEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ieMapEditor(QWidget *parent = 0);
    ~ieMapEditor();
    
    void execute(void);

private:
    
    Ui::ieMapEditor *ui;
    
    std::shared_ptr<ieGameController> m_gameController;
};

#endif // IEMAPEDITOR_H
