#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("TimeManagement四象限时间管理");//设置标题
    //this->adjustSize();
    //QFont font("ZYSong18030" , 12);
    //this->setFont(font);
    //this->showMaximized();//最大化窗口
    //QSplitter *
    QSplitter *splitterMain = new QSplitter(Qt::Vertical, this); //新建分割主窗口，水平分割
    splitterMain->setGeometry(0,40,this->width(),this->geometry().height()-40);
    //splitterMain->setStretchFactor(1,0);//控件伸缩

    //分割窗口
    QSplitter *splitterUp = new QSplitter(Qt::Horizontal,splitterMain);
    QSplitter *splitterDown = new QSplitter(Qt::Horizontal,splitterMain);
    //qDebug()<<this->geometry().height()<<this->frameGeometry().height()-this->geometry().height();
    //QSplitter *splitterUpRight = new QSplitter(Qt::Vertical,this);//上窗口右
    //QSplitter *splitterDownRight = new QSplitter(Qt::Vertical,splitterDown);//下窗口右

    //每个窗口做一个表格
    TableUpLeft = new QTableWidget(splitterUp);
    TableUpLeft->setColumnCount(1);//两栏
    TableUpLeft->setColumnWidth(0,this->width()/2);//宽度为窗口宽度一半
    TableUpLeft->setObjectName("1");//设置名字
    connect(TableUpLeft,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(DoubleClick(int,int)));
    //TableUpLeft->setRowCount(5);
    //TableUpLeft->setColumnWidth(0,5);//第一栏宽度5
    TableUpLeft->setHorizontalHeaderLabels({"很重要-很紧急"});//设置栏标题

    TableUpRight = new QTableWidget(splitterUp);
    TableUpRight->setColumnCount(1);
    TableUpRight->setColumnWidth(0,this->width()/2);
    TableUpRight->setObjectName("2");
    connect(TableUpRight,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(DoubleClick(int,int)));
    //TableUpRight->setColumnWidth(0,5);
    TableUpRight->setHorizontalHeaderLabels({"很重要-不紧急"});

    TableDownLeft = new QTableWidget(splitterDown);
    TableDownLeft->setColumnCount(1);
    TableDownLeft->setColumnWidth(0,this->width()/2);
    TableDownLeft->setObjectName("3");
    connect(TableDownLeft,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(DoubleClick(int,int)));
    //TableDownLeft->setColumnWidth(0,5);
    TableDownLeft->setHorizontalHeaderLabels({"不重要-很紧急"});

    TableDownRight = new QTableWidget(splitterDown);
    TableDownRight->setColumnCount(1);
    TableDownRight->setColumnWidth(0,this->width()/2);
    TableDownRight->setObjectName("4");
    connect(TableDownRight,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(DoubleClick(int,int)));
    //TableDownRight->setColumnWidth(0,5);
    TableDownRight->setHorizontalHeaderLabels({"不重要-不紧急"});

    //创建新建事项的按钮
    QPushButton *CreateNewButton = new QPushButton("新建",this);
    CreateNewButton->adjustSize();
    CreateNewButton->setGeometry(this->width()-CreateNewButton->width()-5,20-CreateNewButton->height()/2,CreateNewButton->width(),CreateNewButton->height());
    connect(CreateNewButton,SIGNAL(clicked(bool)),this,SLOT(CreateNewItem()));
    //this->show();

    //保存功能
    QPushButton *SaveItemsButton = new QPushButton("保存",this);
    SaveItemsButton->adjustSize();
    SaveItemsButton->setGeometry(this->width()-5-5-CreateNewButton->width()*2,20-SaveItemsButton->height()/2,SaveItemsButton->width(),SaveItemsButton->height());
    connect(SaveItemsButton,SIGNAL(clicked(bool)),this,SLOT(SaveItems()));//

    //导入数据功能
    QPushButton *LoadItemButton = new QPushButton("导入",this);
    LoadItemButton->adjustSize();
    LoadItemButton->setGeometry(this->width()-15-CreateNewButton->width()*3,20-LoadItemButton->height()/2,LoadItemButton->width(),LoadItemButton->height());
    connect(LoadItemButton,SIGNAL(clicked(bool)),this,SLOT(LoadItems()));

    //显示时间
    TimeLabel = new QLabel(this);
    TimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
    TimeLabel->adjustSize();
    TimeLabel->setGeometry(5,20-TimeLabel->height()/2,TimeLabel->width(),TimeLabel->height());
    QTimer *Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(TimeUpdate()));
    Timer->start(1000);

    //提示双击删除事项
    QLabel *DeleteTip = new QLabel(this);
    DeleteTip->setText("双击事项删除");
    DeleteTip->adjustSize();
    DeleteTip->setGeometry((this->width()/2)-DeleteTip->width()/2,20-DeleteTip->height()/2,DeleteTip->width(),DeleteTip->height());
}

void MainWindow::CreateNewItem()
{
    //新建事项的窗口
    CreateNewItemWidget = new QWidget();
    CreateNewItemWidget->setWindowTitle("新建事项");
    CreateNewItemWidget->resize(CreateNewItemWidget->width(),CreateNewItemWidget->height()/2);

    //图层
    QVBoxLayout *VBoxLayout = new QVBoxLayout;
    CreateNewItemWidget->setLayout(VBoxLayout);

    //单选组
    QRadioButton *VV = new QRadioButton();//很重要很紧急
    VV->setText("很重要，很紧急");
    QRadioButton *NV = new QRadioButton();
    NV->setText("不重要，很紧急");
    QRadioButton *VN = new QRadioButton();
    VN->setText("很重要，不紧急");
    QRadioButton *NN = new QRadioButton();
    NN->setText("不重要，不紧急");
    ItemFeature = new QButtonGroup(CreateNewItemWidget);//按钮组
    ItemFeature->addButton(VV,1);
    ItemFeature->addButton(VN,2);
    ItemFeature->addButton(NV,3);
    ItemFeature->addButton(NN,4);
    VBoxLayout->addWidget(VV);
    VBoxLayout->addWidget(VN);
    VBoxLayout->addWidget(NV);
    VBoxLayout->addWidget(NN);

    //可编辑文本框
    QLabel *ItemTip = new QLabel(CreateNewItemWidget);//标签
    ItemTip->setText("事项名称");
    ItemTip->adjustSize();
    ItemTip->setGeometry(CreateNewItemWidget->width()/3,(CreateNewItemWidget->height()/2)-80,ItemTip->width(),ItemTip->height());
    NewItem = new QLineEdit(CreateNewItemWidget);//可编辑文本框
    NewItem->setGeometry(CreateNewItemWidget->width()/3,(CreateNewItemWidget->height()/2)-40,ItemTip->width()*6,ItemTip->height()*2);

    //确定和取消按钮
    QPushButton *AddButton = new QPushButton(CreateNewItemWidget);
    AddButton->setText("添加");
    AddButton->adjustSize();
    AddButton->setGeometry(CreateNewItemWidget->width()/3,CreateNewItemWidget->height()/2+40,AddButton->width(),AddButton->height());
    //AddButton->setObjectName(QString::number(ItemFeature->chec)));
    connect(AddButton,SIGNAL(clicked(bool)),this,SLOT(AddNewItem()));

    QPushButton *QuitButton = new QPushButton(CreateNewItemWidget);
    QuitButton->setText("取消");
    QuitButton->adjustSize();
    QuitButton->setGeometry(CreateNewItemWidget->width()/3+NewItem->width()-QuitButton->width(),CreateNewItemWidget->height()/2+40,AddButton->width(),AddButton->height());
    connect(QuitButton,SIGNAL(clicked(bool)),this,SLOT(QuitAdd()));

    CreateNewItemWidget->show();
}

void MainWindow::AddNewItem()
{
    //QObject *Sender = QObject::sender();
    //QPushButton *CastButton = qobject_cast<QPushButton *>(Sender);
    QString FeatureID;
    FeatureID.clear();
    FeatureID = QString::number(ItemFeature->checkedId());

    //排除未输入的情况
    //提示小窗口
    QWidget *Tip = new QWidget();
    QVBoxLayout *TipLayout = new QVBoxLayout();
    QLabel *TipText = new QLabel();
    TipText->setText("请输入事项名称并选择事项属性！");
    TipText->adjustSize();
    Tip->setLayout(TipLayout);
    TipLayout->addWidget(TipText);

    if(NewItem->text()!="")
    {
        QTableWidgetItem *New = new QTableWidgetItem(NewItem->text());
        switch (FeatureID.toInt())
        {
        case 1:
            TableUpLeft->setRowCount(TableUpLeft->rowCount()+1);//行数+1
            TableUpLeft->setItem(TableUpLeft->rowCount()-1,0,New);
            CreateNewItemWidget->close();
            delete CreateNewItemWidget;
            return;
        case 2:
            TableUpRight->setRowCount(TableUpRight->rowCount()+1);
            TableUpRight->setItem(TableUpRight->rowCount()-1,0,New);
            CreateNewItemWidget->close();
            delete CreateNewItemWidget;
            return;
        case 3:
            TableDownLeft->setRowCount(TableDownLeft->rowCount()+1);
            TableDownLeft->setItem(TableDownLeft->rowCount()-1,0,New);
            CreateNewItemWidget->close();
            delete CreateNewItemWidget;
            return;
        case 4:
            TableDownRight->setRowCount(TableDownRight->rowCount()+1);
            TableDownRight->setItem(TableDownRight->rowCount()-1,0,New);
            CreateNewItemWidget->close();
            delete CreateNewItemWidget;
            return;
        default:
            Tip->show();
            return;
        }
    }
    else
    {
        Tip->show();
        return;
    }
    //qDebug()<<NewItem->text();
    //QTableWidgetItem *New = new QTableWidgetItem(NewItem->text());
    //TableUpLeft->setItem(0,0,New);
    //TableUpLeft->show();

}

void MainWindow::QuitAdd()
{
    CreateNewItemWidget->close();
    delete CreateNewItemWidget;
}

void MainWindow::DoubleClick(int row,int column)
{
    QObject *Sender = QObject::sender();//信号发送者
    QTableWidget *CastTable = qobject_cast<QTableWidget *>(Sender);//投影
    switch (CastTable->objectName().toInt())
    {
    case 1:
        TableUpLeft->removeRow(row);
        return;
    case 3:
        TableDownLeft->removeRow(row);
        return;
    case 2:
        TableUpRight->removeRow(row);
        return;
    case 4:
        TableDownRight->removeRow(row);
        return;
    default:
        return;
    }

}

void MainWindow::TimeUpdate()
{
    TimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void MainWindow::SaveItems()
{
    QString path = "./Data.xml";
    QFile DataFile(path);
    if(DataFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        //创建实例
        QXmlStreamWriter stream(&DataFile);
        stream.setAutoFormatting(true);//自动排版

        stream.writeStartDocument();

        stream.writeStartElement("Root");//根节点

        //stream.writeAttribute("Feature","很重要，很紧急");
        stream.writeStartElement("Table");
        stream.writeAttribute("Feature","很重要，很紧急");
        for(int i = 0;i<TableUpLeft->rowCount();i++)
        {
            stream.writeTextElement("Item",TableUpLeft->item(i,0)->text());//逐条写入
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();

        stream.writeStartElement("Table");
        stream.writeAttribute("Feature","很重要，不紧急");
        for(int i = 0;i<TableUpRight->rowCount();i++)
        {
            stream.writeTextElement("Item",TableUpRight->item(i,0)->text());//逐条写入
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();

        stream.writeStartElement("Table");
        stream.writeAttribute("Feature","不重要，很紧急");
        for(int i = 0;i<TableDownLeft->rowCount();i++)
        {
            stream.writeTextElement("Item",TableDownLeft->item(i,0)->text());//逐条写入
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();

        stream.writeStartElement("Table");
        stream.writeAttribute("Feature","不重要，不紧急");
        for(int i = 0;i<TableDownRight->rowCount();i++)
        {
            stream.writeTextElement("Item",TableDownRight->item(i,0)->text());//逐条写入
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();

        stream.writeEndElement();
/*
        stream.writeStartElement("Root");
        stream.writeAttribute("Feature","很重要，不紧急");
        for(int i = 0;i<TableUpRight->rowCount();i++)
        {
            stream.writeTextElement("Item",TableUpRight->item(i,0)->text());
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();

        stream.writeStartElement("Root");
        stream.writeAttribute("Feature","不重要，很紧急");
        for(int i = 0;i<TableDownLeft->rowCount();i++)
        {
            stream.writeTextElement("Item",TableDownLeft->item(i,0)->text());
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();

        stream.writeStartElement("Root");
        stream.writeAttribute("Feature","不重要，不紧急");
        for(int i = 0;i<TableDownRight->rowCount();i++)
        {
            stream.writeTextElement("Item",TableDownRight->item(i,0)->text());
        }
        //stream.writeTextElement("title","22");
        stream.writeEndElement();
*/
        stream.writeEndDocument();
    }
    DataFile.close();

    QWidget *Tip = new QWidget();
    Tip->setWindowTitle("提示");
    QVBoxLayout *Layout = new QVBoxLayout;
    QLabel *TipText = new QLabel(Tip);
    TipText->setText("保存成功！");
    TipText->adjustSize();
    Layout->addWidget(TipText);
    Tip->setLayout(Layout);
    Tip->adjustSize();
    Tip->show();
}

void MainWindow::LoadItems()
{
    //先把四个表格全部清空
    //TableUpLeft->clear();
    TableUpLeft->setRowCount(0);
    //TableUpRight->clear();
    TableUpRight->setRowCount(0);
    //TableDownLeft->clear();
    TableDownLeft->setRowCount(0);
    //TableDownRight->clear();
    TableDownRight->setRowCount(0);

    //设置路径
    QString path = "./Data.xml";
    QFile DataFile(path);
    if(DataFile.exists())//文件存在
    {
        if(DataFile.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QXmlStreamReader stream(&DataFile);//创建实例
            while (!stream.atEnd()) //当不在末尾
            {
                if(stream.isStartElement())//起始元素
                {
                    if(stream.attributes().value("Feature") == "很重要，很紧急")
                    {
                        while(!stream.isEndElement())
                        {
                            stream.readNext();
                            if(stream.name() == "Item")
                            {
                                stream.readNext();
                                QTableWidgetItem *Item = new QTableWidgetItem(stream.text().toString());
                                TableUpLeft->setRowCount(TableUpLeft->rowCount()+1);
                                TableUpLeft->setItem(TableUpLeft->rowCount()-1,0,Item);
                                stream.readNext();
                                stream.readNext();//连读两次以免写入换行符
                            }
                        }
                    }
                    else if (stream.attributes().value("Feature") == "很重要，不紧急")
                    {
                        while(!stream.isEndElement())
                        {
                            stream.readNext();
                            if(stream.name() == "Item")
                            {
                                stream.readNext();
                                QTableWidgetItem *Item = new QTableWidgetItem(stream.text().toString());
                                TableUpRight->setRowCount(TableUpRight->rowCount()+1);
                                TableUpRight->setItem(TableUpRight->rowCount()-1,0,Item);
                                stream.readNext();
                                stream.readNext();//连读两次以免写入换行符
                            }
                        }
                    }
                    else if(stream.attributes().value("Feature") == "不重要，很紧急")
                    {
                        while(!stream.isEndElement())
                        {
                            stream.readNext();
                            if(stream.name() == "Item")
                            {
                                stream.readNext();
                                QTableWidgetItem *Item = new QTableWidgetItem(stream.text().toString());
                                TableDownLeft->setRowCount(TableDownLeft->rowCount()+1);
                                TableDownLeft->setItem(TableDownLeft->rowCount()-1,0,Item);
                                stream.readNext();
                                stream.readNext();//连读两次以免写入换行符
                            }
                        }
                    }
                    else if (stream.attributes().value("Feature") == "不重要，不紧急")
                    {
                        while(!stream.isEndElement())
                        {
                            stream.readNext();
                            if(stream.name() == "Item")
                            {
                                stream.readNext();
                                QTableWidgetItem *Item = new QTableWidgetItem(stream.text().toString());
                                TableDownRight->setRowCount(TableDownRight->rowCount()+1);
                                TableDownRight->setItem(TableDownRight->rowCount()-1,0,Item);
                                stream.readNext();
                                stream.readNext();//连读两次以免写入换行符
                            }
                        }
                    }
                }
                //qDebug()<<stream.text().toString()<<stream.name();
                stream.readNext();
            }
            /*
            while(!stream.atEnd())//未到末尾
            {
                stream.readNext();
                //stream.readNext();//阅读下一个
                if(stream.name()=="Item")//在根节点
                {
                    QString ItemText;
                    stream.readNext();
                    ItemText = stream.text().toString();
                    qDebug()<<ItemText;
                    if(stream.text()!="\n")
                    {
                        QTableWidgetItem *Item = new QTableWidgetItem(ItemText);
                        TableUpLeft->setRowCount(TableUpLeft->rowCount()+1);
                        TableUpLeft->setItem(TableUpLeft->rowCount()-1,0,Item);
                    }
                }
                //if(stream.is)
            }
            //2
            //stream.readNext();
            qDebug()<<stream.name();
            stream.readNext();
            qDebug()<<stream.name();
            stream.readNext();
            qDebug()<<stream.name();
            while(!stream.atEnd())//未到末尾
            {
                stream.readNext();
                qDebug()<<stream.name();
                //stream.readNext();//阅读下一个
                if(stream.name()=="Item")//在根节点
                {
                    QString ItemText;
                    stream.readNext();
                    ItemText = stream.text().toString();
                    if(stream.text()!="\n")
                    {
                        QTableWidgetItem *Item = new QTableWidgetItem(ItemText);
                        TableUpRight->setRowCount(TableUpRight->rowCount()+1);
                        TableUpRight->setItem(TableUpRight->rowCount()-1,0,Item);
                    }
                }
            }
            //3
            stream.readNext();
            //stream.readNext();
            while(!stream.atEnd())//未到末尾
            {
                stream.readNext();
                //stream.readNext();//阅读下一个
                if(stream.name()=="Item")//在根节点
                {
                    QString ItemText;
                    stream.readNext();
                    ItemText = stream.text().toString();
                    if(stream.text()!="\n")
                    {
                        QTableWidgetItem *Item = new QTableWidgetItem(ItemText);
                        TableDownLeft->setRowCount(TableDownLeft->rowCount()+1);
                        TableDownLeft->setItem(TableDownLeft->rowCount()-1,0,Item);
                    }
                }
            }
            //4
            stream.readNext();
            //stream.readNext();
            while(!stream.atEnd())//未到末尾
            {
                stream.readNext();
                //stream.readNext();//阅读下一个
                if(stream.name()=="Item")//在根节点
                {
                    QString ItemText;
                    stream.readNext();
                    ItemText = stream.text().toString();
                    if(stream.text()!="\n")
                    {
                        QTableWidgetItem *Item = new QTableWidgetItem(ItemText);
                        TableDownRight->setRowCount(TableDownRight->rowCount()+1);
                        TableDownRight->setItem(TableDownRight->rowCount()-1,0,Item);
                    }
                }
            }
            */
        }
    }
    else
    {
        QWidget *Tip = new QWidget();
        Tip->setWindowTitle("提示");
        QVBoxLayout *Layout = new QVBoxLayout;
        QLabel *TipText = new QLabel(Tip);
        TipText->setText("未找到文件");
        TipText->adjustSize();
        Layout->addWidget(TipText);
        Tip->setLayout(Layout);
        Tip->adjustSize();
        Tip->show();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

