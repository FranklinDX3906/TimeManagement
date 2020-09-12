#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTableWidget>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void CreateNewItem();//新建事项
    void AddNewItem();//将新建的事项添加到表中
    void QuitAdd();//新建时退出
    void DoubleClick(int,int);//删除item
    void TimeUpdate();//时间更新
    void SaveItems();//保存数据
    void LoadItems();//载入数据

private:
    Ui::MainWindow *ui;

    QWidget *CreateNewItemWidget;//创建新事项

    //四个表格
    QTableWidget *TableUpLeft;//左上表格
    QTableWidget *TableUpRight;//右上表格
    QTableWidget *TableDownLeft;//左下表格
    QTableWidget *TableDownRight;//右下表格

    QLineEdit *NewItem;//新事项的编辑框
    QButtonGroup *ItemFeature;//事项的紧急程度

    QLabel *TimeLabel;//显示时间
};
#endif // MAINWINDOW_H
