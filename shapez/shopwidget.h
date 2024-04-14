#ifndef SHOPWIDGET_H
#define SHOPWIDGET_H

#include <QWidget>
#include <QPushButton>

#define comidity_width 320
#define comidity_height 95
#define comidity_fontsize 12

class ShopWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *comidity1, *comidity2, *comidity3, *comidity4;
public:
    explicit ShopWidget(QWidget *parent = 0);

signals:

public slots:
    void function1();
    void function2();
    void function3();
    void function4();
};

#endif // SHOPWIDGET_H
