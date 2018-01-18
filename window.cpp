#include "window.h"

#include <QtWidgets>
#include <QGridLayout>

const int IdRole = Qt::UserRole;
static QLabel* statusLabel;

Window::Window()
{
    //startButton = new PushButton(tr("start"));
    renderArea = new RenderArea;
    QGridLayout *mainLayout = new QGridLayout;
    resize(620,620);
    mainLayout->addWidget(renderArea, 0, 0, 500, 500);
    setLayout(mainLayout);
    setWindowTitle(tr("IK"));

}
