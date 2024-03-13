#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
class LogWidget:public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = nullptr);

    void loadQss();

    void initControl();

    void initConnect();

    void updateTable();
private:
    QHBoxLayout *totaLayout,*rightDownLayout;
    QVBoxLayout *rightLayout;
    QWidget *rightView,*rightDownView;
    QPushButton *leftBtn,*rightBtn;
    QListWidget *logListWidget;
    QTableWidget *logTable;
    QTableWidgetItem *tabitem;         // 表格单元格
    int count,pageNum;
public slots:
    void leftPage();
    void rightPage();
};

#endif // LOGWIDGET_H
