#ifndef SRC_QT_DIALOG_H_
#define SRC_QT_DIALOG_H_

#include <QDialog>
#include <QString>
#include <QPoint>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#define grid_accuracy_f "%.2f"
#define grid_accuracy_e "%.1e"

typedef struct graphi {
    double width = 0;
    double height = 0;
    double x_min = 0;
    double x_max = 0;
    double scale = 100;
    double res_0 = 0;
    char request[257];
} graphic;

extern "C" {
    #include "../banklib/credit.h"
    #include "../banklib/deposit.h"
    #include "../calclib/calc.h"
 }

#include "ui_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog {
    Q_OBJECT

 public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

 private slots:

    void click_btn_result();
    void click_btns();
    void click_btn_graph();
    void click_btn_clean();
    void click_btn_clean_all();
    void grip_render(QGraphicsScene *scence, graphic neww);
    graphic graph_info(int *error);

    void click_btn_clean_credit();
    void click_credit_result();
    void click_deposite_result();
    void click_btn_clean_deposite();

 private:
    Ui::Dialog *ui;
    QString str;
    int num_of_grid;
};

#endif  // SRC_QT_DIALOG_H_
