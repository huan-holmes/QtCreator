#include "operationwidget.h"
OperationWidget::OperationWidget(QWidget *parent):
    QWidget(parent)
{
    this->setGeometry(300, 30, 1200, 1000);
    this->setStyleSheet("background-color:#1E1E1E;");
    MainVLayout = new QVBoxLayout(this);

    MVLFirstWidget = new QWidget(this);
    MVLSecondWidget = new QWidget(this);
    MVLThirdWidget = new QWidget(this);
    MVLFourthWidget = new QWidget(this);
    MainVLayout->addWidget(MVLFirstWidget);
    MainVLayout->addWidget(MVLSecondWidget);
    MainVLayout->addWidget(MVLThirdWidget);
    MainVLayout->addWidget(MVLFourthWidget);
    MVLFirstWidget->setGeometry(0, 0, width(), 30);
    MVLFirstWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF;max-height: 30px;");
    MVLSecondWidget->setGeometry(0, MVLFirstWidget->height(), width(), 60);
    MVLSecondWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF;max-height: 60px");
    MVLThirdWidget->setGeometry(0, MVLFirstWidget->height() + MVLSecondWidget->height(), width(), height() - MVLFirstWidget->height() - MVLFirstWidget->height() -30);
    MVLThirdWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF;border:1px solid gray;");
    MVLFourthWidget->setGeometry(0, MVLFirstWidget->height() + MVLSecondWidget->height() + MVLThirdWidget->height(), width(), 30);
    MVLFourthWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF;max-height: 30px;border:1px solid gray;");
    this->setLayout(MainVLayout);
    FirstToolBar = new QToolBar(tr("工具栏1"), MVLFirstWidget);
    FirstToolBar->setStyleSheet("border:1px solid gray;");
    FirstToolBar->setGeometry(0, 0, MVLFirstWidget->width(), MVLFirstWidget->height());
    SecondToolBar = new QToolBar(tr("工具栏2"), MVLSecondWidget);
    SecondToolBar->setStyleSheet("border:1px solid gray;");
    SecondToolBar->setGeometry(0, 0, MVLSecondWidget->width(), MVLSecondWidget->height());
    InitToolBarAction();
}
void OperationWidget::InitToolBarAction()
{

    MapBagToolButton = new QToolButton(this);
    MapBagToolButton->setText("地图包");
    MapBagToolButton->setCheckable(true);
    LoaclCopyAction = new QAction((tr("&新建地图")), MVLSecondWidget);
    LoaclCopyAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/localbeifen.png"));
    ServerCopyAction = new QAction((tr("&增量构建")), MVLSecondWidget);
    ServerCopyAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/fuwuqibeifen.png"));
    FirstToolBar->addWidget(MapBagToolButton);
    connect(MapBagToolButton, SIGNAL(clicked()), this, SLOT(onMapBagClicked()));
}
void OperationWidget::onMapBagClicked()
{
    qDebug()<<"----onMapBagClicked()----";
    SecondToolBar->clear();

    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    SecondToolBar->addAction(LoaclCopyAction);
    SecondToolBar->addAction(ServerCopyAction);



}
